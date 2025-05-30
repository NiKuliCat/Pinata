#include "ptapch.h"
#include "OpenGLFrameBuffer.h"
#include "Pinata/Renderer/Texture.h"
#include "OpenGLUtils.h"
#include <glad/glad.h>
namespace Pinata {

	OpenGLFrameBuffer::OpenGLFrameBuffer(const FrameBufferDescription& description)
		:m_Description(description)
	{
		for (auto format : m_Description.AttachmentsDescription.Attachments)
		{
			if (OpenGLUtils::isDepthFormat(format.TextureFormat))
			{
				m_DepthAttachmentDescription = format;
			}
			else
			{
				m_ColorAttachmentDescriptions.emplace_back(format);
			}
		}

		Invaliadta();
	}

	OpenGLFrameBuffer::~OpenGLFrameBuffer()
	{
		glDeleteFramebuffers(1, &m_FrameBuffer_ID);
		glDeleteTextures(m_ColorAttachments.size(), m_ColorAttachments.data());
		glDeleteTextures(1, &m_DepthAttachment);
	}

	int OpenGLFrameBuffer::GetIDBufferValue(int x, int y)
	{
		PTA_CORE_ASSERT(m_ColorAttachments.size() > 1, "Not Created ID Buffer");
		glReadBuffer(GL_COLOR_ATTACHMENT0 + 1);
		int pixel;
		glReadPixels(x, y, 1, 1, GL_RED_INTEGER, GL_INT, &pixel);
		return pixel;
	}

	void OpenGLFrameBuffer::ClearIDBuffer(int value)
	{
		PTA_CORE_ASSERT(m_ColorAttachments.size() > 1, "Not Created ID Buffer");
		auto& description = m_ColorAttachmentDescriptions[1];

		glClearTexImage(m_ColorAttachments[1], 0, OpenGLUtils::FrameBufferFormatToOpenGLFormat(description.TextureFormat),GL_INT, &value);
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
			glDeleteFramebuffers(1, &m_FrameBuffer_ID);
			glDeleteTextures(m_ColorAttachments.size(),m_ColorAttachments.data());
			glDeleteTextures(1, &m_DepthAttachment);

			m_ColorAttachments.clear();
			m_DepthAttachment = 0;
		}

		glCreateFramebuffers(1, &m_FrameBuffer_ID);
		glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBuffer_ID);

		bool multisampled = m_Description.Samples > 1;

		// color attach
		if (m_ColorAttachmentDescriptions.size())
		{
			m_ColorAttachments.resize(m_ColorAttachmentDescriptions.size());
			OpenGLUtils::CreateTextures(multisampled, m_ColorAttachments.data(), m_ColorAttachments.size());
			for (size_t i = 0; i < m_ColorAttachments.size(); i++)
			{
				OpenGLUtils::BindTexture(multisampled, m_ColorAttachments[i]);
				switch (m_ColorAttachmentDescriptions[i].TextureFormat)
				{
					case FrameBufferTexFormat::RGBA8:
					{
						OpenGLUtils::AttachColorTexture(m_ColorAttachments[i], m_Description.Samples, GL_RGBA8, GL_RGBA,m_Description.Width, m_Description.Height, i);
						break;
					}
					case FrameBufferTexFormat::RED_INTEGER:
					{
						OpenGLUtils::AttachColorTexture(m_ColorAttachments[i], m_Description.Samples, GL_R32I, GL_RED_INTEGER, m_Description.Width, m_Description.Height, i);
						break;
					}
				}
			}
		}

		// depth attach
		if (m_DepthAttachmentDescription.TextureFormat != FrameBufferTexFormat::None)
		{
			OpenGLUtils::CreateTextures(multisampled, &m_DepthAttachment, 1);
			OpenGLUtils::BindTexture(multisampled, m_DepthAttachment);
			switch (m_DepthAttachmentDescription.TextureFormat)
			{
				case FrameBufferTexFormat::DEPTH24STENCIL8:
				{
					OpenGLUtils::AttachDepthTexture(m_DepthAttachment, m_Description.Samples, GL_DEPTH24_STENCIL8,GL_DEPTH_STENCIL_ATTACHMENT, m_Description.Width, m_Description.Height);
					break;
				}
			}
		}


		if (m_ColorAttachments.size() > 1)
		{
			PTA_CORE_ASSERT(m_ColorAttachments.size() <= 4, "OpenGL frame buffer size is more than 4 ");
			GLenum buffers[4] = { GL_COLOR_ATTACHMENT0,GL_COLOR_ATTACHMENT1 ,GL_COLOR_ATTACHMENT2 ,GL_COLOR_ATTACHMENT3 };
			glDrawBuffers(m_ColorAttachments.size(), buffers);
		}
		else if (m_ColorAttachments.empty())
		{
			//only depth pass
			glDrawBuffer(GL_NONE);
		}
		PTA_CORE_ASSERT(glCheckFramebufferStatus(GL_FRAMEBUFFER) == = GL_FRAMEBUFFER_COMPLETE, "frame buffer is not completed");

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

}