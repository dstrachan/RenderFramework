#pragma once

#include "stdafx.h"

namespace RenderFramework
{
	struct Uniform
	{
		// Uniform location
		GLint location;
		//Uniform type
		GLenum type;
		// Uniform size
		GLint size;

		Uniform();
		Uniform(GLint location, GLenum type, GLint size);
		~Uniform();
	};
}