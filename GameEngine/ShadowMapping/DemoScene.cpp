#include <glm/gtc/matrix_transform.hpp>

#include "DemoScene.hh"
#include <SDL\SDL.h>

DemoScene::DemoScene(Engine &engine)
: AScene(engine)
{
}

DemoScene::~DemoScene()
{
}

void DemoScene::initSytemeScene()
{
	addSystem<MeshRendererSystem>(0);
	addSystem<GraphNodeSystem>(100);
	addSystem<TrackBallSystem>(150);
	addSystem<CameraSystem>(200);
}

void DemoScene::initRenderer()
{
	std::string const perModelVars[] = { "model" };
	std::string const perFrameVars[] = { "projection", "view", "light", "time" };
	std::string const materialBasic[] = { "ambient", "diffuse", "specular", "transmittance", "emission", "shininess" };

	auto &renderer = _engine.getInstance<Renderer>();
	OpenGLTools::Shader &s = _engine.getInstance<Renderer>().addShader("MaterialBasic", "Shaders/MaterialBasic.vp", "Shaders/MaterialBasic.fp");
	renderer.addUniform("MaterialBasic").init(&s, "MaterialBasic", materialBasic);
	renderer.addUniform("PerFrame").init(&s, "PerFrame", perFrameVars);
	renderer.addUniform("PerModel").init(&s, "PerModel", perModelVars);
	renderer.getShader("MaterialBasic")->addTarget(GL_COLOR_ATTACHMENT0).setTextureNumber(4).build();
	renderer.bindShaderToUniform("MaterialBasic", "PerFrame", "PerFrame");
	renderer.bindShaderToUniform("MaterialBasic", "PerModel", "PerModel");
	renderer.bindShaderToUniform("MaterialBasic", "MaterialBasic", "MaterialBasic");
}

void DemoScene::loadResources()
{
	auto &resources = _engine.getInstance<Resources::ResourceManager>();

	resources.addResource("model:ball", new Resources::SharedMesh(), "Assets/ball/ball.obj");
	resources.addResource("model:cube", new Resources::SharedMesh(), "./Assets/cube/cube.obj");
	resources.addResource("texture:earth", new Resources::Texture(), "Assets/EarthTexture.tga");
	resources.addResource("cubemap:space", new Resources::CubeMap(), "Assets/skyboxSpace");
}

bool DemoScene::userStart()
{
	initSytemeScene();
	initRenderer();
	loadResources();
	
	auto &resources = _engine.getInstance<Resources::ResourceManager>();

	Entity sphere = createEntity();
	Entity plan = createEntity();

	sphere->translate(glm::vec3(0, 10, 0));
	auto &materialSphere = sphere->addComponent<Component::MeshRenderer>("model:ball")->getMaterials()[0];
	sphere->addComponent<Component::MeshRenderer>("model:sphere")->setShader("MaterialBasic");
	materialSphere.ambientTex = resources.getResource("texture:earth");
	materialSphere.diffuseTex = resources.getResource("texture:earth");
	materialSphere.specularTex = resources.getResource("texture:earth");
	materialSphere.normalTex = resources.getResource("texture:earth");
	
	plan->translate(glm::vec3(0, 0, 0));
	auto &materialPlan = plan->addComponent<Component::MeshRenderer>("model:cube")->getMaterials()[0];
	plan->addComponent<Component::MeshRenderer>("model:cube")->setShader("MaterialBasic");
	materialPlan.ambientTex = resources.getResource("");
	materialPlan.diffuseTex = resources.getResource("");
	materialPlan.specularTex = resources.getResource("");
	materialPlan.normalTex = resources.getResource("");
	return (true);
}

bool DemoScene::userUpdate(double time)
{
	auto input = _engine.getInstance<Input>();
	if (input.getInput(SDLK_ESCAPE) || input.getInput(SDL_QUIT))
		return (false);
	return (true);
}