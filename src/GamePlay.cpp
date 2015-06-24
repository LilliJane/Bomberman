//
// GamePlay.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Tue May 19 18:00:56 2015 _p dumont
// Last update Sun Jun 14 19:04:45 2015 Emeline Gaulard
//

#include <stdexcept>
#include <ctime>

#include "GamePlay.hh"
#include "GamePause.hh"
#include "ResourceManager.hh"
#include "Player.hh"
#include "GameScore.hh"

#include "OpenGL.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

GamePlay::GamePlay(Game *g)
  : GameState(g),
    _cube(0, 30, -30, 30, -30, 30),
    _map(200, 200)
{
  _cube.setTexture("crate.tga");
  this->_player_number = 1;
}

GamePlay::~GamePlay()
{
  glUseProgram(0);
  glClearColor(0, 0, 0, 0);
  for (std::vector<IA *>::iterator it = this->_ia.begin();
       it != this->_ia.end();
       ++it)
    delete (*it);
  for (std::vector<IA *>::iterator it = this->_dead_ia.begin();
       it != this->_dead_ia.end();
       ++it)
    delete (*it);
  for (std::vector<BattleWindow *>::iterator it = this->_window.begin();
       it != this->_window.end();
       ++it)
    delete (*it);
  if (SDL_GL_MakeCurrent(this->_actual_game->getContext().getSDL_Window(),
			 this->_actual_game->getContext().getSDL_GLContext()))
    throw (std::runtime_error(SDL_GetError()));
}

int			GamePlay::update(const Time &t)
{
  Time			new_t = t;
  std::vector<IEntity *> &entities = this->_map.get_entities();
  unsigned int		alive = 0;

  for (std::vector<Player *>::iterator it = this->_actual_game->getPlayers().begin();
       it != this->_actual_game->getPlayers().end();
       ++it)
    {
      if ((*it)->getLife())
	++alive;
    }
  if ((alive == 1 && this->_ia.size() == 0) ||
      (alive == 0 && this->_ia.size()))
    {
      this->_actual_game->changeState(new GameScore(this->_actual_game));
      return (1);
    }
  for (unsigned int i = 0 ; i < entities.size() ; ++i)
    {
      ATimeEntity *timedEntitiy = dynamic_cast<ATimeEntity *>(entities[i]);
      if (timedEntitiy)
	{
	  if (timedEntitiy->hasExpired())
	    {
	      Bomb	*bob = dynamic_cast<Bomb *>(timedEntitiy);
	      if (bob)
		this->exploseBomb(bob);
	      else
		{
		  this->_map.rm_entity(timedEntitiy);
		  delete timedEntitiy;
		}
	    }
	}
    }
  for (std::vector<IA *>::iterator it = this->_ia.begin();
       it != this->_ia.end();
       ++it)
    {
      (*it)->doIAThing(this->_map, this);
      (*it)->update(t);
    }
  for (std::vector<Player *>::iterator it = this->_actual_game->getPlayers().begin();
       it != this->_actual_game->getPlayers().end();
       ++it)
    {
      (*it)->update(t);
    }
  for (std::vector<BattleWindow *>::reverse_iterator it = this->_window.rbegin();
       it != this->_window.rend();
       ++it)
    {
      (*it)->draw(new_t);
    }
  return (0);
}

int		GamePlay::sendEvent(const std::pair<Event, Player *> &event)
{
  if (event.first == Escape)
    {
      this->_actual_game->pushState(new GamePause(_actual_game, _map, _ia));
      return (1);
    }
  if (event.first == Up)
    {
      event.second->moveForward(this->_map);
      return (0);
    }
  if (event.first == Down)
    {
      event.second->moveBackward(this->_map);
      return (0);
    }
  if (event.first == Up_release)
    {
      event.second->stopMove();
      return (0);
    }
  if (event.first == Down_release)
    {
      event.second->stopMove();
      return (0);
    }
  if (event.first == Left)
    {
      event.second->turnLeft();
      return (0);
    }
  if (event.first == Right)
    {
      event.second->turnRight();
      return (0);
    }
  if (event.first == PutBomb)
    return (this->onPlayerPutBomb(event));
  return (0);
}

void		GamePlay::resizeMap(size_t w, size_t h)
{
  this->_map.resize(w, h);
  this->_map.generate_random(time(NULL));
}

void		GamePlay::setIANumber(int number)
{
  if (this->_ia.size())
    {
      for (std::vector<IA *>::iterator it = this->_ia.begin();
	   it != this->_ia.end();
	   ++it)
	delete (*it);
    }
  for (int i = 0; i < number; ++i)
    this->_ia.push_back(new IA());
}

