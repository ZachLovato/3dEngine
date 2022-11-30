#include "Engine.h"
#include <iostream> 
#include <Renderer/Program.h>
#include <Renderer/Material.h>

#define POST_PROCESS 

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

	//auto scene = wrap::g_resources.Get<wrap::Scene>("Scenes/multiLit.scn");

	// create framebuffer texture 
	auto texture = std::make_shared<wrap::Texture>();
	//by reducing the texture size the image will become pixelated (512 was default prior, 64 for pixel)
	// change back gltexParamater to Gl_Liner in texture.cpp
	texture->CreateTexture(256, 256);
	wrap::g_resources.Add<wrap::Texture>("fb_texture", texture);

	// create framebuffer
	auto framebuffer = wrap::g_resources.Get<wrap::Framebuffer>("framebuffer", "fb_texture");
	framebuffer->Unbind();

	auto scene = wrap::g_resources.Get<wrap::Scene>("Scenes/PostProcess.scn");


	glm::vec3 rot(0,0,0);
	float ri = 1;
	float ip = 1;
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
		actor = scene->GetActorFromName("box");
		if (actor)
		{
			//std::cout << actor->m_transform.position.x << std::endl;
			//std::cout << actor->m_transform.position.y << std::endl;
			//std::cout << actor->m_transform.position.z << std::endl;

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

		/*auto program = wrap::g_resources.Get<wrap::Program>("shaders/fx/refraction.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("ri", ri);
		}*/

		auto program = wrap::g_resources.Get<wrap::Program>("shaders/fx/reflect_refract.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("ip", ip);
			program->SetUniform("ri", ri);
		}

		auto waveProgram = wrap::g_resources.Get<wrap::Program>("shaders/postprocessing/postWave.prog");
		if (program)
		{
			program->Use();
			program->SetUniform("offset", wrap::g_time.time);
		}

		ImGui::Begin("Transform");
		ImGui::SliderFloat3("Rotation", &rot[0], -360.0f, 360.0f);
		//ImGui::DragFloat3("Rotation", &rot[0]);
		//ImGui::DragFloat("Refraction index", &ri, 0.01f, 0, 1.5);
		ImGui::DragFloat("ip", &ip, 0.01f, 0, 1.5);
		ImGui::DragFloat("RI", &ri, 0.01f, 0, 1.5);
		ImGui::End();

		scene->Update();

		{
			auto actor = scene->GetActorFromName("rtt");
			if (actor)
			{
				actor->SetActive(false);
			}
		}

#ifdef POST_PROCESS 
		// don't draw post process actor when rendering to the framebuffer 
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(false);
			}
		}
		// render pass 1 (render scene to framebuffer) 
		wrap::g_renderer.SetViewport(0, 0, framebuffer -> GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();
		wrap::g_renderer.BeginFrame();
		scene->PreRender(wrap::g_renderer);
		scene->Render(wrap::g_renderer);
		framebuffer->Unbind();

		// render pass 2 (render to screen) 
		wrap::g_renderer.RestoreViewport();
		wrap::g_renderer.BeginFrame();
		scene->PreRender(wrap::g_renderer);

		// draw only the post process actor to the screen 
		{
			auto actor = scene->GetActorFromName("PostProcess");
			if (actor)
			{
				actor->SetActive(true);
				actor->Draw(wrap::g_renderer);
			}
		}
#else 
		neu::g_renderer.BeginFrame();
		scene->PreRender(neu::g_renderer);
		scene->Render(neu::g_renderer);
#endif // POST_PROCESS 

		/*
		// render pass 1 render to framebuffer
		//glViewport(0, 0, 512, 512);
		wrap::g_renderer.SetViewport(0, 0, framebuffer->GetSize().x, framebuffer->GetSize().y);
		framebuffer->Bind();

		wrap::g_renderer.BeginFrame();
		scene->PreRender(wrap::g_renderer);
		scene->Render(wrap::g_renderer);
		framebuffer->Unbind();

		{
			auto actor = scene->GetActorFromName("rtt");
			if (actor)
			{
				actor->SetActive(false);
			}
		}

		// render pass 2. render to screen
		wrap::g_renderer.RestoreViewport();
		wrap::g_renderer.BeginFrame();
		scene->PreRender(wrap::g_renderer);
		scene->Render(wrap::g_renderer);
		*/

		wrap::g_gui.Draw();

		wrap::g_renderer.EndFrame();
		wrap::g_gui.EndFrame();
	}
	scene->RemoveAll();
	wrap::Engine::Instance().Shutdown();

	return 0;
}