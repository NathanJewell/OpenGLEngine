//VertexFormat.h
#pragma once

#include "glm\glm.hpp"

namespace Rendering
{
	struct VertexFormat
	{
	public:
		glm::vec3 position;
		glm::vec4 color;
		glm::vec3 normal;

		VertexFormat(const glm::vec3& pos)
		{
			position = pos;
		}
		VertexFormat(const glm::vec3 &pos, const glm::vec4 &iColor)
		{
			position = pos;
			color = iColor;
		}
		VertexFormat(const glm::vec3& pos, const glm::vec3 &norm)
		{
			position = pos;
			normal = norm;
		}
	};
}



