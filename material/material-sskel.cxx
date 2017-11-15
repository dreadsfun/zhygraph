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

// Begin prologue.
//
//
// End prologue.

#include "material-sskel.hxx"

// materials_sskel
//

void materials_sskel::
material_serializer (::material_sskel& s)
{
  this->material_serializer_ = &s;
}

void materials_sskel::
serializers (::material_sskel& material)
{
  this->material_serializer_ = &material;
}

materials_sskel::
materials_sskel ()
: materials_impl_ (0),
  material_serializer_ (0)
{
}

materials_sskel::
materials_sskel (materials_sskel* impl, void*)
: ::xsde::cxx::serializer::validating::complex_content (impl, 0),
  materials_impl_ (impl),
  material_serializer_ (0)
{
}

// vector_sskel
//

void vector_sskel::
uniform_serializer (::xml_schema::string_sskel& uniform)
{
  this->uniform_serializer_ = &uniform;
}

void vector_sskel::
x_serializer (::xml_schema::float_sskel& x)
{
  this->x_serializer_ = &x;
}

void vector_sskel::
y_serializer (::xml_schema::float_sskel& y)
{
  this->y_serializer_ = &y;
}

void vector_sskel::
z_serializer (::xml_schema::float_sskel& z)
{
  this->z_serializer_ = &z;
}

void vector_sskel::
w_serializer (::xml_schema::float_sskel& w)
{
  this->w_serializer_ = &w;
}

void vector_sskel::
serializers (::xml_schema::string_sskel& uniform,
             ::xml_schema::float_sskel& x,
             ::xml_schema::float_sskel& y,
             ::xml_schema::float_sskel& z,
             ::xml_schema::float_sskel& w)
{
  this->uniform_serializer_ = &uniform;
  this->x_serializer_ = &x;
  this->y_serializer_ = &y;
  this->z_serializer_ = &z;
  this->w_serializer_ = &w;
}

vector_sskel::
vector_sskel ()
: vector_impl_ (0),
  uniform_serializer_ (0),
  x_serializer_ (0),
  y_serializer_ (0),
  z_serializer_ (0),
  w_serializer_ (0)
{
}

vector_sskel::
vector_sskel (vector_sskel* impl, void*)
: ::xsde::cxx::serializer::validating::complex_content (impl, 0),
  vector_impl_ (impl),
  uniform_serializer_ (0),
  x_serializer_ (0),
  y_serializer_ (0),
  z_serializer_ (0),
  w_serializer_ (0)
{
}

// shader_sskel
//

void shader_sskel::
file_serializer (::xml_schema::string_sskel& file)
{
  this->file_serializer_ = &file;
}

void shader_sskel::
serializers (::xml_schema::string_sskel& file)
{
  this->file_serializer_ = &file;
}

shader_sskel::
shader_sskel ()
: shader_impl_ (0),
  file_serializer_ (0)
{
}

shader_sskel::
shader_sskel (shader_sskel* impl, void*)
: ::xsde::cxx::serializer::validating::complex_content (impl, 0),
  shader_impl_ (impl),
  file_serializer_ (0)
{
}

// texture_sskel
//

void texture_sskel::
sampler_serializer (::xml_schema::string_sskel& sampler)
{
  this->sampler_serializer_ = &sampler;
}

void texture_sskel::
file_serializer (::xml_schema::string_sskel& file)
{
  this->file_serializer_ = &file;
}

void texture_sskel::
serializers (::xml_schema::string_sskel& sampler,
             ::xml_schema::string_sskel& file)
{
  this->sampler_serializer_ = &sampler;
  this->file_serializer_ = &file;
}

texture_sskel::
texture_sskel ()
: texture_impl_ (0),
  sampler_serializer_ (0),
  file_serializer_ (0)
{
}

texture_sskel::
texture_sskel (texture_sskel* impl, void*)
: ::xsde::cxx::serializer::validating::complex_content (impl, 0),
  texture_impl_ (impl),
  sampler_serializer_ (0),
  file_serializer_ (0)
{
}

// material_sskel
//

void material_sskel::
name_serializer (::xml_schema::string_sskel& name)
{
  this->name_serializer_ = &name;
}

void material_sskel::
shader_serializer (::shader_sskel& s)
{
  this->shader_serializer_ = &s;
}

void material_sskel::
texture_serializer (::texture_sskel& s)
{
  this->texture_serializer_ = &s;
}

