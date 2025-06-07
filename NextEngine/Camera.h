#pragma once

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

/**
 * @class Camera
 * @brief Represents a 2D camera for view transformations using glm.
 *
 * Manages camera position, target, and orientation, and computes a view matrix
 * for rendering scenes from the camera's perspective.
 */
class Camera {
private:
    glm::vec3 position;  ///< Camera position in world space
    glm::vec3 target;    ///< Target point the camera is looking at
    glm::vec3 up;        ///< Up direction of the camera

public:
    /**
     * @brief Default constructor.
     * Initializes the camera with default position, target, and up vector.
     */
    Camera();

    /**
     * @brief Constructor with perspective settings.
     * @param fov Field of view in degrees.
     * @param aspect Aspect ratio of the view.
     * @param near Near clipping plane distance.
     * @param far Far clipping plane distance.
     */
    Camera(float fov, float aspect, float near, float far) {}

    /**
     * @brief Sets the camera's position.
     * @param pos The new position as a vec3.
     */
    void setPosition(const glm::vec3& pos);

    /**
     * @brief Sets the camera's target (look-at point).
     * @param targetPos The new target position.
     */
    void setTarget(const glm::vec3& targetPos);

    /**
     * @brief Gets the current camera position.
     * @return The position vector.
     */
    glm::vec3 getPosition() const;

    /**
     * @brief Gets the current camera target point.
     * @return The target vector.
     */
    glm::vec3 getTarget() const;  

    /**
     * @brief Computes the view matrix based on current camera vectors.
     * @return A 4x4 view matrix.
     */
    glm::mat4 getViewMatrix();

    /**
     * @brief Moves the camera left by a given distance.
     * @param distance Amount to move.
     */
    void moveLeft(float distance);

    /**
     * @brief Moves the camera right by a given distance.
     * @param distance Amount to move.
     */
    void moveRight(float distance);

    /**
     * @brief Moves the camera up by a given distance.
     * @param distance Amount to move.
     */
    void moveUp(float distance);

    /**
     * @brief Moves the camera down by a given distance.
     * @param distance Amount to move.
     */
    void moveDown(float distance);
};
