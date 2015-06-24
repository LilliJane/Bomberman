//
// Game.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Wed May 13 13:35:19 2015 _p dumont
// Last update Sun Jun 14 21:20:04 2015 Emeline Gaulard
//

#include <stdexcept>
#include <string>
#include <iostream>

#include "Game.hh"
#include "Player.hh"
#include "Time.hh"
#include "Timer.hh"
#include "GameIntro.hh"
#include "JoysticListener.hh"
#include "KeyboardListener.hh"
#include "ResourceManager.hh"

Game::Game(int ac,
	   char **av)
{
  (void)av;
  if (!this->_con_text.start(800, 600, "Bomberman : player 1"))
    throw (std::runtime_error("Can't open a new window"));
  if (!ResourceManager::GetInstance()->PreLoadResource())
    throw (std::runtime_error("Can't preload resource !"));
  if (ac != 0)
    {
      this->addPlayer(glm::vec4(255, 0, 0, 1));
      this->addPlayer(glm::vec4(0, 0, 255, 1));
    }
}

Game::~Game()
{
  this->_con_text.stop();
  while (_actual_state.size())
    {
      delete _actual_state.top();
      _actual_state.pop();
    }
  ResourceManager::DeleteInstance();
}

int			Game::run()
{
  try
  {
    Timer			t;

    this->_actual_state.push(new GameIntro(this));
    while (!this->_actual_state.empty())
      {
	if (!this->_actual_state.top()->update(t.reset()))
	  {
	    std::pair<Event, Player *> e;
	    while (this->_event_listener.poolEvent(e) &&
		   !this->_actual_state.empty() &&
		   this->_actual_state.top()->sendEvent(e))
	      ;
	  }
	this->_con_text.flush();
      }
    return (0);
  }
  catch (std::exception &e)
  {
    std::cerr << e.what() << std::endl;
  }
}


void		Game::pushState(GameState *state)
{
  this->_actual_state.push(state);
}

void		Game::popState()
{
  if (!this->_actual_state.empty())
    {
      delete this->_actual_state.top();
      this->_actual_state.pop();
    }
}

void		Game::changeState(GameState *state)
{
  this->popState();
  this->pushState(state);
}

void		Game::forceFlush() const
{
  this->_con_text.flush();
}

const std::vector<Player *>	&Game::getPlayers() const
{
  return (this->_players);
}

std::vector<Player *>		&Game::getPlayers()
{
  return (this->_players);
}

void			Game::addPlayer(glm::vec4 color)
{
  Player		*p;

  p = new Player(color);
  this->_players.push_back(p);
  this->_event_listener.addListener<KeyboardListener>(&this->_con_text, p);
  this->_event_listener.addListener<JoysticListener>(p);
}

MyContext		&Game::getContext()
{
  return (this->_con_text);
}
