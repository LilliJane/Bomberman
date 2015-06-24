//
// bonusBomb.hh for bonusBomb in /home/tack_g/rendu/cpp_bomberman
//
// Made by g tack
// Login   <tack_g@epitech.net>
//
// Started on  Tue Jun  9 13:20:54 2015 g tack
// Last update Sat Jun 13 17:34:27 2015 Emeline Gaulard
//

#ifndef BONUSBOMB_HH_
# define BONUSBOMB_HH_

# include "ABonus.hh"

class		Player;

class		bonusBomb : public ABonus
{
  public:
    bonusBomb();
  bonusBomb(unsigned int x, unsigned int y);
  virtual ~bonusBomb();

    virtual void	walkOnBonus(Player *p) const;
    virtual void	draw(const Time &t) const;

  private:
    Time	_time;
};

#endif /* !BONUSBOMB_HH_ */
