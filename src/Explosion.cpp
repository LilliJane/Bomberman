//
// Explosion.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Tue Jun  2 23:32:58 2015 _p dumont
// Last update Tue Jun  2 23:32:58 2015 _p dumont
//

#include <stdexcept>
#include "Explosion.hh"

Explosion::Explosion() :
  Cube(), ATimeEntity(), IMapEntity(),
  _time()
{
  if (!this->setTexture("explo.tga"))
    throw std::runtime_error("Failed to set texture for explosion");
  this->setSize(30.f, 30.f, 30.f);
}

#include <iostream>
Explosion::~Explosion()
{
  //std::cout << "Kaboooom !" << std::endl;
}

void		Explosion::draw(const Time &t) const
{
  if (this->_time <= Time())
    Cube::draw(t);
}

unsigned int	Explosion::getCellX() const
{
  return (this->_x / 30.f);
}

unsigned int Explosion::getCellY() const
{
  return (this->_y / 30.f);
}
