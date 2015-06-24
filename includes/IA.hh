//
// IA.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Wed Jun 10 15:14:46 2015 _p dumont
// Last update Wed Jun 10 15:14:47 2015 _p dumont
//

#ifndef IA_HH_
# define IA_HH_

# include <utility>
# include <queue>
# include "Player.hh"
# include "Time.hh"

class GamePlay;

class IA : virtual public Player
{
  public:
    IA();
    ~IA();

    virtual void	doIAThing(Bombermap &map,
				  GamePlay *game);

  private:
    class Coor
    {
      public:
	Coor(unsigned int x = 0, unsigned int y = 0);
	unsigned int x;
	unsigned int y;

	bool	operator ==(const Coor &rhs) const;
	bool	operator !=(const Coor &rhs) const;
    };

    class CoorNode
    {
      public:
	CoorNode(unsigned int x = 0, unsigned int y = 0, unsigned int dist = 0, CoorNode *parent = NULL);

	bool	operator ==(const CoorNode &rhs) const;
	bool	operator !=(const CoorNode &rhs) const;

	Coor	coor;
	CoorNode *parent;
	unsigned int dist;
    };

    void		flee(const Bombermap &map);
    void		lookForBonuses(const Bombermap &map);
    void		placeOffensive(const Bombermap &map);

    bool		cellIsSafe(const Bombermap &map, unsigned int x, unsigned int y) const;
    void		AIMove(Bombermap &map);
    void		checkDirection();
    void		putBomb(Bombermap &map, Bomb *bomb);
    bool		willBombHitPlayer(GamePlay *game) const;
    bool		hasBombOn(const Bombermap &map, unsigned int x, unsigned int y) const;
    bool		onePlayerStillAlive(GamePlay *game) const;

    void		findPath(const Bombermap &map,
				 bool (IA::*canwalkon)(const Bombermap &, unsigned int, unsigned int) const,
				 bool (IA::*isgoal)(const Bombermap &, unsigned int, unsigned int) const,
				 bool (IA::*walkpredicate)(const Bombermap &, unsigned int, unsigned int) const);
    void		findPathAddFrontier(const Bombermap &map,
					    std::deque<CoorNode> &frontier,
					    const std::deque<CoorNode> &visited,
					    const CoorNode &node,
					    bool (IA::*canwalkon)(const Bombermap &, unsigned int, unsigned int) const,
					    bool (IA::*walkpredicate)(const Bombermap &, unsigned int, unsigned int) const) const;
    void		findPathPushPath(CoorNode &node);

    bool		predicateCanWalkOn(const Bombermap &map, unsigned int x, unsigned int y) const;
    bool		predicateIsSafe(const Bombermap &map, unsigned int x, unsigned int y) const;
    bool		predicateHasBonus(const Bombermap &map, unsigned int x, unsigned int y) const;
    bool		predicateIsNearPlayer(const Bombermap &map, unsigned int x, unsigned int y) const;

    GamePlay	*gameplay;
    bool	moving;
    std::queue<Coor>	moves;
    Time	last_calculation;
};

#endif /* !IA_HH_ */
