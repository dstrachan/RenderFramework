#include "stdafx.h"

#include "Geometry.h"

namespace RenderFramework
{
	void CubeGeometry::init()
	{
		std::array<glm::vec3, 24> cube_positions = {
			// Front
			glm::vec3(0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, 0.5f),
			glm::vec3(-0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, 0.5f),

			// Right side
			glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, 0.5f),
			glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(0.5f, -0.5f, -0.5f),

			// Back
			glm::vec3(-0.5f, 0.5f, -0.5f), glm::vec3(0.5f, 0.5f, -0.5f),
			glm::vec3(0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, -0.5f),

			// Left side
			glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),
			glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(-0.5f, -0.5f, 0.5f),

			// Top
			glm::vec3(-0.5f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f),
			glm::vec3(0.5f, 0.5f, -0.5f), glm::vec3(-0.5f, 0.5f, -0.5f),

			// Bottom
			glm::vec3(0.5f, -0.5f, 0.5f), glm::vec3(-0.5f, -0.5f, 0.5f),
			glm::vec3(-0.5f, -0.5f, -0.5f), glm::vec3(0.5f, -0.5f, -0.5f)
		};

		for (auto& v : cube_positions)
			positions.push_back(v);

		// Generate a new buffer object
		glGenBuffers(1, &vbo);
		// Bind the buffer object
		glBindBuffer(GL_ARRAY_BUFFER, vbo);
		// Copy vertex data to the buffer object
		glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(glm::vec3), &positions[0], GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(0);
	}
}