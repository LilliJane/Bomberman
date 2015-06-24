//
// IA.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Wed Jun 10 15:14:53 2015 _p dumont
// Last update Wed Jun 10 15:14:53 2015 _p dumont
//

#include <iostream>
#include "IA.hh"
#include "GamePlay.hh"

IA::Coor::Coor(unsigned int x, unsigned int y) :
  x(x), y(y)
{
}

bool		IA::Coor::operator ==(const IA::Coor &rhs) const
{
  return (this->x == rhs.x && this->y == rhs.y);
}

bool		IA::Coor::operator !=(const IA::Coor &rhs) const
{
  return (this->x != rhs.x || this->y != rhs.y);
}

IA::CoorNode::CoorNode(unsigned int x, unsigned int y, unsigned int dist, IA::CoorNode *parent) :
  coor(x, y), parent(parent), dist(dist)
{
}

bool		IA::CoorNode::operator ==(const IA::CoorNode &rhs) const
{
  return (this->coor == rhs.coor);
}

bool		IA::CoorNode::operator !=(const IA::CoorNode &rhs) const
{
  return (this->coor != rhs.coor);
}

IA::IA() :
  Player(glm::vec4(0.1, 0.1, 0.1, 1)),
  moving(false), moves()
{
  this->setLife(1);
  this->loadSkin();
}

IA::~IA()
{
}

void		IA::doIAThing(Bombermap &map,
			      GamePlay *game)
{
  if (!this->onePlayerStillAlive(game))
    return ;
  this->gameplay = game;
  if (this->_bombs.size() &&
      this->willBombHitPlayer(game) &&
      !this->hasBombOn(map, this->getCellX(), this->getCellY()))
    this->putBomb(map, this->getBomb());
  if (!this->moving)
    {
      if (!this->cellIsSafe(map, this->getCellX(), this->getCellY()))
	this->flee(map);
      else
	this->lookForBonuses(map);
      if (!this->moving)
	this->placeOffensive(map);
    }
  if (this->moving)
    this->AIMove(map);
}

/*
** Finds the nearest cell which is safe (c.f. cellIsSafe)
*/
void		IA::flee(const Bombermap &map)
{
  this->findPath(map, &IA::predicateCanWalkOn, &IA::cellIsSafe, NULL);
}

/*
** Finds a path to a cell where there is a bonus
*/
void		IA::lookForBonuses(const Bombermap &map)
{
  for (std::vector<IEntity *>::const_iterator it = map.get_entities().begin() ;
       it != map.get_entities().end() ; ++it)
    if (dynamic_cast<ABonus *>(*it))
      this->findPath(map, &IA::predicateCanWalkOn, &IA::predicateHasBonus, &IA::predicateIsSafe);
}

/*
** Finds a path to place the AI offensively
*/
void		IA::placeOffensive(const Bombermap &map)
{
  this->findPath(map, &IA::predicateCanWalkOn, &IA::predicateIsNearPlayer, &IA::predicateIsSafe);
}

/*
** Pushes to this->moves the cells the AI has to move to in order to flee
*/
void		IA::findPathPushPath(IA::CoorNode &node)
{
  if (node.parent)
    {
      this->findPathPushPath(*node.parent);
      this->moves.push(node.coor);
    }
}

/*
** Checks if a cell is safe or not
** A cell is considered as safe if all these conditions are met :
** - It is empty
** - The cell is not in range of a bomb (not including possible collisions with
**   crates)
** = true if the cell is safe, false otherwise
*/
bool	IA::cellIsSafe(const Bombermap &map, unsigned int x, unsigned int y) const
{
  const std::vector<IEntity *>	&ents = map.get_entities();
  const Bomb	*bomb;

  if (map.get_block_at(x, y) != CELL_EMPTY)
    return (false);

  /* For each entity, check if it is a bomb */
  for (size_t i = 0 ; i < ents.size() ; ++i)
    {
      bomb = dynamic_cast<Bomb *>(ents[i]);
      if (bomb)
	{
	  /* If it is, check its coordinates and range */
	  if ((bomb->getCellX() == x && (unsigned int)std::abs((int)bomb->getCellY() - (int)y) <= bomb->getRange()) ||
	      (bomb->getCellY() == y && (unsigned int)std::abs((int)bomb->getCellX() - (int)x) <= bomb->getRange()))
	    return (false);
	}
    }
  return (true);
}

