//
// IEntity.hh for  in /home/sabour_f/rendu/cpp_bomberman/includes
//
// Made by Florian SABOURIN
// Login   <sabour_f@epitech.net>
//
// Started on  Tue May 19 19:50:10 2015 Florian SABOURIN
// Last update Tue May 19 19:50:11 2015 Florian SABOURIN
//

#ifndef IENTITY_HH_
# define IENTITY_HH_

/*
** Represents an entity on the map
** It is to be drawn on the screen
** For instance, a bomb and a player are both entities
*/
class IEntity
{
  public:
    IEntity();
    virtual ~IEntity() = 0;
};

#endif /* !IENTITY_HH_ */
