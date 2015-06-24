//
// Load.hh for Bomberman in /home/totote/cpp_bomberman
//
// Made by Emeline Gaulard
// Login   <totote@epitech.net>
//
// Started on  Mon Jun  8 15:48:09 2015 Emeline Gaulard
// Last update Sun Jun 14 22:47:32 2015 Emeline Gaulard
//

#ifndef LOAD_HH_
# define LOAD_HH_

# include <vector>
# include <string>
# include <iostream>
# include "GamePlay.hh"

class	Load
{
  public:
    Load(GamePlay& game);
    ~Load();

    bool			loadFromFile(std::string name);

    unsigned int		findUnsignedInt(std::string delim);
    unsigned short	findUnsignedShort(std::string delim);
    float			findFloat(std::string delim);

    void	run();

  private:
    void	setMap();
    void	setPlayers();
    void	setEntity();
    void	setIA();

  private:
    std::string	_content;
    std::size_t	_found;
    GamePlay&	_game;
};

#endif // LOAD_HH_
