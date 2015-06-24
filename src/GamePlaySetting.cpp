//
// GamePlaySetting.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Wed Jun 10 06:48:38 2015 _p dumont
// Last update Sun Jun 14 19:11:40 2015 Emeline Gaulard
//

#include <stdexcept>

#include "GamePlaySetting.hh"
#include "Button.hh"
#include "InputNumber.hh"

#include "OpenGL.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

#include "Load.hh"

GamePlaySetting::GamePlaySetting(Game *g)
  : GameState(g)
{
  this->_game = new GamePlay(g);
  this->_gui.push_back(new Button("PLAY NOW !", 300, 50));
  dynamic_cast<Button *>(this->_gui[0])->setColor(255, 0, 0);
  this->_selected = this->_gui[0];
  this->_gui[0]->select();
  this->_selected_gui = 0;
  this->_text.push_back(new Text("Player : ", 50, 400));
  this->_text[0]->setColor(255, 0, 0);
  this->_text.push_back(new Text("Map X : ", 50, 350));
  this->_text[1]->setColor(255, 0, 0);
  this->_text.push_back(new Text("Map Y : ", 50, 300));
  this->_text[2]->setColor(255, 0, 0);
  this->_text.push_back(new Text("Nombre d`IA : ", 50, 250));
  this->_text[3]->setColor(255, 0, 0);
  this->_text.push_back(new Text("Select Map : ", 50, 200));
  this->_text[4]->setColor(255, 0, 0);
  this->_gui.push_back(new InputNumber(1, 300, 400, 1, this->_actual_game->getPlayers().size(), 1));
  dynamic_cast<InputNumber *>(this->_gui[1])->setColor(255, 0, 0);
  this->_gui.push_back(new InputNumber(100, 300, 350, 10, 2147483647, 1));
  dynamic_cast<InputNumber *>(this->_gui[2])->setColor(255, 0, 0);
  this->_gui.push_back(new InputNumber(100, 300, 300, 10, 2147483647, 1));
  dynamic_cast<InputNumber *>(this->_gui[3])->setColor(255, 0, 0);
  this->_gui.push_back(new InputNumber(1, 300, 250, 0, 2147483647, 1));
  dynamic_cast<InputNumber *>(this->_gui[4])->setColor(255, 0, 0);
  this->_gui.push_back(new InputNumber(0, 300, 200, 0, 3, 1));
  dynamic_cast<InputNumber *>(this->_gui[5])->setColor(255, 0, 0);
  this->_gui.push_back(new Button("Or load previous game ?", 75, 150));
  dynamic_cast<Button *>(this->_gui[6])->setColor(255, 0, 0);
}

GamePlaySetting::~GamePlaySetting()
{
  for (std::vector<ISelectGUI *>::iterator it = this->_gui.begin();
       it != this->_gui.end();
       ++it)
    delete (*it);
  for (std::vector<Text *>::iterator it = this->_text.begin();
       it != this->_text.end();
       ++it)
    delete (*it);
}

int			GamePlaySetting::update(const Time &t)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  for (std::vector<ISelectGUI *>::iterator it = this->_gui.begin();
       it != this->_gui.end();
       ++it)
    (*it)->draw(t);
  for (std::vector<Text *>::iterator it = this->_text.begin();
       it != this->_text.end();
       ++it)
    (*it)->draw(t);
  return (0);
}

int			GamePlaySetting::sendEvent(const std::pair<Event, Player *> &event)
{
  if (event.first == Escape)
    {
      delete (this->_game);
      this->_actual_game->popState();
      return (1);
    }
  if (event.first == Up)
    {
      this->_gui[this->_selected_gui]->unselect();
      --this->_selected_gui;
      if (this->_selected_gui == (size_t)(-1))
	this->_selected_gui = this->_gui.size() - 1;
      this->_gui[this->_selected_gui]->select();
      this->_selected = this->_gui[this->_selected_gui];
      return (0);
    }
  if (event.first == Down)
    {
      this->_gui[this->_selected_gui]->unselect();
      ++this->_selected_gui;
      if (this->_selected_gui == this->_gui.size())
	this->_selected_gui = 0;
      this->_gui[this->_selected_gui]->select();
      this->_selected = this->_gui[this->_selected_gui];
      return (0);
    }
  if (event.first == Left)
    {
      InputNumber *i;
      if ((i = dynamic_cast<InputNumber *>(this->_gui[this->_selected_gui])))
	--(*i);
      return (0);
    }
  if (event.first == Right)
    {
      InputNumber *i;
      if ((i = dynamic_cast<InputNumber *>(this->_gui[this->_selected_gui])))
	++(*i);
      return (0);
    }
  else if (event.first== Enter)
    {
      if (this->_selected == this->_gui[0] &&
	  dynamic_cast<InputNumber *>(this->_gui[1])->getValue() +
	  dynamic_cast<InputNumber *>(this->_gui[4])->getValue() >= 2)
	{
	  glClearDepth(1.0);
	  this->_game->resizeMap(dynamic_cast<InputNumber *>(this->_gui[2])->getValue(),
	      dynamic_cast<InputNumber *>(this->_gui[3])->getValue());
	  this->_game->setIANumber(dynamic_cast<InputNumber *>(this->_gui[4])->getValue());
	  this->_game->setPlayer(dynamic_cast<InputNumber *>(this->_gui[1])->getValue());
	  this->_game->getFocus(dynamic_cast<InputNumber *>(this->_gui[5])->getValue());
	  this->_actual_game->changeState(this->_game);
	  return (1);
	}
      else if (this->_selected == this->_gui[6])
	{
	  Load	load(*(this->_game));
	  if (!load.loadFromFile("Bomber"))
	    return (1);
	  load.run();
	  glClearDepth(1.0);
	  int players = 0;
	  for (std::vector<Player *>::iterator it = this->_actual_game->getPlayers().begin();
	       it != this->_actual_game->getPlayers().end();
	       ++it)
	    {
	      if ((*it)->getLife())
		++players;
	    }
	  std::cout << "players => " << players << std::endl;
	  this->_game->setPlayer(players);
	  this->_game->setBattleWindow();
	  this->_actual_game->changeState(this->_game);
	  return (1);
	}
    }
  return (0);
}
