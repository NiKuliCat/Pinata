#pragma once
#include "Pinata/Renderer/Texture.h"
#include "stb_image.h"
namespace Pinata {

	class OpenGLTexture2D : public Texture2D
	{
	public:
		OpenGLTexture2D(const TextureAttributes& t_Attributes);
		OpenGLTexture2D(const DefaultTexColor& defaultColor);
		OpenGLTexture2D(const TextureAttributes& t_Attributes, const std::string& path);
		virtual ~OpenGLTexture2D();


	public:
		virtual void SetData(void* data, uint32_t size) override;
		virtual glm::uvec2 GetSize() const override { return m_Size; };
		virtual uint32_t GetWidth() const override { return m_Size.x; };
		virtual uint32_t GetHeight() const override { return m_Size.y; };
		virtual uint32_t GetID() const override { return m_TextureID; }
		virtual void Bind(uint32_t slot = 0) const override;

	private:
		virtual uint32_t SetColorByType(const DefaultTexColor& defaultColor);
	private:
		uint32_t m_TextureID = -1;
		std::string m_Path;
		glm::uvec2 m_Size;

	};
}