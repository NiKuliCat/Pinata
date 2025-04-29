#pragma once
#include "Pinata/Renderer/Texture.h"
#include "stb_image.h"
namespace Pinata {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const TextureAttributes& t_Attributes, const std::string& path);
		virtual ~OpenGLTexture2D();


	public:
		virtual glm::uvec2 GetSize() const override { return m_Size; };
		virtual uint32_t GetWidth() const override { return m_Size.x; };
		virtual uint32_t GetHeight() const override { return m_Size.y; };


		virtual void Bind(uint32_t slot = 0) const override;
	private:
		uint32_t m_TextureID;
		std::string m_Path;
		glm::uvec2 m_Size;

	};
}