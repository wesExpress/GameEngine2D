#ifndef __WINDOWEVENT_H__
#define __WINDOWEVENT_H__

#include "Event.h"

class WindowEvent : public Event
{

};

class WindowCloseEvent : public WindowEvent
{

};

class WindowResizeEvent : public WindowEvent
{
    public:
        WindowResizeEvent(int width, int height);
};

#endif