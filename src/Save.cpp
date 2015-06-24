//
// Save.cpp for bomberman in /home/totote/cpp_bomberman/src
//
// Made by Emeline Gaulard
// Login   <totote@epitech.net>
//
// Started on  Fri May 29 14:36:59 2015 Emeline Gaulard
// Last update Sun Jun 14 22:33:13 2015 Emeline Gaulard
//

#include <ctime>
#include "Save.hh"

#include <iostream>

Save::Save(const Bombermap &map, const std::vector<Player *> &players, const std::vector<IA *> &ia) :
  _map(map),
  _players(players),
  _ia(ia)
{
  std::cout << "Save construct" << std::endl;
  _name = "Bomber";
  _nameFile = "Bomber.save";
}

/*
** add time in sec to get a new file name
*/
Save::Save(const Bombermap& map, const std::vector<Player *> &players, const std::vector<IA *> &ia, std::string &name) :
  _map(map),
  _players(players),
  _ia(ia)
{
  time_t	t = time(0);
  struct tm *	now = localtime( & t );
  std::ostringstream oss;

  oss << now->tm_sec;
  name += oss.str();
  _name = name;
  _nameFile = name + ".save";
}

Save::~Save()
{
  if (_file.is_open())
    _file.close();
}

void	Save::run()
{
  if (!_nameFile.empty())
    {
      _file.open(_nameFile.c_str(), std::ios_base::trunc | std::ios_base::out);
      _file << "{" << _name << "[" << std::endl;
      saveMap();
      savePlayers();
      saveIA();
      saveEntity();
      _file << std::endl << "]}";
      _file.close();
    }
}

void	Save::setName(std::string& name)
{
  _name = name;
  _nameFile = name + ".save";
}

void	Save::saveMap()
{
  int	x;
  int	xMax;
  int	y;
  int	yMax;

  xMax = _map.width();
  yMax = _map.height();
  _file << "\t{map:[width:" << xMax << ",height:" << yMax << "," << std::endl << "\t";
  for (x = 0; x < xMax; ++x)
    {
      for (y = 0; y < yMax; ++y)
	_file << _map.get_block_at(x, y) << ",";
      _file << std::endl << "\t";
    }
  _file << "]}" << std::endl;
}

void	Save::savePlayers()
{
  unsigned int	i;

  _file << "\t{players:" << std::endl;
  if (!_players.empty())
    {
      for (i = 0; i < _players.size(); ++i)
	{
	  _file << "\t[" << _players[i]->getScore() << ",";
	  _file << _players[i]->getSpeed() << ",";
	  _file << _players[i]->getPosX() << ",";
	  _file << _players[i]->getPosY() << ",";
	  _file << _players[i]->getRange() << ",";
	  _file << _players[i]->getNbBombs() << ",";
	  _file << _players[i]->getLife() << ",";
	  _file << _players[i]->getConf().getUp() << ",";
	  _file << _players[i]->getConf().getDown() << ",";
	  _file << _players[i]->getConf().getRight() << ",";
	  _file << _players[i]->getConf().getLeft() << ",";
	  _file << _players[i]->getConf().getRet() << ",";
	  _file << _players[i]->getConf().getEnter() << ",";
	  _file << _players[i]->getConf().getPutBomb() << "]" << std::endl;
	}
    }
  _file << "\t}" << std::endl;
}

void	Save::saveBomb(Bomb *bomb)
{
  _file << "\t[bomb," << bomb->getCellX() << "," << bomb->getCellY() << ",";
  _file << bomb->getRange() << "]" << std::endl;
}

void	Save::saveBonus(ABonus *bonus)
{
  if (bonus->getType() == BONUSBOMB)
    _file << "\t[bonusBomb,";
  else if (bonus->getType()== BONUSSPEED)
    _file << "\t[bonusSpeed,";
  else
    _file << "\t[bonusRange,";
  _file << bonus->getCellX() << "," << bonus->getCellY() << ",/]" << std::endl;
}

void	Save::saveEntity()
{
  std::vector<IEntity *>	tmp;

  tmp = _map.get_entities();
  _file << "\t{entities:" << std::endl;
  for (unsigned int i = 0; i < tmp.size(); ++i)
    {
      if (dynamic_cast<Bomb *>(tmp[i]))
	saveBomb(dynamic_cast<Bomb *>(tmp[i]));
      else
	saveBonus(dynamic_cast<ABonus *>(tmp[i]));
    }
  _file << "\t}" << std::endl;
}

void	Save::saveIA()
{
  unsigned int	i;

  _file << "\t{ia:" << std::endl;
  if (!_ia.empty())
    {
      for (i = 0; i < _ia.size(); ++i)
	{
	  _file << "\t[" << _ia[i]->getScore() << ",";
	  _file << _ia[i]->getSpeed() << ",";
	  _file << _ia[i]->getPosX() << ",";
	  _file << _ia[i]->getPosY() << ",";
	  _file << _ia[i]->getRange() << ",";
	  _file << _ia[i]->getNbBombs() << ",";
	  _file << _ia[i]->getLife() << "]" << std::endl;
	}
    }
  _file << "\t}" << std::endl;
}
