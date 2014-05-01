#include "stdafx.h"

#include "Shader.h"

namespace RenderFramework
{
	Shader::Shader()
		: id(0), type(GL_VERTEX_SHADER)
	{
	}

	Shader::~Shader()
	{
		if (id)
		{
			glDeleteShader(id);
			id = 0;
		}
	}
}