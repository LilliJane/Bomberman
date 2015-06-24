//
// KeyboardListener.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Thu May 14 05:12:27 2015 _p dumont
// Last update Thu May 14 05:12:28 2015 _p dumont
//

#include "KeyboardListener.hh"
#include "Input.hh"

KeyboardListener::KeyboardListener(gdl::SdlContext *ctx, Player *p)
  : AEventListener(), _ctx(ctx), _play(p)
{
  for (int it = 0; it < 4; ++it)
    _release[it] = 0;
  this->_t.reset();
}

KeyboardListener::~KeyboardListener()
{
}

bool		KeyboardListener::poolEvent(std::pair<Event, Player *> &event)
{
  gdl::Input	*i;

  i = ResourceManager::GetInstance()->GetInput();
  this->_ctx->updateInputs(*i);
  if (this->_t.getElapsedTime() > Time::millisecond(100))
    {
      if (i->getKey(this->_play->getConf().getRet()))
	{
	  this->_t.reset();
	  this->_events.push(std::pair<Event, Player *>(Escape, _play));
	}
      if (i->getKey(this->_play->getConf().getUp()))
	{
	  this->_t.reset();
	  _release[0] = 2;
	  this->_events.push(std::pair<Event, Player *>(Up, _play));
	}
      else if (_release[0])
	{
	  this->_t.reset();
	  --_release[0];
	  if (!_release[0])
	    this->_events.push(std::pair<Event, Player *>(Up_release, _play));
	}
      if (i->getKey(this->_play->getConf().getDown()))
	{
	  this->_t.reset();
	  _release[1] = 2;
	  this->_events.push(std::pair<Event, Player *>(Down, _play));
	}
      else if (_release[1])
	{
	  this->_t.reset();
	  --_release[1];
	  if (!_release[1])
	    this->_events.push(std::pair<Event, Player *>(Down_release, _play));
	}
      if (i->getKey(this->_play->getConf().getRight()))
	{
	  this->_t.reset();
	  _release[2] = 2;
	  this->_events.push(std::pair<Event, Player *>(Right, _play));
	}
      else if (_release[2])
	{
	  this->_t.reset();
	  --_release[2];
	  if (!_release[2])
	    this->_events.push(std::pair<Event, Player *>(Right_release, _play));
	}
      if (i->getKey(this->_play->getConf().getLeft()))
	{
	  this->_t.reset();
	  _release[3] = 2;
	  this->_events.push(std::pair<Event, Player *>(Left, _play));
	}
      else if (_release[3])
	{
	  this->_t.reset();
	  --_release[3];
	  if (!_release[3])
	    this->_events.push(std::pair<Event, Player *>(Left_release, _play));
	}
      if (i->getKey(this->_play->getConf().getPutBomb()))
	{
	  this->_t.reset();
	  this->_events.push(std::pair<Event, Player *>(PutBomb, _play));
	}
      if (i->getKey(this->_play->getConf().getEnter()))
	{
	  this->_t.reset();
	  this->_events.push(std::pair<Event, Player *>(Enter, _play));
	}
    }
  return (AEventListener::poolEvent(event));
}
