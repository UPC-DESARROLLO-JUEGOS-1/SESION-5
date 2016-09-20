#include "NImageContent.h"
#include "NContentManagment.h"
#include "PicoPNG.h"
#include "FatalError.h"

NImageContent::NImageContent(NContentManagment* contentManagment) :
	NBaseContent(contentManagment)
{
}

NImageContent::~NImageContent()
{
}

void NImageContent::Initialize(const std::string path)
{
	NBaseContent::Initialize(path);

	// carga el archivo
	std::vector<unsigned char> imageRawBuffer;
	bool loaded = NContentManagment::ReadFileToBuffer(path, imageRawBuffer);
	
	// procesar el PNG
	if (loaded) {
		unsigned long width;
		unsigned long height;

		int errorCode = decodePNG(mImageData, width, height, &(imageRawBuffer[0]),
			imageRawBuffer.size(), true);

		if (errorCode != 0) {
			FatalError("Decodificacion del PNG fallo, codigo de error PicoPNG: " +
				std::to_string(errorCode) + ", en la imagen: " + path);
		}

		glGenTextures(1, &mTextureID);
		glBindTexture(GL_TEXTURE_2D, mTextureID);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
			GL_UNSIGNED_BYTE, &(mImageData[0]));

		glBindTexture(GL_TEXTURE_2D, 0);

		mWidth = width;
		mHeight = height;
	}
}


