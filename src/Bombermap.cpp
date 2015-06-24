//
// Bombermap.cpp for  in /home/sabour_f/rendu/cpp_bomberman/src
//
// Made by Florian SABOURIN
// Login   <sabour_f@epitech.net>
//
// Started on  Tue May 19 18:59:55 2015 Florian SABOURIN
// Last update Sun Jun 14 20:42:58 2015 Emeline Gaulard
//

#include <algorithm>
#include <cstdlib>
#include "Bombermap.hh"

Bombermap::Bombermap() :
  _grid(), _entities()
{
}

Bombermap::Bombermap(size_t w, size_t h) :
  _grid(w, h), _entities()
{
}

Bombermap::~Bombermap()
{
}

void		Bombermap::resize(size_t w, size_t h)
{
  this->_grid.resize(w, h);
}

size_t		Bombermap::width() const
{
  return (this->_grid.width());
}

size_t		Bombermap::height() const
{
  return (this->_grid.height());
}

/*
** Fills the map with random walls
** > seed the seed passed to srandom, if not 0
*/
void		Bombermap::generate_random(unsigned int seed)
{
  int		random_number;

  if (seed)
    std::srand(seed);
  for (size_t x = 0 ; x < this->_grid.width() ; ++x)
    for (size_t y = 0 ; y < this->_grid.height() ; ++y)
      {
	random_number = std::rand() % 4;
	if (!random_number)
	  {
	    if (!(std::rand() % 7))
	      this->_grid.at(x, y) = CELL_PERMA;
	    else
	      this->_grid.at(x, y) = CELL_WALL;
	  }
	else
	  this->_grid.at(x, y) = CELL_EMPTY;
      }
}

#include <iostream>
void		Bombermap::generate_map(std::vector<int> const &values)
{
  size_t	idx;

  idx = 0;
  for (size_t x = 0; x < _grid.width(); ++x)
    for (size_t y = 0; y < _grid.height(); ++y)
      {
	if (values[idx] == CELL_PERMA)
	  _grid.at(x, y) = CELL_PERMA;
	else if (values[idx] == CELL_WALL)
	  _grid.at(x, y) = CELL_WALL;
	else
	  _grid.at(x, y) = CELL_EMPTY;
	idx++;
      }
}

/*
** Adds an entity on the map
** ! e a valid entity
** ! e not already added
*/
void		Bombermap::add_entity(IEntity *e)
{
  this->_entities.push_back(e);
}

/*
** Removes an entity from the map
** = true if e was found, false otherwise
*/
bool		Bombermap::rm_entity(IEntity *e)
{
  std::vector<IEntity *>::iterator	it;

  it = std::find(this->_entities.begin(), this->_entities.end(), e);
  if (it == this->_entities.end())
    return (false);
  this->_entities.erase(it);
  return (true);
}

/*
** Returns the entities stored in the map
** = vector of entities
*/
std::vector<IEntity *>		&Bombermap::get_entities()
{
  return (this->_entities);
}

/*
** Returns the entities stored in the map
** = vector of entities
*/
const std::vector<IEntity *>	&Bombermap::get_entities() const
{
  return (this->_entities);
}

unsigned int			Bombermap::get_block_at(size_t x,
							size_t y) const
{
  if (x < this->_grid.width() &&
      y < this->_grid.height())
    return (this->_grid.at(x, y));
  return (CELL_PERMA);
}


void				Bombermap::rm_block_at(size_t x,
						       size_t y)
{
  if (x < this->_grid.width() &&
      y < this->_grid.height())
    {
      if (this->_grid.at(x, y) == CELL_WALL)
	this->addBonus(x, y);
      this->_grid.at(x, y) = CELL_EMPTY;
    }
}

void				Bombermap::wipe_cell(size_t x, size_t y)
{
  if (x < this->_grid.width() && y < this->_grid.height())
    this->_grid.at(x, y) = CELL_EMPTY;
}

void		Bombermap::bombBonus(size_t x, size_t y)
{
  bonusBomb	*b = new bonusBomb();

  b->move(x * 30.f, 0.f, y * 30.f);
  b->setTime(Time() + Time::second(10));
  this->add_entity(b);
}

void		Bombermap::rangeBonus(size_t x, size_t y)
{
  bonusRange	*b = new bonusRange();

  b->move(x * 30.f, 0.f, y * 30.f);
  b->setTime(Time() + Time::second(10));
  this->add_entity(b);
}

void		Bombermap::speedBonus(size_t x, size_t y)
{
  bonusSpeed	*b = new bonusSpeed();

  b->move(x * 30.f, 0.f, y * 30.f);
  b->setTime(Time() + Time::second(10));
  this->add_entity(b);
}

void		Bombermap::GPSBonus(size_t x, size_t y)
{
  bonusGPS	*b = new bonusGPS();

  b->move(x * 30.f, 0.f, y * 30.f);
  b->setTime(Time() + Time::second(10));
  this->add_entity(b);
}

void				Bombermap::addBonus(size_t x, size_t y)
{
  static void			(Bombermap::*tab[])(size_t, size_t) =
  {
      &Bombermap::bombBonus, &Bombermap::rangeBonus, &Bombermap::speedBonus,
      &Bombermap::bombBonus, &Bombermap::rangeBonus, &Bombermap::speedBonus,
      &Bombermap::bombBonus, &Bombermap::rangeBonus, &Bombermap::speedBonus,
      &Bombermap::bombBonus, &Bombermap::rangeBonus, &Bombermap::speedBonus,
      &Bombermap::bombBonus, &Bombermap::rangeBonus, &Bombermap::speedBonus,
      &Bombermap::bombBonus, &Bombermap::rangeBonus, &Bombermap::speedBonus,
      &Bombermap::bombBonus, &Bombermap::rangeBonus, &Bombermap::speedBonus,
      &Bombermap::bombBonus, &Bombermap::rangeBonus, &Bombermap::speedBonus,
      &Bombermap::bombBonus, &Bombermap::rangeBonus, &Bombermap::speedBonus,
      &Bombermap::bombBonus, &Bombermap::rangeBonus, &Bombermap::speedBonus,
      &Bombermap::GPSBonus
  };
  int				obj;

  obj = rand() % 2;
  if (obj)
    {
      obj = rand() % ((3 * 10) + 1);
      (this->*tab[obj])(x, y);
    }
}
