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
		PTA_CORE_INFO("OpenGL-Version: {0}", reinterpret_cast<const char*>(glGetString(GL_VERSION)));
		PTA_CORE_INFO("OpenGLRenderer: {0}", reinterpret_cast<const char*>(glGetString(GL_RENDERER)));
	}
	void OpenGLContext::SwapBuffers()
	{
		glfwSwapBuffers(m_WindowHandle);
	}
}