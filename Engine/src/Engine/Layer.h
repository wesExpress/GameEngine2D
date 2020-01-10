#ifndef __LAYER_H__
#define __LAYER_H__

#include "Event/Event.h"

namespace Engine
{
    class Layer
    {
        public:
            Layer(const std::string& name = "Layer");
            virtual ~Layer() = default;

            virtual void OnUpdate() {}
            virtual void OnAttach() {}
            virtual void OnDetach() {}
            virtual void OnEvent(Event& e) {}

            inline const std::string& GetName() const { return m_logName; }
        private:
            std::string m_logName;
    };
}

#endif