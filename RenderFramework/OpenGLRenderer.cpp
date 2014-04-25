#include "stdafx.h"

#include "OpenGLRenderer.h"

namespace RenderFramework
{
	OpenGLRenderer* OpenGLRenderer::instance = new OpenGLRenderer();

	OpenGLRenderer::OpenGLRenderer()
		: title("Render Framework"), width(640), height(480)
	{
	}

	OpenGLRenderer::~OpenGLRenderer()
	{
		shutdown();
	}

	bool OpenGLRenderer::initialise()
	{
		// Initialise GLFW
		if (!glfwInit())
		{
#if defined(_DEBUG)
			std::cerr << "ERROR - Could not initialise GLFW" << std::endl;
#endif
			return false;
		}

		// Get the primary monitor
		auto monitor = glfwGetPrimaryMonitor();
		// Get current video mode
		auto video_mode = glfwGetVideoMode(monitor);

		instance->window = glfwCreateWindow(instance->width, instance->height, instance->title.c_str(), nullptr, nullptr);
		if (instance->window == nullptr)
		{
#if defined(_DEBUG)
			std::cerr << "ERROR - Could not create window" << std::endl;
#endif
			glfwTerminate();
			return false;
		}

		glfwMakeContextCurrent(instance->window);
		// Prevents tearing - window refreshes with monitor
		glfwSwapInterval(1);

#if defined(_DEBUG)
		std::clog << "GL Vendor: " << glGetString(GL_VENDOR) << std::endl;
		std::clog << "GL Renderer: " << glGetString(GL_RENDERER) << std::endl;
		std::clog << "GL Version: " << glGetString(GL_VERSION) << std::endl;
		std::clog << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
#endif

		// Initialise GLEW
		auto status = glewInit();
		if (status != GLEW_OK)
		{
#if defined (_DEBUG)
			std::cerr << "ERROR - " << glewGetErrorString(status) << std::endl;
#endif
			glfwTerminate();
			return false;
		}

		instance->running = true;

		return true;
	}

	bool OpenGLRenderer::render()
	{
		if (!instance->running)
		{
#if defined(_DEBUG)
			std::cerr << "ERROR - OpenGLRenderer is not running" << std::endl;
#endif
			return false;
		}

		if (glfwGetKey(instance->window, GLFW_KEY_ESCAPE) || glfwWindowShouldClose(instance->window))
		{
#if defined(_DEBUG)
			std::clog << "LOG - Escape pressed or window closed" << std::endl;
#endif
			instance->running = false;
			return false;
		}

		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(instance->window);

		glfwPollEvents();

		return true;
	}

	void OpenGLRenderer::shutdown()
	{
		glfwTerminate();
	}

	/*
	GETTERS AND SETTERS
	*/

	GLFWwindow* OpenGLRenderer::getWindow()
	{
		return instance->window;
	}

	std::string OpenGLRenderer::getTitle()
	{
		return instance->title;
	}

	void OpenGLRenderer::setTitle(const std::string& value)
	{
		instance->title = value;
		glfwSetWindowTitle(instance->window, instance->title.c_str());
	}

	bool OpenGLRenderer::isRunning()
	{
		return instance->running;
	}

	void OpenGLRenderer::setRunning(bool value)
	{
		instance->running = value;
	}

	unsigned int OpenGLRenderer::getWidth()
	{
		return instance->width;
	}

	unsigned int OpenGLRenderer::getHeight()
	{
		return instance->height;
	}

	void OpenGLRenderer::setSize(unsigned int width, unsigned int height)
	{
		instance->width = width;
		instance->height = height;
		glfwSetWindowSize(instance->window, instance->width, instance->height);
	}
}