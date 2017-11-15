#include "material_library.hpp"
material_library* material_library::instance = nullptr;

const material * material_library::get_material( const std::string & n ) {
	const material* r = nullptr;
	auto fit = instance->m_materials.find( n );
	if( fit == instance->m_materials.end() ) {
		instance->m_logger->init_stream( priority::error, "material_library" ) << "material with name \"" << n << "\" was not found in the library";
	} else {
		r = fit->second;
	}
	return r;
}

const material_library::material_map & material_library::get_materials( void ) {
	return instance->m_materials;
}

void material_library::_parse_lib( void ) {
	try {
		text_asset_ptr t = std::static_pointer_cast< text_asset >(
			m_type_manager->get( "text" )->load_asset( asset_url( m_material_file.get_value() ) )
			);

		xml_schema::document_pimpl doc_p( m_mat_p.root_parser(), m_mat_p.root_name() );
		m_mat_p.pre();
		doc_p.parse( t->get_text().c_str(), t->get_text().length(), true );
		materials* mats = m_mat_p.post();

		for( material& mat : mats->material() ) {
			m_materials.insert( std::make_pair( mat.name(), &mat ) );
			sinfo << "material with name \"" << mat.name() << "\" inserted to material library";
		}

	} catch( const xml_schema::parser_exception& e ) {
		serror << "error parsing material file: " << e.text() << " line: " << e.line() << " column: " << e.column();
	}
}

void material_library::initialize_component( void ) { 
	if( instance == nullptr ) {
		instance = this;
		instance->_parse_lib();
	} else {
		warn( "material library part created (or catalog init called) multiple times, only first istance is used" );
	}
}
