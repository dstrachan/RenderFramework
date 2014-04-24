#include <RenderFramework.h>

int width = 0, height = 0;

int main()
{
	if (!RenderFramework::OpenGLRenderer::initialise())
		exit(EXIT_FAILURE);
	RenderFramework::OpenGLRenderer::setSize(800, 600);

	while (RenderFramework::OpenGLRenderer::isRunning())
	{
		RenderFramework::OpenGLRenderer::render();
	}

	exit(EXIT_SUCCESS);
}