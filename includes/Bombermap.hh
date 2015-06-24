//
// Bombermap.hh for  in /home/sabour_f/rendu/cpp_bomberman/includes
//
// Made by Florian SABOURIN
// Login   <sabour_f@epitech.net>
//
// Started on  Tue May 19 18:59:45 2015 Florian SABOURIN
// Last update Sun Jun 14 20:40:08 2015 Emeline Gaulard
//

#ifndef BOMBERMAP_HH_
# define BOMBERMAP_HH_

# include "Grid.hpp"
# include "IEntity.hh"
# include "bonusBomb.hh"
# include "bonusRange.hh"
# include "bonusSpeed.hh"
# include "bonusGPS.hh"

# define CELL_TOTAL	3	// Total
# define CELL_PERMA	2	// Undestructible wall
# define CELL_WALL	1	// Wall
# define CELL_EMPTY	0	// Nothing

class Bombermap
{
public:
  Bombermap();
  Bombermap(size_t w, size_t h);
  ~Bombermap();

  void		resize(size_t w, size_t h);
  size_t	width() const;
  size_t	height() const;
  void		generate_random(unsigned int seed = 0);
  void		generate_map(std::vector<int> const &values);
  void		add_entity(IEntity *e);
  bool		rm_entity(IEntity *e);

  std::vector<IEntity *>	&get_entities();
  const std::vector<IEntity *>	&get_entities() const;

  unsigned int			get_block_at(size_t x, size_t y) const;
  void				rm_block_at(size_t x, size_t y);
  void				wipe_cell(size_t x, size_t y);
private:
  void	bombBonus(size_t x, size_t y);
  void	rangeBonus(size_t x, size_t y);
  void	speedBonus(size_t x, size_t y);
  void	GPSBonus(size_t x, size_t y);
  void	addBonus(size_t x, size_t y);

  Grid<unsigned int>		_grid;
  std::vector<IEntity *>	_entities;
};

#endif /* !BOMBERMAP_HH_ */
