#include "Camera.h"

#include "LibMath/Angle.h"
#include "LibMath/Arithmetic.h"

#include <iostream>

objParser::Camera::Camera(math::Vector3<float> position, float speed)
	: m_position(position), m_speed(speed), m_angularSpeed(5.0f)
{
	m_up = math::Vector3<float>::Up();
	m_forward = -math::Vector3<float>::Forward();
	m_right = (m_forward.Cross(m_up)).Normalize();
}

math::Matrix4<float> objParser::Camera::GetPerspectiveMatrix(float _near, float _far, float fovDeg, float aspect) const noexcept
{
	float fovRad = fovDeg * DEG2RAD;

	const float tanAngle = tanf(fovRad * 0.5f);
	const float farMinusNear = _far - _near;

	const float perspectiveValues[16] =
	{
		1.0f / (aspect * tanAngle), 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f / tanAngle, 0.0f, 0.0f,
		0.0f, 0.0f, -(_far + _near) / (farMinusNear), -1.0f,
		0.0f, 0.0f, -((2.0f * _far * _near) / (farMinusNear)), 0.0f
	};

	return math::Matrix4<float>(perspectiveValues);
}

math::Matrix4<float> objParser::Camera::GetViewMatrix(void)
{
	// Camera forward direction
	math::Vector3<float> center = m_position + m_forward;
	math::Vector3<float> forward = (center - m_position).Normalize();
	m_right = (forward.Cross(m_up)).Normalize();
	math::Vector3<float> up = m_right.Cross(forward);

	const float viewValues[16] =
	{
		m_right[0], up[0], -forward[0], 0.0f,
		m_right[1], up[1], -forward[1], 0.0f,
		m_right[2], up[2], -forward[2], 0.0f,
		-(m_right.Dot(m_position)), -(up.Dot(m_position)), forward.Dot(m_position), 1.0f
	};

	return math::Matrix4<float>(viewValues);
}

math::Vector3<float> objParser::Camera::GetPosition(void) const noexcept
{
	return m_position;
}

math::Vector3<float>& objParser::Camera::GetPosition(void)
{
	return m_position;
}

void objParser::Camera::CameraInput(GLFWwindow* windowPtr, float deltaTime)
{
	// Keyboard inputs
	if (glfwGetKey(windowPtr, GLFW_KEY_W) == GLFW_PRESS)
		m_position += m_forward * m_speed * deltaTime;
	else if (glfwGetKey(windowPtr, GLFW_KEY_S) == GLFW_PRESS)
		m_position += -m_forward * m_speed * deltaTime;

	if (glfwGetKey(windowPtr, GLFW_KEY_A) == GLFW_PRESS)
		m_position += -m_right * m_speed * deltaTime;
	else if (glfwGetKey(windowPtr, GLFW_KEY_D) == GLFW_PRESS)
		m_position += m_right * m_speed * deltaTime;

	if (glfwGetKey(windowPtr, GLFW_KEY_Q) == GLFW_PRESS)
		m_position -= math::Vector3<float>::Up() * m_speed * deltaTime;
	else if (glfwGetKey(windowPtr, GLFW_KEY_E) == GLFW_PRESS)
		m_position += math::Vector3<float>::Up() * m_speed * deltaTime;

	//std::printf("pos: %f, %f, %f\n", m_position[0], m_position[1], m_position[2]);
}

void objParser::Camera::MouseMotion(math::Vector2<float> const& cursorPos, float deltaTime)
{
	static math::Vector2<float> lastCursorPos(cursorPos);
	static float yaw, pitch = 0.0f;

	// Calculate delta mouse position
	math::Vector2<float> deltaPos = (cursorPos - lastCursorPos) * deltaTime;

	// Prevent large numbers such as garbage data for yaw & pitch

	if (math::Abs(deltaPos[0]) > 3.0f)
		deltaPos[0] = (deltaPos[0] < 0.0f) ? -3.0f : 3.0f;
	if (math::Abs(deltaPos[1]) > 3.0f)
		deltaPos[1] = (deltaPos[1] < 0.0f) ? -3.0f : 3.0f;

	// Assign last cursor value
	lastCursorPos = cursorPos;

	// Update yaw & pitch
	yaw += deltaPos[0] * m_angularSpeed;
	pitch -= deltaPos[1] * m_angularSpeed;

	// Wrap yaw & pitch from 0 - 360 degrees
	yaw = fmodf(yaw, 360.0f);
	pitch = fmodf(pitch, 360.0f);

	// Convert degree to radian
	const float yawRad = yaw * DEG2RAD;
	const float pitchRad = pitch * DEG2RAD;

	// Rotate camera via pitch & yaw values
	m_forward = LibMath::Vector3(
		cosf(yawRad) * cosf(pitchRad),
		sinf(pitchRad),
		sinf(yawRad) * cosf(pitchRad)
	).Normalize();

	m_right = (m_forward.Cross(math::Vector3<float>::Up())).Normalize();
	m_up = (m_right.Cross(m_forward)).Normalize();

	//std::printf("yaw: %f, pitch: %f\n", m_yaw, m_pitch);
}