#pragma once

#include "stdafx.h"

namespace RenderFramework
{
	class Uniform
	{
	public:
		GLint location;
		GLenum type;
		GLint size;
		Uniform() : location(0), type(GL_FLOAT), size(1) { }
		Uniform(GLint location, GLenum type, GLint size)
			: location(location), type(type), size(size)
		{
		}
	};
}