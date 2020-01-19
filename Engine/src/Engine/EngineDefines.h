#ifndef __DEFINES_H__
#define __DEFINES_H__

#define ENGINE_ASSERT(x, ...) { if(!x) { ENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); abort(); } }

#endif