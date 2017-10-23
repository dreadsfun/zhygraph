#include "multi_thread.h"
namespace zhygraph {
	namespace core {
		multi_thread::multi_thread( void ) {
			_init();
		}

		multi_thread::~multi_thread( void ) {
			m_work_time = false;
			m_cv.notify_one();
			m_worker->join();
			delete m_worker;
		}

		std::string multi_thread::pop_last_error( void ) {
			std::string r;
			std::lock_guard< std::mutex > lck( m_err_mut );
			if( !m_errors.empty() ) {
				r = m_errors.top();
				m_errors.pop();
			}
			return r;
		}

		void multi_thread::_init( void ) {
			m_worker = new std::thread(
				[ this ]() {
				while( m_work_time ) {
					std::unique_lock< std::mutex > lck( m_que_mut );
					m_cv.wait( lck );
					while( !m_jobs.empty() ) {
						try {
							m_jobs.front()( );
						} catch( const std::exception& e ) {
							std::lock_guard< std::mutex > lck( m_err_mut );
							m_errors.emplace( e.what() );
						} catch( ... ) {
						}
						m_jobs.pop();
					}
				}
			}
			);
		}

		uint32_t multi_thread_distributor::thread_count( uint32_t n ) {
			uint32_t diff = 0;
			while( n > mthreads.size() ) {
				mthreads.emplace_back();
				++diff;
			}

			while( n < mthreads.size() ) {
				multi_thread* c = nullptr;
				while( c = idle_thread() ) {
					mthreads.remove( *c );
					++diff;
				}
				mthreads.pop_back();
				++diff;
			}
			
			return diff;
		}

		multi_thread* multi_thread_distributor::least_job_thread() {
			uint32_t cmin = 0;
			multi_thread* r = nullptr;
			for( multi_thread& t : mthreads ) {
				if( t.queue_size() == 0 ) {
					return &t;
				} else {
					uint32_t tq = t.queue_size();
					if( tq < cmin ) {
						cmin = tq;
						r = &t;
					}
				}
			}
			return r;
		}

		multi_thread* multi_thread_distributor::most_job_thread() {
			uint32_t cmax = 0;
			multi_thread* r = nullptr;
			for( multi_thread& t : mthreads ) {
				uint32_t tq = t.queue_size();
				if( tq > cmax ) {
					cmax = tq;
					r = &t;
				}
			}
			return r;
		}

		multi_thread* multi_thread_distributor::idle_thread() {
			for( multi_thread& t : mthreads ) {
				if( t.queue_size() == 0 ) {
					return &t;
				}
			}
			return nullptr;
		}
	}
}