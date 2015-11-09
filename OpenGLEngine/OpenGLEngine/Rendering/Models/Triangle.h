//Triangle.h
#pragma once

#include "../Model.h"

namespace Rendering
{
	namespace Models
	{
		class Triangle : public Model
		{
		public:
			Triangle();
			~Triangle();

			void Create();
			virtual void Update() override final;
			virtual void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatri) override final;
		};
	}
}