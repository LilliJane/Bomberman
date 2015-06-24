//
// ADrawable.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Fri May 15 02:40:42 2015 _p dumont
// Last update Fri May 15 02:40:42 2015 _p dumont
//

#include "ADrawable.hh"

ADrawable::ADrawable(float x, float y, float z)
{
  this->_x = x;
  this->_y = y;
  this->_z = z;
}

ADrawable::ADrawable(ADrawable const &ref)
{
  this->_x = ref._x;
  this->_y = ref._y;
  this->_z = ref._z;
}

ADrawable	&ADrawable::operator =(ADrawable const &ref)
{
  this->_x = ref._x;
  this->_y = ref._y;
  this->_z = ref._z;
  return (*this);
}

ADrawable::~ADrawable()
{

}

void	ADrawable::move(float x, float y, float z)
{
  this->_x = x;
  this->_y = y;
  this->_z = z;
}

float	ADrawable::getX() const
{
  return (this->_x);
}

float	ADrawable::getY() const
{
  return (this->_y);
}

float	ADrawable::getZ() const
{
  return (this->_z);
}
