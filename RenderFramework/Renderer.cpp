#include "stdafx.h"

#include "Renderer.h"

namespace RenderFramework
{
	Renderer* Renderer::instance = new Renderer();

	Renderer::Renderer()
		: title("Render Framework"), width(640), height(480)
	{
	}

	Renderer::~Renderer()
	{
		shutdown();
	}

	bool Renderer::initialise()
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
		glewExperimental = GL_TRUE;
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

	bool Renderer::beginRender()
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

		return true;
	}

	bool Renderer::endRender()
	{
		if (!instance->running)
		{
#if defined(_DEBUG)
			std::cerr << "ERROR - OpenGLRenderer is not running" << std::endl;
#endif
			return false;
		}

		glfwSwapBuffers(instance->window);

		glfwPollEvents();

		return true;
	}

	void Renderer::setMVP(const glm::mat4& model, const glm::mat4& view,
		const glm::mat4& projection, const glm::mat3& normal)
	{
		// Set the model matrix
		auto found = instance->program->uniforms.find("M");
		if (found != instance->program->uniforms.end())
			glUniformMatrix4fv(found->second.location, 1, GL_FALSE, glm::value_ptr(model));
		// Set the view matrix
		found = instance->program->uniforms.find("V");
		if (found != instance->program->uniforms.end())
			glUniformMatrix4fv(found->second.location, 1, GL_FALSE, glm::value_ptr(view));
		// Set the projection matrix
		found = instance->program->uniforms.find("P");
		if (found != instance->program->uniforms.end())
			glUniformMatrix4fv(found->second.location, 1, GL_FALSE, glm::value_ptr(projection));
		// Set the normal matrix
		found = instance->program->uniforms.find("N");
		if (found != instance->program->uniforms.end())
			glUniformMatrix3fv(found->second.location, 1, GL_FALSE, glm::value_ptr(normal));
	}

	bool Renderer::render(CubeGeometry* geometry, const glm::mat4& model,
		const glm::mat4& view, const glm::mat4& projection)
	{
		// Check if nullptr
		if (geometry == nullptr)
		{
#if defined(_DEBUG)
			std::cerr << "ERROR - Cannot render nullptr" << std::endl;
#endif
			return false;
		}

		// Check if running
		if (!instance->running)
		{
#if defined(_DEBUG)
			std::cerr << "ERROR - Renderer is not running" << std::endl;
#endif
			return false;
		}

		// Check if Program is bound
		if (instance->program == nullptr)
		{
#if defined(_DEBUG)
			std::cerr << "ERROR - No program bound" << std::endl;
#endif
			return false;
		}

		// Set MVP values
		auto normal = glm::mat3(glm::inverse(glm::transpose(model)));
		instance->setMVP(model, view, projection, normal);

		// Render Geometry
		glBindVertexArray(geometry->getVAO());
		glDrawArrays(geometry->getType(), 0, geometry->getCount());

		return true;
	}

	void Renderer::shutdown()
	{
		glfwTerminate();
	}

	bool Renderer::useProgram(std::shared_ptr<Program> value)
	{
		// Check for valid Program
		if (value == nullptr)
		{
#if defined(_DEBUG)
			std::cerr << "ERROR - Trying to use invalid Program" << std::endl;
#endif
			return false;
		}
		instance->program = value;
		glUseProgram(value->id);
		// TODO: CHECK_GL_ERROR
		return true;
	}

	/*
	GETTERS AND SETTERS
	*/

	GLFWwindow* Renderer::getWindow()
	{
		return instance->window;
	}

	std::string Renderer::getTitle()
	{
		return instance->title;
	}

	void Renderer::setTitle(const std::string& value)
	{
		instance->title = value;
		glfwSetWindowTitle(instance->window, instance->title.c_str());
	}

	bool Renderer::isRunning()
	{
		return instance->running;
	}

	void Renderer::setRunning(bool value)
	{
		instance->running = value;
	}

	unsigned int Renderer::getWidth()
	{
		return instance->width;
	}

	unsigned int Renderer::getHeight()
	{
		return instance->height;
	}

	void Renderer::setSize(unsigned int width, unsigned int height)
	{
		instance->width = width;
		instance->height = height;
		glfwSetWindowSize(instance->window, instance->width, instance->height);
	}
}