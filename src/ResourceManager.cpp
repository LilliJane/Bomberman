//
// ResourceManager.cpp for  in /home/dumont_p/rendu/cpp_bomberman/src
//
// Made by _p dumont
// Login   <dumont_p@epitech.net>
//
// Started on  Tue May 19 16:05:43 2015 _p dumont
// Last update Sun Jun 14 16:41:13 2015 Emeline Gaulard
//

#include <iostream>
#include <stdexcept>

#include "ResourceManager.hh"

ResourceManager		*ResourceManager::_singleton = 0;

ResourceManager::ResourceManager()
  : _zik(true)
{
}

ResourceManager::~ResourceManager()
{
  this->UnloadResource();
  this->UnloadAllTextures();
}

ResourceManager		*ResourceManager::GetInstance()
{
  if (_singleton == 0)
    _singleton = new ResourceManager();
  return (_singleton);
}

void			ResourceManager::DeleteInstance()
{
  delete _singleton;
  _singleton = 0;
}

bool			ResourceManager::PreLoadResource()
{
  _input = new gdl::Input;
  return (this->LoadShader() &&
	  this->LoadFontTexture() && this->LoadSounds() &&
	  _input);
}

bool			ResourceManager::LoadResource()
{
  return (this->LoadBombermanModel() &&
	  this->LoadFieldModel());
}

bool			ResourceManager::UnloadResource()
{
  bool			ret(true);

  ret = ret && this->UnloadFontTexture();
  ret = ret && this->UnloadShader();
  ret = ret && this->UnloadBombermanModel();
  ret = ret && this->UnloadFieldModel();
  return (ret);
}

GLuint			ResourceManager::GetFontTexture() const
{
  return (this->_font.getId());
}

gdl::Model *ResourceManager::GetBomberman()
{
  gdl::Model	*skin = new gdl::Model;

  if (!skin->load("assets/marvin2.fbx"))
    throw (std::runtime_error("Can't copy skin"));
  skin->setCurrentAnim(0);
  skin->createSubAnim(0, "Stop", 0, 0);
  skin->createSubAnim(0, "Start", 1, 26);
  skin->createSubAnim(0, "Forward", 26, 49);
  skin->createSubAnim(0, "Backward", 60, 90);
  skin->setCurrentSubAnim("Stop", false);
  return (skin);
}

gdl::Model		&ResourceManager::GetGround()
{
  return (this->_ground_model);
}

gdl::Model		&ResourceManager::GetIndestructibleBox()
{
  return (this->_indestructible_box_model);
}

gdl::Model		&ResourceManager::GetDestructibleBox()
{
  return (this->_destructible_box_model);
}

gdl::BasicShader	&ResourceManager::GetShader()
{
  return (this->_shader);
}

gdl::Input *ResourceManager::GetInput()
{
  return (this->_input);
}

/*
** Loads a texture from its name
** The id returned is not the id from OpenGL
** = 0 on failure, the id of the texture on success
*/
id_t			ResourceManager::LoadTexture(const std::string &name)
{
  gdl::Texture		*tx;
  id_t			id;

  /* Check if we already loaded the texture */
  id = this->TextureIdFromName(name);
  if (id)
    return (id);

  /* Create a new texture and load */
  tx = new gdl::Texture();
  if (!tx->load(name))
    {
      delete tx;
      return (0);
    }

  /* Assign it to the lowest id available */
  id = 1;
  while (this->_textures.find(id) != this->_textures.end())
    ++id;
  this->_textures[id] = std::pair<std::string, gdl::Texture *>(name, tx);
  return (id);
}

/*
** Gets a texture from its id
** May throw std::out_of_range if id is invalid
** = The texture
*/
gdl::Texture		&ResourceManager::GetTexture(id_t id)
{
  container_type::iterator	it;

  /* Iterate over all textures, and return id */
  it = this->_textures.find(id);
  if (it == this->_textures.end())
    throw std::out_of_range("Request for unknown texture");
  return (*(it->second.second));
}

