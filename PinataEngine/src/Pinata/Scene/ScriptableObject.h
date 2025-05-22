#pragma once
#include "Object.h"
namespace Pinata {

	class ScriptableObject
	{
	public:
		template<typename T>
		T& GetComponent()
		{
			return m_Object.GetComponent<T>();
		}

	protected:
		virtual void OnCreate() {}
		virtual void OnUpdate(float deltatime) {}
		virtual void OnDestory() {}

		const std::string& GetName() const { return m_Object.GetName(); }

	private:
		Object m_Object;
		friend class Scene;
	};

}
