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

#ifndef E__VS14PRJBKP_ENGINE_SCENE_SCENE_PSKEL_HXX
#define E__VS14PRJBKP_ENGINE_SCENE_SCENE_PSKEL_HXX

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

#ifndef XSDE_PARSER_VALIDATION
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
#include <xsde/cxx/hybrid/any-type-pskel.hxx>
#include <xsde/cxx/hybrid/any-type-pimpl.hxx>

namespace xml_schema
{
  using ::xsde::cxx::hybrid::any_type;

  using ::xsde::cxx::hybrid::any_type_pskel;
  using ::xsde::cxx::hybrid::any_type_pimpl;
}


//
// End prologue.

// Forward declarations
//
class vec3_type_pskel;
class vec4_type_pskel;
class scene_graph_pskel;
class nodes_pskel;
class scene_pskel;
class scenes_pskel;
class attribute_pskel;
class node_pskel;

#include <xsde/cxx/ro-string.hxx>

#include <xsde/cxx/parser/xml-schema.hxx>

#include <xsde/cxx/parser/exceptions.hxx>

#include <xsde/cxx/stack.hxx>
#include <xsde/cxx/parser/validating/parser.hxx>
#include <xsde/cxx/parser/validating/xml-schema-pskel.hxx>
#include <xsde/cxx/parser/validating/xml-schema-pimpl.hxx>

