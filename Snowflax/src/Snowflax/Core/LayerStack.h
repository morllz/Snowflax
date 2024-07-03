#pragma once

#include "SFLXpch.h"
#include "Layer.h"


namespace Snowflax {

	class LayerStack : public EventListener {
		using LStack = std::vector<Layer*>;
	public:
		LayerStack() = default;
		virtual ~LayerStack() override;

		void OnEvent(Event& _event) override;
		void Update() const;
		void PushLayer(Layer* _layer);
		void PopLayer(Layer const* _layer);
		void PushOverlay(Layer* _overlay);
		void PopOverlay(Layer const* _overlay);

	private:
		LStack m_Layers;
		int m_LayerInsertIndex = 0;
	};
}