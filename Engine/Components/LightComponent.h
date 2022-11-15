#pragma once
#include "Framework/Component.h"

namespace wrap
{
	class LightComponent : public Component
	{
	public:
		enum class Type
		{
			Point,
			Directional,
			Spot
		};

		CLASS_DECLARATION(LightComponent)

		void Update() override;

		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void SetProgram(std::shared_ptr<Program> programs, int index);

	public:
		Type type = Type::Point;
		glm::vec3 color{ 0 };
		float cutoff = 45.0f;
		float exponent = 50.0f;
	};
}