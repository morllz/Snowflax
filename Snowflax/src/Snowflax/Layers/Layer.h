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
			private:
				bool m_Enabled = false;
				bool m_IsOverlay = false;
			};

			
}