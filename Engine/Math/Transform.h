#pragma once
#include "Vector2.h"
#include "Matrix3x3.h"
#include "MathUtils.h"
#include "Serialization/Serializable.h"

namespace wrap
{
	struct Transform : public ISerializable
	{
		glm::vec3 position;
		glm::vec3 rotation{ 0 };
		glm::vec3 scale{ 1, 1, 1 };

		glm::mat4 matrix;

		Transform() = default;
		Transform(const glm::vec3& position, const glm::vec3 rotation = { 0, 0, 0 }, const glm::vec3& scale = { 1, 1, 1 }) :
			position{ position },
			rotation{ rotation },
			scale{ scale } 
		{}


		virtual bool Write(const rapidjson::Value& value) const override;
		virtual bool Read(const rapidjson::Value& value) override;

		void Update()
		{
			matrix = *this;
		}

		void Update(const glm::mat4& parent)
		{
			matrix = *this;
			matrix = parent * (glm::mat4)*this;
		}

		operator glm::mat4 () const
		{
			glm::mat4 mxScale = glm::scale(scale);
			glm::mat4 mxRotation = glm::eulerAngleXYX(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z));
			glm::mat4 mxTranslation = glm::translate(position);

			return { mxTranslation * mxRotation * mxScale };
		}
	};
}
