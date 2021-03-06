#include "Camera.h"

#include"../Core/MEngine.h"

Camera::Camera()
{
    position = glm::vec3();
    fieldOfView = 45.0f;
    forward = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    worldUp = up;
    nearPlane = 2.0f;
    farPlane = 50.0f;
    yaw = -90.f;
    pitch = 0.f;

    perspective = glm::perspective(fieldOfView, MEngine::GetInstance()->GetScreenWidth() / 
        MEngine::GetInstance()->GetScreenHeight(), nearPlane, farPlane);

    orthorgraphic = glm::ortho(0.0f, MEngine::GetInstance()->GetScreenWidth(),
        0.f, MEngine::GetInstance()->GetScreenHeight(), -1.f, 1.f);

    //lightS = std::vector<LightSource*>();


    UpdateCameraVectors();
}

Camera::~Camera()
{
    
}

void Camera::SetPosition(glm::vec3 position_)
{
    position = position_;
    UpdateCameraVectors();
}

void Camera::SetRotation(float yaw_, float pitch_)
{
    yaw = yaw_;
    pitch = pitch_;
    UpdateCameraVectors();
}

glm::mat4 Camera::GetView() const
{
    return view;
}

glm::mat4 Camera::GetPerspective() const
{
    return perspective;
}

glm::mat4 Camera::GetOrthographic() const
{
    return orthorgraphic;
}

glm::vec3 Camera::GetPosition() const
{
    return position;
}

float Camera::GetNearPlane() const
{
    return nearPlane;
}

float Camera::GetFarPlane() const
{
    return farPlane;
}

void Camera::Addlight(LightSource* lightsource_)
{
    lightS.push_back(lightsource_);
}

std::vector<LightSource*> Camera::get_light() const
{
    return lightS; 
}

void Camera::ProcessMouseMovement(glm::vec2 offset_)
{
    offset_ *= 0.025f;

    yaw += offset_.x;
    pitch += offset_.y;

    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }
    if (yaw < 0.0f) {
        yaw += 360.0f;
    }
    if (yaw > 360.0f) {
        yaw -= 360.0f;
    }
    UpdateCameraVectors();
}

void Camera::ProcessMouseZoom(int y_)
{
    if (y_ < 0 || y_>0) {
        position += static_cast<float>(y_) * (forward * 2.0f);

    }
    UpdateCameraVectors();
}


void Camera::UpdateCameraVectors()
{
    forward.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    forward.y = sin(glm::radians(pitch));
    forward.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    
    forward = glm::normalize(forward);
    right = glm::normalize(glm::cross(forward, worldUp));
    up = glm::normalize(glm::cross(right, forward));
    view = glm::lookAt(position, position + forward, up);
}


