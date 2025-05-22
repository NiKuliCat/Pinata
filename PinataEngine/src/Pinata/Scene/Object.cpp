#include "ptapch.h"
#include "Object.h"
namespace Pinata {

	Object::Object(entt::entity entityHandle, Scene* scene)
		:m_EntityHandle(entityHandle), m_Scene(scene)
	{

	}
}
