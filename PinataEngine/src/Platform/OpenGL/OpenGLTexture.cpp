#include "ptapch.h"
#include "OpenGLTexture.h"
#include <glad/glad.h>
namespace Pinata{
	OpenGLTexture2D::OpenGLTexture2D(const TextureAttributes& t_Attributes, const std::string& path)
		:m_Path(path)
	{


		stbi_set_flip_vertically_on_load(true);
		int width, height, channels;
		stbi_uc* data = stbi_load(path.c_str(), &width, &height, &channels, 0);
		PTA_CORE_ASSERT(data, "Failed to load this image : {0}", path);
		m_Size = { width,height };

		////第一个RGB指opengl保持的图片格式，第二个RGB指源图片数据的格式
		////参考  https://learnopengl-cn.github.io/01%20Getting%20started/06%20Textures/#stb_imageh
		////glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureID);
		glTextureStorage2D(m_TextureID, 1, GL_RGB8, m_Size.x, m_Size.y); // 注意是GL_RGB8 而不是GL_RGB
		glTextureSubImage2D(m_TextureID, 0, 0, 0, m_Size.x, m_Size.y, GL_RGB, GL_UNSIGNED_BYTE,data);

		glTextureParameteri(m_TextureID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTextureParameteri(m_TextureID, GL_TEXTURE_WRAP_T, GL_REPEAT);

		//glGenerateMipmap(GL_TEXTURE_2D);

		stbi_image_free(data);
	}
	OpenGLTexture2D::~OpenGLTexture2D()
	{
		glDeleteTextures(1, &m_TextureID);
	}
	void OpenGLTexture2D::Bind(uint32_t slot) const
	{
		glBindTextureUnit(slot, m_TextureID);
	}
}