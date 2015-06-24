//
// GameConfig.cpp for GameConfig in /home/tack_g/rendu/cpp_bomberman
//
// Made by g tack
// Login   <tack_g@epitech.net>
//
// Started on  Tue May 19 11:38:47 2015 g tack
// Last update Tue May 19 11:38:47 2015 g tack
//

#include "GameCmd.hh"
#include "ResourceManager.hh"
#include "GameConfig.hh"
#include "OpenGL.hh"

GameConfig::GameConfig(Game *g)
  : GameState(g), _zik(true)
{
  this->_buttons.push_back(new Button("Sound", 300, 300));
  this->_buttons.push_back(new Button("Keyboard", 300, 200));
  this->_buttons.push_back(new Button("Cancel", 300, 100));
  for (std::vector<Button *>::iterator it = this->_buttons.begin();
       it != this->_buttons.end();
       ++it)
    (*it)->setColor(0, 255, 0);
  this->_actual_button_id = 0;
  this->_actual_button = this->_buttons[0];
  this->_actual_button->select();
}

GameConfig::~GameConfig()
{
  for (std::vector<Button *>::iterator it = this->_buttons.begin();
       it != this->_buttons.end(); ++it)
    delete (*it);
}

int		GameConfig::update(const Time &t)
{
  (void)t;
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  for (std::vector<Button *>::iterator it = this->_buttons.begin();
       it != this->_buttons.end(); ++it)
    (*it)->draw();
  return (0);
}

int		GameConfig::sendEvent(const std::pair<Event, Player *> &event)
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
  if (event.first== Enter)
    {
//      if (this->_actual_button_id == 1)
//	{
//	  this->_actual_game->pushState(new GameCmd(this->_actual_game));
//	  return (1);
//	}
      if (this->_actual_button_id == 2)
	{
	  this->_actual_game->popState();
	  return (1);
	}
      ResourceManager::GetInstance()->SetSound();
    }
  return (0);
}
