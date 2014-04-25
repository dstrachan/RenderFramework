#pragma once

#include "stdafx.h"

namespace RenderFramework
{
	class ContentManager
	{
	private:
		// Singleton instance
		static ContentManager* instance;

		// Private default constructor
		ContentManager();
		// Private copy constructor
		ContentManager(const ContentManager&) { }
		// Private assignment operator
		void operator=(ContentManager&) { }
	public:
		~ContentManager();

		static bool loadShader(const std::string& name, const std::string& filename, int type);
	};
}