void		GamePlay::setPlayer(unsigned int number)
{
  this->_player_number = number;
  if (this->_actual_game->getPlayers().size() < this->_player_number)
    this->_player_number = this->_actual_game->getPlayers().size();
  for (std::vector<Player *>::iterator it = this->_actual_game->getPlayers().begin();
       it !=  this->_actual_game->getPlayers().end();
       ++it)
    {
      (*it)->loadSkin();
    }
}

/*
** check for entity for explosion.
** ! bomb valid pointer
*/
bool				GamePlay::checkExploseEntity(Bomb *bomb, int x, int y)
{
  if (!bomb->hasExpired() &&
      (int)bomb->getCellX() == x && (int)bomb->getCellY() == y)
    {
      bomb->setTime(Time());
      this->exploseBomb(bomb);
      return (false);
    }
  return (true);
}

bool				GamePlay::checkExploseEntity(ABonus *b, int x, int y)
{
  if (!b->hasExpired() &&
      b->getX() == x && b->getZ() == y)
    {
      this->_map.rm_entity(b);
      return (true);
    }
  return (true);
}

/*
** Generates an explosion for the bomb with specified offsets
** Checks for collision
** If the blast is stopped (by a crate / wall), the function returns false
** = true if the explosion was not blocked, false otherwise
*/
bool				GamePlay::exploseBombAt(Bomb *b,
							int x,
							int y)
{
  Explosion			*explosion;
  Player			*p;
  std::vector<IEntity *>	entities = this->_map.get_entities();
  int				expl_x;
  int				expl_y;

  expl_x = b->getCellX() + x;
  expl_y = b->getCellY() + y;
  for (unsigned int i = 0;
       i < this->_actual_game->getPlayers().size();
       ++i)
    {
      p = this->_actual_game->getPlayers()[i];
      if (b->getPlayer() &&
	  (int)p->getCellX() == expl_x && (int)p->getCellY() == expl_y)
	{
	  p->takeDamage();
	  if (b->getPlayer() != p)
	    b->getPlayer()->setScore(b->getPlayer()->getScore() + 1);
	  else
	    b->getPlayer()->setScore(b->getPlayer()->getScore() == 0 ? 0 : b->getPlayer()->getScore() - 1);
	}
      if (p->getLife() == 0)
	{
	  p->setPosX(-500);
	  p->setPosY(-500);
	}
    }
  for (std::vector<IA *>::iterator it = this->_ia.begin();
       it != this->_ia.end();
       ++it)
    {
      p = (*it);
      if (b->getPlayer() &&
	  (int)p->getCellX() == expl_x && (int)p->getCellY() == expl_y)
	{
	  p->takeDamage();
	  b->getPlayer()->setScore(b->getPlayer()->getScore() + 1);
	}
      if (p->getLife() == 0)
	{
	  this->_dead_ia.push_back(*it);
	  this->_ia.erase(it);
	  --it;
	}
    }
  if (this->_map.get_block_at(expl_x, expl_y) == CELL_EMPTY)
    {
      explosion = new Explosion();
      explosion->move(expl_x * 30, b->getY(), expl_y * 30);
      explosion->setTime(Time() + Time::millisecond(500));
      this->_map.add_entity(explosion);
      for (unsigned int i = 0; i < entities.size() ; ++i)
	{
	  if (dynamic_cast<Bomb *>(entities[i]))
	    {
	      (dynamic_cast<Bomb *>(entities[i]))->reSetPlayer(b->getPlayer());
	      if (!checkExploseEntity(dynamic_cast<Bomb *>(entities[i]),
				      expl_x, expl_y))
		return (false);
	    }
	  else if (dynamic_cast<ABonus *>(entities[i]))
	    {
	      if (!checkExploseEntity(dynamic_cast<ABonus *>(entities[i]),
				      expl_x, expl_y))
		return (false);
	    }
	}
      return (true);
    }
  else if (this->_map.get_block_at(b->getCellX() + x, b->getCellY() + y) == CELL_WALL)
    {
      explosion = new Explosion();
      explosion->move(expl_x * 30.f,
		      b->getY(),
		      expl_y * 30.f);
      explosion->setTime(Time() + Time::millisecond(500));
      this->_map.add_entity(explosion);
      this->_map.rm_block_at(b->getCellX() + x, b->getCellY() + y);
    }
  return (false);
}

void				GamePlay::exploseBomb(Bomb *b)
{
  this->exploseBombAt(b, 0, 0);
  for (unsigned int j = 1;
       j <= b->getRange()
       && this->exploseBombAt(b, 0, j);
       ++j)
    ;
  for (unsigned int j = 1;
       j <= b->getRange()
       && this->exploseBombAt(b, 0, (signed)(-j));
       ++j)
    ;
  for (unsigned int j = 1;
       j <= b->getRange()
       && this->exploseBombAt(b, j, 0);
       ++j)
    ;
  for (unsigned int j = 1;
       j <= b->getRange()
       && this->exploseBombAt(b, (signed)(-j), 0);
       ++j)
    ;
  ResourceManager::GetInstance()->PlaySound(0);
  this->_map.rm_entity(b);
  delete b;
}

