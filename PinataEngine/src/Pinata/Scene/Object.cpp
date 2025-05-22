#include "ptapch.h"
#include "Object.h"
namespace Pinata {

	Object::Object(const std::string& name, entt::entity entityHandle, Scene* scene)
		:m_Name(name),m_EntityHandle(entityHandle),m_Scene(scene)
	{

	}
	Object::Object(entt::entity entityHandle, Scene* scene)
		:m_Name("newObject"), m_EntityHandle(entityHandle), m_Scene(scene)
	{

	}
}
