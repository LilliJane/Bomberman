//
// Player.hh for Player in /home/tack_g/rendu/cpp_bomberman
//
// Made by g tack
// Login   <tack_g@epitech.net>
//
// Started on  Tue May 19 11:46:16 2015 g tack
// Last update Wed Jun 10 22:04:55 2015 Emeline Gaulard
//

#ifndef PLAYER_HH_
# define PLAYER_HH_

# include <queue>

# include "IMapEntity.hh"
# include "ADrawable.hh"
# include "KeyConf.hh"
# include "Game.hh"
# include "Bomb.hh"
# include "Bombermap.hh"
# include "Explosion.hh"

class		Player : public ADrawable, public IMapEntity
{
public:
    Player(glm::vec4 color);
    Player(unsigned int score, unsigned int speed,
	   float x, float y,
	   unsigned short range, unsigned short life,
	   unsigned short nbBombs);
    virtual ~Player();

    virtual unsigned int getCellX() const;
    virtual unsigned int getCellY() const;

    unsigned int	getScore() const;
    unsigned int	getSpeed() const;
    float		getPosX() const;
    float		getPosY() const;
    unsigned short	getRange() const;
    unsigned short	getNbBombs() const;
    unsigned short	getLife() const;
    const KeyConf	&getConf() const;
    KeyConf		&getConf();
    glm::mat4 const	&getCamera() const;

    unsigned int	getInitialSpeed() const;
    unsigned short	getInitialRange() const;
    unsigned int	getActualNbBombs() const;


    void		setScore(unsigned int score);
    void		setSpeed(unsigned int speed);
    void		setPosX(float x);
    void		setPosY(float y);
    void		setRange(unsigned short range);
    void		setNbBombs(unsigned short nb);
    float		getRotation() const;
    void		setGPS(bool gps);
    bool		getGPS() const;

    Bomb		*getBomb();
    void		addBomb();

    void		addRange();
    void		addNbBomb();
    void		addSpeed();

    void		setLife(unsigned short life);

    void		moveForward(Bombermap &map);
    void		moveBackward(Bombermap &map);
    void		stopMove();
    void		turnLeft();
    void		turnRight();

    void		takeDamage();
    void		setConf(KeyConf const &k);

    virtual void	draw(Time const &t) const;
    void		update(Time const &t);

    void		loadSkin();

  protected:
    bool		tryMove(float x, float y, Bombermap const &map);
    void		checkCollisions(Bombermap &map);
    bool		collBonus(ABonus *bonus);
    bool		collExplosion(Explosion *expl);

    unsigned int	_score;
    unsigned int	_speed;// user's speed
    float		_x;
    float		_y;
    float		_delta_x;
    float		_delta_y;
    unsigned short	_range;
    unsigned int	_rotation;
    unsigned int	_rotation_delta;
    unsigned short	_life;
    unsigned short	_nbBombs; // nb bombs...
    std::queue<Bomb *>	_bombs;
    KeyConf		_keyboard;
    glm::mat4		_camera;
    glm::vec4		_color;
    gdl::Model		*_skin;
    Time		_to_update;
    Bombermap		*_map;
    bool		_gps;

    unsigned int		_initialSpeed;
    unsigned short		_initialRange;

  private:
    static int		_player;
};

#endif /* !PLAYER_HH_ */
