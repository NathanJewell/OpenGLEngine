//Model.h
#include "Model.h"

using namespace Rendering;
using namespace Models;

Model::Model(){}

Model::~Model()
{
	Destroy();
}

void Model::Draw(const glm::mat4& projectionMatrix, const glm::mat4& viewMatrix)
{
	//overridden
}

void Model::Update()
{
	//overridden
}

void Model::SetProgram(GLuint shaderProgram)
{
	program = shaderProgram;
}

GLuint Model::GetVao() const
{
	return vao;
}

const std::vector<GLuint>& Model::GetVbos() const
{
	return vbos;
}

void Model::Destroy()
{
	glDeleteVertexArrays(1, &vao);
	glDeleteBuffers(vbos.size(), &vbos[0]);
	vbos.clear();
}