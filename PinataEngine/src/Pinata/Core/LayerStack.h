#pragma once
#include "Pinata/Core/Core.h"
#include "Pinata/Core/Layer.h"
namespace Pinata {


	class PINATA_API LayerStack
	{
	public :
		LayerStack();
		~LayerStack();


		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);
		
		void PushOverlay(Layer* overlay);
		void PopOverlay(Layer* overlay);

		std::vector<Layer*>::iterator begin() { return m_Layer.begin(); }
		std::vector<Layer*>::iterator end() { return m_Layer.end(); }

		std::vector<Layer*>::reverse_iterator rbegin() { return m_Layer.rbegin(); }
		std::vector<Layer*>::reverse_iterator rend() { return m_Layer.rend(); }


		std::vector<Layer*>::const_iterator begin() const { return m_Layer.begin(); }
		std::vector<Layer*>::const_iterator end()const { return m_Layer.end(); }

		std::vector<Layer*>::const_reverse_iterator rbegin() const { return m_Layer.rbegin(); }
		std::vector<Layer*>::const_reverse_iterator rend() const { return m_Layer.rend(); }


	private: 
		std::vector<Layer*> m_Layer;
		std::vector<Layer*>::iterator m_LayerInsert;
	};
}

