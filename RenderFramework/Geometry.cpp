#include "stdafx.h"

#include "Geometry.h"

namespace RenderFramework
{
	bool Geometry::initialise_geometry(Geometry* geometry)
	{
		// Check if nullptr
		if (geometry == nullptr)
		{
#if defined(_DEBUG)
			std::cerr << "ERROR - Geometry is nullptr" << std::endl;
#endif
			return false;
		}

		// Generate a new vertex array object
		glGenVertexArrays(1, &geometry->vao);
		// Bind the vertex array object
		glBindVertexArray(geometry->vao);
		
		// If we have position data then create buffer
		if (geometry->positions.size() > 0)
		{
			// Generate a new buffer object
			glGenBuffers(1, &geometry->pos_buffer);
			// Bind the buffer object
			glBindBuffer(GL_ARRAY_BUFFER, geometry->pos_buffer);
			// Copy vertex data to the buffer object
			glBufferData(GL_ARRAY_BUFFER, geometry->positions.size() * sizeof(glm::vec3), &geometry->positions[0], GL_STATIC_DRAW);
			// Enable attribute pointer for position data
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(0);
		}

		// If we have normal data then create buffer
		if (geometry->normals.size() > 0)
		{
			// Generate a new buffer object
			glGenBuffers(1, &geometry->norm_buffer);
			// Bind the buffer object
			glBindBuffer(GL_ARRAY_BUFFER, geometry->norm_buffer);
			// Copy normal data to the buffer object
			glBufferData(GL_ARRAY_BUFFER, geometry->normals.size() * sizeof(glm::vec3), &geometry->normals[0], GL_STATIC_DRAW);
			// Enable attribute pointer for normal data
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
			glEnableVertexAttribArray(1);
		}

		return true;
	}
}