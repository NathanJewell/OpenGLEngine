//ModelManager.h
#pragma once

#include <map>
#include "ShaderManager.h"
#include "../Rendering/GameObject.h"
#include "../Rendering/Models/Triangle.h"
#include "../Rendering/Models/Cube.h"
#include "../Rendering/Models/LoadedModel.h"

namespace Managers
{
	class ModelManager
	{
	public:
		ModelManager();
		~ModelManager();

		void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
		void Update();
		void DeleteModel(const std::string& modelName);
		const Rendering::GameObject& getModel(const std::string& modelName) const;

	private:
		std::map<std::string, Rendering::GameObject*> gameModelList;
	};
}