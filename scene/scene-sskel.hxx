// Copyright (c) 2005-2011 Code Synthesis Tools CC
//
// This program was generated by CodeSynthesis XSD/e, an XML Schema
// to C++ data binding compiler for embedded systems.
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License version 2 as
// published by the Free Software Foundation.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA
//
//

#ifndef E__VS14PRJBKP_ENGINE_SCENE_SCENE_SSKEL_HXX
#define E__VS14PRJBKP_ENGINE_SCENE_SCENE_SSKEL_HXX

#include <xsde/cxx/version.hxx>

#if (XSDE_INT_VERSION != 3020000L)
#error XSD/e runtime version mismatch
#endif

#include <xsde/cxx/config.hxx>

#ifndef XSDE_ENCODING_UTF8
#error the generated code uses the UTF-8 encodingwhile the XSD/e runtime does not (reconfigure the runtime or change the --char-encoding value)
#endif

#ifndef XSDE_STL
#error the generated code uses STL while the XSD/e runtime does not (reconfigure the runtime or add --no-stl)
#endif

#ifndef XSDE_IOSTREAM
#error the generated code uses iostream while the XSD/e runtime does not (reconfigure the runtime or add --no-iostream)
#endif

#ifndef XSDE_EXCEPTIONS
#error the generated code uses exceptions while the XSD/e runtime does not (reconfigure the runtime or add --no-exceptions)
#endif

#ifndef XSDE_LONGLONG
#error the generated code uses long long while the XSD/e runtime does not (reconfigure the runtime or add --no-long-long)
#endif

#ifndef XSDE_SERIALIZER_VALIDATION
#error the generated code uses validation while the XSD/e runtime does not (reconfigure the runtime or add --suppress-validation)
#endif

#ifdef XSDE_POLYMORPHIC
#error the generated code expects XSD/e runtime without polymorphism support (reconfigure the runtime or add --generate-polymorphic/--runtime-polymorphic)
#endif

#ifndef XSDE_REUSE_STYLE_TIEIN
#error the generated code uses the tiein reuse style while the XSD/e runtime does not (reconfigure the runtime or add --reuse-style-mixin or --reuse-style-none)
#endif

#ifdef XSDE_CUSTOM_ALLOCATOR
#error the XSD/e runtime uses custom allocator while the generated code does not (reconfigure the runtime or add --custom-allocator)
#endif

#include <xsde/cxx/pre.hxx>

// Begin prologue.
//

#include <xsde/cxx/hybrid/any-type.hxx>
#include <xsde/cxx/hybrid/any-type-sskel.hxx>
#include <xsde/cxx/hybrid/any-type-simpl.hxx>

namespace xml_schema
{
  using ::xsde::cxx::hybrid::any_type;

  using ::xsde::cxx::hybrid::any_type_sskel;
  using ::xsde::cxx::hybrid::any_type_simpl;
}


//
// End prologue.

// Forward declarations
//
class vec3_type_sskel;
class vec4_type_sskel;
class scene_graph_sskel;
class nodes_sskel;
class scene_sskel;
class scenes_sskel;
class attribute_sskel;
class node_sskel;

#include <string>

#include <xsde/cxx/serializer/xml-schema.hxx>

#include <xsde/cxx/serializer/exceptions.hxx>

#include <xsde/cxx/serializer/validating/serializer.hxx>
#include <xsde/cxx/serializer/validating/xml-schema-sskel.hxx>
#include <xsde/cxx/serializer/validating/xml-schema-simpl.hxx>

#include <xsde/cxx/serializer/genx/document.hxx>

#include "scene.hxx"

namespace xml_schema
{
  // Built-in XML Schema types mapping.
  //
  using ::xsde::cxx::string_sequence;
  using ::xsde::cxx::qname;
  using ::xsde::cxx::buffer;
  using ::xsde::cxx::time_zone;
  using ::xsde::cxx::gday;
  using ::xsde::cxx::gmonth;
  using ::xsde::cxx::gyear;
  using ::xsde::cxx::gmonth_day;
  using ::xsde::cxx::gyear_month;
  using ::xsde::cxx::date;
  using ::xsde::cxx::time;
  using ::xsde::cxx::date_time;
  using ::xsde::cxx::duration;

