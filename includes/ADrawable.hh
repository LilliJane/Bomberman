//
// ADrawable.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Fri May 15 02:40:19 2015 _p dumont
// Last update Fri May 15 02:40:20 2015 _p dumont
//

#ifndef ADRAWABLE_HH_
# define ADRAWABLE_HH_

# include "Time.hh"

class ADrawable
{
  public:
    ADrawable(float x = 0, float y = 0, float z = 0);
    ADrawable(ADrawable const &ref);
    ADrawable &operator =(ADrawable const &ref);
    virtual ~ADrawable() = 0;

    virtual void	move(float x, float y, float z);

    float	getX() const;
    float	getY() const;
    float	getZ() const;

    virtual void	draw(Time const &t) const = 0;

  protected:
    float	_x;
    float	_y;
    float	_z;
};

#endif /* !ADRAWABLE_HH_ */
