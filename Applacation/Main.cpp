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
	LOG("Engine Initialized");

	wrap::g_renderer.CreateWindow("Neumont", 800, 600);

	auto scene = std::make_unique<wrap::Scene>();

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
	}

	bool quit = false;
	while (!quit)
	{
		wrap::Engine::Instance().Update();


		if (wrap::g_inputSystem.GetKeyState(wrap::key_escape) == wrap::InputSystem::KeyState::Pressed) quit = true;

		auto actor1 = scene->GetActorFromName("Ogre");
		if (actor1)
		{
			//actor1->m_transform.rotation.y += wrap::g_time.deltaTime * 30;
		}


		actor1 = scene->GetActorFromName("Light");
		if (actor1)
		{
			actor1->m_transform.position.x = std::sin(wrap::g_time.time) * 2;
		}


		auto actor2 = scene->GetActorFromName("Box");

		auto material = wrap::g_resources.Get<wrap::Material>("Materials/multi.mtrl");
		if (material)
		{
			//material->uv_offset.y += wrap::g_time.deltaTime;
			//material->uv_offset.x += wrap::g_time.deltaTime;
		}

		scene->Update();

		wrap::g_renderer.BeginFrame();

		scene->Draw(wrap::g_renderer);

		wrap::g_renderer.EndFrame();
	}
	scene->RemoveAll();
	wrap::Engine::Instance().Shutdown();

	return 0;
}