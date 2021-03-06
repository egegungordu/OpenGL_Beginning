#include "Camera.h"
#include "glm/trigonometric.hpp"

static	glm::vec3 Position(0.0f, 150.0f, 2.0f);
static	glm::vec3 CameraAngle(0.0f, 0.0f, -1.0f);
static	glm::vec3 InitialAngle(0.0f, 0.0f, -1.0f);

void Camera::setAngle(float pitchAngle, float yawAngle)
{
    glm::mat3 pitchRotationMatrix(
        1, 0, 0,
        0, glm::cos(pitchAngle), -glm::sin(pitchAngle),
        0, glm::sin(pitchAngle), glm::cos(pitchAngle)
    );
    glm::mat3 yawRotationMatrix(
        glm::cos(yawAngle), 0, glm::sin(yawAngle),
        0, 1, 0,
        -glm::sin(yawAngle), 0, glm::cos(yawAngle)
    );
    CameraAngle = yawRotationMatrix * pitchRotationMatrix  * InitialAngle;
}

void Camera::setPosition(glm::vec3 value)
{
    Position = value;
}

const glm::vec3& Camera::GetPosition()
{
    return Position;
}

const glm::vec3& Camera::GetCameraAngle()
{
    return CameraAngle;
}

