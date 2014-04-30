#pragma once

#include "stdafx.h"

namespace RenderFramework
{
	class Geometry
	{
	protected:
		// Geometry type
		GLenum type;
		// Vertex array object ID
		GLuint vao;
		// Position data buffer ID
		GLuint pos_buffer;
		// Normal data buffer ID
		GLuint norm_buffer;

		Geometry()
			: type(GL_TRIANGLES), vao(0), pos_buffer(0), norm_buffer(0)
		{
		}
		~Geometry()
		{
			if (pos_buffer)
				glDeleteBuffers(1, &pos_buffer);
			if (norm_buffer)
				glDeleteBuffers(1, &norm_buffer);
			if (vao)
				glDeleteVertexArrays(1, &vao);
		}

		static bool initialise_geometry(Geometry* geometry);
		virtual void init() = 0;
	public:
		// Vector containing position data
		std::vector<glm::vec3> positions;
		// Vector containing normal data
		std::vector<glm::vec3> normals;

		GLenum getType() { return type; }
		GLsizei getCount() { return positions.size(); }
		GLuint getVAO() { return vao; }
	};

	class CubeGeometry : public Geometry
	{
	private:
		void init();
	public:
		CubeGeometry()
			: Geometry()
		{
			init();
		}
	};
}