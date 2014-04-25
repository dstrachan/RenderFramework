#pragma once

#include "stdafx.h"

#include "Shader.h"
#include "Program.h"

namespace RenderFramework
{
	class ContentManager
	{
	private:
		// Data store for all Shaders
		std::unordered_map<std::string, std::shared_ptr<Shader>> shaders;
		// Data store for all Programs
		std::unordered_map<std::string, std::shared_ptr<Program>> programs;
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

		// Loads a shader from a file, then adds it to the ContentManager store
		static std::shared_ptr<Shader> loadShader(const std::string& name, const std::string& filename, int type);
		// Creates a Program, then adds it to the ContentManager store
		static std::shared_ptr<Program> createProgram(const std::string& name, std::vector<std::string> shaders);

		/*
		GETTERS AND SETTERS
		*/
		static std::shared_ptr<Program> getProgram(const std::string& name);
	};
}