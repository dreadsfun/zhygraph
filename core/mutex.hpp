#pragma once
#include <mutex>
#include <atomic>
class mutex {
private:
	std::mutex m_internal;
	std::atomic< std::thread::id > m_owner;

public:
	void lock( void ) {
		if( m_owner == std::this_thread::get_id() ) throw std::exception( "mutex already owned by thread" );
		m_internal.lock();
		m_owner = std::this_thread::get_id();
	}

	void force_lock( void ) {
		if( m_owner == std::this_thread::get_id() ) throw std::exception( "mutex already owned by thread" );
		if( m_owner != std::thread::id() ) throw std::exception( "mutex is not available to lock" );
		m_internal.lock();
		m_owner = std::this_thread::get_id();
	}

	bool try_lock( void ) {
		if( m_owner == std::this_thread::get_id() ) throw std::exception( "mutex already owned by thread" );
		if( m_internal.try_lock() ) {
			m_owner = std::this_thread::get_id();
			return true;
		} else {
			return false;
		}
	}

	void unlock( void ) {
		if( m_owner != std::this_thread::get_id() ) throw std::exception( "mutex is not owned by thread" );
		m_internal.unlock();
		m_owner = std::thread::id();
	}
};