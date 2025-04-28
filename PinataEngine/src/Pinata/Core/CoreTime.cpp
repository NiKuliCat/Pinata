#include "ptapch.h"
#include "CoreTime.h"
namespace Pinata {

	float CoreTime::s_lastFrameTime = 0.0f;
	float CoreTime::s_deltaTime = 0.0f;

	 void CoreTime::UpdateTime(const float time)
	{
		s_deltaTime = time - s_lastFrameTime;
		s_lastFrameTime = time;
	}
}