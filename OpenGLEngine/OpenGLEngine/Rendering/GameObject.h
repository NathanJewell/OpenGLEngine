//GameObject.h
#pragma once

#include <vector>
#include "../Dependencies/glew/glew.h"
#include "../Dependencies/freeglut/freeglut.h"
#include "VertexFormat.h"

namespace Rendering
{
	class GameObject
	{
	public:
		virtual ~GameObject() = 0;

		virtual void Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix) = 0;
		virtual void Update() = 0;
		virtual void SetProgram(GLuint shaderProgram) = 0;
		virtual void Destroy() = 0;

		virtual GLuint GetVao() const = 0;
		virtual const std::vector<GLuint>& GetVbos() const = 0;
	};

	inline GameObject::~GameObject()
	{
		//nada
	}
}