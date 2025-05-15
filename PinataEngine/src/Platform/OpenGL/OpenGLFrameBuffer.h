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

		virtual uint32_t GetColorRenderTexture() override { return m_ColorRT_ID; }
		virtual uint32_t GetDepthRenderTexture() override { return m_DepthRT_ID; }

		virtual void ReSize(uint32_t width, uint32_t height) override;

		virtual void Bind()  override;
		virtual void UnBind() override;

	public:

		void Invaliadta();
	private:
		FrameBufferDescription m_Description;
		uint32_t m_FrameBuffer_ID = 0;
		uint32_t m_ColorRT_ID = 0;
		uint32_t m_DepthRT_ID = 0;


	};

}