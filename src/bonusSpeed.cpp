//
// bonusSpeed.cpp for bonusSpeed in /home/tack_g/rendu/cpp_bomberman
//
// Made by g tack
// Login   <tack_g@epitech.net>
//
// Started on  Tue Jun  9 13:21:41 2015 g tack
// Last update Sun Jun 14 15:28:12 2015 Emeline Gaulard
//

#include "bonusSpeed.hh"
#include "Player.hh"

bonusSpeed::bonusSpeed()
  : ABonus(),
    _time()
{
  if (!this->setTexture("bonus.tga"))
    throw std::runtime_error("Failed to set texture for bonusBomb");
  this->setSize(15.f, 15.f, 15.f);
  _type = BONUSSPEED;
}

bonusSpeed::bonusSpeed(unsigned int x, unsigned int y)
  : ABonus(x, y),
    _time()
{
  if (!this->setTexture("crate.tga"))
    throw std::runtime_error("Failed to set texture for bonusBomb");
  this->setSize(15.f, 15.f, 15.f);
  _type = BONUSSPEED;
}

bonusSpeed::~bonusSpeed()
{
}

void	bonusSpeed::walkOnBonus(Player *p) const
{
  p->addSpeed();
  ResourceManager::GetInstance()->PlaySound(1);
}
