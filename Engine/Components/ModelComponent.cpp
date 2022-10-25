#include "Renderer/Model.h" 
#include "Framework/Actor.h" 
#include "Engine.h" 

namespace wrap
{
	void ModelComponent::Draw(Renderer& renderer)
	{
		material->Bind();
		// set model view projection matrix for model 
		material->GetProgram() -> SetUniform("model", (glm::mat4)m_owner->m_transform);
		material->GetProgram() -> SetUniform("view", renderer.GetView());
		material->GetProgram() -> SetUniform("projection", renderer.GetProjection());

		model->m_vertexBuffer.Draw();
	}

	bool ModelComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool ModelComponent::Read(const rapidjson::Value& value)
	{
		std::string model_name;
		READ_DATA(value, model_name);
		std::string mat_name;
		READ_DATA(value, mat_name);

		model = g_resources.Get<Model>(model_name);
		material = g_resources.Get<Material>(mat_name);

		return true;
	}
}
