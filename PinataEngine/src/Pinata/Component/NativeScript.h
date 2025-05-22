#pragma once
#include "Pinata/Scene/ScriptableObject.h"
namespace Pinata {

	class NativeScript
	{
	public:
		ScriptableObject* Instance = nullptr;


		ScriptableObject* (*InstantiateScript)();
		void (*DestoryScript)(NativeScript*);

		template<typename T>
		void Bind()
		{
			InstantiateScript = []() { return  static_cast<ScriptableObject*>(new T()); };
			DestoryScript = [](NativeScript* nsc) {delete nsc->Instance; nsc->Instance = nullptr; };
		}
	};
}