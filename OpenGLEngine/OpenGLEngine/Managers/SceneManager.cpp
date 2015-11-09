//SceneManager.cpp
#include "SceneManager.h"

Managers::SceneManager::SceneManager()
{
	glEnable(GL_DEPTH_TEST);

	shaderManager = new Managers::ShaderManager();
	shaderManager->CreateProgram("colorShader", "Shaders\\vertex.glsl", "Shaders\\fragment.glsl");
	shaderManager->CreateProgram("lightingShader", "Shaders\\LightingVertex.glsl", "Shaders\\LightingFragment.glsl");
	shaderManager->CreateProgram("simpleShader", "Shaders\\SimpleVertex.glsl", "Shaders\\LightingFragment.glsl");

	modelManager = new Managers::ModelManager();

	viewMatrix = glm::mat4(1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, -1.0f, 0.0f,
		0.0f, 0.0f, 10.0f, 1.0f);
	
}

Managers::SceneManager::~SceneManager()
{
	delete shaderManager;
	delete modelManager;
}

void Managers::SceneManager::notifyBeginFrame()
{
	modelManager->Update();
}

void Managers::SceneManager::notifyDisplayFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0, 0.0, 0.0, 1.0);//clear to black

	modelManager->Draw(projectionMatrix, viewMatrix);
}

void Managers::SceneManager::notifyEndFrame()
{
	//nothing yet
}

void Managers::SceneManager::notifyReshape(int width, int height, int prevWidth, int prevHeight)
{
	float ar = (float)glutGet(GLUT_WINDOW_WIDTH) / (float)glutGet(GLUT_WINDOW_HEIGHT);
	float angle = 45.0f, nearClip = 0.1f, farClip = 2000.0f;

	projectionMatrix[0][0] = 1.0f / (ar*tan(angle / 2.0f));
	projectionMatrix[1][1] = 1.0f / tan(angle / 2.0f);
	projectionMatrix[2][2] = (-nearClip - farClip) / (nearClip - farClip);
	projectionMatrix[2][3] = 1.0f;
	projectionMatrix[3][2] = 2.0f * nearClip * farClip / (nearClip - farClip);
}