#pragma once

#include "Snowflax/Events/EventDispatcher.h"


namespace Snowflax {

	class Layer : public EventDispatcher {
	public:
		Layer() = default;
		~Layer() override = default;

		virtual void OnAttach() const = 0;
		virtual void OnDetatch() const = 0;
		virtual void OnUpdate() const = 0;

		bool isOverlay() const { return m_Overlay; }
		bool isEnabled() const { return m_Enabled; }

		explicit(false) operator bool() const { return isEnabled(); }
		virtual void Enable() { m_Enabled = true; }
		virtual void Disable() { m_Enabled = false; }

	private:
		bool m_Enabled = false;
		bool m_Overlay = false;
	};
}