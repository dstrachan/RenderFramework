#include <RenderFramework.h>

std::shared_ptr<RenderFramework::Scene> scene;
std::shared_ptr<RenderFramework::TargetCamera> camera;

void loadContent()
{
	RenderFramework::ContentManager::loadShader("basic_vert", "Shaders/basic.vert",
		GL_VERTEX_SHADER);
	RenderFramework::ContentManager::loadShader("basic_frag", "Shaders/basic.frag",
		GL_FRAGMENT_SHADER);
	auto program = RenderFramework::ContentManager::createProgram("basic",
		{ "basic_vert", "basic_frag" });

	auto geometry = std::make_shared<RenderFramework::CubeGeometry>();

	auto material = std::make_shared<RenderFramework::Material>();
	material->setProgram(program);

	auto transform = std::make_shared<RenderFramework::Transform>();

	auto mesh = std::make_shared<RenderFramework::Mesh>();
	mesh->setGeometry(geometry);
	mesh->setMaterial(material);
	mesh->setTransform(transform);

	scene = std::make_shared<RenderFramework::Scene>();
	scene->meshes.push_back(mesh);

	camera = std::make_shared<RenderFramework::TargetCamera>();
	camera->setProjection(glm::quarter_pi<float>(),
		(float) RenderFramework::Renderer::getWidth() /
		(float) RenderFramework::Renderer::getHeight(),
		2.414f, 10000.0f);
}

void render(float deltaTime)
{	
	camera->update(deltaTime);

	RenderFramework::Renderer::render(scene, camera);
}

int main()
{
	if (!RenderFramework::Renderer::initialise())
		exit(EXIT_FAILURE);
	RenderFramework::Renderer::setTitle("Test Application");

	loadContent();

	auto currTime = std::chrono::system_clock::now();
	auto prevTime = std::chrono::system_clock::now();

	while (RenderFramework::Renderer::isRunning())
	{
		currTime = std::chrono::system_clock::now();
		auto deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(currTime - prevTime).count();

		RenderFramework::Renderer::beginRender();

		render(deltaTime);

		RenderFramework::Renderer::endRender();

		prevTime = currTime;
	}

	RenderFramework::Renderer::shutdown();

	exit(EXIT_SUCCESS);
}