#pragma once
#include "Pinata/Renderer/Buffer.h"

namespace Pinata {

	class OpenGLVertexBuffer : public VertexBuffer
	{
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;

		virtual void SetLayout(BufferLayout& layout) override 
		{
			m_Layout = layout;
		}
		virtual const BufferLayout& GetLayout() const override
		{
			return m_Layout;
		}

	private:
		uint32_t m_VertexBufferID;
		BufferLayout m_Layout;
	};

	class OpenGLIndexBuffer : public IndexBuffer
	{
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
		virtual ~OpenGLIndexBuffer();
		virtual void Bind() const override;
		virtual void UnBind() const override;
		virtual uint32_t GetCount() const override { return  m_Count; }
	public:
		
	private:
		uint32_t m_IndexBufferID;
		uint32_t m_Count;
	};
}