#include <xsde/cxx/parser/expat/document.hxx>

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

  // Base parser skeletons.
  //
  using ::xsde::cxx::parser::parser_base;
  typedef ::xsde::cxx::parser::validating::empty_content parser_empty_content;
  typedef ::xsde::cxx::parser::validating::simple_content parser_simple_content;
  typedef ::xsde::cxx::parser::validating::complex_content parser_complex_content;
  typedef ::xsde::cxx::parser::validating::list_base parser_list_base;

  // Parser skeletons and implementations for the XML Schema
  // built-in types.
  //
  using ::xsde::cxx::parser::validating::any_simple_type_pskel;
  using ::xsde::cxx::parser::validating::any_simple_type_pimpl;

  using ::xsde::cxx::parser::validating::byte_pskel;
  using ::xsde::cxx::parser::validating::byte_pimpl;

  using ::xsde::cxx::parser::validating::unsigned_byte_pskel;
  using ::xsde::cxx::parser::validating::unsigned_byte_pimpl;

  using ::xsde::cxx::parser::validating::short_pskel;
  using ::xsde::cxx::parser::validating::short_pimpl;

  using ::xsde::cxx::parser::validating::unsigned_short_pskel;
  using ::xsde::cxx::parser::validating::unsigned_short_pimpl;

  using ::xsde::cxx::parser::validating::int_pskel;
  using ::xsde::cxx::parser::validating::int_pimpl;

  using ::xsde::cxx::parser::validating::unsigned_int_pskel;
  using ::xsde::cxx::parser::validating::unsigned_int_pimpl;

  using ::xsde::cxx::parser::validating::long_pskel;
  using ::xsde::cxx::parser::validating::long_pimpl;

  using ::xsde::cxx::parser::validating::unsigned_long_pskel;
  using ::xsde::cxx::parser::validating::unsigned_long_pimpl;

  using ::xsde::cxx::parser::validating::integer_pskel;
  using ::xsde::cxx::parser::validating::integer_pimpl;

  using ::xsde::cxx::parser::validating::non_positive_integer_pskel;
  using ::xsde::cxx::parser::validating::non_positive_integer_pimpl;

  using ::xsde::cxx::parser::validating::non_negative_integer_pskel;
  using ::xsde::cxx::parser::validating::non_negative_integer_pimpl;

  using ::xsde::cxx::parser::validating::positive_integer_pskel;
  using ::xsde::cxx::parser::validating::positive_integer_pimpl;

  using ::xsde::cxx::parser::validating::negative_integer_pskel;
  using ::xsde::cxx::parser::validating::negative_integer_pimpl;

  using ::xsde::cxx::parser::validating::boolean_pskel;
  using ::xsde::cxx::parser::validating::boolean_pimpl;

  using ::xsde::cxx::parser::validating::float_pskel;
  using ::xsde::cxx::parser::validating::float_pimpl;

  using ::xsde::cxx::parser::validating::double_pskel;
  using ::xsde::cxx::parser::validating::double_pimpl;

  using ::xsde::cxx::parser::validating::decimal_pskel;
  using ::xsde::cxx::parser::validating::decimal_pimpl;

  using ::xsde::cxx::parser::validating::string_pskel;
  using ::xsde::cxx::parser::validating::string_pimpl;

  using ::xsde::cxx::parser::validating::normalized_string_pskel;
  using ::xsde::cxx::parser::validating::normalized_string_pimpl;

  using ::xsde::cxx::parser::validating::token_pskel;
  using ::xsde::cxx::parser::validating::token_pimpl;

  using ::xsde::cxx::parser::validating::name_pskel;
  using ::xsde::cxx::parser::validating::name_pimpl;

  using ::xsde::cxx::parser::validating::nmtoken_pskel;
  using ::xsde::cxx::parser::validating::nmtoken_pimpl;

  using ::xsde::cxx::parser::validating::nmtokens_pskel;
  using ::xsde::cxx::parser::validating::nmtokens_pimpl;

  using ::xsde::cxx::parser::validating::ncname_pskel;
  using ::xsde::cxx::parser::validating::ncname_pimpl;

  using ::xsde::cxx::parser::validating::language_pskel;
  using ::xsde::cxx::parser::validating::language_pimpl;

  using ::xsde::cxx::parser::validating::id_pskel;
  using ::xsde::cxx::parser::validating::id_pimpl;

  using ::xsde::cxx::parser::validating::idref_pskel;
  using ::xsde::cxx::parser::validating::idref_pimpl;

  using ::xsde::cxx::parser::validating::idrefs_pskel;
  using ::xsde::cxx::parser::validating::idrefs_pimpl;

  using ::xsde::cxx::parser::validating::uri_pskel;
  using ::xsde::cxx::parser::validating::uri_pimpl;

  using ::xsde::cxx::parser::validating::qname_pskel;
  using ::xsde::cxx::parser::validating::qname_pimpl;

  using ::xsde::cxx::parser::validating::base64_binary_pskel;
  using ::xsde::cxx::parser::validating::base64_binary_pimpl;

  using ::xsde::cxx::parser::validating::hex_binary_pskel;
  using ::xsde::cxx::parser::validating::hex_binary_pimpl;

  using ::xsde::cxx::parser::validating::date_pskel;
  using ::xsde::cxx::parser::validating::date_pimpl;

  using ::xsde::cxx::parser::validating::date_time_pskel;
  using ::xsde::cxx::parser::validating::date_time_pimpl;

  using ::xsde::cxx::parser::validating::duration_pskel;
  using ::xsde::cxx::parser::validating::duration_pimpl;

  using ::xsde::cxx::parser::validating::gday_pskel;
  using ::xsde::cxx::parser::validating::gday_pimpl;

  using ::xsde::cxx::parser::validating::gmonth_pskel;
  using ::xsde::cxx::parser::validating::gmonth_pimpl;

  using ::xsde::cxx::parser::validating::gmonth_day_pskel;
  using ::xsde::cxx::parser::validating::gmonth_day_pimpl;

  using ::xsde::cxx::parser::validating::gyear_pskel;
  using ::xsde::cxx::parser::validating::gyear_pimpl;

  using ::xsde::cxx::parser::validating::gyear_month_pskel;
  using ::xsde::cxx::parser::validating::gyear_month_pimpl;

  using ::xsde::cxx::parser::validating::time_pskel;
  using ::xsde::cxx::parser::validating::time_pimpl;

  // Read-only string.
  //
  using ::xsde::cxx::ro_string;

  // Error codes.
  //
  typedef xsde::cxx::parser::expat::xml_error parser_xml_error;
  typedef xsde::cxx::schema_error parser_schema_error;

  // Exceptions.
  //
  typedef xsde::cxx::parser::exception parser_exception;
  typedef xsde::cxx::parser::xml parser_xml;
  typedef xsde::cxx::parser::schema parser_schema;

  // Document parser.
  //
  using xsde::cxx::parser::expat::document_pimpl;

  // Parser context.
  //
  typedef xsde::cxx::parser::context parser_context;
}

