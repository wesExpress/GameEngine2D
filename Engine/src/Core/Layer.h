#ifndef __LAYER_H__
#define __LAYER_H__

#include "Event/Event.h"

class Layer
{
    public:
        Layer(const std::string& name = "Layer");
        virtual ~Layer() = default;

        virtual void OnUpdate() = 0;
        virtual void OnAttach() = 0;
        virtual void OnDetach() = 0;
        virtual void OnEvent(Event& e) = 0;

        inline const std::string& GetName() const { return m_logName; }
    private:
        std::string m_logName;
};

#endif