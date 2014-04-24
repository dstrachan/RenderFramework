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
		static std::shared_ptr<OpenGLRenderer> instance;

		// Private copy constructor
		OpenGLRenderer(const OpenGLRenderer&) { }
		// Private assignment operator
		void operator=(OpenGLRenderer&) { }
	public:
		OpenGLRenderer() : title("Render Framework"), width(640), height(480) { }
		~OpenGLRenderer() { glfwTerminate(); }

		// Gets the window used by the OpenGLRenderer
		static GLFWwindow* get_window() { return instance->window; }
		// Gets the window title
		static std::string getTitle() { return instance->title; }
		// Sets the window title
		static void setTitle(const std::string &value)
		{
			instance->title = value;
			glfwSetWindowTitle(instance->window, instance->title.c_str());
		}
		// Returns the running state of the OpenGLRenderer
		static bool isRunning() { return instance->running; }
		// Sets the running state of the OpenGLRenderer
		static void setRunning(bool value) { instance->running = value; }
		// Gets the window width
		static unsigned int getWidth() { return instance->width; }
		// Gets the window height
		static unsigned int getHeight() { return instance->height; }
		// Sets the window size
		static void setSize(unsigned int width, unsigned int height)
		{
			instance->width = width;
			instance->height = height;
			glfwSetWindowSize(instance->window, instance->width, instance->height);
		}

		// Initialises the OpenGLRenderer and creates a window
		static bool initialise();
		// Renders the current scene
		static bool render();
	};
}