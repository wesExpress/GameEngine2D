#include "Layer.h"

namespace Engine
{
    typedef std::vector<Layer*> LAYER_VEC;

    class LayerStack
    {
        public:
            LayerStack() = default;
            ~LayerStack();

            void PushLayer(Layer* layer);
            void PushOverlay(Layer* layer);
            void PopLayer(Layer* layer);
            void PopOverlay(Layer* layer);

            LAYER_VEC::iterator begin() { return m_layers.begin(); }
            LAYER_VEC::iterator end() { return m_layers.end(); }
            LAYER_VEC::reverse_iterator rbegin() { return m_layers.rbegin(); }
            LAYER_VEC::reverse_iterator rend() { return m_layers.rend(); }

            LAYER_VEC::const_iterator begin() const { return m_layers.begin(); }
            LAYER_VEC::const_iterator end() const { return m_layers.end(); }
            LAYER_VEC::const_reverse_iterator rbegin() const { return m_layers.rbegin(); }
            LAYER_VEC::const_reverse_iterator rend() const { return m_layers.rend(); }
        private:
            LAYER_VEC m_layers;
            unsigned int m_insertIndex = 0;
    };
}