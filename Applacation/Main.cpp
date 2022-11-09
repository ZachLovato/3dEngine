#include "Engine.h"
#include <iostream> 
#include <Renderer/Program.h>
#include <Renderer/Material.h>

int main(int argc, char** argv)
{
	LOG("Application Started...");
	wrap::InitializeMemory();
	wrap::SetFilePath("../Assets");

	wrap::Engine::Instance().Initialize();
	wrap::Engine::Instance().Register();
	LOG("Engine Initialized...");

	wrap::g_renderer.CreateWindow("page...", 800, 600);
	LOG("Window Initialized...");

	auto scene = wrap::g_resources.Get<wrap::Scene>("Scenes/texture.scn");
	//auto scene = wrap::g_resources.Get<wrap::Scene>("Scenes/exScene.scn");

	/*auto scene = std::make_unique<wrap::Scene>();

	rapidjson::Document document;
	bool success = wrap::json::Load("scenes/texture.scn", document);
	if (!success)
	{
		LOG("error loading scene file %s.", "Scenes/basic.scn");
	}
	else
	{
		scene->Read(document);
		scene->Initialize();
	}*/

	bool quit = false;
	while (!quit)
	{
		wrap::Engine::Instance().Update();


		if (wrap::g_inputSystem.GetKeyState(wrap::key_escape) == wrap::InputSystem::KeyState::Pressed) quit = true;

		// -- orge rotation -- 
		//auto actor = scene->GetActorFromName("Ogre");
		//if (actor)
		//{
		//	actor->m_transform.rotation.y += wrap::g_time.deltaTime * 90.0f;
		//}
		// -- orge rotation -- 

		// -- light rotation --
		auto actor = scene->GetActorFromName("Light");
		if (actor)
		{
			// move light using sin wave
			actor->m_transform.position.x = std::sin(wrap::g_time.time);
		}
		// -- light rotation --

		scene->Update();

		wrap::g_renderer.BeginFrame();

		scene->Draw(wrap::g_renderer);

		wrap::g_renderer.EndFrame();
	}
	scene->RemoveAll();
	wrap::Engine::Instance().Shutdown();

	return 0;
}