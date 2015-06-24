//
// Load.cpp for Bomberman in /home/totote/cpp_bomberman
//
// Made by Emeline Gaulard
// Login   <totote@epitech.net>
//
// Started on  Mon Jun  8 15:48:15 2015 Emeline Gaulard
// Last update Sun Jun 14 22:46:59 2015 Emeline Gaulard
//

#include <fstream>
#include <sstream>
#include "Load.hh"

Load::Load(GamePlay& game) :
  _game(game)
{
  _found = 0;
}

Load::~Load()
{

}

bool			Load::loadFromFile(std::string name)
{
  std::ifstream	file;
  std::string	line;

  line = name + ".save";
  file.open(line.c_str());
  line.clear();
  if (file.is_open())
    {
      while (getline(file, line))
	_content.append(line);
      file.close();
      return (true);
    }
  return (false);
}

unsigned int		Load::findUnsignedInt(std::string delim)
{
  unsigned int		tmp;
  size_t		tmp2;
  std::stringstream	ss;

  tmp2 = _content.find(delim.c_str(), _found + 1, 1);
  if (tmp2 != std::string::npos)
    {
      ss << _content.substr(_found + 1, tmp2 - _found - 1);
      ss >> tmp;
      _found = tmp2;
      ss.str(std::string());
      ss.clear();
      return (tmp);
    }
  else
    return (0);
}

unsigned short		Load::findUnsignedShort(std::string delim)
{
  unsigned short	tmp;
  size_t		tmp2;
  std::stringstream	ss;

  tmp2 = _content.find(delim.c_str(), _found + 1, 1);
  if (tmp2 != std::string::npos)
    {
      ss << _content.substr(_found + 1, tmp2 - _found - 1);
      ss >> tmp;
      _found = tmp2;
      ss.str(std::string());
      ss.clear();
      return (tmp);
    }
  else
    return (0);
}

float			Load::findFloat(std::string delim)
{
  float			tmp;
  size_t		tmp2;
  std::stringstream	ss;

  tmp2 = _content.find(delim.c_str(), _found + 1, 1);
  if (tmp2 != std::string::npos)
    {
      ss << _content.substr(_found + 1, tmp2 - _found - 1);
      ss >> tmp;
      _found = tmp2;
      ss.str(std::string());
      ss.clear();
      return (tmp);
    }
  else
    return (0);
}

void			Load::run()
{
  setMap();
  setPlayers();
  setEntity();
  setIA();
}

void	Load::setMap()
{
  size_t		x;
  size_t		y;
  int			tmp;
  size_t		tmp2;
  std::stringstream	ss;
  std::vector<int>	values;
  Bombermap		&map = _game.modifyMap();

  _found = _content.find("map");
  if (_found != std::string::npos)
    _found = _content.find("width", _found + 1, 5);
  if (_found != std::string::npos)
    _found = _content.find(":", _found + 1, 1);
  tmp2 = _content.find(",", _found + 1, 1);
  ss << _content.substr(_found + 1, tmp2 - _found - 1);
  ss >> x;
  ss.str(std::string());
  ss.clear();

  if (_found != std::string::npos)
    _found = _content.find("height", _found + 1, 6);
  if (_found != std::string::npos)
    _found = _content.find(":", _found + 1, 1);
  tmp2 = _content.find(",", _found + 1, 1);
  ss << _content.substr(_found + 1, tmp2 - _found - 1);
  ss >> y;
  ss.str(std::string());
  ss.clear();

  map.resize(x, y);
  for (x = 0; x < map.width(); ++x)
    {
      for (y = 0; y < map.height(); ++y)
	{
	  if (_found != std::string::npos)
	    _found = _content.find(",", _found + 1, 1);
	  if (y == 0)
	    ss << _content.at(_found + 2);
	  else
	    ss << _content.at(_found + 1);
	  ss >> tmp;
	  ss.str(std::string());
	  ss.clear();
	  values.push_back(tmp);
	}
    }
  map.generate_map(values);
}

void			Load::setPlayers()
{
  size_t		tmp;
  std::vector<Player *>	&players = _game.modifyPlayers();
  unsigned int		i;
  unsigned int		up; 
  unsigned int		down;
  unsigned int		left;
  unsigned int		right;
  unsigned int		bomb;
  unsigned int		ret;
  unsigned int		enter;
 
  _found = _content.find("{players:", _found + 1);
  tmp = _content.find("}", _found + 1, 1);
  i = 0;
  while (_found <= tmp && i < players.size())
    {
      _found = _content.find("[", _found + 1);
      players[i]->setScore(findUnsignedInt(","));
      players[i]->setSpeed(findUnsignedInt(","));
      players[i]->setPosX(findFloat(","));
      players[i]->setPosY(findFloat(","));
      players[i]->setRange(findUnsignedShort(","));
      players[i]->setNbBombs(findUnsignedShort(","));
      players[i]->setLife(findUnsignedShort(","));
      up = findUnsignedInt(",");
      down = findUnsignedInt(",");
      right = findUnsignedInt(",");
      left = findUnsignedInt(",");
      ret = findUnsignedInt(",");
      enter = findUnsignedInt(",");
      bomb = findUnsignedInt("]");
      KeyConf keys(up, down, right, left, bomb, ret, enter);
      players[i]->setConf(keys);
      i++;
    }
}

void			Load::setEntity()
{
  std::string		str;
  unsigned int		x;
  unsigned int		y;
  unsigned int		range;
  size_t		next;
  size_t		tmp;
  Bombermap&		map = _game.modifyMap();

  _found = _content.find("{entities:", _found + 1);
  tmp = _content.find("}", _found + 1, 1);
  while (_found <= tmp)
    {
      _found = _content.find("[", _found + 1);
      if (_found == std::string::npos)
	break;
      next = _content.find(",", _found + 1);
      if (next == std::string::npos)
	break;
      str = _content.substr(_found, next - _found - 1);
      x = findUnsignedInt(",");
      y = findUnsignedInt(",");
      if (str == "bomb")
	{
	  range = findUnsignedInt("]");
	  map.add_entity(new Bomb(x, y, range));
	}
      else
	{
	  if (str == "bonusBomb")
	    map.add_entity(new bonusBomb(x, y));
	  else if (str == "bonusRange")
	    map.add_entity(new bonusRange(x, y));
	  else
	    map.add_entity(new bonusSpeed(x, y));
	}
    }
}

void			Load::setIA()
{
  size_t		tmp;
  std::vector<IA*>	&ia = _game.modifyIA();

  _found = _content.find("{ia:", _found + 1);
  tmp = _content.find("}", _found + 1, 1);
  for (std::vector<IA *>::iterator it = ia.begin();
       it != ia.end();
       ++it)
    delete (*it);
  while (_found <= tmp)
    {
      IA *tmpIa = new IA();
      _found = _content.find("[", _found + 1);
      if (_found == std::string::npos)
	break;
      tmpIa->setScore(findUnsignedInt(","));
      tmpIa->setSpeed(findUnsignedInt(","));
      tmpIa->setPosX(findFloat(","));
      tmpIa->setPosY(findFloat(","));
      tmpIa->setRange(findUnsignedShort(","));
      tmpIa->setNbBombs(findUnsignedShort(","));
      tmpIa->setLife(findUnsignedShort("]"));
      ia.push_back(tmpIa);
    }
}
