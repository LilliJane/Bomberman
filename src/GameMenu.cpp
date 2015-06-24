//
// GameMenu.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Fri May 15 03:41:49 2015 _p dumont
// Last update Fri May 15 03:41:50 2015 _p dumont
//

#include "GameMenu.hh"
#include "Text.hh"
#include "GameConfig.hh"
#include "GamePlaySetting.hh"
#include "KeyConf.hh"
#include "Player.hh"

#include "OpenGL.hh"
#include "SDL2/SDL.h"

GameMenu::GameMenu(Game *game)
  : GameState(game)
{
  this->_buttons.push_back(new Button("Play", 300, 400));
  this->_buttons.push_back(new Button("Settings", 300, 300));
  this->_buttons.push_back(new Button("Quit", 300, 200));

  for (std::vector<Button *>::iterator it = this->_buttons.begin();
       it != this->_buttons.end();
       ++it)
    (*it)->setColor(255, 255, 0);
  this->_selected_button = this->_buttons[0];
  this->_selected_button_id = 0;
  this->_selected_button->select();
}

GameMenu::~GameMenu()
{
  for (std::vector<Button *>::iterator it = this->_buttons.begin();
       it != this->_buttons.end();
       ++it)
    delete (*it);
}

int		GameMenu::update(const Time &t)
{
  (void)t;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for (std::vector<Button *>::iterator it = this->_buttons.begin();
       it != this->_buttons.end();
       ++it)
    (*it)->draw();
  return (0);
}

int		GameMenu::sendEvent(const std::pair<Event, Player *> &event)
{
  if (event.first== Escape)
    {
      this->_actual_game->popState();
      return (1);
    }
  else if (event.first== Down)
    {
      ++this->_selected_button_id;
      if (this->_selected_button_id == this->_buttons.size())
	this->_selected_button_id = 0;
      this->_selected_button->unselect();
      this->_selected_button = this->_buttons[this->_selected_button_id];
      this->_selected_button->select();
    }
  else if (event.first== Up)
    {
      --this->_selected_button_id;
      if (this->_selected_button_id == (unsigned int)(-1))
	this->_selected_button_id = this->_buttons.size() - 1;
      this->_selected_button->unselect();
      this->_selected_button = this->_buttons[this->_selected_button_id];
      this->_selected_button->select();
    }
  else if (event.first== Enter)
    {
      if (this->_selected_button == this->_buttons[2])
	{
	  this->_actual_game->popState();
	  return (1);
	}
      else if (this->_selected_button == this->_buttons[0])
	{
	  this->_actual_game->pushState(new GamePlaySetting(this->_actual_game));
	  return (1);
	}
      else if (this->_selected_button == this->_buttons[1])
	{
	  this->_actual_game->pushState(new GameConfig(this->_actual_game));
	  return (1);
	}
    }
  return (0);
}
