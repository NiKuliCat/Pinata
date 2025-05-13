#pragma once

namespace Pinata {


	struct FrameBufferDescription
	{
		uint32_t Width, Height;

		uint32_t samples = 1;
		bool SwapChainTarget = false;
	};

	class FrameBuffer
	{

	public:
		virtual  FrameBufferDescription& GetBufferDescription() = 0;
		virtual const FrameBufferDescription& GetBufferDescription() const  = 0;

		virtual uint32_t GetColorRenderTexture() = 0;
		virtual uint32_t GetDepthRenderTexture() = 0;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;


	public:
		static Ref<FrameBuffer> Create(const FrameBufferDescription& description);

	};
}