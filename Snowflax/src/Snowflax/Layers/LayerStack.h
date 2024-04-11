#pragma once

#include "Layer.h"
#include <vector>


namespace Snowflax {

	class LayerStack {
		using LStack = std::vector<Layer*>;
	public:
		LayerStack() = default;
		~LayerStack() = default;

		void PushLayer(Layer* _pLayer);
		void PopLayer(Layer* _pLayer);
		void PushOverlay(Layer* _pLayer);
		void PopOverlay(Layer* _pLayer);

	private:
		LStack m_Layers;
	};

}