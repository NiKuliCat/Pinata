#pragma once
#include "CoreTime.h"
/// <summary>
/// 提供给外部编辑器使用的API
/// </summary>
namespace Pinata {

	class Time
	{
	public:
		 static float GetDeltaTime() { return CoreTime::GetDeltaTime(); }
	};

}