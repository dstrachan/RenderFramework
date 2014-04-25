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

	bool read_file(const std::string& filename, std::string& content)
	{
		// Create filestream
		std::ifstream file(filename, std::ios_base::in);
		// Check that file exists.  If not, return false
		if (file.bad())
			return false;

		// File is good.  Read contents
		std::stringstream buffer;
		buffer << file.rdbuf();

		// Get contents from the file
		content = buffer.str();

		// Close file and return true
		file.close();
		return true;
	}

	std::shared_ptr<Shader> ContentManager::loadShader(const std::string& name, const std::string& filename, int type)
	{
		// Check if Shader exists
		if (instance->shaders.find(name) != instance->shaders.end())
		{
#if defined(_DEBUG)
			std::cerr << "[ERROR]: ContentManager::loadShader - Name already exists" << std::endl;
#endif
			return nullptr;
		}

		std::string content;
		if (!read_file(filename, content))
		{
#if defined(_DEBUG)
			std::cerr << "[ERROR]: ContentManager::loadShader - Could not read file " << filename.c_str() << std::endl;
#endif
			return nullptr;
		}

		// Create Shader
		auto value = std::make_shared<Shader>();
		value->type = type;
		value->id = glCreateShader(value->type);
		// TODO: CHECK_GL_ERROR

		auto source = content.c_str();
		glShaderSource(value->id, 1, &source, 0);
		glCompileShader(value->id);
		// TODO: CHECK_GL_ERROR

		GLint compiled;
		glGetShaderiv(value->id, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
#if defined(_DEBUG)
			GLsizei length;
			glGetShaderiv(value->id, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> log(length);
			glGetShaderInfoLog(value->id, length, &length, &log[0]);
			std::cerr << "[ERROR]: ContentManager::loadShader - Could not compile Shader " << filename.c_str() << std::endl;
			std::cerr << &log[0] << std::endl;
#endif
			glDeleteShader(value->id);
			return nullptr;
		}

		instance->shaders[name] = value;
#if defined(_DEBUG)
		std::clog << "LOG - Shader " << name.c_str() << " loaded" << std::endl;
#endif
		return value;
	}

	std::shared_ptr<Program> ContentManager::createProgram(const std::string& name, std::vector<std::string> shaders)
	{
		// Check if Program exists
		if (instance->programs.find(name) != instance->programs.end())
		{
#if defined(_DEBUG)
			std::cerr << "[ERROR]: ContentManager::createProgram - Name already exists" << std::endl;
#endif
			return nullptr;
		}

		// Create Program
		auto value = std::make_shared<Program>();

		// Iterate Shader names and add to Program object
		for (auto& name : shaders)
		{
			auto found = instance->shaders.find(name);
			if (found == instance->shaders.end())
			{
#if defined(_DEBUG)
				std::cerr << "[ERROR]: ContentManager::createProgram - Shader " << name << " does not exist" << std::endl;
#endif
				return nullptr;
			}
			else
				value->shaders.push_back(found->second);
		}

		value->id = glCreateProgram();
		// TODO: CHECK_GL_ERROR

		// Attach Shaders to program
		for (auto& s : value->shaders)
			glAttachShader(value->id, s->id);
		// TODO: CHECK_GL_ERROR

		// TODO: CHANGE
		glBindFragDataLocation(value->id, 0, "colour");

		// Link Program
		glLinkProgram(value->id);
		// TODO: CHECK_GL_ERROR

		// Get link status
		GLint linked;
		glGetProgramiv(value->id, GL_LINK_STATUS, &linked);
		if (!linked)
		{
#if defined(_DEBUG)
			GLsizei length;
			glGetProgramiv(value->id, GL_INFO_LOG_LENGTH, &length);
			std::vector<char> log(length);
			glGetProgramInfoLog(value->id, length, &length, &log[0]);
			std::cerr << "[ERROR]: ContentManager::createProgram - Problem linking program" << std::endl;
			std::cerr << &log[0] << std::endl;
#endif
			for (auto& s : value->shaders)
				glDetachShader(value->id, s->id);
			glDeleteProgram(value->id);
			return nullptr;
		}

#if defined(_DEBUG)
		std::clog << "LOG - Program " << name << " built" << std::endl;
#endif

		instance->programs[name] = value;
		return value;
	}

	/*
	GETTERS AND SETTERS
	*/

	std::shared_ptr<Program> ContentManager::getProgram(const std::string& name)
	{
		auto found = instance->programs.find(name);
		if (found != instance->programs.end())
			return found->second;
#if defined(_DEBUG)
		std::cerr << "ERROR - Program " << name << " not found" << std::endl;
#endif
		return nullptr;
	}
}