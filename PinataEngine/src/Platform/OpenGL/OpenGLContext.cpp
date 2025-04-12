#include "ptapch.h"
#include "OpenGLContext.h"

#include <glad/glad.h>
#include "GLFW/glfw3.h"

namespace Pinata {
	OpenGLContext::OpenGLContext(GLFWwindow* windowsHandle)
		:m_WindowHandle(windowsHandle)
	{
		PTA_CORE_ASSERT(windowsHandle, "windows handle is null !");
	}
	void OpenGLContext::Init()
	{
		glfwMakeContextCurrent(m_WindowHandle);
		int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		PTA_CORE_ASSERT(status, "Failed to init Glad !");
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}