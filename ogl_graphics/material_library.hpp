#pragma once
#pragma once
#include <unordered_map>
#include <string>
#include <di_rtlib/define_dependency.hpp>
#include <di_rtlib/define_attribute.hpp>
#include <material/material.hxx>
#include <material/material-pimpl.hxx>
#include <core/asset.hpp>
#include <core/logger.hpp>
class material_library
	: public di::component {
private:
	typedef std::unordered_map< std::string, material* > material_map;

	static material_library* instance;

	component_dependency( m_logger, i_logger );
	component_dependency( m_type_manager, i_asset_type_manager );
	component_attribute( m_material_file, std::string );

	material_map m_materials;
	materials_paggr m_mat_p;

public:
	static const material* get_material( const std::string& n );
	static const material_map& get_materials( void );

private:
	void _parse_lib( void );
	virtual void initialize_component( void ) override;
};

#include <di_rtlib/register_class.hpp>
register_class( material_library );