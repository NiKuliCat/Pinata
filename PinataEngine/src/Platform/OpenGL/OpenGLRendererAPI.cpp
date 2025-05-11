#include "ptapch.h"
#include "OpenGLRendererAPI.h"
#include <glad/glad.h>
namespace Pinata {
	void OpenGLRendererAPI::Init()
	{
		SetBlend(true);
		SetDepthTest(true);
	}
	void OpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void OpenGLRendererAPI::SetClearColor(const glm::vec4 color)
	{
		glClearColor(color.r, color.g, color.b, color.a);
	}
	void OpenGLRendererAPI::SetBlend(bool value)
	{
		if (value)
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else
		{
			glDisable(GL_BLEND);
		}
	}
	void OpenGLRendererAPI::SetDepthTest(bool value)
	{
		if (value)
		{
			glEnable(GL_DEPTH_TEST);
		}
		else
		{
			glDisable(GL_DEPTH_TEST);
		}
	}
	void OpenGLRendererAPI::SetViewport(const uint32_t x, const  uint32_t y, const uint32_t width, const  uint32_t height)
	{
		glViewport(x, y, width, height);
	}
	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
	{
		glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
	}
	void OpenGLRendererAPI::DrawIndexed(const Ref<VertexArray>& vertexArray, const uint32_t count)
	{
		glDrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, nullptr);
	}
}