  // Base serializer skeletons.
  //
  using ::xsde::cxx::serializer::serializer_base;
  typedef ::xsde::cxx::serializer::validating::empty_content serializer_empty_content;
  typedef ::xsde::cxx::serializer::validating::simple_content serializer_simple_content;
  typedef ::xsde::cxx::serializer::validating::complex_content serializer_complex_content;

  // Serializer skeletons and implementations for the
  // XML Schema built-in types.
  //
  using ::xsde::cxx::serializer::validating::any_simple_type_sskel;
  using ::xsde::cxx::serializer::validating::any_simple_type_simpl;

  using ::xsde::cxx::serializer::validating::byte_sskel;
  using ::xsde::cxx::serializer::validating::byte_simpl;

  using ::xsde::cxx::serializer::validating::unsigned_byte_sskel;
  using ::xsde::cxx::serializer::validating::unsigned_byte_simpl;

  using ::xsde::cxx::serializer::validating::short_sskel;
  using ::xsde::cxx::serializer::validating::short_simpl;

  using ::xsde::cxx::serializer::validating::unsigned_short_sskel;
  using ::xsde::cxx::serializer::validating::unsigned_short_simpl;

  using ::xsde::cxx::serializer::validating::int_sskel;
  using ::xsde::cxx::serializer::validating::int_simpl;

  using ::xsde::cxx::serializer::validating::unsigned_int_sskel;
  using ::xsde::cxx::serializer::validating::unsigned_int_simpl;

  using ::xsde::cxx::serializer::validating::long_sskel;
  using ::xsde::cxx::serializer::validating::long_simpl;

  using ::xsde::cxx::serializer::validating::unsigned_long_sskel;
  using ::xsde::cxx::serializer::validating::unsigned_long_simpl;

  using ::xsde::cxx::serializer::validating::integer_sskel;
  using ::xsde::cxx::serializer::validating::integer_simpl;

  using ::xsde::cxx::serializer::validating::non_positive_integer_sskel;
  using ::xsde::cxx::serializer::validating::non_positive_integer_simpl;

  using ::xsde::cxx::serializer::validating::non_negative_integer_sskel;
  using ::xsde::cxx::serializer::validating::non_negative_integer_simpl;

  using ::xsde::cxx::serializer::validating::positive_integer_sskel;
  using ::xsde::cxx::serializer::validating::positive_integer_simpl;

  using ::xsde::cxx::serializer::validating::negative_integer_sskel;
  using ::xsde::cxx::serializer::validating::negative_integer_simpl;

  using ::xsde::cxx::serializer::validating::boolean_sskel;
  using ::xsde::cxx::serializer::validating::boolean_simpl;

  using ::xsde::cxx::serializer::validating::float_sskel;
  using ::xsde::cxx::serializer::validating::float_simpl;

  using ::xsde::cxx::serializer::validating::double_sskel;
  using ::xsde::cxx::serializer::validating::double_simpl;

  using ::xsde::cxx::serializer::validating::decimal_sskel;
  using ::xsde::cxx::serializer::validating::decimal_simpl;

  using ::xsde::cxx::serializer::validating::string_sskel;
  using ::xsde::cxx::serializer::validating::string_simpl;

  using ::xsde::cxx::serializer::validating::normalized_string_sskel;
  using ::xsde::cxx::serializer::validating::normalized_string_simpl;

  using ::xsde::cxx::serializer::validating::token_sskel;
  using ::xsde::cxx::serializer::validating::token_simpl;

  using ::xsde::cxx::serializer::validating::name_sskel;
  using ::xsde::cxx::serializer::validating::name_simpl;

  using ::xsde::cxx::serializer::validating::nmtoken_sskel;
  using ::xsde::cxx::serializer::validating::nmtoken_simpl;

  using ::xsde::cxx::serializer::validating::nmtokens_sskel;
  using ::xsde::cxx::serializer::validating::nmtokens_simpl;

  using ::xsde::cxx::serializer::validating::ncname_sskel;
  using ::xsde::cxx::serializer::validating::ncname_simpl;

  using ::xsde::cxx::serializer::validating::language_sskel;
  using ::xsde::cxx::serializer::validating::language_simpl;

  using ::xsde::cxx::serializer::validating::id_sskel;
  using ::xsde::cxx::serializer::validating::id_simpl;

  using ::xsde::cxx::serializer::validating::idref_sskel;
  using ::xsde::cxx::serializer::validating::idref_simpl;

