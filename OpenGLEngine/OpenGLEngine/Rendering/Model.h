//Model.h
#pragma once

#include <vector>
#include "GameObject.h"

namespace Rendering
{
	namespace Models
	{
		class Model : public GameObject
		{
		public:
			Model();
			virtual ~Model();

			//must implement virtual methods
			virtual void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) override;
			virtual void Update() override;
			virtual void SetProgram(GLuint shaderProgram) override;
			virtual void Destroy() override;

			virtual GLuint GetVao() const override;
			virtual const std::vector<GLuint>& GetVbos() const override;

		protected:
			GLuint vao;
			GLuint program;
			std::vector<GLuint> vbos;
			glm::mat4 translationMatrix;
		};
	}
}