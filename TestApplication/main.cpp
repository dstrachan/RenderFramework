#include <RenderFramework.h>

void loadContent()
{
	RenderFramework::CubeGeometry* cube = new RenderFramework::CubeGeometry();

	auto vertexShader = RenderFramework::ContentManager::loadShader(
		"basic_vert", "Shaders/basic.vert", GL_VERTEX_SHADER);
	auto fragmentShader = RenderFramework::ContentManager::loadShader(
		"basic_frag", "Shaders/basic.frag", GL_FRAGMENT_SHADER);
	auto program = RenderFramework::ContentManager::createProgram("basic", { "basic_vert", "basic_frag" });
	RenderFramework::Renderer::useProgram(program);
}

void render()
{
	glDrawArrays(GL_QUADS, 0, 24);
}

int main()
{
	if (!RenderFramework::Renderer::initialise())
		exit(EXIT_FAILURE);
	RenderFramework::Renderer::setTitle("Test Application");

	loadContent();

	while (RenderFramework::Renderer::isRunning())
	{
		RenderFramework::Renderer::beginRender();

		render();

		RenderFramework::Renderer::endRender();
	}

	RenderFramework::Renderer::shutdown();

	exit(EXIT_SUCCESS);
}