#pragma once

#include "stdafx.h"

#include "Scene.h"
#include "Camera.h"

namespace RenderFramework
{
	class Renderer
	{
	private:
		// Window used by the Renderer
		GLFWwindow* window;
		// Window title
		std::string title;
		// Current Program
		std::shared_ptr<Program> program;
		// Flag indicating that the Renderer is still running
		bool running;
		// The width of the window used by the Renderer
		unsigned int width;
		// The height of the window used by the Renderer
		unsigned int height;
		// Singleton instance
		static Renderer* instance;

		// Private default constructor
		Renderer();
		// Private copy constructor
		Renderer(const Renderer&) { }
		// Private assignment operator
		void operator=(Renderer&) { }

		void setMVP(const glm::mat4& model, const glm::mat4& view,
			const glm::mat4& projection, const glm::mat3& normal);
	public:
		~Renderer();

		// Initialises the Renderer and creates a window
		static bool initialise();
		// Begins a render
		static bool beginRender();
		// Ends a render
		static bool endRender();
		// Shutsdown the Renderer
		static void shutdown();
		// Renders a piece of geometry
		static bool render(std::shared_ptr<Scene> scene, std::shared_ptr<Camera> camera);

		// Uses a Program
		static bool useProgram(std::shared_ptr<Program> value);

		// Gets the window used by the Renderer
		static GLFWwindow* getWindow();
		// Gets the window title
		static std::string getTitle();
		// Sets the window title
		static void setTitle(const std::string& value);
		// Returns the running state of the Renderer
		static bool isRunning();
		// Sets the running state of the Renderer
		static void setRunning(bool value);
		// Gets the window width
		static unsigned int getWidth();
		// Gets the window height
		static unsigned int getHeight();
		// Sets the window size
		static void setSize(unsigned int width, unsigned int height);
	};
}