//
// Player.cpp for Player in /home/tack_g/rendu/cpp_bomberman
//
// Made by g tack
// Login   <tack_g@epitech.net>
//
// Started on  Tue May 19 11:46:11 2015 g tack
// Last update Tue Jun  9 18:11:42 2015 Emeline Gaulard
//

#include <stdexcept>

#include "Player.hh"
#include "ResourceManager.hh"

#include "OpenGL.hh"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtx/rotate_vector.hpp"

int Player::_player = 0;

Player::Player(glm::vec4 color) :
  _score(0), _speed(0), _range(2), _life(1), _nbBombs(1), _camera(), _color(color)
{
  _x = 15.f;
  _y = 15.f;

  if (_player == 0)
    _keyboard = KeyConf();
  else
    _keyboard = KeyConf(SDLK_w, SDLK_s, SDLK_d, SDLK_a, SDLK_SPACE, 0, 0);
  this->_rotation = 0;
  this->_camera = glm::mat4(1);
  this->_camera = glm::scale(this->_camera, glm::vec3(0.07, 0.07, 0.07));
  for (unsigned int i = 0; i < _nbBombs; ++i)
    this->_bombs.push(new Bomb(this, _range));
  this->_skin = 0;
  this->_initialSpeed = _speed;
  this->_initialRange = _range;
  this->_rotation_delta = 0;
  this->_to_update = Time::second(0);
  this->_delta_x = 0;
  this->_delta_y = 0;
  this->_map = 0;
  this->_gps = false;
  ++_player;
}

Player::Player(unsigned int score, unsigned int speed,
	       float x, float y,
	       unsigned short range, unsigned short life,
	       unsigned short nbBombs) :
  _score(score),
  _speed(speed),
  _x(x),
  _y(y),
  _range(range),
  _life(life),
  _nbBombs(nbBombs)
{
  this->_skin = 0;
  this->_rotation_delta = 0;
  this->_to_update = Time::second(0);
  this->_delta_x = 0;
  this->_delta_y = 0;
  this->_map = 0;
  this->_gps = false;
}

Player::~Player()
{
  if (this->_skin)
    delete this->_skin;
}

unsigned int	Player::getCellX() const
{
  return ((unsigned int)(this->_x / 30.f));
}

unsigned int	Player::getCellY() const
{
  return ((unsigned int)(this->_y / 30.f));
}

void		Player::takeDamage()
{
  --this->_life;
  if (this->_life == (unsigned short)(-1))
    this->_life = 0;
  //clignote? perte de bonus? de score? Bref ici on meurt
}

void Player::setConf(const KeyConf &k)
{
  this->_keyboard = k;
}

unsigned int		Player::getScore() const
{
  return (this->_score);
}

unsigned int		Player::getSpeed() const
{
  return (this->_speed);
}

float			Player::getPosX() const
{
  return (this->_x);
}

float			 Player::getPosY() const
{
  return (this->_y);
}

unsigned short		Player::getRange() const
{
  return (this->_range);
}

unsigned short		Player::getNbBombs() const
{
  return (this->_nbBombs);
}

unsigned short		Player::getLife() const
{
  return (this->_life);
}

const KeyConf		&Player::getConf() const
{
  return (this->_keyboard);
}

KeyConf			&Player::getConf()
{
  return (this->_keyboard);
}

glm::mat4 const		&Player::getCamera() const
{
  glm::mat4		projection;
  glm::mat4		transformation;
  glm::vec3		cam(0, 120, -100);

  cam = glm::rotateY(cam, (float)(this->_rotation));
  cam.x -= this->_x;
  cam.z -= this->_y;
  ResourceManager::GetInstance()->GetShader().bind();
  projection = glm::perspective(60.0f, 800.0f / 600.0f, 0.1f, 10000.0f);
  transformation = glm::lookAt(cam, glm::vec3(-this->_x, 0, -this->_y), glm::vec3(0, 1, 0));
  if (!ResourceManager::GetInstance()->GetShader().setUniform("view", transformation) ||
      !ResourceManager::GetInstance()->GetShader().setUniform("projection", projection) ||
      !ResourceManager::GetInstance()->GetShader().setUniform("uColor", this->_color) ||
      !ResourceManager::GetInstance()->GetShader().setUniform("rColor", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)))
    throw (std::runtime_error("Can't set the shaders !"));
  return (this->_camera);
}

