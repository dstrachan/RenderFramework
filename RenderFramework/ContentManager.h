#pragma once

#include "stdafx.h"

#include "Shader.h"
#include "Program.h"
#include "Geometry.h"
#include "Material.h"
#include "Mesh.h"

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

		template <typename T>
		static std::shared_ptr<T> create(const std::string& name);
		template <typename T>
		static std::shared_ptr<T> create(const std::string& name, const std::string& parameter1);
		template <typename T>
		static std::shared_ptr<T> create(const std::string& name, const std::string& parameter1, const std::string& parameter2);

		static void get(std::shared_ptr<Shader>& ptr, const std::string& name);
		static void get(std::shared_ptr<Program>& ptr, const std::string& name);
		static void get(std::shared_ptr<Geometry>& ptr, const std::string& name);
		static void get(std::shared_ptr<Material>& ptr, const std::string& name);
		static void get(std::shared_ptr<Mesh>& ptr, const std::string& name);
	};
}