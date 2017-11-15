#pragma once
#include "export.hpp"
namespace di {
class component;

class i_dependency {
public:
	virtual void set_component( component* c ) = 0;
};
}