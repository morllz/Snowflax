#pragma once

#include "Event.h"
#include "Snowflax/Core/KeyCodes.h"


namespace Snowflax
{
	class KeyPressedEvent final : public Event
	{
	public:
		KeyPressedEvent(const Key::KeyCode _keyCode, const int _modKeyFlags, const int _repeatCount)
			: m_KeyCode(_keyCode),m_ModKeyFlags(_modKeyFlags), m_RepeatCount(_repeatCount) {}

		SFLX_EVENT_CLASS_TYPE(KeyPressed)
		SFLX_EVENT_CLASS_CATEGORY(InputEvents | KeyEvents)

		virtual const char* GetName() const override { return "KeyPressedEvent"; }
		virtual std::string ToString() const override
		{
			std::string modKeyName;
			if(m_ModKeyFlags & static_cast<int>(Key::ModShift)) modKeyName += "Shift ";
			if(m_ModKeyFlags & static_cast<int>(Key::ModControl)) modKeyName += "Control ";
			if(m_ModKeyFlags & static_cast<int>(Key::ModAlt)) modKeyName += "Alt ";
			if(m_ModKeyFlags & static_cast<int>(Key::ModSuper)) modKeyName += "Super ";
			if(m_ModKeyFlags & static_cast<int>(Key::ModCapsLock)) modKeyName += "Caps Lock ";
			if(m_ModKeyFlags & static_cast<int>(Key::ModNumLock)) modKeyName += "Num Lock ";
			if(!modKeyName.empty()) modKeyName.pop_back();

			return std::format(
				"{}(keycode: {}, readable: '{}', mod. tags: {}, repeat count: {})", 
				GetName(), static_cast<int>(m_KeyCode), static_cast<char>(m_KeyCode), modKeyName, m_RepeatCount
			);
		}
	private:
		Key::KeyCode m_KeyCode;
		int m_ModKeyFlags, m_RepeatCount;
	};

	class KeyReleasedEvent final : public Event
	{
	public:
		KeyReleasedEvent(const Key::KeyCode _keyCode, const int _modKeyFlags)
			: m_KeyCode(_keyCode), m_ModKeyFlags(_modKeyFlags) {}

		SFLX_EVENT_CLASS_TYPE(KeyReleased)
		SFLX_EVENT_CLASS_CATEGORY(InputEvents | KeyEvents)

		virtual const char* GetName() const override { return "KeyReleasedEvent"; }
		virtual std::string ToString() const override
		{
			std::string modKeyName;
			if(m_ModKeyFlags & static_cast<int>(Key::ModShift)) modKeyName += "Shift ";
			if(m_ModKeyFlags & static_cast<int>(Key::ModControl)) modKeyName += "Control ";
			if(m_ModKeyFlags & static_cast<int>(Key::ModAlt)) modKeyName += "Alt ";
			if(m_ModKeyFlags & static_cast<int>(Key::ModSuper)) modKeyName += "Super ";
			if(m_ModKeyFlags & static_cast<int>(Key::ModCapsLock)) modKeyName += "Caps Lock ";
			if(m_ModKeyFlags & static_cast<int>(Key::ModNumLock)) modKeyName += "Num Lock ";
			if(!modKeyName.empty()) modKeyName.pop_back();

			return std::format(
				"{}(keycode: {}, readable: '{}', mod. tags: {})", 
				GetName(), static_cast<int>(m_KeyCode), static_cast<char>(m_KeyCode), modKeyName
			);
		}
	private:
		Key::KeyCode m_KeyCode;
		int m_ModKeyFlags;
	};

	class KeyTypedEvent final : public Event
	{
	public:
		KeyTypedEvent(const Key::KeyCode _keyCode)
			: m_KeyCode(_keyCode) {}

		SFLX_EVENT_CLASS_TYPE(KeyTyped)
		SFLX_EVENT_CLASS_CATEGORY(InputEvents | KeyEvents)

		virtual const char* GetName() const override { return "KeyTypedEvent"; }
		virtual std::string ToString() const override
		{
			return std::format(
				"{}(keycode: {}, readable: '{}')", 
				GetName(), static_cast<int>(m_KeyCode), static_cast<char>(m_KeyCode)
			);
		}
	private:
		Key::KeyCode m_KeyCode;
	};
}
