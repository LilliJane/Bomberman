//
// bonusSpeed.hh for bonusSpeed in /home/tack_g/rendu/cpp_bomberman
//
// Made by g tack
// Login   <tack_g@epitech.net>
//
// Started on  Tue Jun  9 13:21:02 2015 g tack
// Last update Sat Jun 13 17:32:55 2015 Emeline Gaulard
//

#ifndef BONUSSPEED_HH_
# define BONUSSPEED_HH_

# include "ABonus.hh"

class		Player;

class		bonusSpeed : public ABonus
{
  public:
    bonusSpeed();
  bonusSpeed(unsigned int x, unsigned int y);
  virtual ~bonusSpeed();

    virtual void	walkOnBonus(Player *p) const;

  private:
    Time	_time;
};

#endif /* !BONUSSPEED_HH_ */
