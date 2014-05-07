#include <RenderFramework.h>

std::shared_ptr<RenderFramework::Scene> scene;
std::shared_ptr<RenderFramework::TargetCamera> camera;
std::shared_ptr<RenderFramework::PointLight> light;

void loadContent()
{
	RenderFramework::ContentManager::load<RenderFramework::Shader>("basic_vert", "Shaders/basic.vert",
		GL_VERTEX_SHADER);
	RenderFramework::ContentManager::load<RenderFramework::Shader>("basic_frag", "Shaders/basic.frag",
		GL_FRAGMENT_SHADER);
	auto program = RenderFramework::ContentManager::create<RenderFramework::Program>(
		"basic_program", std::vector<std::string>{ "basic_vert", "basic_frag" });

	auto geometry = RenderFramework::ContentManager::create<RenderFramework::CubeGeometry>("cube");

	auto material = RenderFramework::ContentManager::create<RenderFramework::Material>(
		"basic_material", "basic_program", std::map<std::string, glm::vec4>{
			{ "diffuse", glm::vec4(0.0f, 0.5f, 0.0f, 1.0f) }
	});

	auto mesh = RenderFramework::ContentManager::create<RenderFramework::Mesh>("basic_mesh",
		"cube", "basic_material");
	mesh->position = glm::vec3(0.0f, 0.0f, 0.0f);

	scene = RenderFramework::ContentManager::create<RenderFramework::Scene>("basic_scene",
		std::vector<std::string>{ "basic_mesh" });

	light = std::make_shared<RenderFramework::PointLight>();
	auto lightTransform = std::make_shared<RenderFramework::Transform>();
	light->position = glm::vec3(10.0f, 10.0f, 10.0f);
	scene->pointLights.push_back(light);

	camera = std::make_shared<RenderFramework::TargetCamera>();
	camera->setProjection(glm::quarter_pi<float>(),
		(float) RenderFramework::Renderer::getWidth() /
		(float) RenderFramework::Renderer::getHeight(),
		2.414f, 10000.0f);
	camera->setPosition(glm::vec3(0.0f, 0.0f, 10.0f));
}

void render(float deltaTime)
{	
	if (glfwGetKey(RenderFramework::Renderer::getWindow(), GLFW_KEY_LEFT))
		light->translate(glm::vec3(1.0f * deltaTime * 0.001f, 0.0f, 0.0f));
	camera->update(deltaTime);
	for (auto& mesh : scene->meshes)
		mesh->rotate(glm::vec3(0.0f, 1.0f, 0.0f) * deltaTime * 0.001f);

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