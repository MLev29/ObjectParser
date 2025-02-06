#pragma once

#include "LibMath/Vector/Vector2.h"
#include "LibMath/Vector/Vector3.h"
#include "LibMath/Matrix/Matrix4.h"

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

#include "tools/MemoryCheck.h"

namespace objParser
{
	class Camera
	{
	public:
								Camera(void) = default;
								Camera(math::Vector3<float> position, float speed);
								~Camera(void) = default;

		math::Matrix4<float>	GetPerspectiveMatrix(float near, float far, float fovDeg, float aspect) const noexcept;
		math::Matrix4<float>	GetViewMatrix(void);
		math::Vector3<float>	GetPosition(void) const noexcept;
		math::Vector3<float>&	GetPosition(void);
		void					CameraInput(GLFWwindow* windowPtr, float deltaTime);
		void					MouseMotion(math::Vector2<float> const& cursorPos, float deltaTime);

	private:
		// View matrix
		math::Vector3<float>	m_position;
		math::Vector3<float>	m_up;
		math::Vector3<float>	m_right;
		math::Vector3<float>	m_forward;
		math::Vector2<float>	m_lastCursorPos;

		// Transformation
		float					m_speed;
		float					m_angularSpeed;
		float					m_yaw;
		float					m_pitch;
	};
}
