#pragma once

#include <glm/glm.hpp>

class Lightable
{
public:
	Lightable();
	~Lightable();

private:
	glm::vec3 diffuseColor;
	glm::vec3 ambientColor;
};

