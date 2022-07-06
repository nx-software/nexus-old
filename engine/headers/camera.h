#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
#ifndef CAMERA_H
#define CAMERA_H
class Camera{
    public:
    glm::vec3 pos;
    glm::vec3 target;
    glm::vec3 direction;
    glm::vec3 up;
    glm::vec3 cameraRight;
    //glm::vec3 up;
    glm::vec3 front;
    Camera(glm::vec3 campos,glm::vec3 camtarget,glm::vec3 camdirection,glm::vec3 camup,glm::vec3 camfront){
        pos = campos;
        target = camtarget;
        direction = camdirection;
        up = camup;
        cameraRight = glm::normalize(glm::cross(up,direction));
        front = camfront;
        //up = glm::cross(direction,cameraRight);
    }

    void updatePostion(glm::vec3 newpos){
        pos = newpos;
    }
    void updateTarget(glm::vec3 newtarget){
        target = newtarget;
    }
    void updateDirection(glm::vec3 newdirection){
        direction = newdirection;
        //up = glm::cross(direction,cameraRight);
    }
};
#endif