//
// MyContext.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Thu Jun 11 08:42:44 2015 _p dumont
// Last update Thu Jun 11 08:42:45 2015 _p dumont
//

#ifndef MYCONTEXT_HH_
# define MYCONTEXT_HH_

# include "SdlContext.hh"

class MyContext : public gdl::SdlContext
{
  public:
    MyContext();
    ~MyContext();

    SDL_GLContext	getSDL_GLContext() const;
    SDL_Window		*getSDL_Window() const;

  protected:
};

#endif /* !MYCONTEXT_HH_ */
