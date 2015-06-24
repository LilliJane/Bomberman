//
// Button.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Fri May 15 03:56:51 2015 _p dumont
// Last update Fri May 15 03:56:52 2015 _p dumont
//

#include "Button.hh"

Button::Button(const std::string &txt, float x, float y)
  : ADrawable(x, y, 0), ISelectGUI(), Text(txt, x, y)
{
  this->_selected = false;
}

Button::Button(const Button &ref)
  : ADrawable(ref), Text(ref)
{
    this->_selected = ref._selected;
}

Button &Button::operator =(Button const &ref)
{
  Text::operator =(ref);
  this->_selected = ref._selected;
  return (*this);
}

Button::~Button()
{

}

void	Button::draw(Time const &t) const
{
  (void)(t);
  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  gluOrtho2D(0, 800, 0, 600);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  glDisable(GL_DEPTH_TEST);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glBegin(GL_QUADS);
  if (this->_selected)
    glColor3ub(255 - this->_r, 255 - this->_g, 255 - this->_b);
  else
    glColor3ub(0, 0, 0);
  {
    glVertex2f(this->_x, this->_y);
    glVertex2f(this->_right, this->_y);
    glVertex2f(this->_right, this->_bot);
    glVertex2f(this->_x, this->_bot);
    glColor3ub(255, 255, 255);
  }
  glEnd();

  glDisable(GL_BLEND);
  glEnable(GL_DEPTH_TEST);

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  Text::draw();
}

void	Button::select()
{
  this->_selected = true;
}

void	Button::unselect()
{
  this->_selected = false;
}
