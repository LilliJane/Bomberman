//
// GamePlay.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Tue May 19 18:00:45 2015 _p dumont
// Last update Sun Jun 14 18:42:52 2015 Emeline Gaulard
//

#ifndef GAMEPLAY_HH_
# define GAMEPLAY_HH_

# include <vector>

# include "Cube.hh"
# include "GameState.hh"
# include "Bombermap.hh"
# include "Bomb.hh"
# include "Explosion.hh"
# include "IA.hh"
# include "BattleWindow.hh"

class		GamePlay : public GameState
{
  public:
    GamePlay(Game *g);
    virtual ~GamePlay();

    virtual int		update(Time const &t);
    virtual int		sendEvent(const std::pair<Event, Player *> &event);

    void		resizeMap(size_t w, size_t h);
    void		setIANumber(int number);
    void		setPlayer(unsigned int number);

    int			onPlayerPutBomb(IA *player);
    void		getFocus(int seed);
    void		setBattleWindow();
    Bombermap const	&getMap() const;
    MyContext const	&getContext() const;
    std::vector<Player *> const	&getPlayers() const;
    std::vector<IA *> const	&getIA() const;
    std::vector<Player *>		&modifyPlayers();
    std::vector<IA *>		&modifyIA();
    Bombermap		&modifyMap();

  private:
    int		onPlayerPutBomb(const std::pair<Event, Player *> &event);
    void	exploseBomb(Bomb *b);
    bool	checkExploseEntity(Bomb *bomb, int x, int y);
    bool	checkExploseEntity(ABonus *b, int x, int y);
    bool	exploseBombAt(Bomb *b, int x, int y);
    void	placePlayer(std::vector<Player *> &players);
    void	freePlayerSpot(size_t x, size_t y);

    Cube				_cube;
    Bombermap				_map;
    std::vector<IA *>			_ia;
    std::vector<IA *>			_dead_ia;
    std::vector<BattleWindow *>		_window;
    unsigned int			_player_number;
};

#endif /* !GAMEPLAY_HH_ */
