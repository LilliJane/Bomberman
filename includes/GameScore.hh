//
// GameScore.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Fri Jun 12 10:56:23 2015 _p dumont
// Last update Fri Jun 12 10:56:23 2015 _p dumont
//

#ifndef GAMESCORE_HH_
# define GAMESCORE_HH_

# include <fstream>
# include "Text.hh"
# include "GameState.hh"

class Game;

class GameScore : public GameState
{
  public:
    GameScore(Game *game);
    virtual ~GameScore();

    virtual int		update(Time const &t);
    virtual int		sendEvent(const std::pair<Event, Player *> &event);

  private:
    void		openScore();

    Text		_win[2];
    unsigned int	_score[2];
};

#endif /* !GAMESCORE_HH_ */
