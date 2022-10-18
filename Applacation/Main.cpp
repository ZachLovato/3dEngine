#include "Engine.h"
#include <iostream>

float points[] = {
   1.0f, 1.0f,  0.0f, // triangle 1
   -1.0f, 1.0f,  0.0f,
   -1.0f, -1.0f,  0.0f,
   -1.0f, -1.0f,  0.0f, // triangle 2
   1.0f, -1.0f,  0.0f,
   1.0f, 1.0f,  0.0f


};

glm::vec3 colors[] =
{ // rgb
	{ 0, 0, 0 },
	{ 0, 0, 0 },
	{ 0, 0, 0 },

	{ 0, 0, 0 },
	{ 0, 0, 0 },
	{ 0, 0, 0 }
};

glm::vec2 texcoords[]
{
	{ 0 , 0 },
	{ 1 , 0 },
	{ 1 , 1 },
	
	{ 1 , 1 },
	{ 0 , 1 },
	{ 0 , 0 }
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
	GLuint pvbo = 0;
	glGenBuffers(1, &pvbo);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), points, GL_STATIC_DRAW);

	GLuint cvbo = 0;
	glGenBuffers(1, &cvbo);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec3), colors, GL_STATIC_DRAW);

	GLuint tvbo = 0;
	glGenBuffers(1, &tvbo);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glBufferData(GL_ARRAY_BUFFER, 6 * sizeof(glm::vec2), texcoords, GL_STATIC_DRAW);

	// create vertex array
	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, pvbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, cvbo);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, tvbo);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 0, NULL);


	std::shared_ptr<neu::Material> material = neu::g_resources.Get<neu::Material>("materials/box.mtrl");
	material->Link();
	material->Bind();

	// create shader
	//std::shared_ptr<neu::Program> pog = neu::g_resources.Get<neu::Program>("shaders/basic.prog");
	//pog->Link();
	//pog->Use();

	//Create Texture
	//std::shared_ptr<neu::Texture> texture1 = neu::g_resources.Get<neu::Texture>("texture/wood.png");
	//std::shared_ptr<neu::Texture> texture2 = neu::g_resources.Get<neu::Texture>("texture/llama.jpg");
	//std::shared_ptr<neu::Texture> texture3 = neu::g_resources.Get<neu::Texture>("texture/create.png");
	//texture1->Bind();


	glm::mat4 mx { 1 };
	//mx = glm::scale(glm::vec3{ 0.5, 0.5 ,0.5});

	bool quit = false;
	while (!quit)
	{
		neu::Engine::Instance().Update();

		if (neu::g_inputSystem.GetKeyState(neu::key_escape) == neu::InputSystem::KeyState::Pressed) quit = true;

		mx = glm::eulerAngleXYX(0, 0, 0);
		material->GetProgram()->SetUniform("tint", glm::vec3{ 1, 0, 0 });
		material->GetProgram()->SetUniform("scale", 1.0f);
		//material->GetProgram()->SetUniform("scale", std::sin(neu::g_time.time * 3));
		material->GetProgram()->SetUniform("transform", mx);

		neu::g_renderer.BeginFrame();

		glDrawArrays(GL_TRIANGLES, 0, 6);

		

		neu::g_renderer.EndFrame();
	}

	neu::Engine::Instance().Shutdown();
	return 0;
}