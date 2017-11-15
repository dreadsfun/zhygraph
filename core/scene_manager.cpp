#include <scene/scene.hxx>
#include <scene/scene-pimpl.hxx>
#include "scene.hpp"
class default_scene_manager
	: public scene_manager_base {
private:
	class node_loader
		: public all_node_visitor {
	private:
		type_manager_ptr m_tmgr;
		bool m_async;
	public:
		node_loader( type_manager_ptr tm, bool async )
			: m_tmgr( tm ),
			m_async( async ) {}
	private:
		virtual void visit( i_scene_node* n ) override {
			n->load( m_tmgr, m_async );
		}
	};

	class node_unloader
		: public all_node_visitor {
	private:
		type_manager_ptr m_tmgr;
	public:
		node_unloader( type_manager_ptr tm )
			: m_tmgr( tm ) {}
	private:
		virtual void visit( i_scene_node* n ) override {
			n->unload( m_tmgr );
		}
	};

	// keep the idea
	//scene_node_ptr m_global_root;

	virtual void initialize_component( void ) override {
		try {
			text_asset_ptr t = std::static_pointer_cast< text_asset >( 
				m_type_manager->get( "text" )->load_asset( asset_url( m_scene_file.get_value() ) ) 
				);
			scene_graph_paggr sg_p;
			xml_schema::document_pimpl doc_p( sg_p.root_parser(), sg_p.root_name() );
			sg_p.pre();
			doc_p.parse( t->get_text().c_str(), t->get_text().length(), true );
			scene_graph* sg = sg_p.post();
			
			if( sg->scenes_present() && sg->nodes_present() ) {
				for( const scene& sc : sg->scenes().scene() ) {
					scene_tree_ptr npsc = std::make_shared< scene_tree >( m_logger.get() );
					sinfo << "building scene \"" << sc.name() << "\"...";
					npsc->build( sc, sg->nodes() );
					m_scenes.insert( std::make_pair( npsc->get_name(), npsc ) );
				}
			}
		} catch( const xml_schema::parser_exception& e ) {
			serror << "error parsing scene file: " << e.text() << " line: " << e.line() << " column: " << e.column();
		}
	}

	virtual bool load_first( void ) override {
		if( m_scenes.size() > 0 ) {
			_load_scene( m_scenes.begin()->second, false );
			return true;
		} else {
			return false;
		}
	}

	virtual bool load_scene( const std::string& n, bool async ) override {
		scene_tree_ptr sc = _get_scene( n );
		if( sc ) {
			_load_scene( sc, async );

			for( const auto& pp : m_loaded ) {
				_unload_scene( pp.second );
			}

			const std::vector< asset_manager_ptr >& mgrs = m_type_manager->get_all();
			for( asset_manager_ptr m : mgrs ) {
				m->unload_unreferenced();
			}
		}
		return sc.operator bool();
	}

	virtual bool load_scene_additive( const std::string& n, bool async ) override {
		scene_tree_ptr sc = _get_scene( n );
		if( sc ) {
			_load_scene( sc, async );
		}
		return sc.operator bool();
	}

	virtual void update( double dt ) override {
		/*static std::shared_ptr< node_updater > nu = std::make_shared< node_updater >();
		nu->set_dt( dt );
		for( const auto& pp : m_loaded ) {
			pp.second->traverse_depth( nu );
		}*/
	}

	scene_tree_ptr _get_scene( const std::string& n ) const {
		scene_tree_ptr r;
		auto fit = m_scenes.find( n );
		if( fit == m_scenes.end() ) {
			serror << "scene with name \"" << n << "\" was not found as a defined scene";
		} else {
			r = fit->second;
		}
		return r;
	}
	
	void _unload_scene( scene_tree_ptr sc ) {
		static std::shared_ptr< node_unloader > nu = std::make_shared< node_unloader >( m_type_manager );
		sc->traverse_depth( nu );
	}

	void _load_scene( scene_tree_ptr sc, bool async ) {
		scene_tree_ptr& st = m_loaded[ sc->get_name() ];
		if( st ) {
			serror << "scene with name \"" << sc->get_name() << "\" is already loaded";
		} else {
			sinfo << "loading scene with name \"" << sc->get_name() << "\"...";
			st = sc;
			sc->traverse_depth( std::make_shared< node_loader >( m_type_manager, async ) );
		}
	}
};

#include <di_rtlib/define_dependency.hpp>
#include "graphics.hpp"
class scene_manager_update_listener
	: public i_update_listener, public di::component {
private:
	component_dependency( m_manager, i_scene_manager );

	virtual void respond( double dt ) override {
		m_manager->update( dt );
	}
};

#include <di_rtlib/register_class.hpp>
register_class( default_scene_manager );
register_class( scene_node_base );
register_class( scene_manager_update_listener );