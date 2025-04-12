#pragma once
#include "Pinata/Renderer/GraphicsContext.h"

struct GLFWwindow;
namespace Pinata {

	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowsHandle);

		virtual	void Init() override;
		virtual void SwapBuffers()override;

	private:

		GLFWwindow* m_WindowHandle;

	};
}


