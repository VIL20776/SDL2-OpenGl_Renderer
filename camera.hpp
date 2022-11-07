#include <glm/glm.hpp>

class Camera
{
    public:
    Camera (glm::vec3 position, glm::vec3 rotation);
    void setTarget (glm::vec3 target);
    void setPosition (glm::vec3 newPosition);
    glm::vec3 getPosition();

    private:
    glm::vec3 position;
    glm::vec3 rotation;

    glm::mat4 viewMatrix;
    glm::mat4 projectionMatrix;

    glm::vec3 target;
    float angle;
    float camDistance;
    float zoomRange;
    float YaxisRange;

    glm::mat4 createViewMatrix();
};