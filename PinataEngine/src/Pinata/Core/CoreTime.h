#pragma once
/// <summary>
/// 引擎内部计算时间增量，时间缩放等
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