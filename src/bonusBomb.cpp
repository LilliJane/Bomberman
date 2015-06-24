//
// bonusBomb.cpp for bonusBomb in /home/tack_g/rendu/cpp_bomberman
//
// Made by g tack
// Login   <tack_g@epitech.net>
//
// Started on  Tue Jun  9 13:21:35 2015 g tack
// Last update Sun Jun 14 15:28:04 2015 Emeline Gaulard
//

#include "bonusBomb.hh"
#include "Player.hh"

bonusBomb::bonusBomb()
  : ABonus(), _time()
{
  if (!this->setTexture("bonus.tga"))
    throw std::runtime_error("Failed to set texture for bonusBomb");
  this->setSize(15.f, 15.f, 15.f);
  _type = BONUSBOMB;
}

bonusBomb::bonusBomb(unsigned int x, unsigned int y) :
  ABonus(x, y), _time()
{
  if (!this->setTexture("crate.tga"))
    throw std::runtime_error("Failed to set texture for bonusBomb");
  this->setSize(15.f, 15.f, 15.f);
  _type = BONUSBOMB;
}

bonusBomb::~bonusBomb()
{
}

void bonusBomb::walkOnBonus(Player *p) const
{
  ResourceManager::GetInstance()->PlaySound(1);
  p->addNbBomb();
}

void bonusBomb::draw(const Time &t) const
{
  if (this->_time <= Time())
    Cube::draw(t);
}
