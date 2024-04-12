#include "LayerStack.h"


using namespace Snowflax;

Snowflax::LayerStack::LayerStack()
{
	m_FirstLayerPos = m_Layers.end();
}

void LayerStack::OnEvent(Event& _event)
{
	for (auto layer : m_Layers) {
		layer->OnEvent(_event);
	}
}

void Snowflax::LayerStack::Update()
{
	for (auto layer : m_Layers) {
		layer->OnUpdate();
	}
}

void LayerStack::PushLayer(Layer* _pLayer)
{
	if (_pLayer->isOverlay()) return;
	if (const auto pos = std::find(m_FirstLayerPos, m_Layers.end(), _pLayer); 
		pos != m_Layers.end()) return;

	m_FirstLayerPos = m_Layers.insert(m_FirstLayerPos, _pLayer);
	_pLayer->OnAttach();
}

void LayerStack::PopLayer(Layer* _pLayer)
{
	if (_pLayer->isOverlay()) return;
	if (const auto pos = std::find(m_FirstLayerPos, m_Layers.end(), _pLayer); 
		pos != m_Layers.end()) m_Layers.erase(pos);

	m_FirstLayerPos = std::find_if(m_FirstLayerPos, m_Layers.end(), [](Layer const* layer) { return !layer->isOverlay(); });
	_pLayer->OnDetatch();
}

void LayerStack::PushOverlay(Layer* _pLayer)
{
	if (!_pLayer->isOverlay()) return;
	if (const auto pos = std::find(m_Layers.begin(), m_FirstLayerPos, _pLayer);
		pos != m_Layers.end()) return;

	m_Layers.insert(m_Layers.begin(), _pLayer);
	_pLayer->OnAttach();
}

void LayerStack::PopOverlay(Layer* _pLayer)
{
	if (!_pLayer->isOverlay()) return;
	if (const auto pos = std::find(m_Layers.begin(), m_FirstLayerPos, _pLayer);
		pos != m_Layers.end()) m_Layers.erase(pos);

	_pLayer->OnDetatch();
}
