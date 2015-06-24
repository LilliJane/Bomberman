//
// Bomb.hh for Bomb in /home/tack_g/rendu/cpp_bomberman
//
// Made by g tack
// Login   <tack_g@epitech.net>
//
// Started on  Tue May 19 12:16:00 2015 g tack
// Last update Sat Jun 13 17:20:01 2015 Emeline Gaulard
//

#ifndef BOMB_HH_
# define BOMB_HH_

# include "IMapEntity.hh"
# include "ATimeEntity.hh"
# include "ADrawable.hh"
# include "Timer.hh"
# include "Cube.hh"

class			Player;

class			Bomb :
    public Cube,
    public ATimeEntity,
    public IMapEntity
{
  public:
    Bomb(Player *p, unsigned int range = 2);
  Bomb(unsigned int range, unsigned int x, unsigned int y);
  virtual ~Bomb();

    virtual unsigned int getCellX() const;
    virtual unsigned int getCellY() const;

    unsigned int	getRange() const;

    virtual void	draw(const Time &t) const;
    Player		*getPlayer();
    void		reSetPlayer(Player *p);

  private:
    Player		*_play;
    Player		*_play2;
    unsigned int	_range;
    Time		_time;
};

#endif /* !BOMB_HH_ */
