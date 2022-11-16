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
	wrap::g_gui.Initialize(wrap::g_renderer);

	auto scene = wrap::g_resources.Get<wrap::Scene>("Scenes/Cubemap.scn");
	//auto scene = wrap::g_resources.Get<wrap::Scene>("Scenes/exScene.scn");


	glm::vec3 rot(0,0,0);
	bool quit = false;
	while (!quit)
	{
		wrap::Engine::Instance().Update();
		wrap::g_gui.BeginFrame(wrap::g_renderer);


		if (wrap::g_inputSystem.GetKeyState(wrap::key_escape) == wrap::InputSystem::KeyState::Pressed) quit = true;

		// -- orge rotation -- 
		auto actor = scene->GetActorFromName("Camera");
		if (actor)
		{
			actor->m_transform.rotation = math::EulerToQuaternion(rot);
		}
		// -- orge rotation -- 

		// -- light rotation --
		//auto actor = scene->GetActorFromName("Light1");
		//if (actor)
		//{
			// move light using sin wave
			//actor->m_transform.position = pos;
			//actor->m_transform.position.x = std::sin(wrap::g_time.time);
		//}
		// -- light rotation --


		ImGui::Begin("Transform");
		ImGui::SliderFloat3("Rotation", &rot[0], -360.0f, 360.0f);
		ImGui::End();

		scene->Update();

		wrap::g_renderer.BeginFrame();

		scene->Render(wrap::g_renderer);
		scene->PreRender(wrap::g_renderer);

		wrap::g_gui.Draw();

		wrap::g_renderer.EndFrame();
		wrap::g_gui.EndFrame();
	}
	scene->RemoveAll();
	wrap::Engine::Instance().Shutdown();

	return 0;
}