/*
** Makes the AI move
** Is different from ADrawable::move
*/
void	IA::AIMove(Bombermap &map)
{
  if (!this->moves.size())
    {
      this->moving = false;
      return ;
    }
  this->checkDirection();
  this->moveForward(map);
  if (this->getCellX() == this->moves.front().x &&
      this->getCellY() == this->moves.front().y)
    {
      this->moves.pop();
      if (!this->moves.size())
	{
	  this->last_calculation = Time::second(0);
	  this->stopMove();
	}
    }
}

/*
** Checks the orientation of the AI (for its next move)
*/
void		IA::checkDirection()
{
  unsigned int	dst;
  const Coor	&nextmove(this->moves.front());

  if (nextmove.x < this->getCellX())
    dst = 90;
  else if (nextmove.x > this->getCellX())
    dst = 270;
  else if (nextmove.y < this->getCellY())
    dst = 0;
  else if (nextmove.y > this->getCellY())
    dst = 180;
  else
    return ;
  if (dst == (this->_rotation + 360 - 90) % 360)
    this->turnRight();
  else if (this->_rotation != dst)
    this->turnLeft();
}

/*
** The AI will put the bomb to its coordinates
** bomb may be NULL
*/
void		IA::putBomb(Bombermap &map, Bomb *bomb)
{
  if (!bomb)
    return ;
  bomb->move(this->getCellX() * 30.f, 0.f, this->getCellY() * 30.f);
  map.add_entity(bomb);
  bomb->setTime(Time() + Time::second(5));
}

/*
** If the AI puts a bomb now, will it hit a player ?
** = true if it will, false otherwise
*/
bool		IA::willBombHitPlayer(GamePlay *game) const
{
  Player	*pl;
  for (std::vector<Player *>::const_iterator it = game->getPlayers().begin() ;
       it != game->getPlayers().end() ; ++it)
    {
      pl = *it;
      if ((pl->getCellX() == this->getCellX() && (std::abs<int>(this->getCellY() - pl->getCellY())) <= this->getRange()) ||
	  (pl->getCellY() == this->getCellY() && (std::abs<int>(this->getCellX() - pl->getCellX())) <= this->getRange()))
	return (true);
    }
  return (false);
}

/*
** Checks if there is already a bomb on a cell
** = true if there is, false otherwise
*/
bool	IA::hasBombOn(const Bombermap &map, unsigned int x, unsigned int y) const
{
  Bomb	*bomb;

  for (std::vector<IEntity *>::const_iterator it = map.get_entities().begin() ;
       it != map.get_entities().end() ; ++it)
    if ((bomb = dynamic_cast<Bomb *>(*it)))
      if (bomb->getCellX() == x && bomb->getCellY() == y)
	return (true);
  return (false);
}

/*
** Warning : doesn't take into account AI
** = true if one player at least is alive, false otherwise
*/
bool		IA::onePlayerStillAlive(GamePlay *game) const
{
  for (std::vector<Player *>::const_iterator it = game->getPlayers().begin() ;
       it != game->getPlayers().end() ; ++it)
    if ((*it)->getLife())
      return (true);
  return (false);
}

/*
** Pathfinding algorithm of AI
** It will go, if possible to a cell for which isgoal returns true
** It will never go on cells for which canwalkon returns false
** If defined, it will avoid cells for which walkpredicate returns false
** If no cell is found, it ignores walkpredicate
*/
void	IA::findPath(const Bombermap &map,
		     bool (IA::*canwalkon)(const Bombermap &, unsigned int, unsigned int) const,
		     bool (IA::*isgoal)(const Bombermap &, unsigned int, unsigned int) const,
		     bool (IA::*walkpredicate)(const Bombermap &, unsigned int, unsigned int) const)
{
  /* We are going to explore cells one by one, from the nearest to the farthest
     * The frontier is composed of the cells we have to visit, i.e. those we
     * haven't visited yet and that are next to a cell we already visited
     * A node's parent is the previous cell the AI has to reach before reaching
     * the node's coordinates :
     *   from (0;0), to reach (0;2) you need to walk on (0;1)
     *   (0;0) is (0;1)'s parent, which is (0;2)'s parent */
  std::deque<CoorNode>	frontier;
  std::deque<CoorNode>	visited;
  CoorNode		current;

  if (last_calculation + Time::millisecond(1000) > Time())
    return ;

  while (this->moves.size())
    this->moves.pop();
  current.coor.x = this->getCellX();
  current.coor.y = this->getCellY();
  current.parent = NULL;
  frontier.push_back(current);
  while (frontier.size())
    {
      /* Get new cell */
      current = frontier.front();
      frontier.pop_front();

      /* If the cell is the goal and the walk predicate, if defined, is true */
      if ((this->*isgoal)(map, current.coor.x, current.coor.y))
	{
	  this->findPathPushPath(current);
	  this->moving = true;
	  this->last_calculation = Time();
	  return ;
	}

      /* Or else add to visited cells the current cell */
      visited.push_back(current);

      /* Add to the frontier any cell next to the current one */
      this->findPathAddFrontier(map, frontier, visited, CoorNode(current.coor.x + 1, current.coor.y, current.dist + 1, &visited.back()), canwalkon, walkpredicate);
      this->findPathAddFrontier(map, frontier, visited, CoorNode(current.coor.x - 1, current.coor.y, current.dist + 1, &visited.back()), canwalkon, walkpredicate);
      this->findPathAddFrontier(map, frontier, visited, CoorNode(current.coor.x, current.coor.y + 1, current.dist + 1, &visited.back()), canwalkon, walkpredicate);
      this->findPathAddFrontier(map, frontier, visited, CoorNode(current.coor.x, current.coor.y - 1, current.dist + 1, &visited.back()), canwalkon, walkpredicate);
    }
  if (walkpredicate)
    this->findPath(map, canwalkon, isgoal, NULL);
}