int		GamePlay::onPlayerPutBomb(const std::pair<Event, Player *> &event)
{
  Player	*player;
  Bomb	*bomb;
  int	cellx;
  int	celly;

  player = event.second;
  bomb = player->getBomb();
  if (bomb)
    {
      cellx = (int)(player->getCellX());
      celly = (int)(player->getCellY());
      bomb->move(cellx * 30.f, 0.f, celly * 30.f);
      bomb->setTime(Time() + Time::second(5));
      this->_map.add_entity(bomb);
    }
  return (0);
}

void		GamePlay::getFocus(int seed)
{
  std::vector<Player *>		full;
  Player			*p;
  Bomb				*b;

  for (std::vector<Player *>::iterator it = this->_actual_game->getPlayers().begin();
       it !=  this->_actual_game->getPlayers().end();
       ++it)
    {
      p = (*it);
      p->loadSkin();
      p->setLife(0);
      p->setPosX(-500);
      p->setPosY(-500);
      p->setNbBombs(1);
      p->stopMove();
      p->setGPS(false);
      if (!(b = p->getBomb()))
	p->addBomb();
      else
	delete b;
    }
  for (unsigned int i = 0;
       i < this->_player_number;
       ++i)
    full.push_back(this->_actual_game->getPlayers()[i]);
  this->setBattleWindow();
  for (std::vector<IA *>::iterator it = this->_ia.begin();
       it != this->_ia.end();
       ++it)
    full.push_back(*it);
  if (seed)
    this->resizeMap(seed * 40, seed * 40);
  this->_map.generate_random(seed);
  this->placePlayer(full);
}

void		GamePlay::setBattleWindow()
{
  for (unsigned int i = 0;
       i < this->_player_number;
       ++i)
    {
      this->_window.push_back(new BattleWindow(this, this->_actual_game->getPlayers()[i], i));
    }
}

void		GamePlay::placePlayer(std::vector<Player *> &players)
{
  unsigned int	i;
  size_t	nb_players;
  float		h = this->_map.height() * 15.f * 0.999f;
  float		w = this->_map.width() * 15.f * 0.999f;

  i = 0;
  nb_players = players.size();
  for (std::vector<Player *>::iterator it = players.begin();
       it != players.end(); ++it)
    {
      (*it)->setLife(1);
      (*it)->setPosX(std::cos((M_PI * 2.f * i) / nb_players) * w + w);
      (*it)->setPosY(std::sin((M_PI * 2.f * i) / nb_players) * h + h);
      this->freePlayerSpot((*it)->getCellX(), (*it)->getCellY());
      ++i;
    }
}

void		GamePlay::freePlayerSpot(size_t x, size_t y)
{
  this->_map.wipe_cell(x - 1, y - 1);
  this->_map.wipe_cell(x - 1, y    );
  this->_map.wipe_cell(x - 1, y + 1);
  this->_map.wipe_cell(x    , y - 1);
  this->_map.wipe_cell(x    , y    );
  this->_map.wipe_cell(x    , y + 1);
  this->_map.wipe_cell(x + 1, y - 1);
  this->_map.wipe_cell(x + 1, y    );
  this->_map.wipe_cell(x + 1, y + 1);
}

Bombermap const		&GamePlay::getMap() const
{
  return (this->_map);
}

MyContext const		&GamePlay::getContext() const
{
  return (this->_actual_game->getContext());
}

std::vector<Player *> const	&GamePlay::getPlayers() const
{
  return (this->_actual_game->getPlayers());
}

std::vector<IA *> const		&GamePlay::getIA() const
{
  return (this->_ia);
}

std::vector<Player *>		&GamePlay::modifyPlayers()
{
  return (this->_actual_game->getPlayers());
}
std::vector<IA *>		&GamePlay::modifyIA()
{
  return (_ia);
}

Bombermap			&GamePlay::modifyMap()
{
  return (_map);
}

int		GamePlay::onPlayerPutBomb(IA *player)
{
  Bomb		*bomb;
  int		cellx;
  int		celly;

  bomb = player->getBomb();
  if (bomb)
    {
      cellx = (int)(player->getCellX());
      celly = (int)(player->getCellY());
      bomb->move(cellx * 30.f, 0.f, celly * 30.f);
      bomb->setTime(Time() + Time::second(5));
      this->_map.add_entity(bomb);
    }
  return (0);
}
