//
// IMapEntity.hh for  in /home/sabour_f/rendu/cpp_bomberman/includes
//
// Made by Florian SABOURIN
// Login   <sabour_f@epitech.net>
//
// Started on  Wed Jun 10 09:36:46 2015 Florian SABOURIN
// Last update Wed Jun 10 09:36:46 2015 Florian SABOURIN
//

#ifndef IMAPENTITY_HH_
# define IMAPENTITY_HH_

/*
** Defines something on the map
** It has to belong to a cell, whose coordinates we can get
*/
class IMapEntity
{
  public:
    IMapEntity();
    virtual ~IMapEntity();

    virtual unsigned int	getCellX() const = 0;
    virtual unsigned int	getCellY() const = 0;
};

#endif /* !IMAPENTITY_HH_ */
