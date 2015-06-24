//
// ISelectGUI.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Wed Jun 10 07:05:59 2015 _p dumont
// Last update Wed Jun 10 07:06:00 2015 _p dumont
//

#ifndef ISELECTGUI_HH_
# define ISELECTGUI_HH_

# include "ADrawable.hh"

class		ISelectGUI : virtual public ADrawable
{
  public:
    ISelectGUI();
    virtual ~ISelectGUI() = 0;

    virtual void	select() = 0;
    virtual void	unselect() = 0;

    virtual void	draw(const Time &t) const = 0;
};

#endif /* !ISELECTGUI_HH_ */
