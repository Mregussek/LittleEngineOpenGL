
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
    vec3 front{ 0.f, 0.f, -1.f };
    vec3 worldUp{ 0.f, 1.f, 0.f };

    f32 yaw{ -90.f };
    f32 pitch{ 0.0f };
    f32 movementSpeed{ 2.5f };
    f32 sensitivity{ 0.1f };
    f32 zoom{ 45.0f };
    f32 far{ 100.f };
    f32 near{ 0.1f };

    f32 aspectRatio{ 1.333f };

};


class Camera {
public:

    void init(CameraSpecification _camSpecs);

    mat4 getModelMartix() const;
    mat4 getViewMatrix() const;
    mat4 getProjectionMatrix() const;
    vec3 getPositionVec() const;

    void processKeyboard(CameraMovement direction, f32 deltaTime);
    void processMouseMovement(f32 xoffset, f32 yoffset, b8 constrainPitch = LTRUE);
    void processMouseScroll(f32 yoffset);

public:

    void updateCameraVectors();


    CameraSpecification mCameraSpecs;
    vec3 mUp{};
    vec3 mRight{};

};


}


#endif