class vec3_type_pskel: public ::xsde::cxx::parser::validating::complex_content
{
  public:
  // Parser callbacks. Override them in your implementation.
  //
  // virtual void
  // pre ();

  // Attributes.
  //
  virtual void
  x (float);

  virtual void
  y (float);

  virtual void
  z (float);

  virtual ::vec3_type
  post_vec3_type () = 0;

  // Parser construction API.
  //
  void
  parsers (::xml_schema::float_pskel& /* x */,
           ::xml_schema::float_pskel& /* y */,
           ::xml_schema::float_pskel& /* z */);

  // Individual attribute parsers.
  //
  void
  x_parser (::xml_schema::float_pskel&);

  void
  y_parser (::xml_schema::float_pskel&);

  void
  z_parser (::xml_schema::float_pskel&);

  virtual void
  _reset ();

  // Constructor.
  //
  vec3_type_pskel ();

  // Implementation details.
  //
  protected:
  vec3_type_pskel* vec3_type_impl_;
  vec3_type_pskel (vec3_type_pskel*, void*);

  protected:
  virtual bool
  _attribute_impl_phase_one (const ::xsde::cxx::ro_string&,
                             const ::xsde::cxx::ro_string&,
                             const ::xsde::cxx::ro_string&);


  protected:
  ::xml_schema::float_pskel* x_parser_;
  ::xml_schema::float_pskel* y_parser_;
  ::xml_schema::float_pskel* z_parser_;

  protected:
  struct v_state_attr_
  {
    bool x;
    bool y;
    bool z;
  };

  v_state_attr_ v_state_attr_first_;
  ::xsde::cxx::stack v_state_attr_stack_;

  virtual void
  _pre_a_validate ();

  virtual void
  _post_a_validate ();
};

class vec4_type_pskel: public ::xsde::cxx::parser::validating::complex_content
{
  public:
  // Parser callbacks. Override them in your implementation.
  //
  // virtual void
  // pre ();

  // Attributes.
  //
  virtual void
  x (float);

  virtual void
  y (float);

  virtual void
  z (float);

  virtual void
  w (float);

  virtual ::vec4_type
  post_vec4_type () = 0;

  // Parser construction API.
  //
  void
  parsers (::xml_schema::float_pskel& /* x */,
           ::xml_schema::float_pskel& /* y */,
           ::xml_schema::float_pskel& /* z */,
           ::xml_schema::float_pskel& /* w */);

  // Individual attribute parsers.
  //
  void
  x_parser (::xml_schema::float_pskel&);

  void
  y_parser (::xml_schema::float_pskel&);

  void
  z_parser (::xml_schema::float_pskel&);

  void
  w_parser (::xml_schema::float_pskel&);

  virtual void
  _reset ();

  // Constructor.
  //
  vec4_type_pskel ();

  // Implementation details.
  //
  protected:
  vec4_type_pskel* vec4_type_impl_;
  vec4_type_pskel (vec4_type_pskel*, void*);

  protected:
  virtual bool
  _attribute_impl_phase_one (const ::xsde::cxx::ro_string&,
                             const ::xsde::cxx::ro_string&,
                             const ::xsde::cxx::ro_string&);


  protected:
  ::xml_schema::float_pskel* x_parser_;
  ::xml_schema::float_pskel* y_parser_;
  ::xml_schema::float_pskel* z_parser_;
  ::xml_schema::float_pskel* w_parser_;

  protected:
  struct v_state_attr_
  {
    bool x;
    bool y;
    bool z;
    bool w;
  };

  v_state_attr_ v_state_attr_first_;
  ::xsde::cxx::stack v_state_attr_stack_;

  virtual void
  _pre_a_validate ();

  virtual void
  _post_a_validate ();
};

