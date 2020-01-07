#ifndef __MOUSEEVENT_H__
#define __MOUSEEVENT_H__

#include "Event.h"
#include <sstream>

class MouseMovedEvent : public Event
{
    public:
        MouseMovedEvent(double x, double y)
        :
        m_x(x),
        m_y(y)
        {}

        inline double GetMouseX() const { return m_x; }
        inline double GetMouseY() const { return m_y; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: (" << GetMouseX() << ", " << GetMouseY() << ")";
            return ss.str();
        }

        EVENT_TYPE(MouseMoved);
        EVENT_CATEGORY(EventCategory::INPUT | EventCategory::MOUSE);

    private:
        double m_x, m_y;
};

class MouseScrolledEvent : public Event
{
    public:
        MouseScrolledEvent(double xDiff, double yDiff)
        :
        m_xDiff(xDiff),
        m_yDiff(yDiff)
        {}

        inline double GetXDiff() const { return m_xDiff; }
        inline double GetYDiff() const { return m_yDiff; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: (" << GetXDiff() << ", " << GetYDiff() << ")";
            return ss.str();
        }

        EVENT_TYPE(MouseScrolled);
        EVENT_CATEGORY(EventCategory::INPUT | EventCategory::MOUSE);

    private:
        double m_xDiff, m_yDiff;
};

class MouseButtonEvent : public Event
{
    public:
        MouseButtonEvent(unsigned int button)
        :
        m_button(button)
        {}

        inline unsigned int GetButton() const { return m_button; }

        EVENT_CATEGORY(EventCategory::INPUT | EventCategory::MOUSE);

    private:
        unsigned int m_button;
};

class MouseButtonPressedEvent : public MouseButtonEvent
{
    public:
        MouseButtonPressedEvent(unsigned int button)
        :
        MouseButtonEvent(button)
        {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressed: " << GetButton();
            return ss.str();
        }

        EVENT_TYPE(MouseButtonPressed);
};

class MouseButtonReleasedEvent : public MouseButtonEvent
{
    public:
        MouseButtonReleasedEvent(unsigned int button)
        :
        MouseButtonEvent(button)
        {}

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleased: " << GetButton();
            return ss.str();
        }

        EVENT_TYPE(MouseButtonReleased);
};

#endif