/*
** Add node to frontier, if not already visited
*/
void	IA::findPathAddFrontier(const Bombermap &map,
				std::deque<IA::CoorNode> &frontier,
				const std::deque<IA::CoorNode> &visited,
				const IA::CoorNode &node,
				bool (IA::*canwalkon)(const Bombermap &, unsigned int, unsigned int) const,
				bool (IA::*walkpredicate)(const Bombermap &, unsigned int, unsigned int) const) const
{
  /* If the cell is too far (avoid long path calculations) */
  if (node.dist > 10)
    return ;

  /* If the predicate is false, don't do anything */
  if (!(this->*canwalkon)(map, node.coor.x, node.coor.y))
    return ;

  /* If there is a walkpredicate, don't add if it returns false */
  if (walkpredicate && !(this->*walkpredicate)(map, node.coor.x, node.coor.y))
    return ;

  /* If we already visited the cell or it is in the frontier, do not push
   * It avoids the program to take an exponential amount of memory and to try
   * going several times on the same cell */
  for (std::deque<IA::CoorNode>::const_iterator it = visited.begin() ;
       it != visited.end() ; ++it)
    if (*it == node)
      return ;
  for (std::deque<IA::CoorNode>::const_iterator it = frontier.begin() ;
       it != frontier.end() ; ++it)
    if (*it == node)
      return ;

  /* Else push back the node */
  frontier.push_back(node);
}

/*
** Method to be passed as a pointer to know if the AI can walk on the cell
** = true if it can, false otherwise
*/
bool	IA::predicateCanWalkOn(const Bombermap &map, unsigned int x, unsigned int y) const
{
  return (map.get_block_at(x, y) == CELL_EMPTY);
}

/*
** Method to be passed as a pointer to know if the cell is safe
** = true if it is, false otherwise
*/
bool	IA::predicateIsSafe(const Bombermap &map, unsigned int x, unsigned int y) const
{
  return (this->cellIsSafe(map, x, y));
}

/*
** Method to be passed as a pointer to know if the cell contains a bonus
** = true if it has, false otherwise
*/
bool	IA::predicateHasBonus(const Bombermap &map, unsigned int x, unsigned int y) const
{
  const std::vector<IEntity *>	&entities = map.get_entities();
  const ABonus			*bonus;

  for (std::vector<IEntity *>::const_iterator it = entities.begin() ;
       it != entities.end() ; ++it)
    if ((bonus = dynamic_cast<ABonus *>(*it)))
      if (bonus->getCellX() == x && bonus->getCellY() == y)
	return (true);
  return (false);
}

/*
** Method to be passed as a pointer to know if the cell is in range of a player
** Uses the internal gameplay
** = true if it is, false otherwise
*/
bool		IA::predicateIsNearPlayer(const Bombermap &map, unsigned int x, unsigned int y) const
{
  Player	*pl;

  (void)(map);
  for (std::vector<Player *>::const_iterator it = this->gameplay->getPlayers().begin() ;
       it != this->gameplay->getPlayers().end() ; ++it)
    {
      pl = *it;
      if ((pl->getCellX() == x && (std::abs<int>(y - pl->getCellY())) <= this->getRange()) ||
	  (pl->getCellY() == y && (std::abs<int>(x - pl->getCellX())) <= this->getRange()))
	return (true);
    }
  return (false);
}

