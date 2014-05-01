#pragma once

#include "stdafx.h"

namespace RenderFramework
{
	struct Shader
	{
		// OpenGL Shader ID
		GLuint id;
		// Shader type
		GLenum type;

		Shader();
		~Shader();
	};
}