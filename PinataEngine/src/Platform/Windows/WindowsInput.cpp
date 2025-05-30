#include "ptapch.h"
#include "Pinata/Core/Input.h"
#include "Pinata/Core/Application.h"
#include <GLFW/glfw3.h>
namespace Pinata {

	bool Input::IsKeyPressed(int keycode)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetKey(window, static_cast<int32_t>(keycode));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	bool Input::IsMouseButtonPressed(int button)
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());

		auto state = glfwGetMouseButton(window, static_cast<int32_t>(button));
		return state == GLFW_PRESS || state == GLFW_REPEAT;
	}
	std::pair<float, float> Input::GetMousePosition()
	{
		auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);
		return {(float)xpos,(float)ypos};
	}
	float Input::GetMouseX()
	{
		auto [x, y] = Input::GetMousePosition();
		return x;
	}
	float Input::GetMouseY()
	{
		auto [x, y] = Input::GetMousePosition();
		return y;
	}

}

