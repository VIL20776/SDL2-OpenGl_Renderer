#include <glm/fwd.hpp>
#include <glm/glm.hpp>

class Camera
{
    public:
    Camera (glm::vec3 position, glm::vec3 rotation);
    glm::mat4 createViewMatrix();
    void setTarget (glm::vec3 target);
    void setPosition (glm::vec3 position);
    void setPosition (float g);
    glm::vec3 getPosition();
    float getAngle();
    glm::vec3 getForwardv();

    private:
    glm::vec3 position;
    glm::vec3 rotation;


    glm::vec3 target;
    float angle;
    float targetDistance;
    float maxDistance, minDistance;

};