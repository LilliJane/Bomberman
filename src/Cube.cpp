//
// Cube.cpp for  in /home/sabour_f/rendu/cpp_bomberman/src
//
// Made by Florian SABOURIN
// Login   <sabour_f@epitech.net>
//
// Started on  Wed May 27 10:07:34 2015 Florian SABOURIN
// Last update Wed May 27 10:07:39 2015 Florian SABOURIN
//

#include <stdexcept>
#include "Cube.hh"
#include "OpenGL.hh"

gdl::Geometry	Cube::_base_geometry;
bool		Cube::_is_geometry_init = false;

Cube::Cube() :
  ADrawable(),
  _txid(0),
  _w(1.f), _h(1.f), _d(1.f),
  _matrix(1.f)
{
  this->checkGeometry();
  this->updateMatrix();
}

Cube::Cube(float x, float y, float z) :
  ADrawable(x, y, z),
  _txid(0),
  _w(1.f), _h(1.f), _d(1.f),
  _matrix(1.f)
{
  this->checkGeometry();
  this->updateMatrix();
}

Cube::Cube(float x, float y, float z,
	   float w, float h, float d) :
  ADrawable(x, y, z),
  _txid(0),
  _w(w), _h(h), _d(d),
  _matrix(1.f)
{
  this->checkGeometry();
  this->updateMatrix();
}

Cube::~Cube()
{
}

/*
** Attach a texture to the cube
** Mandatory for drawing
** = true on success, false otherwise
*/
bool		Cube::setTexture(const std::string &name)
{
  id_t		id;

  id = ResourceManager::GetInstance()->LoadTexture(name);
  if (!id)
    return (false);
  this->_txid = id;
  return (true);
}

/*
** Sets the position of the cube
** Automatically updates the matrix
*/
void		Cube::move(float x, float y, float z)
{
  ADrawable::move(x, y, z);
  this->updateMatrix();
}

void		Cube::setSize(float w, float h, float d)
{
  this->_w = w;
  this->_h = h;
  this->_d = d;
  this->updateMatrix();
}

float		Cube::getWidth() const
{
  return (this->_w);
}
float		Cube::getHeight() const
{
  return (this->_h);
}
float		Cube::getDepth() const
{
  return (this->_d);
}
id_t		Cube::getTxid() const
{
  return (this->_txid);
}

void		Cube::bindTx() const
{
  ResourceManager::GetInstance()->GetTexture(this->_txid).bind();
}

/*
** Draws the cube
** Does nothing if no texture was set
** May throw std::out_of_range if texture was deleted in the meantime
*/
void			Cube::draw(Time const &time) const
{
  (void)time;
  if (this->_txid)
    _base_geometry.draw(ResourceManager::GetInstance()->GetShader(),
			this->_matrix,
			GL_QUADS);
}

/*
** Updates the matrix of the cube (sets position + scale)
*/
void		Cube::updateMatrix()
{
  glm::mat4	mat(1.f);

  mat = glm::translate(mat, glm::vec3(-this->_x, -this->_y, -this->_z));
  mat = glm::scale(mat, glm::vec3(this->_w, this->_h, this->_d));
  this->_matrix = mat;
}

/*
** Checks if the gdl::Geometry associated with any cube has been built or not
** If not, it is built
** It's a (1;1;1) size cube in (0;0;0)
*/
void		Cube::checkGeometry()
{
  if (!_is_geometry_init)
    {
      _base_geometry.pushUv(glm::vec2(0.f, 0.f));
      _base_geometry.pushUv(glm::vec2(0.f, 1.f));
      _base_geometry.pushUv(glm::vec2(1.f, 1.f));
      _base_geometry.pushUv(glm::vec2(1.f, 0.f));
      _base_geometry.pushVertex(glm::vec3(0.f,	0.f,	-1.f));
      _base_geometry.pushVertex(glm::vec3(-1.f,	0.f,	-1.f));
      _base_geometry.pushVertex(glm::vec3(-1.f,	1.f,	-1.f));
      _base_geometry.pushVertex(glm::vec3(0.f,	1.f,	-1.f));

      _base_geometry.pushUv(glm::vec2(0.f, 0.f));
      _base_geometry.pushUv(glm::vec2(0.f, 1.f));
      _base_geometry.pushUv(glm::vec2(1.f, 1.f));
      _base_geometry.pushUv(glm::vec2(1.f, 0.f));
      _base_geometry.pushVertex(glm::vec3(0.f,	0.f,	0.f));
      _base_geometry.pushVertex(glm::vec3(-1.f,	0.f,	0.f));
      _base_geometry.pushVertex(glm::vec3(-1.f,	1.f,	0.f));
      _base_geometry.pushVertex(glm::vec3(0.f,	1.f,	0.f));

      _base_geometry.pushUv(glm::vec2(0.f, 0.f));
      _base_geometry.pushUv(glm::vec2(0.f, 1.f));
      _base_geometry.pushUv(glm::vec2(1.f, 1.f));
      _base_geometry.pushUv(glm::vec2(1.f, 0.f));
      _base_geometry.pushVertex(glm::vec3(-1.f,	0.f,	0.f));
      _base_geometry.pushVertex(glm::vec3(-1.f,	0.f,	-1.f));
      _base_geometry.pushVertex(glm::vec3(-1.f,	1.f,	-1.f));
      _base_geometry.pushVertex(glm::vec3(-1.f,	1.f,	0.f));

      _base_geometry.pushUv(glm::vec2(0.f, 0.f));
      _base_geometry.pushUv(glm::vec2(0.f, 1.f));
      _base_geometry.pushUv(glm::vec2(1.f, 1.f));
      _base_geometry.pushUv(glm::vec2(1.f, 0.f));
      _base_geometry.pushVertex(glm::vec3(0.f,	0.f,	0.f));
      _base_geometry.pushVertex(glm::vec3(0.f,	0.f,	-1.f));
      _base_geometry.pushVertex(glm::vec3(0.f,	1.f,	-1.f));
      _base_geometry.pushVertex(glm::vec3(0.f,	1.f,	0.f));

      _base_geometry.pushUv(glm::vec2(0.f, 0.f));
      _base_geometry.pushUv(glm::vec2(0.f, 1.f));
      _base_geometry.pushUv(glm::vec2(1.f, 1.f));
      _base_geometry.pushUv(glm::vec2(1.f, 0.f));
      _base_geometry.pushVertex(glm::vec3(0.f,	1.f,	0.f));
      _base_geometry.pushVertex(glm::vec3(0.f,	1.f,	-1.f));
      _base_geometry.pushVertex(glm::vec3(-1.f,	1.f,	-1.f));
      _base_geometry.pushVertex(glm::vec3(-1.f,	1.f,	0.f));

      _base_geometry.pushUv(glm::vec2(0.f, 0.f));
      _base_geometry.pushUv(glm::vec2(0.f, 1.f));
      _base_geometry.pushUv(glm::vec2(1.f, 1.f));
      _base_geometry.pushUv(glm::vec2(1.f, 0.f));
      _base_geometry.pushVertex(glm::vec3(0.f,	0.f,	0.f));
      _base_geometry.pushVertex(glm::vec3(0.f,	0.f,	-1.f));
      _base_geometry.pushVertex(glm::vec3(-1.f,	0.f,	-1.f));
      _base_geometry.pushVertex(glm::vec3(-1.f,	0.f,	0.f));

      if (!_base_geometry.build())
	throw std::runtime_error("Cannot build cube geometry");
      _is_geometry_init = true;
    }
}
