//
// Bomb.cpp for Bomb in /home/tack_g/rendu/cpp_bomberman
//
// Made by g tack
// Login   <tack_g@epitech.net>
//
// Started on  Tue May 19 12:16:03 2015 g tack
// Last update Sat Jun 13 17:34:56 2015 Emeline Gaulard
//

#include <stdexcept>
#include "Bomb.hh"
#include "Player.hh"

Bomb::Bomb(Player *p, unsigned int range) :
  Cube(), ATimeEntity(), IMapEntity(),
  _play(p), _play2(p), _range(range), _time()
{
  if (!this->setTexture("bomb.tga"))
    throw std::runtime_error("Failed to set texture for bomb");
  this->setSize(30.f, 30.f, 30.f);
}

Bomb::Bomb(unsigned int range, unsigned int x, unsigned int y) :
  Cube(x * 30.f, 0.f, y * 30.f), ATimeEntity(), IMapEntity(),
  _play(0), _play2(0), _range(range), _time()
{

}


#include <iostream>
Bomb::~Bomb()
{
  if (_play2)
    _play2->addBomb();
}

unsigned int	Bomb::getCellX() const
{
  return (this->_x / 30.f);
}

unsigned int	Bomb::getCellY() const
{
  return (this->_z / 30.f);
}

unsigned int	Bomb::getRange() const
{
  return (this->_range);
}

void		Bomb::draw(const Time &t) const
{
  if (this->_time <= Time())
    Cube::draw(t);
}

Player		*Bomb::getPlayer()
{
  return (this->_play);
}

void		Bomb::reSetPlayer(Player *p)
{
  this->_play = p;
}

