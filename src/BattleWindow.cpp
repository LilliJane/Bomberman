//
// BattleWindow.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Thu Jun 11 08:08:13 2015 _p dumont
// Last update Thu Jun 11 08:08:15 2015 _p dumont
//

#include "BattleWindow.hh"
#include "GamePlay.hh"
#include "Text.hh"
#include <sstream>
#include <string>
#include <iostream>

BattleWindow::BattleWindow(GamePlay const *g,
			   Player const *focus_player,
			   bool create_new_window)
  : _game(g),
    _cube(0, 30, -30, 30, -30, 30)
{
  this->_focus_player = focus_player;
  if (create_new_window)
    {
      if (SDL_GL_SetAttribute(SDL_GL_SHARE_WITH_CURRENT_CONTEXT, 1))
	throw (std::runtime_error(SDL_GetError()));
      this->_context = new MyContext();
      if (!this->_context->start(800, 600, "Bomberman : player 2"))
	throw (std::runtime_error("Can't open a new window"));
    }
  else
    this->_context = 0;
}

BattleWindow::~BattleWindow()
{
  if (this->_context)
    {
      if (SDL_GL_MakeCurrent(this->_context->getSDL_Window(),
			     this->_context->getSDL_GLContext()))
	throw (std::runtime_error(SDL_GetError()));
      SDL_DestroyWindow(this->_context->getSDL_Window());
      SDL_GL_DeleteContext(this->_context->getSDL_GLContext());
      delete this->_context;
    }
  if (SDL_GL_MakeCurrent(this->_game->getContext().getSDL_Window(),
			 this->_game->getContext().getSDL_GLContext()))
    throw (std::runtime_error(SDL_GetError()));
}

