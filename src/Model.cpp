#include "Model.h"

#include <stdio.h>

Model::Model(const float *data, int sizeOfData, GLenum drawType, ModelDataLayout modelDataLayout) 
 : gl_drawType(drawType), modelLayout(modelDataLayout), dataSize(sizeOfData)
{

	//vertex buffer object (VBO)
	glGenBuffers(1, &VBO); // generate the VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //Vertex Array Object (VAO)
	glGenVertexArrays(1, &VAO); //generate the VAO
	glBindVertexArray(VAO); //bind the VAO

    switch(modelLayout)
    {
        case ModelDataLayout::L_3COORD3NORMAL:
            glEnableVertexAttribArray(0); //enable vertex attributes
            glEnableVertexAttribArray(1);
            glBindBuffer(GL_ARRAY_BUFFER, VBO); //bind bound vertex array (VAO) to buffer to read
            
            // index, number of components, data type, normalized, vertex stride, offset
            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)0);
            glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
            break;
        default:
            printf("error creating model, invalid model type!\n");
            exit(EXIT_FAILURE);
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void Model::bindVAO()
{ glBindVertexArray(VAO); }

/*(static)*/ void Model::unbindVAO()
{ glBindVertexArray(0); }