/*
** Unloads a texture from the manager
** May throw std::out_of_range if id is invalid
*/
void			ResourceManager::UnloadTexture(id_t id)
{
  container_type::iterator	it;

  /* Iterate over all textures, and delete texture */
  it = this->_textures.find(id);
  if (it == this->_textures.end())
    throw std::out_of_range("Request for unknown texture");
  delete it->second.second;
  this->_textures.erase(it);
}

/*
** Unloads all textures from the manager
*/
void			ResourceManager::UnloadAllTextures()
{
  container_type::iterator	it;

  /* Iterate over all textures, and delete each one */
  it = this->_textures.begin();
  while (it != this->_textures.end())
    {
      delete it->second.second;
      ++it;
    }
  this->_textures.clear();
}

bool			ResourceManager::LoadFontTexture()
{
  if (this->_font.load("font.tga"))
    return (true);
  std::cerr << "Can't load font.bpp" << std::endl;
  return (false);
}

bool			ResourceManager::UnloadFontTexture()
{
  return (true);
}

bool			ResourceManager::LoadShader()
{
  if (!this->_shader.load("./shaders/basic.vp", GL_VERTEX_SHADER) ||
      !this->_shader.load("./shaders/basic.fp", GL_FRAGMENT_SHADER) ||
      !this->_shader.build())
    return (false);
  return (true);
}

bool			ResourceManager::UnloadShader()
{
  return (true);
}

bool			ResourceManager::LoadBombermanModel()
{
  if (!this->_bomberman_model.load("assets/marvin2.fbx"))
    return (false);
  this->_bomberman_model.setCurrentAnim(0);
  return (true);
}

bool			ResourceManager::UnloadBombermanModel()
{
  return (true);
}

bool			ResourceManager::LoadFieldModel()
{
  //if (!this->_ground_model.load("assets/Crate/crate.fbx"))
    //return (false);
  return (true);
}

bool			ResourceManager::UnloadFieldModel()
{
  return (true);
}

/*
** Gets a texture id from its name
** = 0 on failure, the texture id on success
*/
id_t			ResourceManager::TextureIdFromName(const std::string &name) const
{
  container_type::const_iterator	it;

  /* Iterate over all textures, and return id */
  it = this->_textures.begin();
  while (it != this->_textures.end())
    {
      if (it->second.first == name)
	return (it->first);
      ++it;
    }
  return (0);
}

bool			ResourceManager::LoadSounds()
{
  _music.openFromFile("sounds/guile_theme.wav");
  _music.setVolume(50);
  _music.play();
  _music.setLoop(true);
  _buffer.resize(2);
  _sounds.resize(2);
  if (!_buffer[0].loadFromFile("sounds/bomb.wav"))
    return (false);
  if (!_buffer[1].loadFromFile("sounds/woohoo.wav"))
    return (false);
  for (unsigned int i = 0; i < _buffer.size(); ++i)
    {
      _sounds[i].setBuffer(_buffer[i]);
      _sounds[i].setVolume(50);
    }
  return (true);
}

void			ResourceManager::PlaySound(unsigned int id)
{
  if (id < _sounds.size())
      _sounds[id].play();
}

void			ResourceManager::PlayMusic()
{
  _music.play();
  _music.setLoop(true);
}

void			ResourceManager::SetSound()
{
  if (_zik)
    {
      for (std::vector<sf::Sound>::iterator it = _sounds.begin();
	   it != _sounds.end(); ++it)
	(*it).setVolume(0);
      _music.pause();
    }
  else
    {
      for (std::vector<sf::Sound>::iterator it = _sounds.begin();
	   it != _sounds.end(); ++it)
	(*it).setVolume(50);
      _music.play();
    }
  _zik = !_zik;
}

void			ResourceManager::StopMusic()
{
  _music.stop();
}
