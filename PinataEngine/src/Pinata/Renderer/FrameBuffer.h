#pragma once

namespace Pinata {

	enum class FrameBufferTexFormat
	{
		None = 0,

		RGBA8,
		RGBA16F,

		DEPTH24STENCIL8,
		DEPTH = DEPTH24STENCIL8
	};


	struct FrameBufferTexDescription
	{
		FrameBufferTexFormat  TextureFormat;

		FrameBufferTexDescription() = default;
		FrameBufferTexDescription(FrameBufferTexFormat format)
			:TextureFormat(format){ }
	};

	struct FrameBufferAttachmentDescription
	{
		std::vector<FrameBufferTexDescription> Attachments;

		FrameBufferAttachmentDescription() = default;
		FrameBufferAttachmentDescription(std::initializer_list<FrameBufferTexDescription> attachments)
			:Attachments(attachments){ }

	};


	struct FrameBufferDescription
	{
		FrameBufferAttachmentDescription AttachmentsDescription;
		uint32_t Width, Height;
		uint32_t Samples = 1;
		bool SwapChainTarget = false;
	};

	class FrameBuffer
	{

	public:
		virtual ~FrameBuffer() = default;
		virtual  FrameBufferDescription& GetBufferDescription() = 0;
		virtual const FrameBufferDescription& GetBufferDescription() const  = 0;

		virtual uint32_t GetColorRenderTexture(uint32_t index = 0) = 0;
		virtual uint32_t GetDepthRenderTexture() = 0;

		virtual void ReSize(uint32_t width, uint32_t height) = 0;

		virtual void Bind() = 0;
		virtual void UnBind() = 0;


	public:
		static Ref<FrameBuffer> Create(const FrameBufferDescription& description);

	};
}