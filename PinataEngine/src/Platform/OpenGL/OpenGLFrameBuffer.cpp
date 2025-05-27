#include "ptapch.h"
#include "OpenGLFrameBuffer.h"
#include "Pinata/Renderer/Texture.h"
#include <glad/glad.h>
namespace Pinata {




	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferDescription& description)
		:m_Description(description)
	{
		Invaliadta();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteBuffers(1, &m_FrameBuffer_ID);
		glDeleteTextures(1, &m_ColorRT_ID);
		//glDeleteTextures(1, &m_DepthRT_ID);
	}

	void OpenGLFrameBuffer::ReSize(uint32_t width, uint32_t height)
	{
		m_Description.Width = width;
		m_Description.Height = height;
		Invaliadta();
	}

	void OpenGLFrameBuffer::Bind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer_ID);
		glViewport(0, 0, m_Description.Width, m_Description.Height);
	}

	void OpenGLFrameBuffer::UnBind()
	{
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
	}

	void OpenGLFrameBuffer::Invaliadta()
	{

		if (m_FrameBuffer_ID)
		{
			//glDeleteBuffers(1, &m_FrameBuffer_ID);
			glDeleteTextures(1, &m_ColorRT_ID);
			//glDeleteTextures(1, &m_DepthRT_ID);
		}

		glCreateFramebuffers(1, &m_FrameBuffer_ID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer_ID);

		TextureAttributes attri;
		attri.Width = m_Description.Width;
		attri.Height = m_Description.Height;
		//m_ColorRT_ID = Texture2D::Create(attri)->GetID();

		glCreateTextures(GL_TEXTURE_2D, 1, &m_ColorRT_ID);
		glBindTexture(GL_TEXTURE_2D, m_ColorRT_ID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Description.Width, m_Description.Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ColorRT_ID, 0);

		glCreateTextures(GL_TEXTURE_2D, 1, &m_DepthRT_ID);
		glBindTexture(GL_TEXTURE_2D, m_DepthRT_ID);
		glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, m_Description.Width, m_Description.Height);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, m_DepthRT_ID, 0);


		PTA_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == = GL_FRAMEBUFFER_COMPLETE, "frame buffer is not completed");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

}