#ifndef __LAYER_H__
#define __LAYER_H__

#include "Event/Event.h"
#include "Timestep.h"

namespace Engine
{
    class Layer
    {
        public:
            Layer(const std::string& name = "Layer");
            virtual ~Layer();

            virtual void OnUpdate(const Timestep& ts) {}
            virtual void OnAttach() {}
            virtual void OnDetach() {}
            virtual void OnEvent(Event& e) {}
            virtual void OnImGuiRender() {}

            inline const std::string& GetName() const { return m_logName; }
        private:
            std::string m_logName;
    };
}

#endif