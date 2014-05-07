#include <RenderFramework.h>

std::shared_ptr<RenderFramework::Scene> scene;
std::shared_ptr<RenderFramework::TargetCamera> camera;

void loadContent()
{
	// Load Shaders from files
	RenderFramework::ContentManager::load<RenderFramework::Shader>("basic_vert", "Shaders/basic.vert",
		GL_VERTEX_SHADER);
	RenderFramework::ContentManager::load<RenderFramework::Shader>("basic_frag", "Shaders/basic.frag",
		GL_FRAGMENT_SHADER);
	// Create Program from Shaders
	RenderFramework::ContentManager::create<RenderFramework::Program>("basic_program",
		std::vector<std::string>{ "basic_vert", "basic_frag" });

	// Create CubeGeometry
	RenderFramework::ContentManager::create<RenderFramework::CubeGeometry>("cube");

	// Create Material from Program, then set diffuse colour
	RenderFramework::ContentManager::create<RenderFramework::Material>("basic_material",
		"basic_program", std::map<std::string, glm::vec4>{
			{ "diffuse", glm::vec4(0.0f, 0.5f, 0.0f, 1.0f) }
	});

	// Create Mesh from CubeGeometry and Material, then set position
	RenderFramework::ContentManager::create<RenderFramework::Mesh>("basic_mesh", "cube",
		"basic_material", std::map<std::string, glm::vec3>{
			{ "position", glm::vec3(0.0f, 0.0f, 0.0f) }
	});

	// Create PointLight then set position
	RenderFramework::ContentManager::create<RenderFramework::PointLight>("basic_light",
		std::map<std::string, glm::vec3>{
			{ "position", glm::vec3(10.0f, 10.0f, 10.0f) }
	});

	// Create Scene from Mesh and PointLight
	scene = RenderFramework::ContentManager::create<RenderFramework::Scene>("basic_scene",
		std::vector<std::string>{ "basic_mesh" }, std::vector<std::string>{ "basic_light" });

	// Create TargetCamera
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
	{
		for (auto& light : scene->pointLights)
			light->translate(glm::vec3(1.0f * deltaTime * 0.001f, 0.0f, 0.0f));
	}
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