void		BattleWindow::draw(Time const &t)
{
  if (this->_context)
    {
      if (SDL_GL_MakeCurrent(this->_context->getSDL_Window(), this->_context->getSDL_GLContext()))
	throw (std::runtime_error(SDL_GetError()));
    }
  else
    {
      if (SDL_GL_MakeCurrent(this->_game->getContext().getSDL_Window(),
			     this->_game->getContext().getSDL_GLContext()))
	throw (std::runtime_error(SDL_GetError()));
    }
  glClearColor(255, 255, 255, 0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_DEPTH_TEST);
  this->_focus_player->getCamera();

  this->_cube.setTexture("ground.tga");
  if (_cube.getTxid())
    {
      ResourceManager::GetInstance()->GetTexture(_cube.getTxid()).bind();
      for (int i = -12; i < 12; ++i)
	for (int j = -12; j < 12; ++j)
	  {
	    _cube.move((this->_focus_player->getCellX() + i) * 30,
		       0,
		       (this->_focus_player->getCellY() + j) * 30);
	    this->_cube.draw(t);
	  }
    }
  _cube.setTexture("crate.tga");
  if (_cube.getTxid())
    {
      ResourceManager::GetInstance()->GetTexture(_cube.getTxid()).bind();
      this->drawCubesMatching(CELL_WALL, -30, t);
    }
  _cube.setTexture("wall.tga");
  if (_cube.getTxid())
    {
      ResourceManager::GetInstance()->GetTexture(_cube.getTxid()).bind();
      this->drawCubesMatching(CELL_PERMA, -30, t);
    }
  this->drawPlayer(t);
  this->drawEntities(t);
  if (this->_focus_player->getGPS())
    {
      glm::mat4		mat(1.f);
      gdl::Geometry	_base_geometry;
      glm::mat4		transformation;
      glm::vec3		cam(0, 120, -100);
      Player		*p = 0;
      float		angle = 0;
      float		d =
	  this->_game->getMap().height() *
	  this->_game->getMap().height() +
	  this->_game->getMap().width() *
	  this->_game->getMap().width();

      for (std::vector<Player *>::const_iterator it = this->_game->getPlayers().begin();
	   it != this->_game->getPlayers().end();
	   ++it)
	{
	  if ((*it) != this->_focus_player)
	    {
	      if ((this->_focus_player->getCellX() - (*it)->getCellX()) *
		  (this->_focus_player->getCellX() - (*it)->getCellX()) +
		  (this->_focus_player->getCellY() - (*it)->getCellY()) *
		  (this->_focus_player->getCellY() - (*it)->getCellY()) < d)
		{
		  p = (*it);
		  d = (this->_focus_player->getCellX() - (*it)->getCellX()) *
		      (this->_focus_player->getCellX() - (*it)->getCellX()) +
		      (this->_focus_player->getCellY() - (*it)->getCellY()) *
		      (this->_focus_player->getCellY() - (*it)->getCellY());
		}
	    }
	}
      for (std::vector<IA *>::const_iterator it = this->_game->getIA().begin();
	   it != this->_game->getIA().end();
	   ++it)
	{
	  if ((this->_focus_player->getCellX() - (*it)->getCellX()) *
	      (this->_focus_player->getCellX() - (*it)->getCellX()) +
	      (this->_focus_player->getCellY() - (*it)->getCellY()) *
	      (this->_focus_player->getCellY() - (*it)->getCellY()) < d)
	    {
	      p = (*it);
	      d = (this->_focus_player->getCellX() - (*it)->getCellX()) *
		  (this->_focus_player->getCellX() - (*it)->getCellX()) +
		  (this->_focus_player->getCellY() - (*it)->getCellY()) *
		  (this->_focus_player->getCellY() - (*it)->getCellY());
	    }
	}
      if (p)
	{
	  angle = 90 - atan2((double)(p->getCellY()) - (double)(this->_focus_player->getCellY()),
			     (double)(p->getCellX()) - (double)(this->_focus_player->getCellX())) / M_PI * 180;
	}

      transformation = glm::lookAt(cam, glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
      if (!ResourceManager::GetInstance()->GetShader().setUniform("view", transformation) ||
	  !ResourceManager::GetInstance()->GetShader().setUniform("uColor", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) ||
	  !ResourceManager::GetInstance()->GetShader().setUniform("rColor", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)))
	throw (std::runtime_error("Can't set the shaders !"));

      _base_geometry.pushUv(glm::vec2(0.f, 0.f));
      _base_geometry.pushUv(glm::vec2(0.f, 1.f));
      _base_geometry.pushUv(glm::vec2(1.f, 1.f));
      _base_geometry.pushUv(glm::vec2(1.f, 0.f));
      _base_geometry.pushVertex(glm::vec3(1.f,	0.f,	1.f));
      _base_geometry.pushVertex(glm::vec3(1.f,	0.f,	-1.f));
      _base_geometry.pushVertex(glm::vec3(-1.f,	0.f,	-1.f));
      _base_geometry.pushVertex(glm::vec3(-1.f,	0.f,	1.f));
      mat = glm::translate(mat, glm::vec3(60, 80, 0));
      mat = glm::scale(mat, glm::vec3(10, 10, 10));
      mat = glm::rotate(mat, angle - this->_focus_player->getRotation(), glm::vec3(0, 1, 0));
      if (!_base_geometry.build())
	throw std::runtime_error("Cannot build cube geometry");
      ResourceManager::GetInstance()->GetTexture(
	    ResourceManager::GetInstance()->LoadTexture("GPS.tga")).bind();
      _base_geometry.draw(ResourceManager::GetInstance()->GetShader(),
			  mat,
			  GL_QUADS);
    }
  glUseProgram(0);
  this->displayHud();
  glClearDepth(1.0);

  if (this->_context)
    this->_context->flush();
}

/*
** Draws all cubes on the map matching the value passed in parameter
*/
void		BattleWindow::drawCubesMatching(unsigned int value,
						float y,
						Time const &t)
{
  int		playerX;
  int		playerY;

  playerX = this->_focus_player->getCellX();
  playerY = this->_focus_player->getCellY();
  for (int i = -10; i < 10; ++i)
    {
      for (int j = -10; j < 10; j++)
	{
	  if (this->_game->getMap().get_block_at(playerX + i, playerY + j) == value)
	    {
	      _cube.move((playerX + i/* + 1*/) * 30, y, (playerY + j/* + 1*/) * 30);
	      _cube.draw(t);
	    }
	}
    }
}

void		BattleWindow::drawPlayer(Time const &t)
{
  int		playerX;
  int		playerY;
  Player const	*p;

  playerX = this->_focus_player->getCellX();
  playerY = this->_focus_player->getCellY();
  for (std::vector<Player *>::const_iterator it = this->_game->getPlayers().begin();
       it != this->_game->getPlayers().end();
       ++it)
    {
      p = (*it);
      if ((signed)(p->getCellX()) >= playerX - 10 &&
	  (signed)(p->getCellX()) <= playerX + 10 &&
	  (signed)(p->getCellY()) >= playerY - 10 &&
	  (signed)(p->getCellY()) <= playerY + 10)
	p->draw(t);
    }
  for (std::vector<IA *>::const_iterator it = this->_game->getIA().begin();
       it != this->_game->getIA().end();
       ++it)
    {
      p = (*it);
      if ((signed)(p->getCellX()) >= playerX - 10 &&
	  (signed)(p->getCellX()) <= playerX + 10 &&
	  (signed)(p->getCellY()) >= playerY - 10 &&
	  (signed)(p->getCellY()) <= playerY + 10)
	p->draw(t);
    }
}

