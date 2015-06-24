//
// bonusRange.hh for bonusRange in /home/tack_g/rendu/cpp_bomberman
//
// Made by g tack
// Login   <tack_g@epitech.net>
//
// Started on  Tue Jun  9 13:20:36 2015 g tack
// Last update Sat Jun 13 17:33:40 2015 Emeline Gaulard
//

#ifndef BONUSRANGE_HH_
# define BONUSRANGE_HH_

# include "ABonus.hh"

class		Player;

class		bonusRange : public ABonus
{
  public:
    bonusRange();
  bonusRange(unsigned int x, unsigned int y);
    virtual ~bonusRange();

    virtual void walkOnBonus(Player *p) const;

  private:
    Time	_time;
};

#endif /* !BONUSRANGE_HH_ */
