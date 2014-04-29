#pragma once

#include "stdafx.h"

namespace RenderFramework
{
	class Geometry
	{
	protected:
		// Vertex buffer object ID
		GLuint vbo;
		
		// Vector containing position data
		std::vector<glm::vec3> positions;

		Geometry()
			: vbo(0)
		{
		}
		~Geometry()
		{
			if (vbo)
				glDeleteBuffers(1, &vbo);
		}
	public:
		virtual void init() = 0;
	};

	class CubeGeometry : Geometry
	{
	public:
		CubeGeometry()
			: Geometry()
		{
			init();
		}
		virtual void init();
	};
}