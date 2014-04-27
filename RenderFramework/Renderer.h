#pragma once

#include "stdafx.h"

#include "Program.h"

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
		// Flag indicating that the OpenGLRenderer is still running
		bool running;
		// The width of the window used by the OpenGLRenderer
		unsigned int width;
		// The height of the window used by the OpenGLRenderer
		unsigned int height;
		// Singleton instance
		static Renderer* instance;

		// Private default constructor
		Renderer();
		// Private copy constructor
		Renderer(const Renderer&) { }
		// Private assignment operator
		void operator=(Renderer&) { }
	public:
		~Renderer();

		// Initialises the OpenGLRenderer and creates a window
		static bool initialise();
		// Begins a render
		static bool beginRender();
		// Ends a render
		static bool endRender();
		// Shutsdown the OpenGLRenderer
		static void shutdown();

		// Uses a Program
		static bool useProgram(std::shared_ptr<Program> value);

		/*
		GETTERS AND SETTERS
		*/

		// Gets the window used by the OpenGLRenderer
		static GLFWwindow* getWindow();
		// Gets the window title
		static std::string getTitle();
		// Sets the window title
		static void setTitle(const std::string& value);
		// Returns the running state of the OpenGLRenderer
		static bool isRunning();
		// Sets the running state of the OpenGLRenderer
		static void setRunning(bool value);
		// Gets the window width
		static unsigned int getWidth();
		// Gets the window height
		static unsigned int getHeight();
		// Sets the window size
		static void setSize(unsigned int width, unsigned int height);
	};
}