#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>
#include "Engine.h"

namespace Engine
{
    class Texture
    {
        public:
            virtual ~Texture() = default;

            virtual uint32_t GetHeight() const = 0;
            virtual uint32_t GetWidth() const  = 0;

            virtual void Bind(uint32_t slot = 0) const = 0;
    };

    class Texture2D : public Texture
    {
        public:
            static Ref<Texture2D> Create(const std::string& path);
    };
}

#endif