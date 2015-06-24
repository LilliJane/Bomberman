//
// Grid.hpp for  in /home/sabour_f/rendu/cpp_bomberman/includes
//
// Made by Florian SABOURIN
// Login   <sabour_f@epitech.net>
//
// Started on  Tue May 19 18:34:27 2015 Florian SABOURIN
// Last update Tue May 19 18:34:27 2015 Florian SABOURIN
//

#ifndef GRID_HPP
# define GRID_HPP

# include <vector>
# include <stdexcept>

template <typename T>
class Grid
{
  public:
    Grid(size_t w = 0, size_t h = 0) :
      _grid()
    {
      this->resize(w, h);
    }

    ~Grid()
    {
    }

    // WARNING
    // When changing the width of the grid
    // All indexes are invalidated
    void		resize(size_t w, size_t h)
    {
      this->_w = w;
      this->_h = h;
      this->_grid.resize(w * h);
    }

    T		&at(unsigned int x, unsigned int y)
    {
      if (x > this->_w || y > this->_h)
	throw std::out_of_range("Grid::at()");
      return (this->_grid[y * this->_w + x]);
    }

    const T	&at(unsigned int x, unsigned int y) const
    {
      if (x > this->_w || y > this->_h)
	throw std::out_of_range("Grid::at()");
      return (this->_grid[y * this->_w + x]);
    }

    size_t	width() const
    {
      return (this->_w);
    }

    size_t	height() const
    {
      return (this->_h);
    }

  private:
    // Using vector to ensure that all datas will be copied
    // when a reallocation happens
    std::vector<T>	_grid;
    size_t		_w;
    size_t		_h;
};

#endif // GRID_HPP
