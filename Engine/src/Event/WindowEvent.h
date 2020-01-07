#ifndef __WINDOWEVENT_H__
#define __WINDOWEVENT_H__

#include "Event.h"
#include <sstream>

class WindowCloseEvent : public Event
{
    public:
        WindowCloseEvent() = default;

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowCloseEvent";
            return ss.str();
        }

        EVENT_TYPE(WINDOW);
};

class WindowResizeEvent : public Event
{
    public:
        WindowResizeEvent(int width, int height);

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: (" << m_width << ", " << m_height << ")";
            return ss.str();
        }

        EVENT_TYPE(WINDOW);
    private:
        int m_width, m_height;
};

#endif