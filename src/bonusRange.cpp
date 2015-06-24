//
// bonusRange.cpp for bonusRange in /home/tack_g/rendu/cpp_bomberman
//
// Made by g tack
// Login   <tack_g@epitech.net>
//
// Started on  Tue Jun  9 13:21:30 2015 g tack
// Last update Sun Jun 14 15:28:20 2015 Emeline Gaulard
//

#include "bonusRange.hh"
#include "Player.hh"

bonusRange::bonusRange()
  : ABonus(),
    _time()
{
  if (!this->setTexture("bonus.tga"))
    throw std::runtime_error("Failed to set texture for bonusBomb");
  this->setSize(15.f, 15.f, 15.f);
  _type = BONUSRANGE;
}

bonusRange::bonusRange(unsigned int x, unsigned int y)
  : ABonus(x, y),
    _time()
{
  if (!this->setTexture("crate.tga"))
    throw std::runtime_error("Failed to set texture for bonusBomb");
  this->setSize(15.f, 15.f, 15.f);
  _type = BONUSRANGE;
}

bonusRange::~bonusRange()
{
}

void bonusRange::walkOnBonus(Player *p) const
{
  p->addRange();
  ResourceManager::GetInstance()->PlaySound(1);
}
