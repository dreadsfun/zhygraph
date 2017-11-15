#pragma once
#include "export.hpp"
#include <string>
namespace di {
class i_attribute {
public:
	virtual void parse_string( const std::string& v ) = 0;
	virtual std::string format_string( void ) const = 0;
};
}