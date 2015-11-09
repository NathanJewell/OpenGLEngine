//SceneManager.h
#pragma once

#include "ShaderManager.h"
#include "../Core/Listener.h"
#include "ModelManager.h"
#include "glm\gtc\matrix_transform.hpp"
namespace Managers
{
	class SceneManager : public Core::Listener
	{
	public:
		SceneManager();
		~SceneManager();

		virtual void notifyBeginFrame();
		virtual void notifyDisplayFrame();
		virtual void notifyEndFrame();
		virtual void notifyReshape(int width, int height, int prevWidth, int prevHeight);

	private:
		Managers::ShaderManager* shaderManager;
		Managers::ModelManager* modelManager;
		glm::mat4 projectionMatrix, viewMatrix; //transformation matrices
	};
}