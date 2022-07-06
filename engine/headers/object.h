#ifndef OBJECT_H
#define OBJECT_H
#include "texture.h"
class object{
	public:
		float vertices[180];
		unsigned int* indices[100];
//		texture tex;
		unsigned char *data;
		const char *vertexShaderPath;
		const char *fragShaderPath;
		object(float Basevertices[180],const char *BasevertexShaderPath,const char *BasefragShaderPath,unsigned char *newdata,unsigned int* Baseindices[100]=NULL){ //texture tex): tex(tex){
			unsigned int i;
			for(i = 0;i<180;i++){
				vertices[i] = Basevertices[i];
				//std::cout<< "VERT : " << vertices[i] <<std::endl; 
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

			}
		
};
#endif