#pragma once

#include "stdafx.h"

#include "Shader.h"
#include "Program.h"
#include "Geometry.h"
#include "Material.h"
#include "Mesh.h"
#include "Scene.h"

namespace RenderFramework
{
	class ContentManager
	{
	private:
		// Data store for all Shaders
		std::unordered_map<std::string, std::shared_ptr<Shader>> shaderMap;
		// Data store for all Programs
		std::unordered_map<std::string, std::shared_ptr<Program>> programMap;
		// Data store for all Geometry
		std::unordered_map<std::string, std::shared_ptr<Geometry>> geometryMap;
		// Data store for all Materials
		std::unordered_map<std::string, std::shared_ptr<Material>> materialMap;
		// Data store for all Meshes
		std::unordered_map<std::string, std::shared_ptr<Mesh>> meshMap;
		// Data store for all Scenes
		std::unordered_map<std::string, std::shared_ptr<Scene>> sceneMap;
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

		// Gets content from the ContentManager store
		template <typename T>
		static std::shared_ptr<T> get(const char* name);

		// Loads content from a file, then adds it to the ContentManager store
		template <typename T, typename... Arguments>
		static std::shared_ptr<T> load(const char* name, Arguments... parameters);

		// Creates content from existing content, then adds it to the ContentManager store
		template <typename T, typename... Arguments>
		static std::shared_ptr<T> create(const char* name, Arguments... parameters);
	};

	// Get
	extern template std::shared_ptr<Shader> ContentManager::get(const char* name);
	extern template std::shared_ptr<Program> ContentManager::get(const char* name);
	extern template std::shared_ptr<Geometry> ContentManager::get(const char* name);
	extern template std::shared_ptr<Material> ContentManager::get(const char* name);
	extern template std::shared_ptr<Mesh> ContentManager::get(const char* name);
	extern template std::shared_ptr<Scene> ContentManager::get(const char* name);

	// Load
	extern template std::shared_ptr<Shader> ContentManager::load(const char* name,
		const char* filename, int type);

	// Create
	extern template std::shared_ptr<Program> ContentManager::create(const char* name,
		std::vector<std::string> shaders);
	extern template std::shared_ptr<CubeGeometry> ContentManager::create(const char* name);
	extern template std::shared_ptr<Material> ContentManager::create(const char* name,
		const char* program, std::map<std::string, glm::vec4> parameters);
	extern template std::shared_ptr<Mesh> ContentManager::create(const char* name,
		const char* geometry, const char* material, std::map<std::string, glm::vec3> parameters);
	extern template std::shared_ptr<Scene> ContentManager::create(const char* name,
		std::vector<std::string> meshes);

	// Error handling
	template <typename T>
	std::shared_ptr<T> ContentManager::get(const char* name)
	{
		std::cerr << "Error trying to get object from content manager of unknown type" << std::endl;
		std::cerr << "Type of: " << typeid(T).name() << std::endl;
		return nullptr;
	}

	template <typename T, typename... Arguments>
	std::shared_ptr<T> ContentManager::load(const char* name, Arguments... parameters)
	{
		check(parameters...);
		std::cerr << "Error trying to load object of unknown type or with incorrect parameters"
			<< std::endl;
		std::cerr << "Type of: " << typeid(T).name() << std::endl;
		return nullptr;
	}

	template <typename... Arguments>
	void check(Arguments... args);

	template <typename T>
	void check(T arg)
	{
		std::cerr << "Type : " << typeid(T).name() << std::endl;
	}

	template <typename T, typename... Arguments>
	void check(T val, Arguments... args)
	{
		std::cerr << "Type : " << typeid(T).name() << std::endl;
		check(args...);
	}

	template <typename T, typename... Arguments>
	std::shared_ptr<T> ContentManager::create(const char* name, Arguments... parameters)
	{
		check(parameters...);
		std::cerr << "Error trying to create object of unknown type or with incorrect parameters"
			<< std::endl;
		std::cerr << "Type of: " << typeid(T).name() << std::endl;
		return nullptr;
	}
}