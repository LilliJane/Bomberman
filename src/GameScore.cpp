//
// GameScore.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Fri Jun 12 10:56:30 2015 _p dumont
// Last update Fri Jun 12 10:56:30 2015 _p dumont
//

#include <sstream>

#include "GameScore.hh"
#include "OpenGL.hh"
#include "Player.hh"

GameScore::GameScore(Game *game)
  : GameState(game)
{
  _score[0] = 0;
  _score[1] = 0;
  openScore();
}

GameScore::~GameScore()
{
  std::ofstream file;
  std::stringstream ss;

  file.open("./.highscore", std::fstream::out | std::fstream::trunc);
  if (file.is_open())
    {
      ss << _score[0] << "\n" << _score[1] << "\n";
      file << ss.str();
      file.close();
    }
}

int			GameScore::update(Time const &diff)
{
  Player		*p;
  Text			txt;
  std::stringstream	ss;

  (void)diff;
  glClearColor(0, 0, 0, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  txt.setColor(255, 0, 0);
  _win[0].setColor(255, 0, 0);
  _win[1].setColor(0, 0, 255);
  _win[0].move(50, 450, 0);
  _win[1].move(50, 410, 0);
  for (unsigned int i = 0;
       i < this->_actual_game->getPlayers().size();
       ++i)
    {
      p = this->_actual_game->getPlayers()[i];
      ss.str("");
      if (p->getScore() > _score[i])
	{
	  ss << "Player" << (i + 1) << " beat the old record";
	  _win[i].setText(ss.str());
	  _score[i] = p->getScore();
	}
      ss.str("");
      ss << "Player" << (i + 1) << " max score : " << p->getScore();
      txt.setText(ss.str());
      txt.move(100, 350 - (i * 30), 0);
      txt.draw();
      _win[i].draw();
      txt.setColor(0, 0, 255);
    }
  return (0);
}

int		GameScore::sendEvent(const std::pair<Event, Player *> &event)
{
  if (event.first == Escape)
    {
      this->_actual_game->popState();
      return (1);
    }
  return (0);
}

void GameScore::openScore()
{
  unsigned int	i;
  std::string	s;
  std::ifstream file;
  std::stringstream ss;

  file.open("./.highscore", std::fstream::in);
  i = 0;
  if (file.is_open())
    {
      while (std::getline(file, s) && i < 2)
	{
	  if (s[0] == '-')
	    throw std::runtime_error("Error: Invalid value");
	  ss << s;
	  ss >> _score[i];
	  ++i;
	}
      file.close();
    }
}
