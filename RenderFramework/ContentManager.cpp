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

	template <>
	std::shared_ptr<Shader> ContentManager::get(const char* name)
	{
		auto found = instance->shaderMap.find(name);
		if (found != instance->shaderMap.end())
			return found->second;
#if defined(_DEBUG)
		std::cerr << "ERROR - Shader " << name << " not found" << std::endl;
#endif
		return nullptr;
	}

	template <>
	std::shared_ptr<Program> ContentManager::get(const char* name)
	{
		auto found = instance->programMap.find(name);
		if (found != instance->programMap.end())
			return found->second;
#if defined(_DEBUG)
		std::cerr << "ERROR - Program " << name << " not found" << std::endl;
#endif
		return nullptr;
	}

	template <>
	std::shared_ptr<Geometry> ContentManager::get(const char* name)
	{
		auto found = instance->geometryMap.find(name);
		if (found != instance->geometryMap.end())
			return found->second;
#if defined(_DEBUG)
		std::cerr << "ERROR - Geometry " << name << " not found" << std::endl;
#endif
		return nullptr;
	}

	template <>
	std::shared_ptr<Material> ContentManager::get(const char* name)
	{
		auto found = instance->materialMap.find(name);
		if (found != instance->materialMap.end())
			return found->second;
#if defined(_DEBUG)
		std::cerr << "ERROR - Material " << name << " not found" << std::endl;
#endif
		return nullptr;
	}

	template <>
	std::shared_ptr<Mesh> ContentManager::get(const char* name)
	{
		auto found = instance->meshMap.find(name);
		if (found != instance->meshMap.end())
			return found->second;
#if defined(_DEBUG)
		std::cerr << "ERROR - Mesh " << name << " not found" << std::endl;
#endif
		return nullptr;
	}

	template <>
	std::shared_ptr<Scene> ContentManager::get(const char* name)
	{
		auto found = instance->sceneMap.find(name);
		if (found != instance->sceneMap.end())
			return found->second;
#if defined(_DEBUG)
		std::cerr << "ERROR - Scene " << name << " not found" << std::endl;
#endif
		return nullptr;
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

	template <>
	std::shared_ptr<Shader> ContentManager::load(const char* name, const char* filename, int type)
	{
		// Check if Shader exists
		if (instance->shaderMap.find(name) != instance->shaderMap.end())
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
			std::cerr << "[ERROR]: ContentManager::loadShader - Could not read file " << filename << std::endl;
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
			std::cerr << "[ERROR]: ContentManager::loadShader - Could not compile Shader " << filename << std::endl;
			std::cerr << &log[0] << std::endl;
#endif
			glDeleteShader(value->id);
			return nullptr;
		}

		instance->shaderMap[name] = value;
#if defined(_DEBUG)
		std::clog << "LOG - Shader " << name << " loaded" << std::endl;
#endif
		return value;
	}

	template <>
	std::shared_ptr<Program> ContentManager::create(const char* name, std::vector<std::string> shaders)
	{
		// Check if Program exists
		if (instance->programMap.find(name) != instance->programMap.end())
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
			auto found = instance->shaderMap.find(name);
			if (found == instance->shaderMap.end())
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

		// Get Uniforms
		GLint uniforms;
		glGetProgramiv(value->id, GL_ACTIVE_UNIFORMS, &uniforms);
		GLint length;
		glGetProgramiv(value->id, GL_ACTIVE_UNIFORM_MAX_LENGTH, &length);
		std::vector<char> buffer(length);

		// Iterate Uniforms and add to Program object
		GLenum type;
		GLsizei name_length;
		GLint size;
		for (auto i = 0; i < uniforms; ++i)
		{
			glGetActiveUniform(value->id, i, length, &name_length, &size, &type, &buffer[0]);
			std::string name(&buffer[0]);
			auto uniform_location = glGetUniformLocation(value->id, name.c_str());
			if (uniform_location != -1)
				value->uniforms[name] = Uniform(uniform_location, type, size);
		}

		instance->programMap[name] = value;
		return value;
	}

	template <>
	std::shared_ptr<CubeGeometry> ContentManager::create(const char* name)
	{
		auto geometry = std::make_shared<CubeGeometry>();
		instance->geometryMap[name] = geometry;
		return geometry;
	}

	template <>
	std::shared_ptr<Material> ContentManager::create(const char* name,
		const char* program, std::map<std::string, glm::vec4> parameters)
	{
		auto material = std::make_shared<Material>();
		material->program = get<Program>(program);
		material->diffuse = parameters.at("diffuse");
		instance->materialMap[name] = material;
		return material;
	}

	template <>
	std::shared_ptr<Mesh> ContentManager::create(const char* name, const char* geometry, const char* material)
	{
		auto mesh = std::make_shared<Mesh>();
		mesh->geometry = get<Geometry>(geometry);
		mesh->material = get<Material>(material);
		instance->meshMap[name] = mesh;
		return mesh;
	}

	template <>
	std::shared_ptr<Scene> ContentManager::create(const char* name, std::vector<std::string> meshes)
	{
		auto scene = std::make_shared<Scene>();
		for (auto& m : meshes)
		{
			scene->meshes.push_back(get<Mesh>(m.c_str()));
		}
		instance->sceneMap[name] = scene;
		return scene;
	}
}