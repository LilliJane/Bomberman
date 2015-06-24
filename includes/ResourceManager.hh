//
// ResourceManager.hh for  in /home/dumont_p/rendu/cpp_bomberman/includes
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Tue May 19 16:05:34 2015 _p dumont
// Last update Sun Jun 14 16:26:00 2015 Emeline Gaulard
//

#ifndef RESOURCEMANAGER_HH_
# define RESOURCEMANAGER_HH_

# include <map>
# include <utility>
# include <sys/types.h>
# include <SFML/Audio.hpp>
# include "OpenGL.hh"
# include "gdl/Input.hh"
# include "gdl/Model.hh"
# include "gdl/BasicShader.hh"
# include "gdl/Texture.hh"

class ResourceManager
{
  public:
    static ResourceManager	*GetInstance();
    static void			DeleteInstance();

    bool			PreLoadResource();
    bool			LoadResource();
    bool			UnloadResource();

    GLuint			GetFontTexture() const;
    gdl::Model			*GetBomberman();
    gdl::Model			&GetGround();
    gdl::Model			&GetIndestructibleBox();
    gdl::Model			&GetDestructibleBox();
    gdl::BasicShader		&GetShader();
    gdl::Input			*GetInput();

    id_t			LoadTexture(const std::string &name);
    gdl::Texture		&GetTexture(id_t id);
    void			UnloadTexture(id_t id);
    void			UnloadAllTextures();

    void			PlaySound(unsigned int id);
    void			PlayMusic();
    void			SetSound();
    void			StopMusic();

  private:
    typedef std::map<id_t, std::pair<std::string, gdl::Texture *> > container_type;

    static ResourceManager	*_singleton;

    ResourceManager();
    ResourceManager(ResourceManager const &ref);
    ResourceManager &operator =(ResourceManager const &ret);
    ~ResourceManager();

    bool			LoadFontTexture();
    bool			UnloadFontTexture();

    bool			LoadShader();
    bool			UnloadShader();

    bool			LoadBombermanModel();
    bool			UnloadBombermanModel();

    bool			LoadFieldModel();
    bool			UnloadFieldModel();

    bool			LoadSounds();

    id_t			TextureIdFromName(const std::string &name) const;

    bool			_zik;
    gdl::Input			*_input;
    gdl::Texture		_font;
    gdl::Model			_bomberman_model;
    gdl::Model			_ground_model;
    gdl::Model			_indestructible_box_model;
    gdl::Model			_destructible_box_model;
    gdl::BasicShader		_shader;
    std::vector<sf::SoundBuffer>	_buffer;
    std::vector<sf::Sound>	_sounds;
    sf::Music			_music;
    container_type		_textures;
};

#endif /* !RESOURCEMANAGER_HH_ */
