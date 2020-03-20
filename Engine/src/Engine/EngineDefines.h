#ifndef __DEFINES_H__
#define __DEFINES_H__

#include <memory>
#include "Logging.h"

#ifdef __APPLE__
    static inline std::string const ASSET_PATH = "/Users/wesleypeters/random_code/GameEngine2D/Application/assets/";
#else
    static inline std::string const ASSET_PATH = "C:/Users/wcp/source/projects/GameEngine2D/Application/assets/";
#endif

#define BIND_FN(x) std::bind(&x, this, std::placeholders::_1)
#define BIT(x) (1 << x)
#define ENGINE_ASSERT(x, ...) { if(!x) { ENGINE_ERROR("Assertion Failed: {0}", __VA_ARGS__); abort(); } }

namespace Engine
{
    template<typename T>
    using Scope = std::unique_ptr<T>;

    template<typename T>
    using Ref = std::shared_ptr<T>;
}

#endif