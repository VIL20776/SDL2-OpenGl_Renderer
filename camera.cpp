#include "camera.hpp"
#include <glm/ext/matrix_transform.hpp>
#include <glm/fwd.hpp>
#include <glm/gtx/transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 rotation)
{
    this->position = position;
    this->rotation = rotation;

    target = {0, 0, 0};
}

glm::mat4 Camera::createViewMatrix()
{
    if (target != glm::vec3(0,0,0)) {
        return glm::lookAt(position, target, {0, 1, 0});
    }
    
    using glm::mat4;
	
	mat4 identity = glm::mat4(1);
	mat4 translateMat = glm::translate(identity, position);
	
	mat4 pitch = glm::rotate(identity, glm::radians(rotation.x), {1, 0, 0});
	mat4 yaw = glm::rotate(identity, glm::radians(rotation.y), {0, 1, 0});
	mat4 roll = glm::rotate(identity, glm::radians(rotation.z), {0, 0, 1});
	
	mat4 rotationMat = pitch * yaw * roll;
	
	mat4 camMatrix = translateMat * rotationMat;
	
	return glm::inverse(camMatrix);
}

void Camera::setTarget(const glm::vec3 target)
{
    this->target = target;
    this->targetDistance = glm::length(target - position);
    minDistance = targetDistance - 5;
    maxDistance = targetDistance + 5;
}
    
void Camera::setPosition(const glm::vec3 position)
{
    //Check distance
    float targetDistance = glm::length(target - position);
    if (targetDistance < minDistance || targetDistance > maxDistance) 
        return;
        
    this->targetDistance = targetDistance;
    this->position = position;
}

glm::vec3 Camera::getPosition() { return position;}


