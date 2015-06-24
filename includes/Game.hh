//
// Game.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Wed May 13 13:35:31 2015 _p dumont
// Last update Sun Jun 14 21:20:14 2015 Emeline Gaulard
//

#ifndef GAME_HH_
# define GAME_HH_

# include <stack>

# include "EventListener.hpp"
# include "MyContext.hh"

class GameState;
class Player;

class Game
{
  public:
    Game(int ac, char **av);
    ~Game();

  int				run();
  void				pushState(GameState *state);
  void				popState();
  void				changeState(GameState *state);
  void				forceFlush() const;
  const std::vector<Player *>	&getPlayers() const;
  std::vector<Player *>		&getPlayers();
  void				addPlayer(glm::vec4 color);

  MyContext			&getContext();

private:
  std::stack<GameState *>	_actual_state;
  EventListener			_event_listener;
  std::vector<Player *>		_players;
  MyContext			_con_text;
};

#endif // GAME_HH_
