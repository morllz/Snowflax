#pragma once

#include "Snowflax/Infrastructure/Events/EventDispatcher.h"


using namespace Snowflax::Infrastructure::Events;

namespace Snowflax {
	namespace Infrastructure {
		namespace Layers {

			class SNOWFLAX_API Layer : public EventDispatcher {
			public:
				Layer() = default;
				virtual ~Layer() = default;

				virtual void OnAttach() const = 0;
				virtual void OnDetatch() const = 0;
				virtual void OnUpdate() const = 0;
			private:
				bool m_Enabled = false;
				bool m_IsOverlay = false;
			};

			
		}
	}
}