unsigned short		Player::getInitialRange() const
{
  return (this->_initialRange);
}

unsigned int		Player::getInitialSpeed() const
{
  return (this->_initialSpeed);
}

unsigned int		Player::getActualNbBombs() const
{
  return (this->_bombs.size());
}

void		Player::setScore(unsigned int score)
{
  _score = score;
}

void		Player::setSpeed(unsigned int speed)
{
  _speed = speed;
}

void		Player::setPosX(float x)
{
  _x = x;
}

void		Player::setPosY(float y)
{
  _y = y;
}

void		Player::setRange(unsigned short range)
{
  _range = range;
}

void		Player::setNbBombs(unsigned short nb)
{
  _nbBombs = nb;
}

float		Player::getRotation() const
{
  return ((float)(this->_rotation));
}

void		Player::setGPS(bool gps)
{
  this->_gps = gps;
}

bool		Player::getGPS() const
{
  return (this->_gps);
}

/*
** Returns a pointer to a bomb that has not previously be returned
** May return NULL if the player has no more bombs available
*/
Bomb	*Player::getBomb()
{
  Bomb	*b;

  b = 0;
  if (this->_bombs.size())
    {
      b = this->_bombs.front();
      this->_bombs.pop();
    }
  return (b);
}

void	Player::addBomb()
{
  this->_bombs.push(new Bomb(this, _range));
}

void	Player::addNbBomb()
{
  ++this->_nbBombs;
  this->addBomb();
}

void	Player::addSpeed()
{
  ++this->_speed;
}

void	Player::addRange()
{
  ++this->_range;
}

void	Player::setLife(unsigned short life)
{
  this->_life = life;
}

#include <iostream>
void			Player::moveForward(Bombermap &map)
{
  float			tmp_x = 0;
  float			tmp_y = 0;

  if (!this->_delta_x &&
      !this->_delta_y)
    this->_skin->setCurrentSubAnim("Forward", true);
  if (this->_rotation < 90)
    tmp_y -= 3.f + (3.f * this->_speed) / 10;
  else if (this->_rotation >= 90 &&
	   this->_rotation < 180)
    tmp_x -= 3.f + (3.f * this->_speed) / 10;
  else if (this->_rotation >= 180 &&
	   this->_rotation < 270)
    tmp_y += 3.f + (3.f * this->_speed) / 10;
  else
    tmp_x += 3.f + (3.f * this->_speed) / 10;

  this->_delta_x = tmp_x;
  this->_delta_y = tmp_y;
  this->_map = &map;
}

void			Player::moveBackward(Bombermap &map)
{
  float			tmp_x = 0;
  float			tmp_y = 0;

  if (!this->_delta_x &&
      !this->_delta_y)
    this->_skin->setCurrentSubAnim("Backward", true);
  if (this->_rotation < 90)
    tmp_y += 1.f + (1.f * this->_speed) / 10;
  else if (this->_rotation >= 90 &&
	   this->_rotation < 180)
    tmp_x += 1.f + (1.f * this->_speed) / 10;
  else if (this->_rotation >= 180 &&
	   this->_rotation < 270)
    tmp_y -= 1.f + (1.f * this->_speed) / 10;
  else
    tmp_x -= 1.f + (1.f * this->_speed) / 10;

  this->_delta_x = tmp_x;
  this->_delta_y = tmp_y;
  this->_map = &map;
}

void			Player::stopMove()
{
  this->_delta_x = 0;
  this->_delta_y = 0;
  this->_skin->setCurrentSubAnim("Stop", false);
}

void			Player::turnLeft()
{
  if (this->_rotation % 90 == 0)
    this->_rotation_delta = 10;
}

