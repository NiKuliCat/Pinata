#pragma once
#include "Pinata/Core/Core.h"

namespace Pinata {

	class PINATA_API Input
	{
	public:
		static bool IsKeyPressed(int keycode) ;
		static bool IsMouseButtonPressed(int button); 
		static std::pair<float, float> GetMousePosition();
		static float GetMouseX();
		static float GetMouseY();
	};
}
