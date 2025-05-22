#pragma once
#include "Scene.h"
#include "entt.hpp"
#include "Pinata/Component/Tag.h"
namespace Pinata {

	class Object
	{
	public:
		Object() = default;
		Object(entt::entity entityHandle, Scene* scene);
		Object(const Object& other) = default;
		~Object() = default;


	public:
		template<typename T>
		bool HasComponent()
		{
			return m_Scene->GetRegistry().all_of<T>(m_EntityHandle);
		}

		template<typename T,typename... Args>
		T& AddComponent(Args&&... args)
		{
			PTA_CORE_ASSERT(!HasComponent<T>(), "the object already has this component !");
			return m_Scene->GetRegistry().emplace<T>(m_EntityHandle, std::forward<Args>(args)...);
		}

		template<typename T>
		T& GetComponent()
		{
			PTA_CORE_ASSERT(HasComponent<T>(), "the object not have this component !");
			return m_Scene->GetRegistry().get<T>(m_EntityHandle);
		}

		template<typename T>
		void RemoveComponent()
		{
			PTA_CORE_ASSERT(HasComponent<T>(), "the object not have this component !");
			m_Scene->GetRegistry().remove<T>(m_EntityHandle);
		}

		operator bool() const { return m_EntityHandle != entt::null; }
		operator uint32_t() const { return (uint32_t)m_EntityHandle; }
		bool operator ==(const Object& other) { return m_EntityHandle == other.m_EntityHandle && m_Scene == other.m_Scene; }
		bool operator !=(const Object& other) { return m_EntityHandle != other.m_EntityHandle || m_Scene != other.m_Scene; }


		std::string& GetName() { return GetComponent<Name>().GetName(); }
	private:
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;
	};
}