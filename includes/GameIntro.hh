//
// GameIntro.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Wed May 13 17:01:04 2015 _p dumont
// Last update Wed May 13 17:01:05 2015 _p dumont
//

#ifndef GAMEINTRO_HH_
# define GAMEINTRO_HH_

# include <pthread.h>
# include <signal.h>

# include "GameState.hh"

class Game;

class GameIntro : public GameState
{
  public:
    GameIntro(Game *game);
    virtual ~GameIntro();

    virtual int		update(Time const &t);
    virtual int		sendEvent(const std::pair<Event, Player *> &event);

  private:
    static void		loadResources(GameIntro *game);

    Time		_t;
    bool		_loaded;
    pthread_t		_thread;
    pthread_attr_t	_thread_attr;
};

#endif /* !GAMEINTRO_HH_ */
