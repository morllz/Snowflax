#include "SFLXpch.h"
#include "LayerStack.h"
#include <ranges>

namespace Snowflax
{
	LayerStack::~LayerStack()
	{
		for (Layer* layer : m_Layers)
		{
			layer->OnDetach();
			delete layer;
		}
	}

	void LayerStack::OnEvent(Event& _event)
	{
		for (auto layer : m_Layers | std::views::reverse) {
			if(_event)
			{
				layer->OnEvent(_event);
				break;
			}
		}
	}

	void LayerStack::Update() const
	{
		for (auto layer : m_Layers) {
			layer->OnUpdate();
		}
	}

	void LayerStack::PushLayer(Layer* _layer)
	{
		_layer->SetOverlay(false);
		m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, _layer);
		m_LayerInsertIndex++;
	}

	void LayerStack::PushOverlay(Layer* _overlay)
	{
		_overlay->SetOverlay(true);
		m_Layers.emplace_back(_overlay);
	}

	void LayerStack::PopLayer(Layer const* _layer)
	{
		if (auto pos = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, _layer);
			pos != m_Layers.begin() + m_LayerInsertIndex)
		{
			_layer->OnDetach();
			m_Layers.erase(pos);
			m_LayerInsertIndex--;
		}
	}

	void LayerStack::PopOverlay(Layer const* _overlay)
	{
		if (auto pos = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), _overlay);
			pos != m_Layers.end())
		{
			_overlay->OnDetach();
			m_Layers.erase(pos);
		}
	}


}
