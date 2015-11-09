//LoadedModel.cpp
#include "LoadedModel.h"
#include <iostream>

using namespace Rendering;
using namespace Models;

inline static void Log(LogLevel level, const std::string& text) //alias for Managers::LogManager::Log()
{
	Managers::LogManager::Log(level, text);
}

#define PI 3.14159265

LoadedModel::LoadedModel(){}//empty
LoadedModel::~LoadedModel(){}//handled in base class

void LoadedModel::Create(const std::string loadPath)
{
	GLuint vao;
	GLuint vertexBuffer;
	GLuint colorBuffer;
	GLuint normalBuffer;
	GLuint uvBuffer;


	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	std::vector<glm::vec3> vertices;
	std::vector<glm::vec3> normals;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> colors;
	loadOBJ(loadPath, vertices, uvs, normals);
	colors = vertices;

	//VERTEX BUFFER
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//COLOR BUFFER
	glGenBuffers(1, &colorBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*colors.size(), &colors[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

	//NORMAL BUFFER
	glGenBuffers(1, &normalBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size()*sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);


	glBindVertexArray(0);
	this->vao = vao;
	this->vbos.push_back(vertexBuffer);
	this->vbos.push_back(colorBuffer);

	rotationSpeed = glm::vec3(90.0, 90.0, 90.0);
	rotation = glm::vec3(0.0, 0.0, 0.0);

	
}

void LoadedModel::Update(){}//empty

void LoadedModel::Draw(const glm::mat4& projectionMatrix,
	const glm::mat4& viewMatrix)
{
	float currentTime = (float)glutGet(GLUT_ELAPSED_TIME);

	rotation = glm::vec3(0.0, 1.0, 0.0);
	rotation *= .00001f * rotationSpeed * currentTime;

	//glm::vec3 translation = glm::vec3(glm::abs(glm::cos(currentTime / 1000)));
	glm::vec3 translation = glm::vec3(0.0, 0.0, 0.0);
	//translation *= 0.0f;
	//std::cout << "Translation: " << translation.x << ", " << translation.y << ", " << translation.z << std::endl;

	translationMatrix = glm::translate(translation);

	glm::mat4 translate = glm::mat4(1.0, 0.0, 0.0, translation.x, //con
		0.0, 1.0, 0.0, translation.y,
		0.0, 0.0, 1.0, translation.z,
		0.0, 0.0, 0.0, 1.0);

	glm::mat4 rotate_x = glm::mat4(1.0, 0.0, 0.0, 0.0,
		0.0, glm::cos(rotation.x), glm::sin(rotation.x), 0.0,
		0.0, -glm::sin(rotation.x), glm::cos(rotation.x), 0.0,
		0.0, 0.0, 0.0, 1.0);

	glm::mat4 rotate_y = glm::mat4(glm::cos(rotation.y), 0.0, -glm::sin(rotation.y), 0.0,
		0.0, 1.0, 0.0, 0.0,
		glm::sin(rotation.y), 0.0, glm::cos(rotation.y), 0.0,
		0.0, 0.0, 0.0, 1.0);

	glm::mat4 rotate_z = glm::mat4(glm::cos(rotation.z), -glm::sin(rotation.z), 0.0, 0.0,
		glm::sin(rotation.z), glm::cos(rotation.z), 0.0, 0.0,
		0.0, 0.0, 1.0, 0.0,
		0.0, 0.0, 0.0, 1.0);


	glm::mat4 rotate = rotate_x * rotate_z * rotate_y; //can add scaling here
	glm::mat4 model = translate * rotate;
	glm::mat4 MVP = projectionMatrix * viewMatrix * model;

	glm::vec4 lightColor = glm::vec4(1.0, 1.0, 1.0, 1.0);
	glm::vec4 ambientColor = glm::vec4(0.0, 0.0, 0.0, 0.0);
	glm::vec4 diffuseColor = glm::vec4(0.0, 0.0, 1.0, 1.0);
	glm::vec3 lightPosition_worldspace = glm::vec3(5.0f, 0.0, 0.0);
	float lightPower = 60; //power in watts

	//std::cout << translation.x << ", " << translation.y << ", " << translation.z << "\n";

	glUseProgram(program);


	//passing transformation parameters for vertex shader
	glUniformMatrix4fv(glGetUniformLocation(program, "rotation_matrix"), 1, false, &rotate[0][0]);		//pass uniform rotation matrix into shader
	glUniformMatrix4fv(glGetUniformLocation(program, "model_matrix"), 1, false, &translate[0][0]);		//pass translationVector into shader
	glUniformMatrix4fv(glGetUniformLocation(program, "view_matrix"), 1, false, &viewMatrix[0][0]);				//pass viewMatrix into shader
	glUniformMatrix4fv(glGetUniformLocation(program, "projection_matrix"), 1, false, &projectionMatrix[0][0]);	//pass projectionMatrix into shader
	glUniformMatrix4fv(glGetUniformLocation(program, "MVP"), 1, false, &MVP[0][0]);								//pass precalculated matrix into shader

	//passing lighting parameters for fragment shader
	glUniform4f(glGetUniformLocation(program, "lightColor"), lightColor.r, lightColor.g, lightColor.b, lightColor.a);
	glUniform4f(glGetUniformLocation(program, "ambientColor"), ambientColor.r, ambientColor.g, ambientColor.b, ambientColor.a);
	glUniform4f(glGetUniformLocation(program, "diffuseColor"), diffuseColor.r, diffuseColor.g, diffuseColor.b, diffuseColor.a);
	glUniform3f(glGetUniformLocation(program, "lightPosition_worldspace"), lightPosition_worldspace.x, lightPosition_worldspace.y, lightPosition_worldspace.z);
	glUniform1f(glGetUniformLocation(program, "lightPower"), lightPower);
	glBindVertexArray(vao);

	GLint numVertices;
	glGetIntegerv(GL_MAX_ELEMENTS_VERTICES, &numVertices);
	glDrawArrays(GL_TRIANGLES, 0, numVertices);//12*3 for 12 triangle = 2 tri per face and six faces
}

bool LoadedModel::loadOBJ(const std::string& path, std::vector<glm::vec3>& outVerts, std::vector<glm::vec2>& outUV, std::vector<glm::vec3>& outNormals)
{
	//create temporary variables
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> tempVertices;
	std::vector<glm::vec2> tempUVs;
	std::vector<glm::vec3> tempNormals;
	
	int UVS = false;
	int NORMALS = false;
	int VERTICES = false;

	//START READING DATA
	//FILE* file;
	FILE* file = fopen(path.c_str(), "r");//open file to read
	if (file == NULL) //error if file was not opened
	{
		Log(LOG_ERROR, "In LoadedModel\n\t loadOBJ():\t Could not open .OBJ file.");
		//printf("LoadedModel ERROR:\n\tin loadOBJ():\tCould not open .OBJ file.\n");
		return false;
	}
	std::cout << "Loading .OBJ file \"" << path.c_str() << "\".: \n";
	while (true){
		char lineHeader[128];

		//read first word of line
		
		int res = fscanf(file, "%s ", lineHeader);
		if (res == EOF) //EOF mean end of file -- exit while loop at EOF
			break;
		if (strcmp(lineHeader, "spec") == 0)
		{
			fscanf(file, "%d %d %d\n", &VERTICES, &NORMALS, &UVS);
		//	Log(LOG_INFO,
		//		"\t Loading vertices?: "+ VERTICES	+ "\n" +
		//		"\tLoading normals?: "	+ NORMALS	+ "\n" +
		//		"\tLoading UVs?: "		+ UVS		+ "\n");

			std::cout << "\tLoading vertices?: \t" << VERTICES << "\n";
			std::cout << "\tLoading normals?: \t" << NORMALS << "\n";
			std::cout << "\tLoading UVs?:     \t" << UVS << "\n";
		}
		else if (strcmp(lineHeader, "v") == 0 && VERTICES) //if the first character of the line is a v
		{
			glm::vec3 vertex;
			fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			tempVertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0 && UVS)
		{
			glm::vec2 uv;
			fscanf(file, "%f %f\n", &uv.x, &uv.y);
			tempUVs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0 && NORMALS)
		{
			glm::vec3 normal;
			fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			tempNormals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0 && NORMALS && VERTICES && !UVS)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

			int matches = fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
			
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);

		}
		else if (strcmp(lineHeader, "f") == 0 && NORMALS && VERTICES && UVS)
		{
			std::string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			std::cout << matches << std::endl;

			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
		
	}
	//END DATA READING SECTION

	//BEGIN DATA PROCESSING SECTION
	for (unsigned int i = 0; i < vertexIndices.size(); i++)//iterate through all vertex indices
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = tempVertices[vertexIndex - 1];	//must subtract 1 b/c object indexing starts at 1
		outVerts.push_back(vertex);
	}

	//repeat same verticeIndice iteration process for uv and normal
	if (UVS)
	{
		for (unsigned int i = 0; i < uvIndices.size(); i++)
		{
			unsigned int uvIndex = uvIndices[i];
			glm::vec2 uv = tempUVs[uvIndex - 1];
			outUV.push_back(uv);
		}
	}
	if (NORMALS)
	{
		for (unsigned int i = 0; i < normalIndices.size(); i++)
		{
			unsigned int normalIndex = normalIndices[i];
			glm::vec3 normal = tempNormals[normalIndex - 1];
			outNormals.push_back(normal);
		}
	}
	return true;
}
