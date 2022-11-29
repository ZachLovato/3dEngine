#pragma once
#include "Texture.h"
#include "Core/Logger.h" 
#include <SDL.h> 
#include <SDL_image.h> 
#include <cstdarg> 
#include <vector>

namespace wrap
{
	class CubemapTexture : public Texture
	{
	public:
		bool Create(std::string filename, ...) override;
		bool Load(const std::vector<std::string>& filename);
		std::vector<std::string> GenerateCubeMapNames(const std::string& basename, const std::string& extension);
		GLenum GetInternalFormat(GLuint format);


	private:

	};
}