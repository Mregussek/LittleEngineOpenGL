
#ifndef CAMERA_H
#define CAMERA_H


#include "includes.h"
#include "defines.h"
#include "math/vec3.h"
#include "math/mat4.h"


namespace le
{


enum class CameraMovement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};


const f32 YAW{ -90.f };
const f32 PITCH{ 0.0f };
const f32 SPEED{ 2.5f };
const f32 SENSITIVITY{ 0.1f };
const f32 ZOOM{ 45.0f };


class Camera {
public:

    Camera() = default;

    void init() {
        updateCameraVectors();
    }

    mat4 GetViewMatrix() {
        return mat4::lookAt(Position, Position + Front, Up);
    }

    void ProcessKeyboard(CameraMovement direction, f32 deltaTime) {
        const f32 velocity = MovementSpeed * deltaTime;
        if (direction == CameraMovement::FORWARD)
            Position = Position + Front * velocity;
        if (direction == CameraMovement::BACKWARD)
            Position = Position - Front * velocity;
        if (direction == CameraMovement::LEFT)
            Position = Position - Right * velocity;
        if (direction == CameraMovement::RIGHT)
            Position = Position + Right * velocity;
    }

    void ProcessMouseMovement(f32 xoffset, f32 yoffset, b8 constrainPitch = LTRUE) {
        xoffset *= MouseSensitivity;
        yoffset *= MouseSensitivity;

        Yaw += xoffset;
        Pitch += yoffset;

        if (constrainPitch) {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }

        updateCameraVectors();
    }

    void ProcessMouseScroll(f32 yoffset) {
        Zoom -= (f32)yoffset;
        if (Zoom < 1.0f)
            Zoom = 1.0f;
        if (Zoom > 45.0f)
            Zoom = 45.0f;
    }

private:

    void updateCameraVectors() {
        const vec3 front{
            cos(LDEG2RAD(Yaw)) * cos(LDEG2RAD(Pitch)),
            sin(LDEG2RAD(Pitch)),
            sin(LDEG2RAD(Yaw)) * cos(LDEG2RAD(Pitch))
        };
        Front = vec3::normalize(front);

        Right = vec3::normalize(vec3::cross(Front, WorldUp));
        Up = vec3::normalize(vec3::cross(Right, Front));
    }


    vec3 Position{ 0.0f, 0.0f, 0.0f };
    vec3 Front{ 0.0f, 0.0f, -1.0f };
    vec3 Up{ 0.0f, 1.f, 0.0f };
    vec3 Right;
    vec3 WorldUp;

    float Yaw{ YAW };
    float Pitch{ PITCH };

    float MovementSpeed{ SPEED };
    float MouseSensitivity{ SENSITIVITY };
    float Zoom{ ZOOM };

};


}


#endif