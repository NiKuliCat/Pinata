#pragma once
/// <summary>
/// �����ڲ�����ʱ��������ʱ�����ŵ�
/// </summary>
namespace Pinata {

	class CoreTime
	{
	public:
		static void UpdateTime(const float time);
		const static float GetDeltaTime()  { return s_deltaTime; }

	private:
		static float s_lastFrameTime;
		static float s_deltaTime;

	};
}