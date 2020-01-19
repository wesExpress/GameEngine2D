#ifndef __DEFINES_H__
#define __DEFINES_H__

#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)
#define BIT(x) (1 << x)
#define ENGINE_ASSERT(x, ...) { if(!x) { ENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); abort(); } }

#endif