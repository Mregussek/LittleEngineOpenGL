
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


struct CameraSpecification {

    vec3 position{ 0.f, 0.f, 0.f };
    vec3 up{ 0.f, 1.f, 0.f };
    vec3 front{ 0.f, 0.f, -1.f };

    f32 yaw{ -90.f };
    f32 pitch{ 0.0f };
    f32 movementSpeed{ 2.5f };
    f32 sensitivity{ 0.1f };
    f32 zoom{ 45.0f };

    f32 aspectRatio{ 1.333f };

};


class Camera {
public:

    void init(CameraSpecification _camSpecs) {
        camSpecs = _camSpecs;
        Position = camSpecs.position;
        Front = camSpecs.front;
        Up = camSpecs.up;
        Yaw = camSpecs.yaw;
        Pitch = camSpecs.pitch;
        MovementSpeed = camSpecs.movementSpeed;
        MouseSensitivity = camSpecs.sensitivity;
        Zoom = camSpecs.zoom;
        aspectRatio = camSpecs.aspectRatio;
        updateCameraVectors();
    }

    mat4 GetViewMatrix() {
        return mat4::lookAt(Position, Position + Front, Up);
    }

    mat4 GetProjectionMatrix() {
        return mat4::perspective(LDEG2RAD(Zoom), aspectRatio, 0.1f, 100.0f);
    }

    void ProcessKeyboard(CameraMovement direction, f32 deltaTime) {
        const f32 velocity = MovementSpeed * deltaTime;
        if (direction == CameraMovement::FORWARD) {
            Position = Position + Front * velocity;
        }
        else if (direction == CameraMovement::BACKWARD) {
            Position = Position - Front * velocity;
        }
        if (direction == CameraMovement::LEFT) {
            Position = Position - Right * velocity;
        }
        else if (direction == CameraMovement::RIGHT) {
            Position = Position + Right * velocity;
        }
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
        if (Zoom < 1.0f) {
            Zoom = 1.0f;
        }
        else if (Zoom > 45.0f) {
            Zoom = 45.0f;
        }
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


    CameraSpecification camSpecs;

    vec3 Position;
    vec3 Front;
    vec3 Up;
    vec3 Right;
    vec3 WorldUp;

    f32 Yaw;
    f32 Pitch;

    f32 MovementSpeed;
    f32 MouseSensitivity;
    f32 Zoom;

    f32 aspectRatio;

};


}


#endif