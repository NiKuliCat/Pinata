#pragma once
#include <glm/glm.hpp>
namespace Pinata {
	
	enum class TextureType
	{
		Default,
		Normal
	};
	enum class TextureShape
	{
		Cube
	};

	enum class DefaultTexColor
	{
		White,
		Black,
		Magenta
	};
	enum class ImageFormat
	{
		RGB,
		RGBA,
		SRGB,
		SRGBA
	};
	enum class ImageWarpMode
	{
		Repeat,
		Clamp,
		Mirror
	};
	enum class ImageFilterMode
	{
		Point,
		Linear,
		Bilinear,
		Trilinear
	};

	struct TextureAttributes
	{
		uint32_t Width = 1;
		uint32_t Height = 1;
		TextureType Type = TextureType::Default;
		ImageFormat Format = ImageFormat::RGB;
		ImageWarpMode Warp = ImageWarpMode::Repeat;
		ImageFilterMode Filter = ImageFilterMode::Linear;
		
		bool GenerateMipmaps = true;
	};

	class Texture
	{
	public:
		virtual ~Texture() = default;
		virtual void SetData(void* data, uint32_t size) = 0;
		virtual glm::uvec2 GetSize() const = 0;
		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;


		virtual void Bind(uint32_t slot = 0) const = 0;

 	};


	class Texture2D : public Texture
	{
	public:
		static Ref<Texture2D> DefaultTexture(const DefaultTexColor& defaultColor);
		static Ref<Texture2D> Create(const TextureAttributes& t_Attributes);
		static Ref<Texture2D> Create(const TextureAttributes& t_Attributes, const std::string& path);




	};
}