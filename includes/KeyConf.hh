//
// KeyConf.hh for KeyConf in /home/tack_g/rendu/cpp_bomberman
//
// Made by g tack
// Login   <tack_g@epitech.net>
//
// Started on  Tue May 19 19:58:36 2015 g tack
// Last update Tue May 19 19:58:36 2015 g tack
//

#ifndef KEYCONF_HH_
# define KEYCONF_HH_

# include <vector>
# include "SDL_keycode.h"

class		KeyConf
{
  public:
    KeyConf(unsigned int up = SDLK_UP, unsigned int down = SDLK_DOWN,
	    unsigned int right = SDLK_RIGHT, unsigned int left = SDLK_LEFT,
	    unsigned int bomb = SDLK_RCTRL,
	    unsigned int ret = SDLK_ESCAPE, unsigned int enter = SDLK_RETURN);
    virtual ~KeyConf();

    unsigned int	getUp() const;
    unsigned int	getDown() const;
    unsigned int	getRight() const;
    unsigned int	getLeft() const;
    unsigned int	getRet() const;
    unsigned int	getEnter() const;
    unsigned int	getPutBomb() const;

    bool		alreadyExist(unsigned int c) const;
    void		addNewKey(unsigned int id, unsigned int k);

    void		setUp(unsigned int c);
    void		setDown(unsigned int c);
    void		setRight(unsigned int c);
    void		setLeft(unsigned int c);
    void		setPutBomb(unsigned int c);

    void		operator =(KeyConf const &k);

  private:
    unsigned int	_conf[7];
};

#endif /* !KEYCONF_HH_ */