void			Player::turnRight()
{
  if (this->_rotation % 90 == 0)
    this->_rotation_delta = -10;
}

void			Player::draw(Time const &t) const
{
  if (!ResourceManager::GetInstance()->GetShader().setUniform("uColor", this->_color) ||
      !ResourceManager::GetInstance()->GetShader().setUniform("rColor", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)))
    throw (std::runtime_error("Can't set the shaders !"));
  glm::mat4 camera = glm::mat4(1);
  camera = glm::scale(camera, glm::vec3(0.07, 0.07, 0.07));
  camera = glm::translate(camera, glm::vec3(-this->_x / 0.07, 0, -this->_y / 0.07));
  camera = glm::rotate(camera, (float)(this->_rotation), glm::vec3(0, 1, 0));
  this->_skin->draw(ResourceManager::GetInstance()->GetShader(),
		    camera,
		    t.toDouble(t));
}

void			Player::update(Time const &t)
{
  Time			t2(t);
  float			tmp_x = this->_x + this->_delta_x;
  float			tmp_y = this->_y + this->_delta_y;

  if (this->_to_update >= t)
    this->_to_update -= t;
  else
    {
      t2 -= this->_to_update;
      this->_to_update = Time::second(0);
    }
  while (this->_to_update == Time::second(0))
    {
      this->_to_update = Time::millisecond(33);
      if (this->_to_update >= t2)
	this->_to_update -= t2;
      else
	{
	  t2 -= this->_to_update;
	  this->_to_update = Time::second(0);
	}
      this->_rotation = (this->_rotation + this->_rotation_delta + 360) % 360;
      if (this->_rotation % 90 == 0)
	this->_rotation_delta = 0;
      if (this->_rotation_delta == 0 &&
	  this->_map)
	{
	  if (this->tryMove(tmp_x, tmp_y, *(this->_map)))
	    this->checkCollisions(*(this->_map));
	}
    }
}

void			Player::loadSkin()
{
  if (!this->_skin)
    this->_skin = ResourceManager::GetInstance()->GetBomberman();
}

/*
** Tries to move to the coordinates (x;y)
** Checks for collisions in the map
** Updates the coordinates of the player if successful, does nothing otherwise
** = true if the player can move, false otherwise
*/
bool		Player::tryMove(float x, float y, const Bombermap &map)
{
  if (x >= 0.f && y >= 0.f &&
      map.get_block_at((int)(x / 30), (int)(y / 30)) == CELL_EMPTY)
    {
      this->_x = x;
      this->_y = y;
      return (true);
    }
  return (false);
}

/*
** Checks for collisions with entities (explosions, bombs, bonuses..)
*/
void		Player::checkCollisions(Bombermap &map)
{
  std::vector<IEntity *> &entities = map.get_entities();
  IMapEntity	*ent;
  size_t	i;

  i = 0;
  while (i < entities.size())
    {
      ent = dynamic_cast<IMapEntity *>(entities[i]);
      if (ent && ent->getCellX() == this->getCellX() &&
	  ent->getCellY() == this->getCellY())
	{
	  if (this->collBonus(dynamic_cast<ABonus *>(ent)))
	    entities.erase(entities.begin() + i);
	  else
	    {
	      this->collExplosion(dynamic_cast<Explosion *>(ent));
	      ++i;
	    }
	}
      else
	++i;
    }
}

/*
** Checks for collision between a bonus and the player
** If bonus is NULL, does nothing (so it works with dynamic casts)
** = true if the bonus was consumed, false otherwise
*/
bool		Player::collBonus(ABonus *bonus)
{
  if (!bonus)
    return (false);
  bonus->walkOnBonus(this);
  return (true);
}

/*
** Checks for collision between an explosion and the player
** If expl is NULL, does nothing (so it works with dynamic casts)
** = true if the player was , false otherwise
*/
bool		Player::collExplosion(Explosion *expl)
{
  if (!expl)
    return (false);
  this->takeDamage();
  return (true);
}
