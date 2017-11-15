#include "multi_thread.hpp"

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

//void job_handle::wait( void ) {
//	while( !m_job_ready ) {
//		std::unique_lock< std::mutex > lck( m_wait );
//		m_cv.wait( lck );
//	}
//}
////
////void job_handle::wait_for() {
////	std::unique_lock< std::mutex > lck( m_wait );
////	m_cv.wait_for( lck, );
////}
////
////void job_handle::wait_until() {
////}
//
//void job_handle::notify_ready( void ) { 
//	{
//		std::lock_guard< std::mutex > lck( m_wait );
//		m_job_ready.exchange( true );
//	}
//	m_cv.notify_all();
//}
//
//const std::atomic_bool & job_handle::is_ready( void ) const {
//	return m_job_ready;
//}
