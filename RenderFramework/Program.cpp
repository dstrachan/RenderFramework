#include "stdafx.h"

#include "Program.h"

namespace RenderFramework
{
	Program::Program()
		: id(0)
	{
	}

	Program::~Program()
	{
		if (id)
		{
			for (auto& s : shaders)
				glDetachShader(id, s->id);
			glDeleteShader(id);
			id = 0;
		}
	}
}