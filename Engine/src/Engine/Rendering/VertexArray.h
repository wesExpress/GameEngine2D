#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__

#include "Buffer.h"
#include "Engine/EngineDefines.h"
namespace Engine
{
    class VertexArray
    {
        public:
            virtual ~VertexArray() {}
            
            virtual void Bind() const = 0;
            virtual void UnBind() const = 0;

            virtual void AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer) = 0;
            virtual void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) = 0;

            const virtual std::vector<Ref<VertexBuffer>> GetVertexBuffers() const = 0;
            const virtual Ref<IndexBuffer> GetIndexBuffer() const = 0;

            static VertexArray* Create();
    };
}

#endif