  using ::xsde::cxx::serializer::validating::idrefs_sskel;
  using ::xsde::cxx::serializer::validating::idrefs_simpl;

  using ::xsde::cxx::serializer::validating::uri_sskel;
  using ::xsde::cxx::serializer::validating::uri_simpl;

  using ::xsde::cxx::serializer::validating::qname_sskel;
  using ::xsde::cxx::serializer::validating::qname_simpl;

  using ::xsde::cxx::serializer::validating::base64_binary_sskel;
  using ::xsde::cxx::serializer::validating::base64_binary_simpl;

  using ::xsde::cxx::serializer::validating::hex_binary_sskel;
  using ::xsde::cxx::serializer::validating::hex_binary_simpl;

  using ::xsde::cxx::serializer::validating::date_sskel;
  using ::xsde::cxx::serializer::validating::date_simpl;

  using ::xsde::cxx::serializer::validating::date_time_sskel;
  using ::xsde::cxx::serializer::validating::date_time_simpl;

  using ::xsde::cxx::serializer::validating::duration_sskel;
  using ::xsde::cxx::serializer::validating::duration_simpl;

  using ::xsde::cxx::serializer::validating::gday_sskel;
  using ::xsde::cxx::serializer::validating::gday_simpl;

  using ::xsde::cxx::serializer::validating::gmonth_sskel;
  using ::xsde::cxx::serializer::validating::gmonth_simpl;

  using ::xsde::cxx::serializer::validating::gmonth_day_sskel;
  using ::xsde::cxx::serializer::validating::gmonth_day_simpl;

  using ::xsde::cxx::serializer::validating::gyear_sskel;
  using ::xsde::cxx::serializer::validating::gyear_simpl;

  using ::xsde::cxx::serializer::validating::gyear_month_sskel;
  using ::xsde::cxx::serializer::validating::gyear_month_simpl;

  using ::xsde::cxx::serializer::validating::time_sskel;
  using ::xsde::cxx::serializer::validating::time_simpl;

  // Error codes.
  //
  typedef xsde::cxx::serializer::genx::xml_error serializer_xml_error;
  typedef xsde::cxx::schema_error serializer_schema_error;

  // Exceptions.
  //
  typedef xsde::cxx::serializer::exception serializer_exception;
  typedef xsde::cxx::serializer::xml serializer_xml;
  typedef xsde::cxx::serializer::schema serializer_schema;

  // Document serializer.
  //
  using xsde::cxx::serializer::genx::writer;
  using xsde::cxx::serializer::genx::document_simpl;

  // Serializer context.
  //
  typedef xsde::cxx::serializer::context serializer_context;
}

class vec3_type_sskel: public ::xsde::cxx::serializer::validating::complex_content
{
  public:
  // Serializer callbacks. Override them in your implementation.
  //

  virtual void
  pre (const ::vec3_type&) = 0;

  // Attributes.
  //
  virtual float
  x () = 0;

  virtual float
  y () = 0;

  virtual float
  z () = 0;

  // virtual void
  // post ();

  // Serializer construction API.
  //
  void
  serializers (::xml_schema::float_sskel& /* x */,
               ::xml_schema::float_sskel& /* y */,
               ::xml_schema::float_sskel& /* z */);

  // Individual attribute serializers.
  //
  void
  x_serializer (::xml_schema::float_sskel&);

  void
  y_serializer (::xml_schema::float_sskel&);

  void
  z_serializer (::xml_schema::float_sskel&);

  virtual void
  _reset ();

  // Constructor.
  //
  vec3_type_sskel ();

  // Implementation.
  //
  public:
  virtual void
  _serialize_attributes ();

  protected:
  vec3_type_sskel* vec3_type_impl_;
  vec3_type_sskel (vec3_type_sskel*, void*);

  protected:
  ::xml_schema::float_sskel* x_serializer_;
  ::xml_schema::float_sskel* y_serializer_;
  ::xml_schema::float_sskel* z_serializer_;
};

class vec4_type_sskel: public ::xsde::cxx::serializer::validating::complex_content
{
  public:
  // Serializer callbacks. Override them in your implementation.
  //

  virtual void
  pre (const ::vec4_type&) = 0;

  // Attributes.
  //
  virtual float
  x () = 0;

  virtual float
  y () = 0;

  virtual float
  z () = 0;

  virtual float
  w () = 0;

  // virtual void
  // post ();

