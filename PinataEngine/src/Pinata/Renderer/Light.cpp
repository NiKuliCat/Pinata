#include "ptapch.h"
#include "Light.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLLight.h"
namespace Pinata {



	Ref<Light> Light::Create(LightType& lightType, glm::vec3& position, glm::vec3& direction)
	{
        LightData data(position, direction, lightType);

        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None:
        {
            return nullptr;
            break;
        }
        case RendererAPI::API::OpenGL:
        {
            return  CreateRef<OpenGLLight>(data);
            break;
        }
        }
	}

}