#ifndef __BUFFER_H__
#define __BUFFER_H__

#include "Logging.h"
#include "EngineDefines.h"

namespace Engine
{
    enum class ShaderDataType
    {
        None = 0,
        Int, Int2, Int3, Int4,
        Float, Float2, Float3, Float4,
        Mat3, Mat4,
        Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType type)
    {
        switch(type)
        {
            case ShaderDataType::Int:      return sizeof(int);
            case ShaderDataType::Int2:     return sizeof(int) * 2;
            case ShaderDataType::Int3:     return sizeof(int) * 3;
            case ShaderDataType::Int4:     return sizeof(int) * 4;

            case ShaderDataType::Float:    return sizeof(float);
            case ShaderDataType::Float2:   return sizeof(float) * 2;
            case ShaderDataType::Float3:   return sizeof(float) * 3;
            case ShaderDataType::Float4:   return sizeof(float) * 4;

            case ShaderDataType::Mat3:     return sizeof(float) * 3 * 3;
            case ShaderDataType::Mat4:     return sizeof(float) * 4 * 4;

            case ShaderDataType::Bool:     return sizeof(bool);

            default: return 0;
        }

        ENGINE_ERROR("Invalid shader data type!");
        return 0;
    }

    struct BufferElement
    {
        ShaderDataType type;
        std::string name;
        uint32_t size;
        uint32_t offset;
        bool normalized;

        BufferElement() {}

        BufferElement(ShaderDataType type, const std::string& name, bool normalized = false)
        :
        type(type), name(name), size(ShaderDataTypeSize(type)), offset(0), normalized(normalized)
        {}

        uint32_t GetElementCount() const
        {
            switch(type)
            {
                case ShaderDataType::Float:
                case ShaderDataType::Bool:
                case ShaderDataType::Int: return 1;

                case ShaderDataType::Float2:
                case ShaderDataType::Int2: return 2;

                case ShaderDataType::Float3:
                case ShaderDataType::Mat3:
                case ShaderDataType::Int3: return 3;

                case ShaderDataType::Float4:
                case ShaderDataType::Mat4:
                case ShaderDataType::Int4: return 4;

                default: return 0 ;
            }

            ENGINE_ERROR("Invalid shader data type!");
            return 0;
        }
    };

    using ElementVec = std::vector<BufferElement>;

    class BufferLayout
    {
        public:
            BufferLayout() {}

            BufferLayout(const std::initializer_list<BufferElement>& elements)
            :
            m_elements(elements)
            {
                CalculateOffsetAndStride();
            }

            inline const ElementVec& GetElements() const { return m_elements; }
            inline const uint32_t GetStride() const { return m_stride; }

            ElementVec::iterator begin() { return m_elements.begin(); }
            ElementVec::iterator end() { return m_elements.end(); }
            ElementVec::const_iterator begin() const { return m_elements.begin(); }
            ElementVec::const_iterator end() const { return m_elements.end(); }
        private:
            void CalculateOffsetAndStride()
            {
                m_stride = 0;
                uint32_t offset = 0;
                for (auto& element : m_elements )
                {
                    element.offset = offset;
                    offset += element.size;
                    m_stride += element.size;
                }
            }

            ElementVec m_elements;
            uint32_t m_stride;
    };

    class VertexBuffer
    {
        public:
            virtual ~VertexBuffer() {}

            virtual void Bind() const = 0;
            virtual void UnBind() const = 0;

            virtual const BufferLayout& GetLayout() const = 0;
            virtual void SetLayout(const BufferLayout& layout) = 0;

            static Ref<VertexBuffer> Create(float* vertices, uint32_t size);
    };

    class IndexBuffer
    {
        public:
            virtual ~IndexBuffer() {}

            virtual void Bind() const = 0;
            virtual void UnBind() const = 0;

            virtual uint32_t GetCount() const = 0;

            static Ref<IndexBuffer> Create(uint32_t* indices, uint32_t count);
    };
}

#endif
