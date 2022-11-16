#include "LightComponent.h"
#include "Core/Utilities.h"
#include "Engine.h"

namespace wrap
{
	void LightComponent::Update()
	{
		
	}

	bool LightComponent::Write(const rapidjson::Value& value) const
	{
		return true;
	}

	bool LightComponent::Read(const rapidjson::Value& value)
	{
		READ_DATA(value, color);
		READ_DATA(value, cutoff);
		READ_DATA(value, exponent);

		std::string type_name;
		READ_DATA(value, type_name);
		if (CompareIgnoreCase(type_name, "directional"))
		{
			type = Type::Directional;
		}
		else if (CompareIgnoreCase(type_name, "spot"))
		{
			type = Type::Spot;
		}
		else
		{
			type = Type::Point;
		}

		return true;
	}

	void LightComponent::SetProgram(std::shared_ptr<Program> programs, int index)
	{
		// transform the light position by the view, puts light in model view space 
		glm::vec4 position = g_renderer.GetView() * glm::vec4(m_owner->m_transform.position, 1);
		glm::vec3 direction = m_owner->m_transform.getForward();

		// create array light name from index (lights[0], ...) 
		std::string lightName = "lights[" + std::to_string(index) + ']';

		programs->Use();
		programs->SetUniform(lightName + ".type", (int)type);
		programs->SetUniform(lightName + "color", color);
		programs->SetUniform(lightName + "position", position);
		programs->SetUniform(lightName + "direction", direction);
		programs->SetUniform(lightName + "cutoff", direction);
		programs->SetUniform(lightName + "exponent", exponent);

		/*
		* // transform the light position by the view, puts light in model view space
		glm::vec4 position = g_renderer.GetView() * glm::vec4(m_owner->m_transform.position, 1);
		glm::vec3 direction = m_owner->m_transform.getForward();

		// get all programs in the resource system
		auto programs = g_resources.Get<Program>();
		// set programs light properties
		for (auto& program : programs)
		{
			program->SetUniform("light.type", (int)type);
			program->SetUniform("light.ambient", glm::vec3{ 0.2f });
			program->SetUniform("light.color", color);
			program->SetUniform("light.position", position);
			program->SetUniform("light.direction", direction);
			program->SetUniform("light.cutoff", glm::radians(cutoff));
			program->SetUniform("light.exponent", exponent);
		}
		*/
	}

}