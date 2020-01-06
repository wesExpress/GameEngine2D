#ifndef __KEYBOARDEVENT_H__
#define __KEYBOARDEVENT_H__

#include "Event.h"

class KeyboardEvent : public Event
{

};

class KeyPressedEvent : public KeyboardEvent
{

};

class KeyReleasedEvent : public KeyboardEvent
{

}; 

#endif