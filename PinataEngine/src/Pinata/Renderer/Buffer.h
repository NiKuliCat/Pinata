#pragma once

namespace Pinata {

	enum class ShaderDataType
	{
		None = 0, Float,Float2,Float3,Float4,Int,Int2,Int3,Int4,Mat3,Mat4,Bool
	};

	static uint32_t GetShaderDataTypeSize(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::None:			return 0;
			case ShaderDataType::Float:			return 4;
			case ShaderDataType::Float2:		return 2 * 4;
			case ShaderDataType::Float3:		return 3 * 4;
			case ShaderDataType::Float4:		return 4 * 4;
			case ShaderDataType::Int:			return 4;
			case ShaderDataType::Int2:			return 2 * 4;
			case ShaderDataType::Int3:			return 3 * 4;
			case ShaderDataType::Int4:			return 4 * 4;
			case ShaderDataType::Mat3:			return 3 * 3 * 4;
			case ShaderDataType::Mat4:			return 4 * 4 * 4;
			case ShaderDataType::Bool:			return 1;
		}
	}

	static uint32_t GetShaderDataTypeCount(ShaderDataType type)
	{
		switch (type)
		{
			case ShaderDataType::None:			return 0;
			case ShaderDataType::Float:			return 1;
			case ShaderDataType::Float2:		return 2;
			case ShaderDataType::Float3:		return 3;
			case ShaderDataType::Float4:		return 4;
			case ShaderDataType::Int:			return 1;
			case ShaderDataType::Int2:			return 2;
			case ShaderDataType::Int3:			return 3;
			case ShaderDataType::Int4:			return 4;
			case ShaderDataType::Mat3:			return 3;
			case ShaderDataType::Mat4:			return 4;
			case ShaderDataType::Bool:			return 1;
		}
	}

	struct BufferElement
	{
		std::string Name;
		ShaderDataType DataType;
		uint32_t Size;
		uint32_t Count;
		uint32_t Offset;
		bool Normalized;

		BufferElement() = default;
		BufferElement( ShaderDataType type, const std::string& name,bool normalized = false)
			:Name(name), DataType(type),Size(GetShaderDataTypeSize(type)),Count(GetShaderDataTypeCount(type)),Offset(0), Normalized(normalized)
		{

		}

	};

	class BufferLayout
	{
	public:
		BufferLayout() {}
		BufferLayout(const std::initializer_list<BufferElement>& elements)
			:m_Elements(elements)
		{
			CaculateVertexStrideAndOffset();
		}

		inline const std::vector<BufferElement>& GetElements() const  { return m_Elements; }
		inline const uint32_t GetVertexStride() const { return m_Stride; }


		std::vector<BufferElement>::iterator begin() { return m_Elements.begin(); }
		std::vector<BufferElement>::iterator end() { return m_Elements.end(); }
		std::vector<BufferElement>::const_iterator begin() const { return m_Elements.begin(); }
		std::vector<BufferElement>::const_iterator end() const { return m_Elements.end(); }

	private:
		 uint32_t CaculateVertexStrideAndOffset()
		{
			 uint32_t offset = 0;
			 m_Stride = 0;
			 for (auto& element : m_Elements)
			 {
				 element.Offset = offset;
				 offset += element.Size;
				 m_Stride += element.Size;
			 }

			 return m_Stride;
		}

	private:
		std::vector<BufferElement> m_Elements;
		uint32_t m_Stride = 0;
	};

	///////////////////////////// vertex buffer /////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
	class VertexBuffer
	{
	public:

		virtual ~VertexBuffer(){}
		virtual void Bind() const = 0;
		virtual void UnBind() const = 0;

		virtual void SetLayout(BufferLayout& layout)  = 0;
		virtual const  BufferLayout& GetLayout() const = 0;

		virtual void SetData(const void* data, uint32_t size) = 0;

	public:
		static Ref<VertexBuffer> Create(uint32_t size);
		static Ref<VertexBuffer> Create(float* vertices, uint32_t size);

	};

	///////////////////////////// index buffer /////////////////////////////////////////
	///////////////////////////////////////////////////////////////////////////////////
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