#include "ptapch.h"
#include "Texture.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"
namespace Pinata {


    Ref<Texture2D> Texture2D::Create(const TextureAttributes& t_Attributes)
    {
        return Ref<Texture2D>();
    }
    Ref<Texture2D> Texture2D::Create(const TextureAttributes& t_Attributes, const std::string& path)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None:
            {
                return nullptr;
                break;
            }
            case RendererAPI::API::OpenGL:
            {
                return  std::make_shared<OpenGLTexture2D>(t_Attributes, path);
                break;
            }
        }
    }


}