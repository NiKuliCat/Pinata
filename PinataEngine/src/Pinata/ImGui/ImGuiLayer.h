#pragma once
#include "Pinata/Core/Layer.h"
#include "Pinata/Core/Core.h"

#include "Pinata/Event/MouseEvent.h"
#include "Pinata/Event/KeyboardEvent.h"
#include "Pinata/Event/ApplicationEvent.h"
namespace Pinata {

	class PINATA_API ImGuiLayer : public  Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;


		void SetDarkThemeColor();
		void Begin();
		void End();

	private:
		float m_Time = 0.0f;
	};
}