  // Serializer construction API.
  //
  void
  serializers (::xml_schema::float_sskel& /* x */,
               ::xml_schema::float_sskel& /* y */,
               ::xml_schema::float_sskel& /* z */,
               ::xml_schema::float_sskel& /* w */);

  // Individual attribute serializers.
  //
  void
  x_serializer (::xml_schema::float_sskel&);

  void
  y_serializer (::xml_schema::float_sskel&);

  void
  z_serializer (::xml_schema::float_sskel&);

  void
  w_serializer (::xml_schema::float_sskel&);

  virtual void
  _reset ();

  // Constructor.
  //
  vec4_type_sskel ();

  // Implementation.
  //
  public:
  virtual void
  _serialize_attributes ();

  protected:
  vec4_type_sskel* vec4_type_impl_;
  vec4_type_sskel (vec4_type_sskel*, void*);

  protected:
  ::xml_schema::float_sskel* x_serializer_;
  ::xml_schema::float_sskel* y_serializer_;
  ::xml_schema::float_sskel* z_serializer_;
  ::xml_schema::float_sskel* w_serializer_;
};

class scene_graph_sskel: public ::xsde::cxx::serializer::validating::complex_content
{
  public:
  // Serializer callbacks. Override them in your implementation.
  //

  virtual void
  pre (const ::scene_graph&) = 0;

  // Elements.
  //
  virtual bool
  nodes_present ();

  virtual const ::nodes&
  nodes () = 0;

  virtual bool
  scenes_present ();

  virtual const ::scenes&
  scenes () = 0;

  // virtual void
  // post ();

  // Serializer construction API.
  //
  void
  serializers (::nodes_sskel& /* nodes */,
               ::scenes_sskel& /* scenes */);

  // Individual element serializers.
  //
  void
  nodes_serializer (::nodes_sskel&);

  void
  scenes_serializer (::scenes_sskel&);

  virtual void
  _reset ();

  // Constructor.
  //
  scene_graph_sskel ();

  // Implementation.
  //
  public:
  virtual void
  _serialize_content ();

  protected:
  scene_graph_sskel* scene_graph_impl_;
  scene_graph_sskel (scene_graph_sskel*, void*);

  protected:
  ::nodes_sskel* nodes_serializer_;
  ::scenes_sskel* scenes_serializer_;
};

class nodes_sskel: public ::xsde::cxx::serializer::validating::complex_content
{
  public:
  // Serializer callbacks. Override them in your implementation.
  //

  virtual void
  pre (const ::nodes&) = 0;

  // Elements.
  //
  virtual bool
  node_next () = 0;

  virtual const ::node&
  node () = 0;

  // virtual void
  // post ();

  // Serializer construction API.
  //
  void
  serializers (::node_sskel& /* node */);

  // Individual element serializers.
  //
  void
  node_serializer (::node_sskel&);

  virtual void
  _reset ();

  // Constructor.
  //
  nodes_sskel ();

  // Implementation.
  //
  public:
  virtual void
  _serialize_content ();

  protected:
  nodes_sskel* nodes_impl_;
  nodes_sskel (nodes_sskel*, void*);

  protected:
  ::node_sskel* node_serializer_;
};

class scene_sskel: public ::xsde::cxx::serializer::validating::complex_content
{
  public:
  // Serializer callbacks. Override them in your implementation.
  //

  virtual void
  pre (const ::scene&) = 0;

  // Attributes.
  //
  virtual ::std::string
  name () = 0;

  virtual bool
  graph_present ();

  virtual ::std::string
  graph () = 0;

  // virtual void
  // post ();

  // Serializer construction API.
  //
  void
  serializers (::xml_schema::token_sskel& /* name */,
               ::xml_schema::string_sskel& /* graph */);

  // Individual attribute serializers.
  //
  void
  name_serializer (::xml_schema::token_sskel&);

  void
  graph_serializer (::xml_schema::string_sskel&);

  virtual void
  _reset ();

  // Constructor.
  //
  scene_sskel ();

  // Implementation.
  //
  public:
  virtual void
  _serialize_attributes ();

  protected:
  scene_sskel* scene_impl_;
  scene_sskel (scene_sskel*, void*);

  protected:
  ::xml_schema::token_sskel* name_serializer_;
  ::xml_schema::string_sskel* graph_serializer_;
};

class scenes_sskel: public ::xsde::cxx::serializer::validating::complex_content
{
  public:
  // Serializer callbacks. Override them in your implementation.
  //

