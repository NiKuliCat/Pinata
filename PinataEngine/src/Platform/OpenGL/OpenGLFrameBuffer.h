#pragma once
#include "Pinata/Renderer/FrameBuffer.h"

namespace Pinata {


	class OpenGLFrameBuffer : public FrameBuffer
	{


	public:
		OpenGLFrameBuffer(const FrameBufferDescription& description);
		virtual ~OpenGLFrameBuffer();


	public:
		virtual  FrameBufferDescription& GetBufferDescription() override { return m_Description; }
		virtual const FrameBufferDescription& GetBufferDescription() const override { return m_Description; }

		virtual uint32_t GetColorRenderTexture(uint32_t index = 0) override { return m_ColorAttachments[index]; }
		virtual uint32_t GetDepthRenderTexture() override { return m_DepthAttachment; }

		virtual void ReSize(uint32_t width, uint32_t height) override;

		virtual void Bind()  override;
		virtual void UnBind() override;

	public:

		void Invaliadta();
	private:
		FrameBufferDescription m_Description;
		std::vector<FrameBufferTexDescription> m_ColorAttachmentDescriptions; // 可以有多个颜色缓冲区，但只有一个深度缓冲区
		FrameBufferTexDescription m_DepthAttachmentDescription;

		uint32_t m_FrameBuffer_ID = 0;
		std::vector<uint32_t> m_ColorAttachments ;
		uint32_t m_DepthAttachment = 0;


	};

}