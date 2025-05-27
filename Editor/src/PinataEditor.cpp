#pragma once
#include <Pinata.h>
#include <ImGui/imgui.h>
#include "EditorLayer.h"
#include <Pinata/Core/EntryPoint.h>

namespace Pinata {

	class PinataEditor : public Application
	{
	public:
		PinataEditor()
			:Application("Pinata Engine")
		{
			PushLayer(new EditorLayer());
		}
		~PinataEditor()
		{

		}
	};

	Application* CreateApplication()
	{
		return new PinataEditor();
	}

}