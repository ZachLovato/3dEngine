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
	wrap::InitializeMemory();

	wrap::SetFilePath("../assets");

	wrap::Engine::Instance().Initialize();
	wrap::Engine::Instance().Register();
	LOG("Engine Started...");

	wrap::g_renderer.CreateWindow("Bork", 800, 600);
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

	std::shared_ptr<wrap::VertexBuffer> vb = wrap::g_resources.Get<wrap::VertexBuffer>("box");
	vb->CreateVertexBuffer(sizeof(vertices), 36, vertices);
	vb->SetAttribute(0, 3, 8 * sizeof(float), 0);
	vb->SetAttribute(1, 3, 8 * sizeof(float), 3 * sizeof(float));
	vb->SetAttribute(2, 3, 8 * sizeof(float), 6 * sizeof(float));
 
	//creat emateral
	std::shared_ptr<wrap::Material> material = wrap::g_resources.Get<wrap::Material>("materials/box.mtrl");
	material->Link();
	material->Bind();

	material->GetProgram()->SetUniform("tint", glm::vec3{ 1, 0, 0 });
	material->GetProgram()->SetUniform("scale", 1.0f);

	glm::mat4 model { 1 };
	glm::mat4 projection = glm::perspective(45.0f, wrap::g_renderer.GetWidth() / (float)wrap::g_renderer.GetHeight(), 0.01f, 100.0f);

	glm::vec3 cameraPosition{ 0, 0, 2 };
	float speed = 3;

	bool quit = false;
	while (!quit)
	{
		wrap::Engine::Instance().Update();

		if (wrap::g_inputSystem.GetKeyState(wrap::key_escape) == wrap::InputSystem::KeyState::Pressed) quit = true;
		//add input to camera
		if (wrap::g_inputSystem.GetKeyState(wrap::key_left) == wrap::InputSystem::KeyState::Held)
		{
			cameraPosition.x -= speed * wrap::g_time.deltaTime; // move left
		}
		if (wrap::g_inputSystem.GetKeyState(wrap::key_right) == wrap::InputSystem::KeyState::Held)
		{
			cameraPosition.x += speed * wrap::g_time.deltaTime; // move right
		}
		if (wrap::g_inputSystem.GetKeyState(wrap::key_up) == wrap::InputSystem::KeyState::Held)
		{
			cameraPosition.y += speed * wrap::g_time.deltaTime; // move up
		}
		if (wrap::g_inputSystem.GetKeyState(wrap::key_down) == wrap::InputSystem::KeyState::Held)
		{
			cameraPosition.y -= speed * wrap::g_time.deltaTime; // move down
		}
		if (wrap::g_inputSystem.GetKeyState(wrap::key_w) == wrap::InputSystem::KeyState::Held)
		{
			cameraPosition.z -= speed * wrap::g_time.deltaTime; // zoom in
		}
		if (wrap::g_inputSystem.GetKeyState(wrap::key_s) == wrap::InputSystem::KeyState::Held)
		{
			cameraPosition.z += speed * wrap::g_time.deltaTime; // zoom out
		}

		//model = glm::eulerAngleXYX(0.0f, wrap::g_time.time * 2, std::sin(wrap::g_time.time));
		
		//glm::mat4 view = glm::lookAt(cameraPosition, glm::vec3{ 0, 0, 0 }, glm::vec3{ 0, 1, 0 });
		glm::mat4 view = glm::lookAt(cameraPosition, cameraPosition + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });
		glm::mat4 mvp = projection * view * model;

		//material->GetProgram()->SetUniform("scale", std::sin(wrap::g_time.time));
		material->GetProgram()->SetUniform("mvp", mvp);

		wrap::g_renderer.BeginFrame();

		vb->Draw();

		wrap::g_renderer.EndFrame();
	}

	wrap::Engine::Instance().Shutdown();
	return 0;
}