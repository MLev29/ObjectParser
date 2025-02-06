#pragma once
#include <GLFW/glfw3.h>
#include "MemoryCheck.h"

namespace objParser
{
	float DeltaTime(void)
	{
		static float prevTime = 0.0f;
		float currentTime = static_cast<float>(glfwGetTime());

		float deltaTime = currentTime - prevTime;
		prevTime = currentTime;

		return deltaTime;
	}
}