class scene_graph_pskel: public ::xsde::cxx::parser::validating::complex_content
{
  public:
  // Parser callbacks. Override them in your implementation.
  //
  // virtual void
  // pre ();

  // Elements.
  //
  virtual void
  nodes (::nodes*);

  virtual void
  scenes (::scenes*);

  virtual ::scene_graph*
  post_scene_graph () = 0;

  // Parser construction API.
  //
  void
  parsers (::nodes_pskel& /* nodes */,
           ::scenes_pskel& /* scenes */);

  // Individual element parsers.
  //
  void
  nodes_parser (::nodes_pskel&);

  void
  scenes_parser (::scenes_pskel&);

  virtual void
  _reset ();

  // Constructor.
  //
  scene_graph_pskel ();

  // Implementation details.
  //
  protected:
  scene_graph_pskel* scene_graph_impl_;
  scene_graph_pskel (scene_graph_pskel*, void*);

  protected:
  virtual bool
  _start_element_impl (const ::xsde::cxx::ro_string&,
                       const ::xsde::cxx::ro_string&);

  virtual bool
  _end_element_impl (const ::xsde::cxx::ro_string&,
                     const ::xsde::cxx::ro_string&);

  protected:
  ::nodes_pskel* nodes_parser_;
  ::scenes_pskel* scenes_parser_;

  public:
  struct v_state_descr_
  {
    void (::scene_graph_pskel::*func) (
      unsigned long&,
      unsigned long&,
      const ::xsde::cxx::ro_string&,
      const ::xsde::cxx::ro_string&,
      bool);
    unsigned long state;
    unsigned long count;
  };

  struct v_state_
  {
    v_state_descr_ data[2UL];
    unsigned long size;
  };

  protected:
  v_state_ v_state_first_;
  ::xsde::cxx::stack v_state_stack_;

  virtual void
  _pre_e_validate ();

  virtual void
  _post_e_validate ();

  void
  sequence_0 (unsigned long&,
              unsigned long&,
              const ::xsde::cxx::ro_string&,
              const ::xsde::cxx::ro_string&,
              bool);
};

class nodes_pskel: public ::xsde::cxx::parser::validating::complex_content
{
  public:
  // Parser callbacks. Override them in your implementation.
  //
  // virtual void
  // pre ();

  // Elements.
  //
  virtual void
  node (::node*);

  virtual ::nodes*
  post_nodes () = 0;

  // Parser construction API.
  //
  void
  parsers (::node_pskel& /* node */);

  // Individual element parsers.
  //
  void
  node_parser (::node_pskel&);

  virtual void
  _reset ();

  // Constructor.
  //
  nodes_pskel ();

  // Implementation details.
  //
  protected:
  nodes_pskel* nodes_impl_;
  nodes_pskel (nodes_pskel*, void*);

  protected:
  virtual bool
  _start_element_impl (const ::xsde::cxx::ro_string&,
                       const ::xsde::cxx::ro_string&);

  virtual bool
  _end_element_impl (const ::xsde::cxx::ro_string&,
                     const ::xsde::cxx::ro_string&);

  protected:
  ::node_pskel* node_parser_;

  public:
  struct v_state_descr_
  {
    void (::nodes_pskel::*func) (
      unsigned long&,
      unsigned long&,
      const ::xsde::cxx::ro_string&,
      const ::xsde::cxx::ro_string&,
      bool);
    unsigned long state;
    unsigned long count;
  };

  struct v_state_
  {
    v_state_descr_ data[2UL];
    unsigned long size;
  };

  protected:
  v_state_ v_state_first_;
  ::xsde::cxx::stack v_state_stack_;

  virtual void
  _pre_e_validate ();

  virtual void
  _post_e_validate ();

  void
  sequence_0 (unsigned long&,
              unsigned long&,
              const ::xsde::cxx::ro_string&,
              const ::xsde::cxx::ro_string&,
              bool);
};

class scene_pskel: public ::xsde::cxx::parser::validating::complex_content
{
  public:
  // Parser callbacks. Override them in your implementation.
  //
  // virtual void
  // pre ();

