#include <fstream>

#include "NContentManagment.h"
#include "NFramework.h"
#include "NImageContent.h"

NContentManagment::~NContentManagment()
{
	
}

void NContentManagment::Initialize()
{

}

bool NContentManagment::ReadFileToBuffer(const std::string path,
	std::vector<unsigned char>& buffer)
{
	std::ifstream file(path, std::ios::binary);

	if (file.fail()) {
		perror(path.c_str());
		return false;
	}

	// leer del inicio al final
	file.seekg(0, std::ios::end);
	// necesito tamanio del archivo
	int fileSize = file.tellg();
	file.seekg(0, std::ios::beg);

	// reducir el tamanio debido al header del archivo
	fileSize -= file.tellg();

	buffer.resize(fileSize);
	file.read((char *)&(buffer[0]), fileSize);
	file.close();

	return true;
}