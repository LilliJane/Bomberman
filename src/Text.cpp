//
// Text.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Fri May 15 03:00:19 2015 _p dumont
// Last update Fri May 15 03:00:19 2015 _p dumont
//

#include <stdexcept>

#include "Text.hh"
#include "ResourceManager.hh"

#define CHAR_X 35 / 2
#define TEXT_X 0.00815
#define CHAR_Y 64 / 2

double		Text::_char_position[256] =
{
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X, //10
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X, //20
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X, //30
  63 * TEXT_X,
  63 * TEXT_X,
  68 * TEXT_X, // '!'
  82 * TEXT_X, // ' " '
  81 * TEXT_X, // '#'
  63 * TEXT_X,
  70 * TEXT_X, // '%'
  63 * TEXT_X,
  63 * TEXT_X,
  74 * TEXT_X, //40 '('
  75 * TEXT_X, // ')'
  71 * TEXT_X, // '*'
  73 * TEXT_X, //'+'
  62 * TEXT_X, // ','
  72 * TEXT_X, // '-'
  65 * TEXT_X, // '.'
  67 * TEXT_X, // '/'
  52 * TEXT_X, //0
  53 * TEXT_X, //1
  54 * TEXT_X, //2
  55 * TEXT_X, //3
  56 * TEXT_X, //4
  57 * TEXT_X, //5
  58 * TEXT_X, //6
  59 * TEXT_X, //7
  60 * TEXT_X, //8
  61 * TEXT_X, //9
  66 * TEXT_X, //:
  64 * TEXT_X, // ';'
  83 * TEXT_X, //60 '<'
  63 * TEXT_X,
  84 * TEXT_X, // '>'
  63 * TEXT_X, // '?'
  63 * TEXT_X, // should be '@'
  0  * TEXT_X, //A
  1  * TEXT_X, //B
  2  * TEXT_X, //C
  3  * TEXT_X, //D
  4  * TEXT_X, //E
  5  * TEXT_X, //F
  6  * TEXT_X, //G
  7  * TEXT_X, //H
  8  * TEXT_X, //I
  9  * TEXT_X, //J
  10 * TEXT_X, //K
  11 * TEXT_X, //L
  12 * TEXT_X, //M
  13 * TEXT_X, //N
  14 * TEXT_X, //O
  15 * TEXT_X, //P
  16 * TEXT_X, //Q
  17 * TEXT_X, //R
  18 * TEXT_X, //S
  19 * TEXT_X, //T
  20 * TEXT_X, //U
  21 * TEXT_X, //V
  22 * TEXT_X, //W
  23 * TEXT_X, //X
  24 * TEXT_X, //Y
  25 * TEXT_X, //Z
  76 * TEXT_X, // '['
  63 * TEXT_X,
  77 * TEXT_X, // ']'
  63 * TEXT_X,
  87 * TEXT_X, // '_'
  86 * TEXT_X, // '`' magic quote
  26 * TEXT_X, //a
  27 * TEXT_X, //b
  28 * TEXT_X, //c
  29 * TEXT_X, //d
  30 * TEXT_X, //e
  31 * TEXT_X, //f
  32 * TEXT_X, //g
  33 * TEXT_X, //h
  34 * TEXT_X, //i
  35 * TEXT_X, //j
  36 * TEXT_X, //k
  37 * TEXT_X, //l
  38 * TEXT_X, //m
  39 * TEXT_X, //n
  40 * TEXT_X, //o
  41 * TEXT_X, //p
  42 * TEXT_X, //q
  43 * TEXT_X, //r
  44 * TEXT_X, //s
  45 * TEXT_X, //t
  46 * TEXT_X, //u
  47 * TEXT_X, //v
  48 * TEXT_X, //w
  49 * TEXT_X, //x
  50 * TEXT_X, //y
  51 * TEXT_X, //z
  78 * TEXT_X, // '{'
  85 * TEXT_X, // '|'
  79 * TEXT_X, // '}'
  80 * TEXT_X, // '~"
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X,
  63 * TEXT_X
};

Text::Text(std::string const &txt,
	   float x,
	   float y)
  : ADrawable(x, y, 0)
{
  this->_txt = txt;
  this->_a = 0;
  this->_r = 0;
  this->_g = 0;
  this->_b = 0;
  this->_bot = y + CHAR_Y;
  this->_right = this->_x + txt.size() * CHAR_X;;
}

Text::Text(Text const &ref) :
  ADrawable(ref)
{
  this->_txt = ref._txt;
  this->_a = ref._a;
  this->_r = ref._r;
  this->_g = ref._g;
  this->_b = ref._b;
  this->_bot = ref._bot;
  this->_right = ref._right;
}

Text &Text::operator =(Text const &ref)
{
  ADrawable::operator =(ref);
  this->_txt = ref._txt;
  this->_a = ref._a;
  this->_r = ref._r;
  this->_g = ref._g;
  this->_b = ref._b;
  this->_bot = ref._bot;
  this->_right = ref._right;
  return (*this);
}

Text::~Text()
{

}

std::string	Text::getText() const
{
  return (this->_txt);
}

void		Text::setText(std::string const &txt)
{
  this->_txt = txt;
  this->_right = this->_x + txt.size() * CHAR_X;
}

void		Text::setColor(unsigned short r,
			       unsigned short g,
			       unsigned short b,
			       unsigned short a)
{
  this->_a = a;
  this->_r = r;
  this->_g = g;
  this->_b = b;
}

void	Text::draw(Time const &t) const
{
  (void)t;

  glMatrixMode(GL_MODELVIEW);
  glPushMatrix();
  glLoadIdentity();

  gluOrtho2D(0, 800, 0, 600);
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  glDisable(GL_DEPTH_TEST);
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glBindTexture(GL_TEXTURE_2D, ResourceManager::GetInstance()->GetFontTexture());

  for (unsigned int i = 0;
       i < this->_txt.length();
       ++i)
    {
      if (this->_txt[i] != ' ' &&
	  this->_txt[i] != '\t')
	{
	  glBegin(GL_QUADS);
	  {
	    glColor3ub(this->_r, this->_g, this->_b);

	    glTexCoord2f(this->_char_position[(int)(this->_txt[i])], 1);
	    glVertex2f(this->_x + i * CHAR_X, this->_y + CHAR_Y);
	    glTexCoord2f(this->_char_position[(int)(this->_txt[i])] + 0.0075, 1);
	    glVertex2f(this->_x + i * CHAR_X + CHAR_X, this->_y + CHAR_Y);
	    glTexCoord2f(this->_char_position[(int)(this->_txt[i])] + 0.0075, 0);
	    glVertex2f(this->_x + i * CHAR_X + CHAR_X, this->_y);
	    glTexCoord2f(this->_char_position[(int)(this->_txt[i])], 0);
	    glVertex2f(this->_x + i * CHAR_X, this->_y);
	    glColor3ub(255, 255, 255);
	  }
	  glEnd();
	}
    }

  glDisable(GL_BLEND);
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_DEPTH_TEST);

  //glMatrixMode(GL_PROJECTION);
  glPopMatrix();
  glMatrixMode(GL_MODELVIEW);
  glPopMatrix();

}
