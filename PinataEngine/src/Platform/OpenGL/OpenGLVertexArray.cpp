#include "ptapch.h"
#include "OpenGLVertexArray.h"
#include <glad/glad.h>
namespace Pinata {

	static GLenum ShaderDataTypeToOpenGL(ShaderDataType type)
	{
		switch (type
)
		{
			case Pinata::ShaderDataType::Float:		return GL_FLOAT;
			case Pinata::ShaderDataType::Float2:	return GL_FLOAT;
			case Pinata::ShaderDataType::Float3:	return GL_FLOAT;
			case Pinata::ShaderDataType::Float4:	return GL_FLOAT;
			case Pinata::ShaderDataType::Int:		return GL_INT;
			case Pinata::ShaderDataType::Int2:		return GL_INT;
			case Pinata::ShaderDataType::Int3:		return GL_INT;
			case Pinata::ShaderDataType::Int4:		return GL_INT;
			case Pinata::ShaderDataType::Mat3:		return GL_FLOAT;
			case Pinata::ShaderDataType::Mat4:		return GL_FLOAT;
			case Pinata::ShaderDataType::Bool:		return GL_BOOL;
		}
		PTA_CORE_ASSERT(false, "Unkown ShaderDataType!");
		return 0;
	}

	OpenGLVertexArray::OpenGLVertexArray()
	{
		glCreateVertexArrays(1, &m_VertexArrayID);
	}
	OpenGLVertexArray::~OpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &m_VertexArrayID);
	}
	void OpenGLVertexArray::Bind() const
	{
		glBindVertexArray(m_VertexArrayID);
	}
	void OpenGLVertexArray::UnBind() const
	{
		glBindVertexArray(0);
	}
	void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
	{
		PTA_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size, "vertex buffer not set layout");
		//首先绑定顶点组
		glBindVertexArray(m_VertexArrayID);

		vertexBuffer->Bind();

		uint32_t index = 0;
		const auto& layout = vertexBuffer->GetLayout();
		for (auto& element : layout)
		{
			glEnableVertexAttribArray(index);
			glVertexAttribPointer(
				index, element.Count,
				ShaderDataTypeToOpenGL(element.DataType), 
				element.Normalized ? GL_TRUE : GL_FALSE,
				layout.GetVertexStride(), (void*)element.Offset);
			index++;
		}
		m_VertexBuffers.push_back(vertexBuffer);

	}
	void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
	{
		//首先绑定顶点组
		glBindVertexArray(m_VertexArrayID);
		indexBuffer->Bind();

		m_IndexBuffer = indexBuffer;
	}
	const std::vector<Ref<VertexBuffer>>& OpenGLVertexArray::GetVertexBuffers() const
	{
		return m_VertexBuffers;
	}
	const Ref<IndexBuffer>& OpenGLVertexArray::GetIndexBuffer() const
	{
		return m_IndexBuffer;
	}
}