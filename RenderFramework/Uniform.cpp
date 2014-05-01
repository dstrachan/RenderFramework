#include "stdafx.h"

#include "Uniform.h"

namespace RenderFramework
{
	Uniform::Uniform()
		: Uniform(0, GL_FLOAT, 1)
	{
	}

	Uniform::Uniform(GLint location, GLenum type, GLint size)
		: location(location), type(type), size(size)
	{
	}

	Uniform::~Uniform()
	{
	}
}