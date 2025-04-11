#pragma once
#include "Core.h"
#include "Pinata/Event/Event.h"

namespace Pinata {

	struct WindowProps
	{
		std::string Title;
		uint32_t Width;
		uint32_t Height;


		WindowProps(const std::string& title = "Pinata Engine",
					const uint32_t width = 1920,
					const uint32_t height = 1080)
			:Title(title),Width(width),Height(height)
		{

		}
	};

	class PINATA_API Window
	{
	public:
		using EventCallbackFn = std::function<void(Event&)>; // ����ָ�� ���� ����ֵΪ�� ����Ϊevent

		virtual ~Window() = default;

		virtual void OnUpdata() = 0;

		virtual uint32_t GetWidth() const = 0;
		virtual uint32_t GetHeight() const = 0;

		virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
		virtual void SetVSync(bool enabled) = 0;
		virtual bool isVSync() const = 0;

		virtual void* GetNativeWindow()  const  = 0;
		static Window* Create(const WindowProps& props = WindowProps());

	};
}