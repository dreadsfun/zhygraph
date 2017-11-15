#pragma once
#include <chrono>
using std::chrono::high_resolution_clock;
typedef std::chrono::time_point< high_resolution_clock > time_point;
using std::chrono::duration;

namespace detail {
	class init_time {
	public:
		init_time( time_point& tp ) {
			tp = high_resolution_clock::now();
		}
	};
}

class engine_time {
public:
	static double elapsed_seconds( void ) {
		return static_cast< duration< double > >( high_resolution_clock::now() - start ).count();
	}

private:
	static detail::init_time init;
	static time_point start;
};

class stop_watch {
public:
	double stop( void ) {
		if( m_run ) {
			return engine_time::elapsed_seconds() - m_internal;
			m_run = false;
		} else {
			return 0;
		}
	}

	double get( void ) {
		if( m_run ) {
			return engine_time::elapsed_seconds() - m_internal;
		} else {
			return 0;
		}
	}

	void start( void ) {
		m_internal = engine_time::elapsed_seconds();
		m_run = true;
	}

private:
	bool m_run { false };
	double m_internal { 0.0 };
};

detail::init_time engine_time::init ( engine_time::start );
time_point engine_time::start;