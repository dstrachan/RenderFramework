#include "stdafx.h"

#include "ContentManager.h"

namespace RenderFramework
{
	ContentManager* ContentManager::instance = new ContentManager();

	ContentManager::ContentManager()
	{
	}

	ContentManager::~ContentManager()
	{
	}

	bool ContentManager::loadShader(const std::string& name, const std::string& filename, int type)
	{
	}
}