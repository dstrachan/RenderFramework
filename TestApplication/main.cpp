#include <RenderFramework.h>

/*

Scene* scene = new Scene();
Camera* camera = new PerspectiveCmaera(75.0f, width / height, 0.1f, 1000.0f);

Geometry* geometry = new CubeGeometry(1.0f, 1.0f, 1.0f);
Material* material = new BasicMaterial({ colour: 0x00ff00 });
Mesh* cube = new Mesh(geometry, material);
scene.add(cube);

*/
RenderFramework::CubeGeometry* cube;

void loadContent()
{
	cube = new RenderFramework::CubeGeometry();

	auto vertexShader = RenderFramework::ContentManager::loadShader(
		"basic_vert", "Shaders/basic.vert", GL_VERTEX_SHADER);
	auto fragmentShader = RenderFramework::ContentManager::loadShader(
		"basic_frag", "Shaders/basic.frag", GL_FRAGMENT_SHADER);
	auto program = RenderFramework::ContentManager::createProgram("basic", { "basic_vert", "basic_frag" });
	RenderFramework::Renderer::useProgram(program);
}

void render()
{
	RenderFramework::Renderer::render(cube);
	// RenderFramework::Renderer::render(scene, camera);
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