//
// IBonus.cpp for IBonus in /home/tack_g/rendu/cpp_bomberman
//
// Made by g tack
// Login   <tack_g@epitech.net>
//
// Started on  Tue Jun  9 14:18:07 2015 g tack
// Last update Sun Jun 14 15:27:55 2015 Emeline Gaulard
//

#include "ABonus.hh"

ABonus::ABonus()
  : Cube(), ATimeEntity(), IMapEntity()
{
}

ABonus::ABonus(unsigned int x, unsigned int y)
  : Cube(x * 30.f, 0.f, y * 30.f), ATimeEntity(), IMapEntity()
{
  
}

ABonus::~ABonus()
{
}

unsigned int ABonus::getCellX() const
{
  return (this->_x / 30.f);
}

unsigned int ABonus::getCellY() const
{
  return (this->_z / 30.f);
}

int	ABonus::getType() const
{
  return (_type);
}