  // Attributes.
  //
  virtual void
  name (const ::std::string&);

  virtual void
  graph (const ::std::string&);

  virtual ::scene
  post_scene () = 0;

  // Parser construction API.
  //
  void
  parsers (::xml_schema::token_pskel& /* name */,
           ::xml_schema::string_pskel& /* graph */);

  // Individual attribute parsers.
  //
  void
  name_parser (::xml_schema::token_pskel&);

  void
  graph_parser (::xml_schema::string_pskel&);

  virtual void
  _reset ();

  // Constructor.
  //
  scene_pskel ();

  // Implementation details.
  //
  protected:
  scene_pskel* scene_impl_;
  scene_pskel (scene_pskel*, void*);

  protected:
  virtual bool
  _attribute_impl_phase_one (const ::xsde::cxx::ro_string&,
                             const ::xsde::cxx::ro_string&,
                             const ::xsde::cxx::ro_string&);


  protected:
  ::xml_schema::token_pskel* name_parser_;
  ::xml_schema::string_pskel* graph_parser_;

  protected:
  struct v_state_attr_
  {
    bool name;
  };

  v_state_attr_ v_state_attr_first_;
  ::xsde::cxx::stack v_state_attr_stack_;

  virtual void
  _pre_a_validate ();

  virtual void
  _post_a_validate ();
};

class scenes_pskel: public ::xsde::cxx::parser::validating::complex_content
{
  public:
  // Parser callbacks. Override them in your implementation.
  //
  // virtual void
  // pre ();

  // Elements.
  //
  virtual void
  scene (const ::scene&);

  virtual ::scenes*
  post_scenes () = 0;

  // Parser construction API.
  //
  void
  parsers (::scene_pskel& /* scene */);

  // Individual element parsers.
  //
  void
  scene_parser (::scene_pskel&);

  virtual void
  _reset ();

  // Constructor.
  //
  scenes_pskel ();

  // Implementation details.
  //
  protected:
  scenes_pskel* scenes_impl_;
  scenes_pskel (scenes_pskel*, void*);

  protected:
  virtual bool
  _start_element_impl (const ::xsde::cxx::ro_string&,
                       const ::xsde::cxx::ro_string&);

  virtual bool
  _end_element_impl (const ::xsde::cxx::ro_string&,
                     const ::xsde::cxx::ro_string&);

  protected:
  ::scene_pskel* scene_parser_;

  public:
  struct v_state_descr_
  {
    void (::scenes_pskel::*func) (
      unsigned long&,
      unsigned long&,
      const ::xsde::cxx::ro_string&,
      const ::xsde::cxx::ro_string&,
      bool);
    unsigned long state;
    unsigned long count;
  };

  struct v_state_
  {
    v_state_descr_ data[2UL];
    unsigned long size;
  };

  protected:
  v_state_ v_state_first_;
  ::xsde::cxx::stack v_state_stack_;

  virtual void
  _pre_e_validate ();

  virtual void
  _post_e_validate ();

  void
  sequence_0 (unsigned long&,
              unsigned long&,
              const ::xsde::cxx::ro_string&,
              const ::xsde::cxx::ro_string&,
              bool);
};

class attribute_pskel: public ::xsde::cxx::parser::validating::complex_content
{
  public:
  // Parser callbacks. Override them in your implementation.
  //
  // virtual void
  // pre ();

  // Attributes.
  //
  virtual void
  name (const ::std::string&);

  virtual void
  value (const ::std::string&);

  virtual ::attribute
  post_attribute () = 0;

  // Parser construction API.
  //
  void
  parsers (::xml_schema::token_pskel& /* name */,
           ::xml_schema::string_pskel& /* value */);

  // Individual attribute parsers.
  //
  void
  name_parser (::xml_schema::token_pskel&);

  void
  value_parser (::xml_schema::string_pskel&);

  virtual void
  _reset ();

  // Constructor.
  //
  attribute_pskel ();

  // Implementation details.
  //
  protected:
  attribute_pskel* attribute_impl_;
  attribute_pskel (attribute_pskel*, void*);

