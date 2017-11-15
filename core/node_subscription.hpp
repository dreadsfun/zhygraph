#pragma once
#include "export.hpp"
#include <unordered_map>
#include <string>
class i_scene_node;

class node_subscription {
#pragma region types
public:
	typedef std::unordered_multimap< std::string, i_scene_node* > node_map;
	typedef node_map::_Mylist::const_iterator node_range_iterator;
	typedef std::pair< node_range_iterator, node_range_iterator > node_range_iterator_pair;
#pragma endregion

#pragma region data members
private:
	node_map m_nodes;
#pragma endregion

#pragma region member functions
public:
	CORE_SHARED node_subscription( void ) = default;
	CORE_SHARED node_subscription( const std::vector< std::string >& al );
	CORE_SHARED node_subscription& allow_name( const std::string& n );
	CORE_SHARED void subscribe_as( const std::string& n, i_scene_node* nd );
	CORE_SHARED node_range_iterator_pair get_subscribers( const std::string& n ) const;
#pragma endregion
};