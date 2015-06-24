//
// Explosion.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Tue Jun  2 23:32:49 2015 _p dumont
// Last update Tue Jun  2 23:32:50 2015 _p dumont
//

#ifndef EXPLOSION_HH_
# define EXPLOSION_HH_

# include "ATimeEntity.hh"
# include "IMapEntity.hh"
# include "ADrawable.hh"
# include "Timer.hh"
# include "Cube.hh"

class			Explosion : public Cube, public ATimeEntity, public IMapEntity
{
  public:
    Explosion();
    virtual ~Explosion();

    virtual void	draw(const Time &t) const;

    virtual unsigned int getCellX() const;
    virtual unsigned int getCellY() const;

  private:
    unsigned int	_range;
    Time		_time;
};

#endif /* !EXPLOSION_HH_ */