  protected:
  virtual bool
  _attribute_impl_phase_one (const ::xsde::cxx::ro_string&,
                             const ::xsde::cxx::ro_string&,
                             const ::xsde::cxx::ro_string&);


  protected:
  ::xml_schema::token_pskel* name_parser_;
  ::xml_schema::string_pskel* value_parser_;
};

class node_pskel: public ::xsde::cxx::parser::validating::complex_content
{
  public:
  // Parser callbacks. Override them in your implementation.
  //
  // virtual void
  // pre ();

  // Attributes.
  //
  virtual void
  name (const ::std::string&);

  virtual void
  class_ (const ::std::string&);

  // Elements.
  //
  virtual void
  position (const ::vec3_type&);

  virtual void
  rotation (const ::vec4_type&);

  virtual void
  scale (const ::vec3_type&);

  virtual void
  attribute (const ::attribute&);

  virtual ::node*
  post_node () = 0;

  // Parser construction API.
  //
  void
  parsers (::xml_schema::token_pskel& /* name */,
           ::xml_schema::token_pskel& /* class */,
           ::vec3_type_pskel& /* position */,
           ::vec4_type_pskel& /* rotation */,
           ::vec3_type_pskel& /* scale */,
           ::attribute_pskel& /* attribute */);

  // Individual attribute parsers.
  //
  void
  name_parser (::xml_schema::token_pskel&);

  void
  class__parser (::xml_schema::token_pskel&);

  // Individual element parsers.
  //
  void
  position_parser (::vec3_type_pskel&);

  void
  rotation_parser (::vec4_type_pskel&);

  void
  scale_parser (::vec3_type_pskel&);

  void
  attribute_parser (::attribute_pskel&);

  virtual void
  _reset ();

  // Constructor.
  //
  node_pskel ();

  // Implementation details.
  //
  protected:
  node_pskel* node_impl_;
  node_pskel (node_pskel*, void*);

  protected:
  virtual bool
  _start_element_impl (const ::xsde::cxx::ro_string&,
                       const ::xsde::cxx::ro_string&);

  virtual bool
  _end_element_impl (const ::xsde::cxx::ro_string&,
                     const ::xsde::cxx::ro_string&);

  protected:
  virtual bool
  _attribute_impl_phase_one (const ::xsde::cxx::ro_string&,
                             const ::xsde::cxx::ro_string&,
                             const ::xsde::cxx::ro_string&);


  protected:
  ::xml_schema::token_pskel* name_parser_;
  ::xml_schema::token_pskel* class__parser_;
  ::vec3_type_pskel* position_parser_;
  ::vec4_type_pskel* rotation_parser_;
  ::vec3_type_pskel* scale_parser_;
  ::attribute_pskel* attribute_parser_;

  public:
  struct v_state_descr_
  {
    void (::node_pskel::*func) (
      unsigned long&,
      unsigned long&,
      const ::xsde::cxx::ro_string&,
      const ::xsde::cxx::ro_string&,
      bool);
    unsigned long state;
    unsigned long count;
  };

  struct v_state_
  {
    v_state_descr_ data[2UL];
    unsigned long size;
  };

  protected:
  v_state_ v_state_first_;
  ::xsde::cxx::stack v_state_stack_;

  virtual void
  _pre_e_validate ();

  virtual void
  _post_e_validate ();

  void
  sequence_0 (unsigned long&,
              unsigned long&,
              const ::xsde::cxx::ro_string&,
              const ::xsde::cxx::ro_string&,
              bool);

  protected:
  struct v_state_attr_
  {
    bool name;
    bool class_;
  };

  v_state_attr_ v_state_attr_first_;
  ::xsde::cxx::stack v_state_attr_stack_;

  virtual void
  _pre_a_validate ();

  virtual void
  _post_a_validate ();
};

// Begin epilogue.
//
//
// End epilogue.

#include <xsde/cxx/post.hxx>

#endif // E__VS14PRJBKP_ENGINE_SCENE_SCENE_PSKEL_HXX