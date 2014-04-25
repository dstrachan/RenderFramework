#include <RenderFramework.h>

int main()
{
	if (!RenderFramework::OpenGLRenderer::initialise())
		exit(EXIT_FAILURE);
	RenderFramework::OpenGLRenderer::setSize(800, 600);

	while (RenderFramework::OpenGLRenderer::isRunning())
	{
		RenderFramework::OpenGLRenderer::render();
	}

	RenderFramework::OpenGLRenderer::shutdown();

	exit(EXIT_SUCCESS);
}