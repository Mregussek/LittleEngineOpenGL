
#include "Camera.h"


namespace le
{

void Camera::init(CameraSpecification _camSpecs) {
    mCameraSpecs = _camSpecs;
    updateCameraVectors();
}


mat4 Camera::getModelMartix() const {
    return mat4::identity();
}


mat4 Camera::getViewMatrix() const {
    return mat4::lookAt(mCameraSpecs.position,
                        mCameraSpecs.position + mCameraSpecs.front,
                        mUp);
}


mat4 Camera::getProjectionMatrix() const {
    return mat4::perspective(LDEG2RAD(mCameraSpecs.zoom),
                             mCameraSpecs.aspectRatio,
                             mCameraSpecs.near,
                             mCameraSpecs.far);
}


vec3 Camera::getPositionVec() const {
    return mCameraSpecs.position;
}


void Camera::processKeyboard(CameraMovement direction, f32 deltaTime) {
    const f32 velocity{ mCameraSpecs.movementSpeed * deltaTime };
    if (direction == CameraMovement::FORWARD) {
        mCameraSpecs.position = mCameraSpecs.position + mCameraSpecs.front * velocity;
    }
    else if (direction == CameraMovement::BACKWARD) {
        mCameraSpecs.position = mCameraSpecs.position - mCameraSpecs.front * velocity;
    }
    if (direction == CameraMovement::LEFT) {
        mCameraSpecs.position = mCameraSpecs.position - mRight * velocity;
    }
    else if (direction == CameraMovement::RIGHT) {
        mCameraSpecs.position = mCameraSpecs.position + mRight * velocity;
    }
}


void Camera::processMouseMovement(f32 xoffset, f32 yoffset, b8 constrainPitch) {
    xoffset *= mCameraSpecs.sensitivity;
    yoffset *= mCameraSpecs.sensitivity;

    mCameraSpecs.yaw += xoffset;
    mCameraSpecs.pitch += yoffset;

    if (constrainPitch) {
        if (mCameraSpecs.pitch > 89.0f)
            mCameraSpecs.pitch = 89.0f;
        if (mCameraSpecs.pitch < -89.0f)
            mCameraSpecs.pitch = -89.0f;
    }

    updateCameraVectors();
}


void Camera::processMouseScroll(f32 yoffset) {
    mCameraSpecs.zoom -= (f32)yoffset;
    if (mCameraSpecs.zoom < 1.0f) {
        mCameraSpecs.zoom = 1.0f;
    }
    else if (mCameraSpecs.zoom > 45.0f) {
        mCameraSpecs.zoom = 45.0f;
    }
}


void Camera::updateCameraVectors() {
    const f32 yaw{ mCameraSpecs.yaw };
    const f32 pitch{ mCameraSpecs.pitch };
    const vec3 front{
        cos(LDEG2RAD(yaw)) * cos(LDEG2RAD(pitch)),
        sin(LDEG2RAD(pitch)),
        sin(LDEG2RAD(yaw)) * cos(LDEG2RAD(pitch))
    };
    mCameraSpecs.front = vec3::normalize(front);
    mRight = vec3::normalize(vec3::cross(mCameraSpecs.front, mCameraSpecs.worldUp));
    mUp = vec3::normalize(vec3::cross(mRight, mCameraSpecs.front));
}


}