  virtual void
  pre (const ::scenes&) = 0;

  // Elements.
  //
  virtual bool
  scene_next () = 0;

  virtual const ::scene&
  scene () = 0;

  // virtual void
  // post ();

  // Serializer construction API.
  //
  void
  serializers (::scene_sskel& /* scene */);

  // Individual element serializers.
  //
  void
  scene_serializer (::scene_sskel&);

  virtual void
  _reset ();

  // Constructor.
  //
  scenes_sskel ();

  // Implementation.
  //
  public:
  virtual void
  _serialize_content ();

  protected:
  scenes_sskel* scenes_impl_;
  scenes_sskel (scenes_sskel*, void*);

  protected:
  ::scene_sskel* scene_serializer_;
};

class attribute_sskel: public ::xsde::cxx::serializer::validating::complex_content
{
  public:
  // Serializer callbacks. Override them in your implementation.
  //

  virtual void
  pre (const ::attribute&) = 0;

  // Attributes.
  //
  virtual bool
  name_present ();

  virtual ::std::string
  name () = 0;

  virtual bool
  value_present ();

  virtual ::std::string
  value () = 0;

  // virtual void
  // post ();

  // Serializer construction API.
  //
  void
  serializers (::xml_schema::token_sskel& /* name */,
               ::xml_schema::string_sskel& /* value */);

  // Individual attribute serializers.
  //
  void
  name_serializer (::xml_schema::token_sskel&);

  void
  value_serializer (::xml_schema::string_sskel&);

  virtual void
  _reset ();

  // Constructor.
  //
  attribute_sskel ();

  // Implementation.
  //
  public:
  virtual void
  _serialize_attributes ();

  protected:
  attribute_sskel* attribute_impl_;
  attribute_sskel (attribute_sskel*, void*);

  protected:
  ::xml_schema::token_sskel* name_serializer_;
  ::xml_schema::string_sskel* value_serializer_;
};

class node_sskel: public ::xsde::cxx::serializer::validating::complex_content
{
  public:
  // Serializer callbacks. Override them in your implementation.
  //

  virtual void
  pre (const ::node&) = 0;

  // Attributes.
  //
  virtual ::std::string
  name () = 0;

  virtual ::std::string
  class_ () = 0;

  // Elements.
  //
  virtual bool
  position_present ();

  virtual const ::vec3_type&
  position () = 0;

  virtual bool
  rotation_present ();

  virtual const ::vec4_type&
  rotation () = 0;

  virtual bool
  scale_present ();

  virtual const ::vec3_type&
  scale () = 0;

  virtual bool
  attribute_next ();

  virtual const ::attribute&
  attribute () = 0;

  // virtual void
  // post ();

  // Serializer construction API.
  //
  void
  serializers (::xml_schema::token_sskel& /* name */,
               ::xml_schema::token_sskel& /* class */,
               ::vec3_type_sskel& /* position */,
               ::vec4_type_sskel& /* rotation */,
               ::vec3_type_sskel& /* scale */,
               ::attribute_sskel& /* attribute */);

  // Individual attribute serializers.
  //
  void
  name_serializer (::xml_schema::token_sskel&);

  void
  class__serializer (::xml_schema::token_sskel&);

  // Individual element serializers.
  //
  void
  position_serializer (::vec3_type_sskel&);

  void
  rotation_serializer (::vec4_type_sskel&);

  void
  scale_serializer (::vec3_type_sskel&);

  void
  attribute_serializer (::attribute_sskel&);

  virtual void
  _reset ();

  // Constructor.
  //
  node_sskel ();

  // Implementation.
  //
  public:
  virtual void
  _serialize_attributes ();

  virtual void
  _serialize_content ();

  protected:
  node_sskel* node_impl_;
  node_sskel (node_sskel*, void*);

  protected:
  ::xml_schema::token_sskel* name_serializer_;
  ::xml_schema::token_sskel* class__serializer_;
  ::vec3_type_sskel* position_serializer_;
  ::vec4_type_sskel* rotation_serializer_;
  ::vec3_type_sskel* scale_serializer_;
  ::attribute_sskel* attribute_serializer_;
};

// Begin epilogue.
//
//
// End epilogue.

#include <xsde/cxx/post.hxx>

#endif // E__VS14PRJBKP_ENGINE_SCENE_SCENE_SSKEL_HXX
