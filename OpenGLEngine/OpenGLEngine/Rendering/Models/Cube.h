//Cube.h
#pragma once

#include "../Model.h"
#include <time.h>
#include <stdarg.h>
#include "glm/gtx/transform.hpp"

namespace Rendering
{
	namespace Models
	{
		class Cube : public Model
		{
		public:
			Cube();
			~Cube();

			void Create();
			virtual void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix);
			virtual void Update();

		private:
			glm::vec3 rotation, rotationSpeed;
			const glm::mat4 translation;
		};
	}
}