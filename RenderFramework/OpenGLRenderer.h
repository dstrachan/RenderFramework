#pragma once

#include "stdafx.h"

namespace RenderFramework
{
	class OpenGLRenderer
	{
	private:
		// Window used by the OpenGLRenderer
		GLFWwindow* window;
		// Window title
		std::string title;
		// Flag indicating that the OpenGLRenderer is still running
		bool running;
		// The width of the window used by the OpenGLRenderer
		unsigned int width;
		// The height of the window used by the OpenGLRenderer
		unsigned int height;
		// Singleton instance
		static OpenGLRenderer* instance;

		// Private default constructor
		OpenGLRenderer();
		// Private copy constructor
		OpenGLRenderer(const OpenGLRenderer&) { }
		// Private assignment operator
		void operator=(OpenGLRenderer&) { }
	public:
		~OpenGLRenderer();

		// Initialises the OpenGLRenderer and creates a window
		static bool initialise();
		// Renders the current scene
		static bool render();
		// Shutsdown the OpenGLRenderer
		static void shutdown();

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