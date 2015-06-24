//
// IBonus.hh for IBonus in /home/tack_g/rendu/cpp_bomberman
//
// Made by g tack
// Login   <tack_g@epitech.net>
//
// Started on  Tue Jun  9 14:01:02 2015 g tack
// Last update Sat Jun 13 17:31:41 2015 Emeline Gaulard
//

#ifndef IBONUS_HH_
# define IBONUS_HH_

# include "ATimeEntity.hh"
# include "Cube.hh"
# include "IMapEntity.hh"

# define BONUSBOMB 1
# define BONUSSPEED 2
# define BONUSRANGE 3
# define BONUSGPS 4

class Player;
/*
** Represents a bonus on the map
** Just cast into ABonus to know if entity is a bonus or bomb
** virtual method for all bonus (walk into = add bonus)
*/
class		ABonus : public Cube, public ATimeEntity, public IMapEntity
{
  public:
    ABonus();
  ABonus(unsigned int x, unsigned int y);
  virtual ~ABonus() = 0;

    virtual void walkOnBonus(Player *p) const = 0;

    virtual unsigned int getCellX() const;
    virtual unsigned int getCellY() const;
  virtual int		getType() const;
protected:
  int	_type;
};

#endif /* !IBONUS_HH_ */
