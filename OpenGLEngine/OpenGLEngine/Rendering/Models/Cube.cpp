//Cube.cpp
#include "Cube.h"
#include <iostream>
using namespace Rendering;
using namespace Models;

#define PI 3.14159265

Cube::Cube(){}//empty
Cube::~Cube(){}//handled in base class

void Cube::Create()
{
	GLuint vao;
	GLuint vbo;

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<VertexFormat> vertices;

	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0),
		glm::vec4(0.0, 0.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0),
		glm::vec4(1.0, 0.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0)));

	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0),
		glm::vec4(0.0, 1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0),
		glm::vec4(0.0, 0.0, 1.0, 1.0)));

	//vertices for the right face of the cube
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0),
		glm::vec4(1.0, 1.0, 0.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0),
		glm::vec4(1.0, 0.0, 0.0, 1.0)));

	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0),
		glm::vec4(1.0, 0.0, 0.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0),
		glm::vec4(1.0, 0.0, 1.0, 1.0)));

	//vertices for the back face of the cube
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0),
		glm::vec4(0.0, 0.0, 0.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0),
		glm::vec4(1.0, 0.0, 0.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0),
		glm::vec4(1.0, 1.0, 0.0, 1.0)));

	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0),
		glm::vec4(0.0, 0.0, 0.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0),
		glm::vec4(1.0, 1.0, 0.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0),
		glm::vec4(0.0, 1.0, 0.0, 1.0)));

	//vertices for the left face of the cube
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0),
		glm::vec4(0.0, 0.0, 0.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0),
		glm::vec4(0.0, 0.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0),
		glm::vec4(0.0, 1.0, 1.0, 1.0)));

	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0),
		glm::vec4(0.0, 0.0, 0.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0),
		glm::vec4(0.0, 1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0),
		glm::vec4(0.0, 1.0, 0.0, 1.0)));

	//vertices for the upper face of the cube
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, 1.0),
		glm::vec4(1.0, 1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0),
		glm::vec4(0.0, 1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0),
		glm::vec4(1.0, 1.0, 0.0, 1.0)));

	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, 1.0),
		glm::vec4(0.0, 1.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, 1.0, -1.0),
		glm::vec4(1.0, 1.0, 0.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, 1.0, -1.0),
		glm::vec4(0.0, 1.0, 0.0, 1.0)));

	//vertices for the bottom face of the cube
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, -1.0),
		glm::vec4(0.0, 0.0, 0.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0),
		glm::vec4(1.0, 0.0, 0.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0),
		glm::vec4(0.0, 0.0, 1.0, 1.0)));

	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, -1.0),
		glm::vec4(1.0, 0.0, 0.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(-1.0, -1.0, 1.0),
		glm::vec4(0.0, 0.0, 1.0, 1.0)));
	vertices.push_back(VertexFormat(glm::vec3(1.0, -1.0, 1.0),
		glm::vec4(1.0, 0.0, 1.0, 1.0)));

	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glBufferData(GL_ARRAY_BUFFER, sizeof(VertexFormat) * 36, &vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)0);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, sizeof(VertexFormat), (void*)(offsetof(VertexFormat, VertexFormat::color)));
	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vbo);

	rotationSpeed = glm::vec3(90.0, 90.0, 90.0);
	rotation = glm::vec3(0.0, 0.0, 0.0);
	
}

void Cube::Update(){}//empty

void Cube::Draw(const glm::mat4& projectionMatrix,
	const glm::mat4& viewMatrix)
{
	float currentTime = (float)glutGet(GLUT_ELAPSED_TIME);

	rotation = .0005f * rotationSpeed * currentTime;
	
	glm::vec3 translation = glm::vec3(glm::abs(glm::cos(currentTime/1000)));
	translation *= 5.0f;
	//std::cout << "Translation: " << translation.x << ", " << translation.y << ", " << translation.z << std::endl;
	
	glm::vec3 rotationSin = glm::vec3(rotation.x * PI / 180, rotation.y * PI / 180, rotation.z*PI / 180);
	translationMatrix = glm::translate(translation);
	glUseProgram(program);
	glUniform3f(glGetUniformLocation(program, "rotation"), rotationSin.x, rotationSin.y, rotationSin.z);		//passing rotation vector into shader
	glUniformMatrix4fv(glGetUniformLocation(program, "translation"), 1, false, &translationMatrix[0][0]);		//pass translationVector into shader
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &viewMatrix[0][0]);				//pass viewMatrix into shader
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projectionMatrix[0][0]);	//pass projectionMatrix into shader

	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}