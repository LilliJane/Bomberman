//
// GamePause.cpp for GamePause in /home/tack_g/rendu/cpp_bomberman
//
// Made by g tack
// Login   <tack_g@epitech.net>
//
// Started on  Sat Jun 13 14:26:08 2015 g tack
// Last update Sat Jun 13 14:26:08 2015 g tack
//

#include "Save.hh"
#include "GameMenu.hh"
#include "GamePause.hh"

GamePause::GamePause(Game *g, const Bombermap &map, const std::vector<IA *> &ia)
  : GameState(g), _map(map), _ia(ia)
{
  this->_buttons.push_back(new Button("Save", 300, 400));
  this->_buttons.push_back(new Button("Sound", 300, 300));
  this->_buttons.push_back(new Button("Cancel", 300, 200));
  this->_buttons.push_back(new Button("Quit", 300, 100));
  for (std::vector<Button *>::iterator it = this->_buttons.begin();
       it != _buttons.end(); ++it)
    (*it)->setColor(255, 0, 0);
  this->_selected_button = _buttons[0];
  this->_actual_button =  0;
  this->_selected_button->select();
}

GamePause::~GamePause()
{
  glClearColor(0, 0, 0, 0);
  for (std::vector<Button *>::iterator it = _buttons.begin();
       it != _buttons.end(); ++it)
    delete (*it);
}

int		GamePause::update(const Time &diff)
{
  (void)diff;
  for (std::vector<Button *>::iterator it = _buttons.begin();
       it != _buttons.end(); ++it)
    (*it)->draw();
  return (0);
}

int		GamePause::sendEvent(const std::pair<Event, Player *> &event)
{
  if (event.first == Escape)
    {
      this->_actual_game->popState();
      return (1);
    }
  else if (event.first == Up)
    {
      --this->_actual_button;
      if (this->_actual_button == (unsigned int)(-1))
	this->_actual_button = this->_buttons.size() - 1;
      this->_selected_button->unselect();
      this->_selected_button = this->_buttons[this->_actual_button];
      this->_selected_button->select();
    }
  else if (event.first == Down)
    {
      ++this->_actual_button;
      if (this->_actual_button == this->_buttons.size())
	this->_actual_button = 0;
      this->_selected_button->unselect();
      this->_selected_button = this->_buttons[this->_actual_button];
      this->_selected_button->select();
    }
  else if (event.first == Enter)
    {
      if (this->_actual_button == 0)
	{
	  return (this->saving());
	}
      else if (this->_actual_button == 1)
	ResourceManager::GetInstance()->SetSound();
      else if (this->_actual_button == 3)
	{
	  this->_actual_game->popState();
	  this->_actual_game->popState();
	  return (1);
	}
      else
	{
	  this->_actual_game->popState();
	  return (1);
	}
    }
  return (0);
}

int		GamePause::saving()
{
  Save		s(_map, this->_actual_game->getPlayers(), _ia);

  s.run();
  return (0);
}
