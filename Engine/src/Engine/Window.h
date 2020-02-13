#ifndef __WINDOW_H__
#define __WINDOW_H__

#include "Logging.h"
#include "Event/Event.h"

#define DEFAULT_WINDOW_WIDTH 1280
#define DEFAULT_WINDOW_HEIGHT 720
#define DEFAULT_WINDOW_TITLE "GameEngine2D"

namespace Engine
{
    struct WindowProps
    {
        WindowProps()
        :
        width(DEFAULT_WINDOW_WIDTH),
        height(DEFAULT_WINDOW_HEIGHT),
        title(DEFAULT_WINDOW_TITLE)
        {}

        WindowProps(unsigned int width, 
        unsigned int height, 
        const char* title)
        :
        width(width),
        height(height),
        title(title)
        {}

        WindowProps(const WindowProps& other)
        :
        width(other.width),
        height(other.height),
        title(other.title)
        {}

        unsigned int width, height;
        std::string title;
        std::function<void(Event&)> EventCallback;
    };

    class Window
    {
        public:
            virtual ~Window() {};

            virtual void Update() = 0;
            virtual unsigned int GetWidth() const = 0;
            virtual unsigned int GetHeight() const = 0;
            virtual void* GetWindow() const = 0;

            virtual inline void SetEventCallback(const std::function<void(Event&)>& callback) = 0;

            static Window* Create(const WindowProps& props = WindowProps());
    };
}
#endif