/*
** Method for draw bonus
** b must be a valid pointer
** AND b must be a valid bonus
*/
void				BattleWindow::drawEntity(ABonus *b, const Time &t)
{
  if (!ResourceManager::GetInstance()->GetShader().setUniform("rColor", glm::vec4(0.0f, 0.0f, 0.0f, -1.0f)))
    throw (std::runtime_error("Can't set the shaders !"));
  b->bindTx();
  b->draw(t);
}

void				BattleWindow::drawEntity(Bomb *bomb, const Time &t)
{
  if (!ResourceManager::GetInstance()->GetShader().setUniform("uColor", glm::vec4(1.0f, 1.0f, 1.0f, 1.0f)) ||
      !ResourceManager::GetInstance()->GetShader().setUniform("rColor", glm::vec4(1.0f, 1.0f, 1.0f, 0.0f)))
    throw (std::runtime_error("Can't set the shaders !"));
  bomb->bindTx();
  bomb->draw(t);
}

void				BattleWindow::drawEntity(Explosion *explosion, const Time &t)
{
  if (!ResourceManager::GetInstance()->GetShader().setUniform("uColor", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)) ||
      !ResourceManager::GetInstance()->GetShader().setUniform("rColor", glm::vec4(0.0f, 0.0f, 0.0f, 1.0f)))
    throw (std::runtime_error("Can't set the shaders !"));
  explosion->bindTx();
  explosion->draw(t);
}

void				BattleWindow::drawEntities(const Time &t)
{
  std::vector<IEntity *> const	&entities = this->_game->getMap().get_entities();

  for (unsigned int i = 0 ; i < entities.size() ; ++i)
    {
      if (dynamic_cast<Explosion *>(entities[i]))
	this->drawEntity(dynamic_cast<Explosion *>(entities[i]), t);
      else if (dynamic_cast<Bomb *>(entities[i]))
	this->drawEntity(dynamic_cast<Bomb *>(entities[i]), t);
      else
	this->drawEntity(dynamic_cast<ABonus *>(entities[i]), t);
    }
}

void					BattleWindow::displayHud()
{
  std::stringstream			ss;
  std::string				str;
  int					rng = 0;
  short					spd = 0;

  if (this->_focus_player->getRange() > this->_focus_player->getInitialRange())
    rng = this->_focus_player->getRange() - this->_focus_player->getInitialRange();
  if (this->_focus_player->getSpeed() > this->_focus_player->getInitialSpeed())
    spd = this->_focus_player->getSpeed() - this->_focus_player->getInitialSpeed();
  if (spd != 0 && rng != 0)
    {
      ss << "Speed:" << this->_focus_player->getSpeed() << "(+" << spd
	 << ") Bombs:" << this->_focus_player->getActualNbBombs() << " Range:" <<
	    this->_focus_player->getRange() << "(+" << rng << ")" <<
	    " Score:" << this->_focus_player->getScore();
    }
  else if (spd != 0 && rng == 0)
    {
      ss << "Speed:" << this->_focus_player->getSpeed() << "(+" << spd
	 << ") Bombs:" << this->_focus_player->getActualNbBombs() << " Range:"
	 << this->_focus_player->getRange() << " Score:"
	 << this->_focus_player->getScore();
    }
  else if (spd == 0 && rng != 0)
    {
      ss << "Speed:" << this->_focus_player->getSpeed() << " Bombs:" <<
	    this->_focus_player->getActualNbBombs() << " Range:" <<
	    this->_focus_player->getRange() << "(+" << rng << ")" <<
	    " Score:" << this->_focus_player->getScore();
    }
  else
    {
      ss << "Speed:" << this->_focus_player->getSpeed() << " Bombs:"
	 << this->_focus_player->getActualNbBombs() << " Range:"
	 << this->_focus_player->getRange() << " Score:"
	 << this->_focus_player->getScore();
    }
  str = ss.str();
  Text	txt(str);
  txt.setColor(155, 155, 155);
  txt.draw();
}
