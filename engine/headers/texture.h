#ifndef TEXTURE_H
#define TEXTURE_H
#include "stb_image.h"
class texture{
    public:
        unsigned char *data;
        texture(const char* name,int width, int height, int nrChannels){
            data = stbi_load(name, &width, &height, &nrChannels, 0); 
            //std::cout<<data <<std::endl;;
        }
};
#endif