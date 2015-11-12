//LoadedModel.h
#pragma once

#include "../Model.h"
#include <time.h>
#include <stdarg.h>
#include "glm/gtx/transform.hpp"
#include <vector>
#include "../../Managers/LogManager.h"
#include "../BMPLoader.h"

namespace Rendering
{
	namespace Models
	{
		class LoadedModel : public Model
		{
		public:
			LoadedModel();
			~LoadedModel();

			void Create(const std::string loadPath);
			void setTextureString(const std::string& texPath);
			virtual void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
			virtual void Update();

		private:
			glm::vec3 rotation, rotationSpeed;
			const glm::mat4 translation;
			GLuint textureID;
			std::string texturePath;
			bool loadOBJ(const std::string& path, std::vector<glm::vec3>& outVerts, std::vector<glm::vec2>& outUV, std::vector<glm::vec3>& outNormals);
		};
	}
}