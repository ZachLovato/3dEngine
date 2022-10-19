#include "Engine.h"
#include <iostream>

float vertices[] = {
	-0.5f, -0.5f, -0.5f,1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f, -0.5f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f, -0.5f,1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f, -0.5f,  0.5f,1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f,  0.5f,  0.5f,1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,1.0f, 1.0f, 1.0f, 0.0f, 0.0f,

	-0.5f,  0.5f,  0.5f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f, -0.5f,1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	-0.5f, -0.5f,  0.5f,1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	 0.5f,  0.5f,  0.5f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f, -0.5f,1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f,

	-0.5f, -0.5f, -0.5f,1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f, -0.5f, -0.5f,1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f, -0.5f,  0.5f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f, -0.5f,  0.5f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f, -0.5f,  0.5f,1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f, -0.5f, -0.5f,1.0f, 1.0f, 1.0f, 0.0f, 1.0f,

	-0.5f,  0.5f, -0.5f,1.0f, 1.0f, 1.0f, 0.0f, 1.0f,
	 0.5f,  0.5f, -0.5f,1.0f, 1.0f, 1.0f, 1.0f, 1.0f,
	 0.5f,  0.5f,  0.5f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	 0.5f,  0.5f,  0.5f,1.0f, 1.0f, 1.0f, 1.0f, 0.0f,
	-0.5f,  0.5f,  0.5f,1.0f, 1.0f, 1.0f, 0.0f, 0.0f,
	-0.5f,  0.5f, -0.5f,1.0f, 1.0f, 1.0f, 0.0f, 1.0f
};


int main(int argc, char** argv)
{
	LOG("App Started...");
	neu::InitializeMemory();

	neu::SetFilePath("../assets");

	neu::Engine::Instance().Initialize();
	neu::Engine::Instance().Register();
	LOG("Engine Started...");

	neu::g_renderer.CreateWindow("Bork", 800, 600);
	LOG("Window Started...");
	
	// create vertex buffer
	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// create vertex array
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));


	std::shared_ptr<neu::Material> material = neu::g_resources.Get<neu::Material>("materials/box.mtrl");
	material->Link();
	material->Bind();

	material->GetProgram()->SetUniform("tint", glm::vec3{ 1, 0, 0 });
	material->GetProgram()->SetUniform("scale", 1.0f);

	glm::mat4 model { 1 };
	glm::mat4 projection = glm::perspective(45.0f, neu::g_renderer.GetWidth() / (float)neu::g_renderer.GetHeight(), 0.01f, 100.0f);

	glm::vec3 cameraPosition{ 0, 0, 2 };
	float speed = 3;

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;
		//add input to camera
		if (neu::g_inputSystem.GetKeyState(neu::key_left) == neu::InputSystem::KeyState::Held)
		{
			cameraPosition.x -= speed * neu::g_time.deltaTime; // move left
		}
		if (neu::g_inputSystem.GetKeyState(neu::key_right) == neu::InputSystem::KeyState::Held)
		{
			cameraPosition.x += speed * neu::g_time.deltaTime; // move right
		}
		if (neu::g_inputSystem.GetKeyState(neu::key_up) == neu::InputSystem::KeyState::Held)
		{
			cameraPosition.y += speed * neu::g_time.deltaTime; // move up
		}
		if (neu::g_inputSystem.GetKeyState(neu::key_down) == neu::InputSystem::KeyState::Held)
		{
			cameraPosition.y -= speed * neu::g_time.deltaTime; // move down
		}
		if (neu::g_inputSystem.GetKeyState(neu::key_w) == neu::InputSystem::KeyState::Held)
		{
			cameraPosition.z -= speed * neu::g_time.deltaTime; // zoom in
		}
		if (neu::g_inputSystem.GetKeyState(neu::key_s) == neu::InputSystem::KeyState::Held)
		{
			cameraPosition.z += speed * neu::g_time.deltaTime; // zoom out
		}

		//model = glm::eulerAngleXYX(0.0f, neu::g_time.time * 2, std::sin(neu::g_time.time));
		
		//glm::mat4 view = glm::lookAt(cameraPosition, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 });
		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });
		glm::mat4 mvp = projection * view * model;

		//material->GetProgram()->SetUniform("scale", std::sin(neu::g_time.time));
		material->GetProgram()->SetUniform("mvp", mvp);

		neu::g_renderer.BeginFrame();

		glDrawArrays(GL_TRIANGLES, 0, 36);

		neu::g_renderer.EndFrame();
	}

	neu::Engine::Instance().Shutdown();
	return 0;
}