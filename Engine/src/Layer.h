#include "Event/Event.h"

class Layer
{
    public:
        Layer(const std::string& name)
        :
        m_logName(name)
        {}

        virtual ~Layer() = default;

        virtual void Attach() = 0;
        virtual void Detach() = 0;
        virtual void OnEvent(Event& e) = 0;

        inline const std::string& GetName() const { return m_logName; }
    private:
        std::string m_logName;
};