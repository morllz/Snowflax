#pragma once

#include "SFXpch.h"
#include "Layer.h"


namespace Snowflax {

	class LayerStack : IEventListener {
		using LStack = std::vector<Layer*>;
		using LIterator = LStack::iterator;
	public:
		LayerStack();
		~LayerStack() override;

		void OnEvent(Event& _event) override;
		void Update();
		void PushLayer(Layer* _pLayer);
		void PopLayer(Layer* _pLayer);
		void PushOverlay(Layer* _pLayer);
		void PopOverlay(Layer* _pLayer);

	private:
		LStack m_Layers;
		LIterator m_FirstLayerPos;
	};
}