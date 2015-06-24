//
// Button.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Fri May 15 03:56:43 2015 _p dumont
// Last update Fri May 15 03:56:43 2015 _p dumont
//

#ifndef BUTTON_HH_
# define BUTTON_HH_

# include "Text.hh"
# include "ISelectGUI.hh"

class Button :
    virtual public ISelectGUI,
    virtual public Text
{
  public:
    Button(std::string const &txt = "", float x = 0, float y = 0);
    Button(Button const &ref);
    Button &operator =(Button const &ref);
    virtual ~Button();

    virtual void	draw(Time const &t = Time::second(0)) const;

    virtual void	select();
    virtual void	unselect();

  protected:
    bool		_selected;
};

#endif /* !BUTTON_HH_ */
