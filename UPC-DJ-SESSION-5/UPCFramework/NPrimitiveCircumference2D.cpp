#include "NPrimitiveCircumference2D.h"
#include "dtPrimitiveQuadVertex.h"
#include "NShaderManagment.h"
#include "NPrimitiveShader.h"
#include "NFramework.h"
#include "math.h"

#include <iostream>
#include <vector>

#define PI 3.14159265

void NPrimitiveCircumference2D::Initialize(float x, float y, float radius, int vertexCount)
{
	NDrawable2D::Initialize(x, y);

	mRadius = radius;
	mIBO_ID = 0;

	int arraySize = vertexCount + 1;
	float slicedAngle = (PI * 2.0f) / (float)vertexCount;

	dtPrimitiveQuadVertex* vertexData = new dtPrimitiveQuadVertex[arraySize];
	vertexData[0].SetPosition(0, 0);
	vertexData[0].SetColor(255, 255, 255, 255);

	for (int i = 1; i < arraySize; i++)
	{
		float cx = mRadius * sinf(slicedAngle * i);
		float cy = mRadius * cosf(slicedAngle * i);

		vertexData[i].SetPosition(cx, cy);
		vertexData[i].SetColor(255, 255, 255, 255);
	}

	int size = ((sizeof(float) * 2) + (sizeof(GLbyte) * 4)) * arraySize;

	glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID);
	glBufferData(GL_ARRAY_BUFFER, size, &(vertexData[0]), GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	// Now we define the indices
	if (mIBO_ID == 0) {
		glGenBuffers(1, &mIBO_ID);

		int indicesCounter = 0;
		int indicesArraySize = vertexCount * 3; // because each triangle have 3 vertex
		unsigned int* indicesData = new unsigned int[indicesArraySize];

		for (int i = 0; i < indicesArraySize; i += 3)
		{
			indicesData[i] = 0;
			indicesData[i + 1] = (indicesCounter + 1);
			indicesData[i + 2] = (indicesCounter + 2);

			indicesCounter++;
		}
		// Fix the last one
		indicesData[indicesArraySize - 1] = 1;
		// mIndicesCount is the same as indicesArraySize
		mIndicesCount = indicesArraySize;

		int indexDataSize = sizeof(int) * indicesArraySize;

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO_ID);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, indexDataSize, &(indicesData[0]), GL_STATIC_DRAW);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}

	NFramework* framework = NFramework::GET_FRAMEWORK();
	NShaderManagment* shaderManagment = framework->GetShaderManagment();

	const std::string baseShaderPath = "Shaders/Primitive2DShader";
	mCurrentShader = (NBaseShader*)shaderManagment->LoadAndGetShader<NPrimitiveShader>(baseShaderPath);
}

void NPrimitiveCircumference2D::Draw(float dt) {
	mCurrentShader->Use();

	GLuint mvpLocation = mCurrentShader->GetUniformLocation("wvp");
	glm::mat4 cameraMatrix = mRenderCamera->GetResultMatrix();
	glm::mat4 resultMatrix = cameraMatrix * mWorldMatrix;

	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &(resultMatrix[0][0]));

	glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID);

	// Position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(dtPrimitiveQuadVertex), (void*)offsetof(dtPrimitiveQuadVertex, Position));
	// Color
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(dtPrimitiveQuadVertex), (void*)offsetof(dtPrimitiveQuadVertex, Color));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIBO_ID);
	
	// Esto dibuja en Frame Buffer
	glDrawElements(GL_TRIANGLES, mIndicesCount, GL_UNSIGNED_INT, (void*)0);
	//glDrawArrays(GL_TRIANGLES, 0, mIndicesCount);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glDisableVertexAttribArray(0);

	mCurrentShader->Unuse();
}
