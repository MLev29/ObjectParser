#pragma once

#include "LibMath/vector/Vector2.h"

#include "camera/Camera.h"
#include "shader/Shader.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "tools/MemoryCheck.h"

#ifndef MESH_FILL
#define MESH_FILL 1
#endif

namespace objParser
{
	class Engine
	{
	public:
					Engine(void) = delete;
					Engine(math::Vector2<int> const& windowSize);
					~Engine(void) = default;

		int			Init(void);
		void		Update(float deltaTime);
		void		Shutdown(void);

		GLFWwindow* GetWindowPtr(void) const noexcept;
	private:
		static void SFrameBufferCallback(GLFWwindow* windowPtr, int width, int height);
		static void SInputCallback(GLFWwindow* windowPtr, int key, int scanCode, int action, int mods);

		void		FrameBufferCallback(int width, int height);
		void		Input(void);
		math::Vector2<float> GetCursorPos(void) const noexcept;

		Camera*				m_camera;
		Shader*				m_shader;
		GLFWwindow*			m_windowPtr;
		math::Vector2<int>	m_windowSize;
	};
}