//
// GameCmd.cpp for GameCmd in /home/tack_g/rendu/cpp_bomberman
//
// Made by g tack
// Login   <tack_g@epitech.net>
//
// Started on  Tue May 19 19:18:06 2015 g tack
// Last update Tue May 19 19:18:06 2015 g tack
//

#include <sstream>
#include "GameCmd.hh"
#include "Player.hh"

#include <iostream>

GameCmd::GameCmd(Game *g) :
  GameState(g)
{
  _k = this->_actual_game->getPlayers()[0]->getConf();
  this->_buttons.push_back(new Button("UP", 50, 550));
  this->_buttons.push_back(new Button("DOWN", 50, 500));
  this->_buttons.push_back(new Button("RIGHT", 50, 450));
  this->_buttons.push_back(new Button("LEFT", 50, 400));
  this->_buttons.push_back(new Button("PUT BOMB", 50, 350));

  this->_buttons.push_back(new Button("Accept", 150, 10));
  this->_buttons.push_back(new Button("Cancel", 450, 10));
  for (std::vector<Button *>::iterator it = _buttons.begin();
       it != _buttons.end(); ++it)
    (*it)->setColor(0, 0, 255);
  this->_actual_button = this->_buttons[0];
  this->_actual_button_id = 0;
  this->_actual_button->select();
}

GameCmd::~GameCmd()
{
  for (std::vector<Button *>::iterator it = this->_buttons.begin();
       it != this->_buttons.end(); ++it)
    delete (*it);
}

int		GameCmd::update(const Time &diff)
{
  (void)(diff);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for (std::vector<Button *>::iterator it = this->_buttons.begin();
       it != this->_buttons.end(); ++it)
    (*it)->draw();
  return (0);
}

int		GameCmd::sendEvent(const std::pair<Event, Player *> &event)
{
  if (event.first== Escape)
    {
      this->_actual_game->popState();
      return (1);
    }
  else if (event.first== Down)
    {
      ++this->_actual_button_id;
      if (this->_actual_button_id == this->_buttons.size())
	this->_actual_button_id = 0;
      this->_actual_button->unselect();
      this->_actual_button = this->_buttons[this->_actual_button_id];
      this->_actual_button->select();
    }
  else if (event.first== Up)
    {
      --this->_actual_button_id;
      if (this->_actual_button_id == (unsigned int)(-1))
	this->_actual_button_id = this->_buttons.size() - 1;
      this->_actual_button->unselect();
      this->_actual_button = this->_buttons[this->_actual_button_id];
      this->_actual_button->select();
    }
  else if (event.first== Enter)
    {
      if (this->_actual_button_id == this->_buttons.size() - 1)
	{
	  this->_actual_game->popState();
	  return (1);
	}
      else if (this->_actual_button_id == this->_buttons.size() - 2)
	{
	  this->_actual_game->getPlayers()[0]->setConf(this->_k);
	  this->_actual_game->popState();
	  return (1);
	}
      else
	{
	  this->_actual_button->setColor(255, 0, 0);
	  this->_actual_button->draw();
	  this->_actual_game->forceFlush();
	  while (this->waitInput());
	  this->_actual_button->setColor(0, 0, 255);
	}
    }
  return (0);
}

int		GameCmd::waitInput()
{
  gdl::Input	*i;
  unsigned int	it;
  bool		spec = false;

  i = ResourceManager::GetInstance()->GetInput();
  this->_actual_game->getContext().updateInputs(*i);
  for (it = '\r'; i->getKey(it) == false && it <= 127; ++it);
  if (it == 128)
    {
      spec = true;
      for (it = 0; i->getKey((it | (1 << 30))) == false && it < 255; ++it);
    }
  if (it == 255)
    return (1);
  if (it == SDLK_ESCAPE || it == SDLK_RETURN)
    return (0);
  if (spec)
    it |= 1 << 30;
  if (it == SDLK_KP_ENTER)
    return (0);
  if (this->_k.alreadyExist(it))
    return (0);
  this->_k.addNewKey(this->_actual_button_id, it);
  return (0);
}
