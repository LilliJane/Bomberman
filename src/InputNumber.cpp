//
// InputNumber.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Wed Jun 10 08:48:01 2015 _p dumont
// Last update Wed Jun 10 08:48:02 2015 _p dumont
//

#include "InputNumber.hh"

InputNumber::InputNumber(int value,
			 float x,
			 float y,
			 int min_value,
			 int max_value,
			 unsigned int step) :
  ADrawable(x, y, 0),
  ISelectGUI(),
  Text("", x, y)
{
  std::stringstream	sstream;

  this->_value = value;
  this->_selected = false;
  this->_min_value = min_value;
  this->_max_value = max_value;
  this->_step = step;
  sstream << this->_value;
  this->setText(sstream.str());
}

InputNumber::~InputNumber()
{

}

void	InputNumber::draw(const Time &t) const
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

void	InputNumber::select()
{
  this->_selected = true;
}

void	InputNumber::unselect()
{
  this->_selected = false;
}

int	InputNumber::getValue() const
{
  return (this->_value);
}

InputNumber	&InputNumber::operator ++()
{
  std::stringstream	sstream;

  if (this->_value <= this->_max_value - (signed)(this->_step))
    this->_value += this->_step;
    sstream << this->_value;
  this->setText(sstream.str());
  return (*this);
}

InputNumber	&InputNumber::operator --()
{
  std::stringstream	sstream;

  if (this->_value >= this->_min_value + (signed)(this->_step))
    this->_value -= this->_step;
  sstream << this->_value;
  this->setText(sstream.str());
  return (*this);
}
