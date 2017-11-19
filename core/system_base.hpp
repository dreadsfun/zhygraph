#pragma once
#include <di_rtlib/define_dependency.hpp>
#include "logger.hpp"
#include "node_subscription.hpp"
#include "scene_node.hpp"
class system_base
	: public di::component {
private:
	class _node_subscriptor
		: public all_node_visitor {
	private:
		node_subscription m_ns;

	public:
		_node_subscriptor( void ) = default;
		_node_subscriptor( const node_subscription& ns )
			: m_ns( ns ) { }

		void set_subscription( const node_subscription& ns ) {
			m_ns = ns;
		}

		node_subscription& get_subscription( void ) {
			return m_ns;
		}

	private:
		virtual void visit( i_scene_node* n ) override {
			n->update( m_ns );
		}
		virtual void visit( const i_scene_node* n ) const override { }
	};

protected:
	component_dependency( m_logger, i_logger );

	virtual void _process_scene( i_scene_node* root, node_subscription& ns ) = 0;

public:
	virtual node_subscription create_subscription( void ) = 0;

	void process_scene( i_scene_node* root ) {
		_node_subscriptor _ns;
		_ns.set_subscription( this->create_subscription() );
		root->traverse_depth( _ns );
		_process_scene( root, _ns.get_subscription() );
	}
};