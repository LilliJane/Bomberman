//
// KeyConf.cpp for KeyConf in /home/tack_g/rendu/cpp_bomberman
//
// Made by g tack
// Login   <tack_g@epitech.net>
//
// Started on  Tue May 19 19:58:41 2015 g tack
// Last update Tue May 19 19:58:41 2015 g tack
//

#include "KeyConf.hh"
#include <iostream>
KeyConf::KeyConf(unsigned int up, unsigned int down, unsigned int right,
		 unsigned int left, unsigned int bomb, unsigned int ret, unsigned int enter)
{
  _conf[0] = up;
  _conf[1] = down;
  _conf[2] = right;
  _conf[3] = left;
  _conf[4] = ret;
  _conf[5] = enter;
  _conf[6] = bomb;
}

KeyConf::~KeyConf()
{
}

unsigned int	KeyConf::getUp() const
{
  return (this->_conf[0]);
}

unsigned int	KeyConf::getDown() const
{
  return (this->_conf[1]);
}

unsigned int	KeyConf::getRight() const
{
  return (this->_conf[2]);
}

unsigned int	KeyConf::getLeft() const
{
  return (this->_conf[3]);
}

unsigned int KeyConf::getRet() const
{
  return (this->_conf[4]);
}

unsigned int KeyConf::getEnter() const
{
  return (this->_conf[5]);
}

unsigned int	KeyConf::getPutBomb() const
{
  return (this->_conf[6]);
}

bool		KeyConf::alreadyExist(unsigned int c) const
{
  for (unsigned int i = 0; i < 7; ++i)
    {
      if (_conf[i] == c)
	return (true);
    }
  return (false);
}

void		 KeyConf::addNewKey(unsigned int id, unsigned int k)
{
  static void	(KeyConf::*tab[])(unsigned int) =
  {
    &KeyConf::setUp, &KeyConf::setDown, &KeyConf::setRight,
    &KeyConf::setLeft, &KeyConf::setLeft
  };

  (this->*tab[id])(k);
}

void		KeyConf::setUp(unsigned int c)
{
  this->_conf[0] = c;
}

void		KeyConf::setDown(unsigned int c)
{
  this->_conf[1] = c;
}

void		KeyConf::setRight(unsigned int c)
{
  this->_conf[2] = c;
}

void		KeyConf::setLeft(unsigned int c)
{
  this->_conf[3] = c;
}

void		KeyConf::setPutBomb(unsigned int c)
{
  this->_conf[6] = c;
}

void KeyConf::operator =(const KeyConf &k)
{
  this->_conf[0] = k._conf[0];
  this->_conf[1] = k._conf[1];
  this->_conf[2] = k._conf[2];
  this->_conf[3] = k._conf[3];
  this->_conf[4] = k._conf[4];
  this->_conf[5] = k._conf[5];
  this->_conf[6] = k._conf[6];
}

