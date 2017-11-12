#include "logger.h"
namespace zhygraph {
	namespace core {
		log_stream::log_stream( log_stream && m )
			: m_owner( m.m_owner ),
			m_stream( std::move( m.m_stream ) ) {
			m.m_owner = nullptr;
		}

		log_stream::log_stream( log_priority p, const std::string & cl, const logger * l )
			: m_owner( l ),
			m_cl( cl ),
			m_pr( p ) { }

		log_stream::~log_stream( void ) {
			m_owner->log( m_pr, m_stream.str(), m_cl );
			m_stream.clear();
		}
		log_stream logger::init_stream( log_priority p, const std::string & cl ) const {
			return log_stream( p, cl, this );
		}

		std::mutex stdout_channel::cout_lock;
	}
}