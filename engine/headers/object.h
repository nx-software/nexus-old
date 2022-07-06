#ifndef OBJECT_H
#define OBJECT_H
#include "texture.h"
#include <list>

class object{
	public:
		float vertices[180];
		unsigned int* indices[100];
//		texture tex;
		unsigned char *data;
		const char *vertexShaderPath;
		const char *fragShaderPath;
		float x;
		float y;
		float z;
		object(float Basevertices[180],const char *BasevertexShaderPath,const char *BasefragShaderPath,unsigned char *newdata,int x,int y,int z,unsigned int* Baseindices[100]=NULL){ //texture tex): tex(tex){
			unsigned int i;
			std::list<float> nums;
			for(i = 0;i<180;i++){
				vertices[i] = (float)Basevertices[i];
				std::cout<<"i: " <<std::to_string(i) <<" | VERT : " << vertices[i] <<" | SHOULD HAVE BEEN: "<<std::to_string(Basevertices[i]) <<" | LOSS: "<<std::to_string(Basevertices[i]-vertices[i]) <<std::endl;
				nums.push_back(Basevertices[i]-vertices[i]); 
			}
			
			// for(i = 0;i<100;i++){
			// 	indices[i] = Baseindices[i];
			// 	//std::cout<< "IND : " << indices[i] <<std::endl; 
			// }
			vertexShaderPath = BasevertexShaderPath;
			fragShaderPath = BasefragShaderPath;
			//this->tex.data = tex.data;
			data = newdata;
			//std::cout<<"OBJECT DATA: "<<data << std::endl;
			//std::cout<<"OG DATA: "<<newdata << std::endl;
			this->x = x;
			this->y = y;
			this->z = z;
			}
		
};
#endif