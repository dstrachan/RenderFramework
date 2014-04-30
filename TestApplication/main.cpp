#include <RenderFramework.h>

std::shared_ptr<RenderFramework::CubeGeometry> geometry;
std::shared_ptr<RenderFramework::Material> material;
std::shared_ptr<RenderFramework::Mesh> mesh;
RenderFramework::TargetCamera* camera;

GLuint id;

void loadContent()
{
	geometry = std::make_shared<RenderFramework::CubeGeometry>();
	material = std::make_shared<RenderFramework::Material>();
	mesh = std::make_shared<RenderFramework::Mesh>();
	mesh->setGeometry(geometry);
	mesh->setMaterial(material);

	auto vertexShader = RenderFramework::ContentManager::loadShader(
		"basic_vert", "Shaders/basic.vert", GL_VERTEX_SHADER);
	auto fragmentShader = RenderFramework::ContentManager::loadShader(
		"basic_frag", "Shaders/basic.frag", GL_FRAGMENT_SHADER);
	auto program = RenderFramework::ContentManager::createProgram("basic", { "basic_vert", "basic_frag" });
	RenderFramework::Renderer::useProgram(program);
	material->setProgram(program);

	id = program->id;

	camera = new RenderFramework::TargetCamera();
	camera->setProjection(glm::quarter_pi<float>(),
		(float) RenderFramework::Renderer::getWidth() /
		(float) RenderFramework::Renderer::getHeight(),
		2.414f, 10000.0f);
}

void render(float deltaTime)
{
	auto position = camera->getPosition();
	if (glfwGetKey(RenderFramework::Renderer::getWindow(), GLFW_KEY_LEFT))
		position.x -= deltaTime / 100.0f;
	camera->setPosition(position);
	camera->update(deltaTime);

	auto model = glm::mat4(1.0f);
	auto view = camera->getView();
	auto projection = camera->getProjection();
	RenderFramework::Renderer::render(mesh, model, view, projection);
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