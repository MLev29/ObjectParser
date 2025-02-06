#include "Engine.h"
#include "resourceManager/ResourceManager.h"
#include "model/Model.h"

#include <chrono>
#include <iostream>

#define MODEL_1 "bunny.obj"


objParser::Engine::Engine(math::Vector2<int> const& windowSize)
	: m_windowPtr(nullptr), m_windowSize(windowSize)
{
	m_shader = nullptr;
	m_camera = nullptr;
}

int objParser::Engine::Init(void)
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_windowPtr = glfwCreateWindow(m_windowSize[0], m_windowSize[1], "Shadow Mapping", NULL, NULL);
	if (m_windowPtr == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(m_windowPtr);
	glfwSetFramebufferSizeCallback(m_windowPtr, SFrameBufferCallback);

	// Init GLAD
	if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);
	glPolygonMode(GL_FRONT_AND_BACK, MESH_FILL ? GL_FILL : GL_LINE);

	m_shader = new Shader("Default.vs", "Default.fs");
	m_shader->InitShaders();

	auto startTime = std::chrono::high_resolution_clock::now();
	ResourceManager::GetInstance()->Load<Model>(MODEL_1);
	auto endTime = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime);
	auto durationSeconds = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
	auto durationMicro = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
	std::printf("Loading time: %f us\n", (float) durationMicro.count());
	std::printf("Loading time: %f ms\n", (float) duration.count());
	std::printf("Loading time: %f s\n", (float) durationSeconds.count());

	ResourceManager::GetInstance()->GetResource<Model>(MODEL_1)->SetColor({0.0f, 0.04f, 1.0f});
	
	m_camera = new Camera(math::Vector3<float>::Zero(), 5.0f);
	glfwSetInputMode(m_windowPtr, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	return 0;
}

void objParser::Engine::Update(float deltaTime)
{
	Input();
	m_camera->CameraInput(m_windowPtr, deltaTime);
	m_camera->MouseMotion(GetCursorPos(), deltaTime);

	static float denominator = 1.0f / m_windowSize[0];
	const float aspectRatio = static_cast<float>(m_windowSize[0] * denominator);

	glClearColor(0.0f, 0.26f, 0.26f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	math::Matrix4<float> perspective = m_camera->GetPerspectiveMatrix(0.01f, 100.0f, 60.0f, aspectRatio);
	math::Matrix4<float> view = m_camera->GetViewMatrix();
	math::Vector3 lightColor(1.0f);
	math::Vector3 lightPos = math::Vector3(-50.0f, 5.0f, 0.0f);

	m_shader->Use();
	m_shader->SetMatrix4("view", &view);
	m_shader->SetMatrix4("projection", &perspective);
	m_shader->SetVec3("viewPos", m_camera->GetPosition());
	m_shader->SetBool("isTextured", false);
	m_shader->SetVec3("lightColor", lightColor);
	m_shader->SetVec3("lightPos", lightPos);
	
	ResourceManager::GetInstance()->Update(m_shader);


	glfwSwapBuffers(m_windowPtr);
	glfwPollEvents();
}

void objParser::Engine::Shutdown(void)
{
	ResourceManager::GetInstance()->UnloadAll();
	ResourceManager::GetInstance()->CloseResourceManager();

	if (m_camera)
		delete m_camera;

	if (m_shader)
		delete m_shader;

	glfwTerminate();
}

GLFWwindow* objParser::Engine::GetWindowPtr(void) const noexcept
{
	return m_windowPtr;
}

void objParser::Engine::SFrameBufferCallback(GLFWwindow* windowPtr, int width, int height)
{
	Engine* engine = reinterpret_cast<Engine*>(glfwGetWindowUserPointer(windowPtr));

	if (engine)
		engine->FrameBufferCallback(width, height);
}

void objParser::Engine::SInputCallback(GLFWwindow* windowPtr, int key, int scanCode, int action, int mods)
{
	(void) windowPtr;
	(void) key;
	(void) scanCode;
	(void) action;
	(void) mods;
}

void objParser::Engine::FrameBufferCallback(int width, int height)
{
	glViewport(0, 0, width, height);
}

void objParser::Engine::Input(void)
{
	if (glfwGetKey(m_windowPtr, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(m_windowPtr, true);
}

math::Vector2<float> objParser::Engine::GetCursorPos(void) const noexcept
{
	double xCursorPos;
	double yCursorPos;

	glfwGetCursorPos(m_windowPtr, &xCursorPos, &yCursorPos);

	return math::Vector2<float>(
		xCursorPos,
		yCursorPos
	);
}
