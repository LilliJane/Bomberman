//
// bonusGPS.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Sun Jun 14 15:52:26 2015 _p dumont
// Last update Sun Jun 14 15:52:27 2015 _p dumont
//

#include "bonusGPS.hh"
#include "Player.hh"

#include <iostream>
bonusGPS::bonusGPS()
  : ABonus(), _time()
{
  if (!this->setTexture("bonus.tga"))
    throw std::runtime_error("Failed to set texture for bonusBomb");
  this->setSize(15.f, 15.f, 15.f);
  _type = BONUSGPS;
}

bonusGPS::bonusGPS(unsigned int x, unsigned int y) :
  ABonus(x, y), _time()
{
  if (!this->setTexture("crate.tga"))
    throw std::runtime_error("Failed to set texture for bonusBomb");
  this->setSize(15.f, 15.f, 15.f);
  _type = BONUSGPS;
}

bonusGPS::~bonusGPS()
{
}

void bonusGPS::walkOnBonus(Player *p) const
{
  p->setGPS(true);
}

void bonusGPS::draw(const Time &t) const
{
  if (this->_time <= Time())
    Cube::draw(t);
}
