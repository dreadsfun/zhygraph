#pragma once
#include <thread>
#include <condition_variable>
#include <queue>
#include <functional>
#include <stack>
#include <atomic>
#include <memory>
#include <list>
namespace zhygraph {
	namespace core {
		using namespace std;

		template< typename T >
		class job_handle {
		private:
			std::mutex m_wait;
			std::condition_variable m_cv;
			std::atomic_bool m_job_ready { false };

			T m_result;

		public:
			void wait( void ) {
				while( !m_job_ready ) {
					std::unique_lock< std::mutex > lck( m_wait );
					m_cv.wait( lck );
				}
			}

			void notify_ready( void ) {
				{
					std::lock_guard< std::mutex > lck( m_wait );
					m_job_ready.exchange( true );
				}
				m_cv.notify_all();
			}

			const std::atomic_bool& is_ready( void ) const {
				return m_job_ready;
			}

			void set_result( const T& r ) {
				m_result = r;
			}

			T get_result( void ) const {
				return m_result;
			}
		};

		template< typename T >
		using job_handle_ptr = std::shared_ptr< job_handle< T > >;

		template<>
		class job_handle< void > {
		private:
			std::mutex m_wait;
			std::condition_variable m_cv;
			std::atomic_bool m_job_ready { false };

		public:
			void wait( void ) {
				while( !m_job_ready ) {
					std::unique_lock< std::mutex > lck( m_wait );
					m_cv.wait( lck );
				}
			}

			void notify_ready( void ) {
				{
					std::lock_guard< std::mutex > lck( m_wait );
					m_job_ready.exchange( true );
				}
				m_cv.notify_all();
			}

			const std::atomic_bool& is_ready( void ) const {
				return m_job_ready;
			}
		};

		class multi_thread {
		private:
			std::thread* m_worker { nullptr };
			std::condition_variable m_cv;
			std::queue< std::function< void( void ) > > m_jobs;
			std::mutex m_que_mut;
			std::mutex m_err_mut;
			std::stack< std::string > m_errors;
			std::atomic_bool m_work_time { true };

		public:
			multi_thread( void );
			~multi_thread( void );
			multi_thread( const multi_thread& ) = delete;
			multi_thread& operator = ( const multi_thread& ) = delete;
			std::string pop_last_error( void );

			template< typename F, typename ... A >
			job_handle_ptr< typename std::result_of< F( A ... ) >::type > push_job( F&& j, const A& ... args ) {
				using Rof = typename std::result_of< F( A ... ) >::type;
				job_handle_ptr< Rof > jh = std::make_shared< job_handle< Rof > >();
				{
					std::lock_guard< std::mutex > lck( m_que_mut );
					m_jobs.emplace(
						[ jh, &j, args ... ]() {
						jh->set_result( j( args ... ) );
						jh->notify_ready();
					}
					);
				}
				m_cv.notify_one();
				return jh;
			}

			template< typename F, typename ... A >
			job_handle_ptr< void > push_no_result_job( F&& j, const A& ... args ) {
				job_handle_ptr< void > jh = std::make_shared< job_handle< void > >();
				{
					std::lock_guard< std::mutex > lck( m_que_mut );
					m_jobs.emplace(
						[ jh, &j, args ... ]() {
						j( args ... );
						jh->notify_ready();
					}
					);
				}
				m_cv.notify_one();
				return jh;
			}

			size_t queue_size() {
				lock_guard<mutex> g( m_que_mut );
				return m_jobs.size();
			}

			bool operator == ( const multi_thread& o ) const {
				return m_worker->get_id() == o.m_worker->get_id();
			}

		private:
			void _init( void );
		};

		class multi_thread_distributor {
		private:
			list<multi_thread> mthreads;

		public:
			uint32_t thread_count(uint32_t n);
			multi_thread* least_job_thread();
			multi_thread* most_job_thread();
			multi_thread* idle_thread();
		};
	}
}