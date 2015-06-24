//
// MyContext.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Thu Jun 11 08:42:55 2015 _p dumont
// Last update Thu Jun 11 08:42:55 2015 _p dumont
//

#include "MyContext.hh"

MyContext::MyContext() : gdl::SdlContext()
{

}

MyContext::~MyContext()
{

}

SDL_GLContext		MyContext::getSDL_GLContext() const
{
  return (this->_glContext);
}

SDL_Window		*MyContext::getSDL_Window() const
{
  return (this->_window);
}
