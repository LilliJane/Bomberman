//
// Save.hh for bomberman in /home/totote/cpp_bomberman/src
//
// Made by Emeline Gaulard
// Login   <totote@epitech.net>
//
// Started on  Fri May 29 14:37:56 2015 Emeline Gaulard
// Last update Sun Jun 14 22:32:06 2015 Emeline Gaulard
//

#ifndef SAVE_HH_
# define SAVE_HH_

# include <fstream>
# include <ostream>
# include <iostream>
# include <string>
# include <sstream>
# include "Player.hh"
# include "Grid.hpp"
# include "IEntity.hh"
# include "IA.hh"
# include "Bomb.hh"
# include "ABonus.hh"

class	Save
{
public:
  Save(const Bombermap& map, const std::vector<Player *> &players, const std::vector<IA *> &ia);
  Save(const Bombermap& map, const std::vector<Player *> &players, const std::vector<IA *> &ia, std::string &name);
  ~Save();

  void	setName(std::string& name);

  void	run();

private:
  void	saveMap();
  void	savePlayers();
  void	saveBomb(Bomb *bomb);
  void	saveBonus(ABonus *bonus);
  void	saveEntity();
  void	saveIA();

  const Bombermap		&_map;
  const std::vector<Player *>	&_players;
  const std::vector<IA *>	&_ia;
  std::string			_name;
  std::ofstream			_file;
  std::string			_nameFile;
};

#endif // SAVE_HH_
