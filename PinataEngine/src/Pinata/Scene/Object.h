#pragma once
#include "Scene.h"
#include "entt.hpp"
namespace Pinata {

	class Object
	{
	public:
		Object() = default;
		Object(const std::string& name,entt::entity entityHandle, Scene* scene);
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

		const std::string& GetName() const { return m_Name; }

	private:
		std::string m_Name = "new object";
		entt::entity m_EntityHandle{ entt::null };
		Scene* m_Scene = nullptr;
	};
}