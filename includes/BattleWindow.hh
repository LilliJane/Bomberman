//
// BattleWindow.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Thu Jun 11 07:51:04 2015 _p dumont
// Last update Thu Jun 11 07:51:04 2015 _p dumont
//

#ifndef BATTLEWINDOW_HH_
# define BATTLEWINDOW_HH_

# include "Player.hh"

# include "MyContext.hh"

class		GamePlay;

class		BattleWindow
{
  public:
    BattleWindow(GamePlay const *g,
		 Player const *focus_player,
		 bool create_new_window = false);
    ~BattleWindow();

    void		draw(Time const &t);
    void		displayHud();

  private:
    void		drawEntity(ABonus *b, const Time &t);
    void		drawEntity(Bomb *bomb, const Time &t);
    void		drawEntity(Explosion *explosion, const Time &t);
    void		drawEntities(const Time &t);
    void		drawCubesMatching(unsigned int value,
					  float y,
					  Time const &t);
    void		drawPlayer(Time const &t);

    Player const	*_focus_player;
    MyContext		*_context;
    GamePlay const	*_game;
    Cube		_cube;
};

#endif /* !BATTLEWINDOW_HH_ */
