//
// EventListener.hpp for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Wed May 13 21:05:42 2015 _p dumont
// Last update Wed May 13 21:05:43 2015 _p dumont
//

#ifndef EVENTLISTENER_HPP_
# define EVENTLISTENER_HPP_

# include <vector>

# include "AEventListener.hh"
# include "SdlContext.hh"

class Player;

class EventListener : public AEventListener
{
  public:
    EventListener();
    ~EventListener();

    template <class C>
    void	addListener(Player *p)
    {
      this->_listener.push_back(new C(p));
    }

    template <class C>
    void	addListener(gdl::SdlContext *data, Player *p)
    {
      this->_listener.push_back(new C(data, p));
    }

    bool	poolEvent(std::pair<Event, Player *> &event);

  private:
    std::vector<AEventListener *>	_listener;
};

#endif /* !EVENTLISTENER_HH_ */