void material_sskel::
vector_serializer (::vector_sskel& s)
{
  this->vector_serializer_ = &s;
}

void material_sskel::
serializers (::xml_schema::string_sskel& name,
             ::shader_sskel& shader,
             ::texture_sskel& texture,
             ::vector_sskel& vector)
{
  this->name_serializer_ = &name;
  this->shader_serializer_ = &shader;
  this->texture_serializer_ = &texture;
  this->vector_serializer_ = &vector;
}

material_sskel::
material_sskel ()
: material_impl_ (0),
  name_serializer_ (0),
  shader_serializer_ (0),
  texture_serializer_ (0),
  vector_serializer_ (0)
{
}

material_sskel::
material_sskel (material_sskel* impl, void*)
: ::xsde::cxx::serializer::validating::complex_content (impl, 0),
  material_impl_ (impl),
  name_serializer_ (0),
  shader_serializer_ (0),
  texture_serializer_ (0),
  vector_serializer_ (0)
{
}

#include <assert.h>

// materials_sskel
//

bool materials_sskel::
material_next ()
{
  return this->materials_impl_ ? this->materials_impl_->material_next () : false;
}

void materials_sskel::
_reset ()
{
  if (this->resetting_)
    return;

  typedef ::xsde::cxx::serializer::validating::complex_content base;
  base::_reset ();

  this->resetting_ = true;

  if (this->material_serializer_)
    this->material_serializer_->_reset ();

  this->resetting_ = false;
}

// vector_sskel
//

bool vector_sskel::
y_present ()
{
  return this->vector_impl_ ? this->vector_impl_->y_present () : false;
}

bool vector_sskel::
z_present ()
{
  return this->vector_impl_ ? this->vector_impl_->z_present () : false;
}

bool vector_sskel::
w_present ()
{
  return this->vector_impl_ ? this->vector_impl_->w_present () : false;
}

void vector_sskel::
_reset ()
{
  typedef ::xsde::cxx::serializer::validating::complex_content base;
  base::_reset ();

  if (this->uniform_serializer_)
    this->uniform_serializer_->_reset ();

  if (this->x_serializer_)
    this->x_serializer_->_reset ();

  if (this->y_serializer_)
    this->y_serializer_->_reset ();

  if (this->z_serializer_)
    this->z_serializer_->_reset ();

  if (this->w_serializer_)
    this->w_serializer_->_reset ();
}

// shader_sskel
//

void shader_sskel::
_reset ()
{
  typedef ::xsde::cxx::serializer::validating::complex_content base;
  base::_reset ();

  if (this->file_serializer_)
    this->file_serializer_->_reset ();
}

// texture_sskel
//

void texture_sskel::
_reset ()
{
  typedef ::xsde::cxx::serializer::validating::complex_content base;
  base::_reset ();

  if (this->sampler_serializer_)
    this->sampler_serializer_->_reset ();

  if (this->file_serializer_)
    this->file_serializer_->_reset ();
}

// material_sskel
//

bool material_sskel::
texture_next ()
{
  return this->material_impl_ ? this->material_impl_->texture_next () : false;
}

bool material_sskel::
vector_next ()
{
  return this->material_impl_ ? this->material_impl_->vector_next () : false;
}

void material_sskel::
_reset ()
{
  if (this->resetting_)
    return;

  typedef ::xsde::cxx::serializer::validating::complex_content base;
  base::_reset ();

  if (this->name_serializer_)
    this->name_serializer_->_reset ();

  this->resetting_ = true;

  if (this->shader_serializer_)
    this->shader_serializer_->_reset ();

  if (this->texture_serializer_)
    this->texture_serializer_->_reset ();

  if (this->vector_serializer_)
    this->vector_serializer_->_reset ();

  this->resetting_ = false;
}

// Element validation and serialization for materials_sskel.
//
void materials_sskel::
_serialize_content ()
{
  ::xsde::cxx::serializer::context& ctx = this->_context ();

  // material
  //
  while (this->material_next ())
  {
    const ::material& r = this->material ();

    if (this->material_serializer_)
    {
      this->material_serializer_->pre (r);
      this->_start_element ("material");
      this->material_serializer_->_pre_impl (ctx);

      if (ctx.error_type ())
        return;

      this->material_serializer_->_serialize_attributes ();

      if (ctx.error_type ())
        return;

      this->material_serializer_->_serialize_content ();

      if (ctx.error_type ())
        return;

      this->material_serializer_->_post_impl ();

      if (ctx.error_type ())
        return;

      this->_end_element ();
      this->material_serializer_->post ();
    }
  }
}

