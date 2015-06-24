//
// GamePlaySetting.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Wed Jun 10 06:48:27 2015 _p dumont
// Last update Wed Jun 10 06:48:27 2015 _p dumont
//

#ifndef GAMEPLAYSETTING_HH_
# define GAMEPLAYSETTING_HH_

# include <vector>

# include "GameState.hh"
# include "ISelectGUI.hh"
# include "GamePlay.hh"
# include "Text.hh"

class Game;

class GamePlaySetting : public GameState
{
  public:
    GamePlaySetting(Game *game);
    virtual ~GamePlaySetting();

    virtual int			update(Time const &t);
    virtual int			sendEvent(const std::pair<Event, Player *> &event);

  private:
    std::vector<ISelectGUI *>	_gui;
    size_t			_selected_gui;
    std::vector<Text *>		_text;
    ISelectGUI			*_selected;
    GamePlay			*_game;
};

#endif /* !GAMEPLAYSETTING_HH_ */
