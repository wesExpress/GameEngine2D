#ifndef __KEYBOARDEVENT_H__
#define __KEYBOARDEVENT_H__

#include <sstream>
#include "Event.h"

class KeyboardEvent : public Event
{
    protected:
        KeyboardEvent(int keyCode)
        :
        m_keyCode(keyCode)
        {}

    public:
        unsigned int GetKeyCode() const { return m_keyCode; }
        EVENT_CATEGORY(INPUT | KEYBOARD);

    private:
        unsigned int m_keyCode;
};

class KeyPressedEvent : public KeyboardEvent
{
    public:
        KeyPressedEvent(int key)
        :
        KeyboardEvent(key)
        {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << GetKeyCode();
            return ss.str();
        }

        EVENT_TYPE(KeyPressed);
};

class KeyReleasedEvent : public KeyboardEvent
{
    public:
        KeyReleasedEvent(int key)
        :
        KeyboardEvent(key)
        {}
        
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: ";
            return ss.str();
        }

        EVENT_TYPE(KeyReleased);
}; 

#endif