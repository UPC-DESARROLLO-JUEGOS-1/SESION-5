#include "NPrimitiveQuad.h"
#include "dtPrimitiveQuadVertex.h"
#include "NFramework.h"
#include "NShaderManagment.h"
#include "NPrimitiveShader.h"

void NPrimitiveQuad::Initialize(float x, float y, float width, float height) {
	NDrawable2D::Initialize(x, y);
	
	mWidth = width;
	mHeight = height;

	NFramework* framework = NFramework::GET_FRAMEWORK();
	NShaderManagment* shaderManagment = framework->GetShaderManagment();

	const std::string baseShaderPath = "Shaders/Primitive2DShader";
	mCurrentShader = (NBaseShader*)shaderManagment->LoadAndGetShader<NPrimitiveShader>(baseShaderPath);

	dtPrimitiveQuadVertex* vertexData = new dtPrimitiveQuadVertex[6];
	// primer triangulo
	vertexData[0].SetPosition(mWidth, mHeight);
	vertexData[1].SetPosition(0, mHeight);
	vertexData[2].SetPosition(0, 0);
	// segundo triangulo
	vertexData[3].SetPosition(0, 0);
	vertexData[4].SetPosition(mWidth, 0);
	vertexData[5].SetPosition(mWidth, mHeight);

	// colores
	vertexData[0].SetColor(255, 0, 255, 255);
	vertexData[1].SetColor(255, 255, 0, 255);
	vertexData[2].SetColor(0, 0, 255, 255);
	vertexData[3].SetColor(0, 0, 255, 255);
	vertexData[4].SetColor(125, 80, 60, 255);
	vertexData[5].SetColor(255, 0, 255, 255);
	
	int size = ((sizeof(float) * 2) + (sizeof(GLbyte) * 4)) * 6;

	glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID);
	glBufferData(GL_ARRAY_BUFFER, size, &vertexData[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void NPrimitiveQuad::Draw(float dt) {
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
	// Esto dibuja en Frame Buffer
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	mCurrentShader->Unuse();
}