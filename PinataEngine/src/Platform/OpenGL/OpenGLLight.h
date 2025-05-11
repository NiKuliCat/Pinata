#pragma once
#include "Pinata/Renderer/Light.h"

namespace Pinata {


	class OpenGLLight : public Light
	{
	public:
		OpenGLLight(LightData& lightData);
	private:
		LightData m_LightData;
	};

}