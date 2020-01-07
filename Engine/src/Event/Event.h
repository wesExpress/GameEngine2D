#ifndef __EVENT_H__
#define __EVENT_H__

#include <string>

enum class EventType
{
    NONE = 0,
    MOUSE,
    KEYBOARD,
    WINDOW
};

#define EVENT_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
virtual EventType GetEventType() const override { return GetStaticType(); }\
virtual const char* GetName() const override { return #type; }
class Event
{
    public:
        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual std::string ToString() const { return GetName(); }
};

inline std::ostream& operator<<(std::ostream& os, const Event& e)
{
    return os << e.ToString();
}

#endif