#ifndef __WINDOWEVENT_H__
#define __WINDOWEVENT_H__

#include "Event.h"

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

        EVENT_TYPE(WindowClosed);
        EVENT_CATEGORY(EventCategory::WINDOW);
};

class WindowResizeEvent : public Event
{
    public:
        WindowResizeEvent(unsigned int width, unsigned int height)
        :
        m_width(width),
        m_height(height)
        {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizeEvent: (" << m_width << ", " << m_height << ")";
            return ss.str();
        }

        inline unsigned int GetWidth() const { return m_width; }
        inline unsigned int GetHeight() const { return m_height; }

        EVENT_TYPE(WindowResized);
        EVENT_CATEGORY(EventCategory::WINDOW);
    private:
        unsigned int m_width, m_height;
};

#endif