// Element validation and serialization for material_sskel.
//
void material_sskel::
_serialize_content ()
{
  ::xsde::cxx::serializer::context& ctx = this->_context ();

  // shader
  //
  {
    const ::shader& r = this->shader ();

    if (this->shader_serializer_)
    {
      this->shader_serializer_->pre (r);
      this->_start_element ("shader");
      this->shader_serializer_->_pre_impl (ctx);

      if (ctx.error_type ())
        return;

      this->shader_serializer_->_serialize_attributes ();

      if (ctx.error_type ())
        return;

      this->shader_serializer_->_serialize_content ();

      if (ctx.error_type ())
        return;

      this->shader_serializer_->_post_impl ();

      if (ctx.error_type ())
        return;

      this->_end_element ();
      this->shader_serializer_->post ();
    }
    else
    {
      this->_schema_error (::xsde::cxx::schema_error::expected_element);
      return;
    }
  }

  // texture
  //
  while (this->texture_next ())
  {
    const ::texture& r = this->texture ();

    if (this->texture_serializer_)
    {
      this->texture_serializer_->pre (r);
      this->_start_element ("texture");
      this->texture_serializer_->_pre_impl (ctx);

      if (ctx.error_type ())
        return;

      this->texture_serializer_->_serialize_attributes ();

      if (ctx.error_type ())
        return;

      this->texture_serializer_->_serialize_content ();

      if (ctx.error_type ())
        return;

      this->texture_serializer_->_post_impl ();

      if (ctx.error_type ())
        return;

      this->_end_element ();
      this->texture_serializer_->post ();
    }
  }

  // vector
  //
  while (this->vector_next ())
  {
    const ::vector& r = this->vector ();

    if (this->vector_serializer_)
    {
      this->vector_serializer_->pre (r);
      this->_start_element ("vector");
      this->vector_serializer_->_pre_impl (ctx);

      if (ctx.error_type ())
        return;

      this->vector_serializer_->_serialize_attributes ();

      if (ctx.error_type ())
        return;

      this->vector_serializer_->_serialize_content ();

      if (ctx.error_type ())
        return;

      this->vector_serializer_->_post_impl ();

      if (ctx.error_type ())
        return;

      this->_end_element ();
      this->vector_serializer_->post ();
    }
  }
}

// Attribute validation and serialization for vector_sskel.
//
void vector_sskel::
_serialize_attributes ()
{
  ::xsde::cxx::serializer::context& ctx = this->_context ();

  // uniform
  //
  {
    const ::std::string& r = this->uniform ();

    if (this->uniform_serializer_)
    {
      this->uniform_serializer_->pre (r);
      this->_start_attribute ("uniform");
      this->uniform_serializer_->_pre_impl (ctx);

      if (ctx.error_type ())
        return;

      this->uniform_serializer_->_serialize_content ();

      if (ctx.error_type ())
        return;

      this->uniform_serializer_->_post_impl ();

      if (ctx.error_type ())
        return;

      this->_end_attribute ();
      this->uniform_serializer_->post ();
    }
    else
    {
      this->_schema_error (::xsde::cxx::schema_error::expected_attribute);
      return;
    }
  }

  // x
  //
  {
    float r = this->x ();

    if (this->x_serializer_)
    {
      this->x_serializer_->pre (r);
      this->_start_attribute ("x");
      this->x_serializer_->_pre_impl (ctx);

      if (ctx.error_type ())
        return;

      this->x_serializer_->_serialize_content ();

      if (ctx.error_type ())
        return;

      this->x_serializer_->_post_impl ();

      if (ctx.error_type ())
        return;

      this->_end_attribute ();
      this->x_serializer_->post ();
    }
    else
    {
      this->_schema_error (::xsde::cxx::schema_error::expected_attribute);
      return;
    }
  }

  // y
  //
  if (this->y_present ())
  {
    float r = this->y ();

    if (this->y_serializer_)
    {
      this->y_serializer_->pre (r);
      this->_start_attribute ("y");
      this->y_serializer_->_pre_impl (ctx);

      if (ctx.error_type ())
        return;

      this->y_serializer_->_serialize_content ();

      if (ctx.error_type ())
        return;

      this->y_serializer_->_post_impl ();

      if (ctx.error_type ())
        return;

      this->_end_attribute ();
      this->y_serializer_->post ();
    }
  }

  // z
  //
  if (this->z_present ())
  {
    float r = this->z ();

    if (this->z_serializer_)
    {
      this->z_serializer_->pre (r);
      this->_start_attribute ("z");
      this->z_serializer_->_pre_impl (ctx);

      if (ctx.error_type ())
        return;

      this->z_serializer_->_serialize_content ();

      if (ctx.error_type ())
        return;

      this->z_serializer_->_post_impl ();

      if (ctx.error_type ())
        return;

      this->_end_attribute ();
      this->z_serializer_->post ();
    }
  }

  // w
  //
  if (this->w_present ())
  {
    float r = this->w ();

    if (this->w_serializer_)
    {
      this->w_serializer_->pre (r);
      this->_start_attribute ("w");
      this->w_serializer_->_pre_impl (ctx);

      if (ctx.error_type ())
        return;

      this->w_serializer_->_serialize_content ();

      if (ctx.error_type ())
        return;

      this->w_serializer_->_post_impl ();

      if (ctx.error_type ())
        return;

      this->_end_attribute ();
      this->w_serializer_->post ();
    }
  }
}

