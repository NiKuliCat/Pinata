#pragma once
#include "Pinata/Core/Core.h"
#include "Pinata/Core/Window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace Pinata {
	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowProps& props);

		virtual ~WindowsWindow();

		void OnUpdata() override;

		inline uint32_t GetWidth() const  override { return m_Data.Width; }
		inline uint32_t GetHeight() const override { return m_Data.Height; }

		inline void SetEventCallback(const EventCallbackFn& callback) override { m_Data.EventCallback = callback; }

		void SetVSync(bool enabled) override;
		bool isVSync() const override;

	private:

		virtual void Init(const WindowProps& props);
		virtual void Shutdown();

	private:
		GLFWwindow* m_Window;


	private:

		struct WindowData
		{
			std::string Title;
			uint32_t Width, Height;

			bool VSync;
			EventCallbackFn EventCallback;
		};

		WindowData m_Data;
	};

}