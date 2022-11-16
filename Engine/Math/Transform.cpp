#include "Transform.h"

bool wrap::Transform::Write(const rapidjson::Value& value) const
{
    return true;
}

bool wrap::Transform::Read(const rapidjson::Value& value)
{
    READ_DATA(value, position);
    READ_DATA(value, scale);

    glm::vec3 eular;
    READ_NAME_DATA(value, "rotation", eular);
    rotation = math::EulerToQuaternion(eular);

    return true;
}
