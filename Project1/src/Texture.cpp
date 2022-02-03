#include "Texture.h"
#include "stb_image/stb_image.h" //can add this path as a linker like we did with the opengl binaries

Texture::Texture(const std::string& path)
	: m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1); //opengl start texture rendering from the bottom left as (0, 0)
										 //while PNGs start rendering from the top, thus we use this function
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4); // 4 because RGBA is the required no of desired channels

	// Generate the texture
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	//Add parameters to the textures
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); //set texture parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE); //S, T are like the x, y coordinates

	//Specifying the texture image and adding the data stored in m_LocalBuffer
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer); //free the local buffer.
}

Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot); //openGL has a max of 32 texture slots which are consecutive in memory, thus the " + slot "
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
