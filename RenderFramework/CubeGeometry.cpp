#include "stdafx.h"

#include "Geometry.h"

namespace RenderFramework
{
	CubeGeometry::CubeGeometry()
		: Geometry()
	{
		init();
	}

	CubeGeometry::~CubeGeometry()
	{
	}

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
		std::array<glm::vec3, 6> cube_normals = {
			glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(-1.0f, 0.0f, 0.0f),
			glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, -1.0f, 0.0f)
		};
		std::array<glm::vec2, 4> cube_texcoords = {
			glm::vec2(1.0f, 1.0f),
			glm::vec2(0.0f, 1.0f),
			glm::vec2(0.0f, 0.0f),
			glm::vec2(1.0f, 0.0f)
		};

		for (auto i = 0; i < 24; ++i)
		{
			positions.push_back(cube_positions[i]);
			normals.push_back(cube_normals[i / 4]);
		}

		// Set geometry type
		type = GL_QUADS;

		// Try to initialise geometry
		if (!initialise_geometry(this))
		{
#if defined(_DEBUG)
			std::cerr << "ERROR - Could not initialise CubeGeometry" << std::endl;
#endif
			return;
		}

#if defined(_DEBUG)
		std::clog << "LOG - CubeGeometry created" << std::endl;
#endif
	}
}