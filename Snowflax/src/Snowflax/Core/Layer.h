#pragma once

#include "Snowflax/Events/EventDispatcher.h"


namespace Snowflax {

	class Layer : public EventListener, EventDispatcher {
	public:
		Layer() = default;
		~Layer() override = default;

		void OnEvent(Event& _e) override { Send(_e); }

		virtual void OnAttach() const = 0;
		virtual void OnDetach() const = 0;
		virtual void OnUpdate() const = 0;

		bool IsOverlay() const { return m_IsOverlay; }
		bool IsEnabled() const { return m_Enabled; }

		explicit virtual operator bool() const { return IsEnabled(); }
		virtual void Enable() { m_Enabled = true; }
		virtual void Disable() { m_Enabled = false; }
		virtual void SetOverlay(bool _isOverlay) { m_IsOverlay = _isOverlay; }

	private:
		bool m_Enabled = true;
		bool m_IsOverlay = false;
	};
}