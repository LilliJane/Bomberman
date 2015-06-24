//
// GameIntro.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Wed May 13 17:01:26 2015 _p dumont
// Last update Wed May 13 17:01:26 2015 _p dumont
//

#include <stdexcept>

#include "Game.hh"
#include "GameIntro.hh"
#include "Text.hh"
#include "GameMenu.hh"
#include "ResourceManager.hh"

#include "OpenGL.hh"

GameIntro::GameIntro(Game *game)
  : GameState(game)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  if (pthread_attr_init(&this->_thread_attr))
    throw (std::runtime_error("pthread_attr_init()"));
  this->_loaded = false;
  if (pthread_create(&this->_thread,
		     &this->_thread_attr,
		     reinterpret_cast<void *(*)(void *)>(&this->loadResources),
		     static_cast<void*>(this)))
    throw (std::runtime_error("Can't create thread !"));
  //Text t("this story beggin", 0, 50);
  //t.setColor(255, 0, 0);
  //t.draw();
  this->_t = this->_t.fromLongLongInt(0);
}

GameIntro::~GameIntro()
{
  timespec	ts;

  ts.tv_sec = 0;
  ts.tv_nsec = 50000000;
  if (!this->_loaded)
    {
      if (pthread_timedjoin_np(this->_thread, 0, &ts))
	pthread_kill(this->_thread, SIGUSR1);
    }
}

int		GameIntro::update(Time const &diff)
{
  Text		truc[8] =
  {
    Text("The story begins", 0, 500),
    Text("in a galaxy", 0, 450),
    Text("far far away", 0, 400),
    Text("in a world ruled by artificial intelligence", 0 , 350),
    Text("where lives an old man", 0 , 300),
    Text("known as", 0 , 250),
    Text("...", 0, 200),
    Text("BOMBER-MAN !!!", 0, 150)
  };
  Text		skip("(press escape to skip)", 200, 50);
  skip.setColor(255, 0, 0);


  if (this->_loaded)
    skip.draw();
  this->_t += diff;
  if (this->_t.getSecond() < 8)
    {
      truc[this->_t.getSecond()].setColor(239, 216, 7);
      truc[this->_t.getSecond()].draw();
    }
  else if (this->_loaded)
    {
      this->_actual_game->changeState(new GameMenu(this->_actual_game));
      return (1);
    }
  return (0);
}

int		GameIntro::sendEvent(const std::pair<Event, Player *> &event)
{
  if (this->_loaded)
    {
      if (event.first == Escape)
	{
	  this->_actual_game->changeState(new GameMenu(this->_actual_game));
	  return (1);
	}
    }
  return (0);
}

void		GameIntro::loadResources(GameIntro *game)
{
  if (!ResourceManager::GetInstance()->LoadResource())
    throw (std::runtime_error("Can't load all the resources !"));
  game->_loaded = true;
}
