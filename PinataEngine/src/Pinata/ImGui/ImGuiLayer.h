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

		void OnAttach() override;
		void OnDetach() override;
		void OnUpdata() override;
		void OnEvent(Event& event) override;

	private:

		//mouse
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);

		//keyboard
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);

		//plication
		bool OnWindowResizeEvent(WindowResizeEvent& e);

	private:
		float m_Time = 0.0f;
	};
}
