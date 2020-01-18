#ifndef __VERTEXARRAY_H__
#define __VERTEXARRAY_H__

namespace Engine
{
    class VertexArray
    {
        public:
            virtual ~VertexArray() {}
            
            virtual void Bind() const = 0;
            virtual void UnBind() const = 0;

            static VertexArray* Create();
    };
}

#endif