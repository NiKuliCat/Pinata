#pragma once
#include "Pinata/Renderer/UniformBuffer.h"

namespace Pinata {

	class OpenGLUniformBuffer : public UniformBuffer
	{
	public:
		OpenGLUniformBuffer(uint32_t size,uint32_t binding);
		~OpenGLUniformBuffer();
		virtual void SetData(const void* data, uint32_t size, uint32_t offset = 0) override;

	private:
		uint32_t m_UniformBufferID = 0;
	};
}