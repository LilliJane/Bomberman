//
// main.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Wed May 13 13:33:32 2015 _p dumont
// Last update Wed May 13 13:33:32 2015 _p dumont
//

#include "Game.hh"

int		main(int ac,
		     char **av)
{
  Game		bomberman(ac, av);

  return (bomberman.run());
}
