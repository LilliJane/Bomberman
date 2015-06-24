//
// bonusGPS.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Sun Jun 14 15:52:37 2015 _p dumont
// Last update Sun Jun 14 15:52:37 2015 _p dumont
//

#ifndef BONUSGPS_HH_
# define BONUSGPS_HH_

# include "ABonus.hh"

class		Player;

class		bonusGPS : public ABonus
{
  public:
    bonusGPS();
    bonusGPS(unsigned int x, unsigned int y);
    virtual ~bonusGPS();

    virtual void	walkOnBonus(Player *p) const;
    virtual void	draw(const Time &t) const;

  private:
    Time	_time;
};

#endif /* !BONUSGPS_HH_ */
