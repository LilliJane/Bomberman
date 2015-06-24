//
// Cube.hh for  in /home/sabour_f/rendu/cpp_bomberman/includes
//
// Made by Florian SABOURIN
// Login   <sabour_f@epitech.net>
//
// Started on  Wed May 27 10:07:56 2015 Florian SABOURIN
// Last update Wed May 27 10:07:56 2015 Florian SABOURIN
//

#ifndef CUBE_HH_
# define CUBE_HH_

# include <string>
# include "ResourceManager.hh"
# include "ADrawable.hh"
# include "gdl/Geometry.hh"
# include "glm/gtc/matrix_transform.hpp"

class Cube : public ADrawable
{
  public:
   Cube();
   Cube(float x, float y, float z);
   Cube(float x, float y, float z,
	float w, float h, float d);
   virtual ~Cube();

   virtual void	move(float x, float y, float z);
   bool		setTexture(const std::string &name);
   void		setSize(float w, float h, float d);
   float	getWidth() const;
   float	getHeight() const;
   float	getDepth() const;
   id_t		getTxid() const;
   void		bindTx() const;


   virtual void	draw(Time const &t) const;

  private:
   Cube(const Cube &);
   Cube &operator=(const Cube &);

   void		updateMatrix();
   void		checkGeometry();

   id_t		_txid;
   float	_w;
   float	_h;
   float	_d;
   glm::mat4	_matrix;
   static gdl::Geometry _base_geometry;
   static bool	_is_geometry_init;
};

#endif /* !CUBE_HH_ */
