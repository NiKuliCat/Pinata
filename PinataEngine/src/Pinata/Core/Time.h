#pragma once
#include "CoreTime.h"
/// <summary>
/// �ṩ���ⲿ�༭��ʹ�õ�API
/// </summary>
namespace Pinata {

	class Time
	{
	public:
		 static float GetDeltaTime() { return CoreTime::GetDeltaTime(); }
	};

}