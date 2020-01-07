#ifndef __KEYBOARDEVENT_H__
#define __KEYBOARDEVENT_H__

#include <sstream>
#include "Event.h"

class KeyboardEvent : public Event
{
    public:
        EVENT_TYPE(KEYBOARD);
};

class KeyPressedEvent : public KeyboardEvent
{
    public:
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: ";
            return ss.str();
        }
};

class KeyReleasedEvent : public KeyboardEvent
{
    public:
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: ";
            return ss.str();
        }
}; 

#endif