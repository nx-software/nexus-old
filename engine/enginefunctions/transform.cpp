#include "../headers/transform.h"
glm::mat4 scale(double x, double y, double z){
    glm::mat4 scaled = glm::mat4(1.0f);
    scaled = glm::scale(scaled,glm::vec3(x,y,z));
    return scaled;
}
glm::mat4 rotate(float radians,double axis1, double axis2, double axis3){
    glm::mat4 rot = glm::mat4(1.0f);
    rot = glm::rotate(rot,glm::radians(radians),glm::vec3(axis1,axis2,axis3));
    return rot;
}
