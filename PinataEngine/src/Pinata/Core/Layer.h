#pragma once
#include "Pinata/Core/Core.h"
#include "Pinata/Event/Event.h"
namespace Pinata {

	class PINATA_API Layer
	{
	public:
		Layer(const std::string& name = "Layer");

		virtual ~Layer() = default;

		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void OnUpdata() {}
		virtual void OnImGuiRender(){}
		virtual void OnEvent(Event& event)	{}

		inline const std::string& GetName() const { return m_DebugName; }

	protected:

		std::string  m_DebugName;


	};


}
