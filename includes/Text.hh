//
// Text.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Fri May 15 03:00:13 2015 _p dumont
// Last update Fri May 15 03:00:13 2015 _p dumont
//

#ifndef TEXT_HH_
# define TEXT_HH_

# include <string>

# include "ADrawable.hh"

# include "OpenGL.hh"

class Text : virtual public ADrawable
{
  public:
    Text(std::string const &txt = "",
	 float x = 0,
	 float y = 0);
    Text(Text const &ref);
    Text &operator =(Text const &ref);
    virtual ~Text();

    std::string		getText() const;
    void		setText(std::string const &txt);
    void		setColor(unsigned short r,
				 unsigned short g,
				 unsigned short b,
				 unsigned short a = 0);

    virtual void	draw(Time const &t = Time::second(0)) const;

  protected:
    static double	_char_position[256];

    std::string		_txt;
    unsigned short	_r;
    unsigned short	_g;
    unsigned short	_b;
    unsigned short	_a;
    double		_bot;
    double		_right;
};

#endif /* !TEXT_HH_ */
