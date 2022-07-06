#include "../../glm/glm.hpp"
#include "../../glm/gtc/matrix_transform.hpp"
#include "../../glm/gtc/type_ptr.hpp"
#ifndef TRANSFORM_H
#define TRANSFORM_H
glm::mat4 scale(double x, double y, double z);
glm::mat4 rotate(float radians,double axis1, double axis2, double axis3);
#endif