// Attribute validation and serialization for shader_sskel.
//
void shader_sskel::
_serialize_attributes ()
{
  ::xsde::cxx::serializer::context& ctx = this->_context ();

  // file
  //
  {
    const ::std::string& r = this->file ();

    if (this->file_serializer_)
    {
      this->file_serializer_->pre (r);
      this->_start_attribute ("file");
      this->file_serializer_->_pre_impl (ctx);

      if (ctx.error_type ())
        return;

      this->file_serializer_->_serialize_content ();

      if (ctx.error_type ())
        return;

      this->file_serializer_->_post_impl ();

      if (ctx.error_type ())
        return;

      this->_end_attribute ();
      this->file_serializer_->post ();
    }
    else
    {
      this->_schema_error (::xsde::cxx::schema_error::expected_attribute);
      return;
    }
  }
}

// Attribute validation and serialization for texture_sskel.
//
void texture_sskel::
_serialize_attributes ()
{
  ::xsde::cxx::serializer::context& ctx = this->_context ();

  // sampler
  //
  {
    const ::std::string& r = this->sampler ();

    if (this->sampler_serializer_)
    {
      this->sampler_serializer_->pre (r);
      this->_start_attribute ("sampler");
      this->sampler_serializer_->_pre_impl (ctx);

      if (ctx.error_type ())
        return;

      this->sampler_serializer_->_serialize_content ();

      if (ctx.error_type ())
        return;

      this->sampler_serializer_->_post_impl ();

      if (ctx.error_type ())
        return;

      this->_end_attribute ();
      this->sampler_serializer_->post ();
    }
    else
    {
      this->_schema_error (::xsde::cxx::schema_error::expected_attribute);
      return;
    }
  }

  // file
  //
  {
    const ::std::string& r = this->file ();

    if (this->file_serializer_)
    {
      this->file_serializer_->pre (r);
      this->_start_attribute ("file");
      this->file_serializer_->_pre_impl (ctx);

      if (ctx.error_type ())
        return;

      this->file_serializer_->_serialize_content ();

      if (ctx.error_type ())
        return;

      this->file_serializer_->_post_impl ();

      if (ctx.error_type ())
        return;

      this->_end_attribute ();
      this->file_serializer_->post ();
    }
    else
    {
      this->_schema_error (::xsde::cxx::schema_error::expected_attribute);
      return;
    }
  }
}

// Attribute validation and serialization for material_sskel.
//
void material_sskel::
_serialize_attributes ()
{
  ::xsde::cxx::serializer::context& ctx = this->_context ();

  // name
  //
  {
    const ::std::string& r = this->name ();

    if (this->name_serializer_)
    {
      this->name_serializer_->pre (r);
      this->_start_attribute ("name");
      this->name_serializer_->_pre_impl (ctx);

      if (ctx.error_type ())
        return;

      this->name_serializer_->_serialize_content ();

      if (ctx.error_type ())
        return;

      this->name_serializer_->_post_impl ();

      if (ctx.error_type ())
        return;

      this->_end_attribute ();
      this->name_serializer_->post ();
    }
    else
    {
      this->_schema_error (::xsde::cxx::schema_error::expected_attribute);
      return;
    }
  }
}

// Begin epilogue.
//
//
// End epilogue.
