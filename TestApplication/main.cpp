#include <RenderFramework.h>

std::shared_ptr<RenderFramework::CubeGeometry> geometry;
std::shared_ptr<RenderFramework::Material> material;
std::shared_ptr<RenderFramework::Transform> transform;
std::shared_ptr<RenderFramework::Mesh> mesh;
std::shared_ptr<RenderFramework::TargetCamera> camera;

void loadContent()
{
	RenderFramework::ContentManager::loadShader("basic_vert", "Shaders/basic.vert",
		GL_VERTEX_SHADER);
	RenderFramework::ContentManager::loadShader("basic_frag", "Shaders/basic.frag",
		GL_FRAGMENT_SHADER);
	auto program = RenderFramework::ContentManager::createProgram("basic",
		{ "basic_vert", "basic_frag" });

	geometry = std::make_shared<RenderFramework::CubeGeometry>();

	material = std::make_shared<RenderFramework::Material>();
	material->setProgram(program);

	transform = std::make_shared<RenderFramework::Transform>();

	mesh = std::make_shared<RenderFramework::Mesh>();
	mesh->setGeometry(geometry);
	mesh->setMaterial(material);
	mesh->setTransform(transform);

	camera = std::make_shared<RenderFramework::TargetCamera>();
	camera->setProjection(glm::quarter_pi<float>(),
		(float) RenderFramework::Renderer::getWidth() /
		(float) RenderFramework::Renderer::getHeight(),
		2.414f, 10000.0f);
}

void render(float deltaTime)
{
	if (glfwGetKey(RenderFramework::Renderer::getWindow(), GLFW_KEY_LEFT))
		transform->rotate(glm::vec3(0.0f, -1.0f, 0.0f) * deltaTime * 0.1f);
	else if (glfwGetKey(RenderFramework::Renderer::getWindow(), GLFW_KEY_RIGHT))
		transform->rotate(glm::vec3(0.0f, 1.0f, 0.0f) * deltaTime * 0.1f);
	if (glfwGetKey(RenderFramework::Renderer::getWindow(), GLFW_KEY_UP))
		transform->rotate(glm::vec3(1.0f, 0.0f, 0.0f) * deltaTime * 0.1f);
	else if (glfwGetKey(RenderFramework::Renderer::getWindow(), GLFW_KEY_DOWN))
		transform->rotate(glm::vec3(-1.0f, 0.0f, 0.0f) * deltaTime * 0.1f);
	
	camera->update(deltaTime);

	RenderFramework::Renderer::render(mesh, camera);
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