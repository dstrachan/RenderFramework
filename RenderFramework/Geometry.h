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

		Geometry();
		~Geometry();

		static bool initialise_geometry(Geometry* geometry);
		virtual void init() = 0;
	public:
		// Vector containing position data
		std::vector<glm::vec3> positions;
		// Vector containing normal data
		std::vector<glm::vec3> normals;

		GLsizei getCount() const;
		GLenum getType() const;
		GLuint getVAO() const;
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