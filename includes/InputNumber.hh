//
// InputNumber.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Wed Jun 10 08:47:48 2015 _p dumont
// Last update Wed Jun 10 08:47:48 2015 _p dumont
//

#ifndef INPUTNUMBER_HH_
# define INPUTNUMBER_HH_

# include <climits>
# include <sstream>

# include "Text.hh"
# include "ISelectGUI.hh"

class InputNumber :
    virtual public ISelectGUI,
    virtual public Text
{
  public:
    InputNumber(int value = 0,
		float x = 0,
		float y = 0,
		int min_value = INT_MIN,
		int max_value = INT_MAX,
		unsigned int step = 1);
    virtual ~InputNumber();

    virtual void	draw(const Time &t) const;

    virtual void	select();
    virtual void	unselect();

    int			getValue() const;

    InputNumber &operator ++();
    InputNumber &operator --();

  protected:
    bool		_selected;
    int			_value;
    int			_min_value;
    int			_max_value;
    unsigned int	_step;
};


#endif /* !INPUTNUMBER_HH_ */
