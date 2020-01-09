#include "LayerStack.h"

namespace Engine
{
    LayerStack::~LayerStack()
    {
        for (Layer* layer : m_layers)
        {
            layer->OnDetach();
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* layer)
    {
        m_layers.emplace(m_layers.begin() + m_insertIndex, layer);
        m_insertIndex++;
    }

    void LayerStack::PushOverlay(Layer* layer)
    {
        m_layers.emplace_back(layer);
    }

    void LayerStack::PopLayer(Layer* layer)
    {
        auto it = std::find(m_layers.begin(), m_layers.begin() + m_insertIndex, layer);
        if (it != m_layers.begin() + m_insertIndex)
        {
            layer->OnDetach();
            m_layers.erase(it);
            m_insertIndex--;
        }
    }

    void LayerStack::PopOverlay(Layer* layer)
    {
        auto it = std::find(m_layers.begin() + m_insertIndex, m_layers.end(), layer);
        if (it != m_layers.end())
        {
            layer->OnDetach();
            m_layers.erase(it);
        }
    }
}