#include "node_subscription.hpp"

node_subscription::node_subscription( const std::vector<std::string>& al ) {
	for( const std::string& a : al ) {
		this->allow_name( a );
	}
}

node_subscription & node_subscription::allow_name( const std::string & n ) {
	m_nodes.insert( std::make_pair( n, nullptr ) );
	return *this;
}

void node_subscription::subscribe_as( const std::string & n, i_scene_node * nd ) {
	if( nd == nullptr ) return;
	if( m_nodes.find( n ) != m_nodes.end() ) {
		m_nodes.emplace( n, nd );
	}
}

node_subscription::node_range_iterator_pair node_subscription::get_subscribers( const std::string & n ) const {
	auto itp = m_nodes.equal_range( n );
	for( ; itp.first->second == nullptr && itp.first != itp.second; itp.first++ );
	return itp;
}