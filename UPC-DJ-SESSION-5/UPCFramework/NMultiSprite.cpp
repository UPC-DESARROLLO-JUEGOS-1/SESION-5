#include "NMultiSprite.h"
#include "dtSpriteVertex.h"
#include "NFramework.h"
#include "NMultiSpriteShader.h"

void NMultiSprite::Initialize(float x, float y, float width, float height,
	const std::string path, const std::string bumpPath)
{
	NFramework* framework = NFramework::GET_FRAMEWORK();
	NContentManagment* contentManagment = framework->GetContentManagment();
	NShaderManagment* shaderManagment = framework->GetShaderManagment();

	mBumpTexture = contentManagment->LoadAndGetContent<NImageContent>(bumpPath);

	NSprite::Initialize(x, y, width, height, path);

	const std::string baseShaderPath = "Shaders/MultiSpriteShader";
	mCurrentShader = (NBaseShader*)shaderManagment->LoadAndGetShader<NMultiSpriteShader>(baseShaderPath);
}

void NMultiSprite::Draw(float dt)
{
	// Blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	mCurrentShader->Use();

	GLuint mvpLocation = mCurrentShader->GetUniformLocation("wvp");
	glm::mat4 cameraMatrix = mRenderCamera->GetResultMatrix();
	glm::mat4 resultMatrix = cameraMatrix * mWorldMatrix;

	glUniformMatrix4fv(mvpLocation, 1, GL_FALSE, &(resultMatrix[0][0]));
	
	// We need to explicitly get the uniform location of samplers
	// in multi sprite mode, and then bind them with the correct index.
	GLuint textureLocation = mCurrentShader->GetUniformLocation("sampler");
	GLuint bumpTexLocation = mCurrentShader->GetUniformLocation("sampler2");

	// Then bind the uniform samplers to texture units:
	glUniform1i(textureLocation, 0);
	glUniform1i(bumpTexLocation, 1);

	// Activo la textura 0
	glActiveTexture(GL_TEXTURE0);
	// Hago binding de la textura en GPU 0
	glBindTexture(GL_TEXTURE_2D, mContent->GetTextureID());

	// Activo la textura 1
	glActiveTexture(GL_TEXTURE1);
	// Hago binding de la textura en GPU 
	glBindTexture(GL_TEXTURE_2D, mBumpTexture->GetTextureID());

	glBindBuffer(GL_ARRAY_BUFFER, mVBO_ID);

	glEnableVertexAttribArray(0);

	// Position
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE,
		sizeof(dtSpriteVertex),
		(void*)offsetof(dtSpriteVertex, Position));
	// Color
	glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE,
		sizeof(dtSpriteVertex),
		(void*)offsetof(dtSpriteVertex, Color));
	// UV
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE,
		sizeof(dtSpriteVertex),
		(void*)offsetof(dtSpriteVertex, UV));

	// Esto dibuja en Frame Buffer
	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	mCurrentShader->Unuse();
}
