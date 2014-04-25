#include <RenderFramework.h>

float vertices[] =
{
	0.0f, 0.5f,
	0.5f, -0.5f,
	-0.5f, -0.5f
};

void loadContent()
{
	GLuint vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	auto vertexShader = RenderFramework::ContentManager::loadShader(
		"basic_vert", "Shaders/basic.vert", GL_VERTEX_SHADER);
	auto fragmentShader = RenderFramework::ContentManager::loadShader(
		"basic_frag", "Shaders/basic.frag", GL_FRAGMENT_SHADER);
	auto program = RenderFramework::ContentManager::createProgram("basic", { "basic_vert", "basic_frag" });
	RenderFramework::OpenGLRenderer::useProgram(program);

	/*GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);*/

	GLint posAttrib = glGetAttribLocation(program->id, "position");
	glVertexAttribPointer(posAttrib, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(posAttrib);

	GLint uniColour = glGetUniformLocation(program->id, "triangle_colour");
	glUniform3f(uniColour, 1.0f, 0.0f, 0.0f);
}

void render()
{
	glDrawArrays(GL_TRIANGLES, 0, 3);
}

int main()
{
	if (!RenderFramework::OpenGLRenderer::initialise())
		exit(EXIT_FAILURE);
	RenderFramework::OpenGLRenderer::setSize(800, 600);

	loadContent();

	while (RenderFramework::OpenGLRenderer::isRunning())
	{
		RenderFramework::OpenGLRenderer::beginRender();

		render();

		RenderFramework::OpenGLRenderer::endRender();
	}

	RenderFramework::OpenGLRenderer::shutdown();

	exit(EXIT_SUCCESS);
}