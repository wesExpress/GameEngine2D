#ifndef __EVENT_H__
#define __EVENT_H__

#define BIT(x) (1 << x)

namespace Engine
{
    enum EventCategory
    {
        NONE = 0,
        INPUT = BIT(0),
        MOUSE = BIT(1),
        KEYBOARD = BIT(2),
        WINDOW = BIT(3)
    };

    enum class EventType
    {
        None = 0,
        KeyPressed, KeyReleased, KeyRepeated, KeyTyped,
        MouseMoved, MouseButtonPressed, MouseButtonReleased, MouseScrolled,
        WindowResized, WindowClosed
    };

    #define EVENT_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
    virtual EventType GetEventType() const override { return GetStaticType(); }\
    virtual const char* GetName() const override { return #type; }
    #define EVENT_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    class Event
    {
        public:
            virtual EventType GetEventType() const = 0;
            virtual int GetCategoryFlags() const = 0;
            virtual const char* GetName() const = 0;
            virtual std::string ToString() const { return GetName(); }

            inline bool InCategory(EventCategory category) { return GetCategoryFlags() & category; }

            bool handled = false;
    };

    class EventDispatcher
    {
        template<typename T>
        using EventFn = std::function<bool(T&)>;

        public:
            EventDispatcher(Event& e)
            :
            m_event(e)
            {}
            
            template<typename T>
            bool Dispatch(EventFn<T> function)
            {
                if (m_event.GetEventType() == T::GetStaticType())
                {
                    m_event.handled = function(*(T*)&m_event);
                    return true;
                }
                return false;
            }

        private:
            Event& m_event;
    };

    inline std::ostream& operator<<(std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }
}

#endif