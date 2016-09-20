#pragma once

#include <map>
#include <vector>
#include <iostream>
#include <type_traits>

#include "NBaseContent.h"

class NImageContent;
class NFramework;

class NContentManagment
{
public:
	NContentManagment(NFramework* framework) { mFramework = framework; }
	~NContentManagment();

	void Initialize();

	template<typename T>
	T* LoadAndGetContent(const std::string path) {
		std::map<std::string, NBaseContent*>::iterator mit = mContents.find(path);
		T* result = mit != mContents.end() ? (T*)mit->second : nullptr;

		if (result == nullptr) {
			result = new T(this);
			result->Initialize(path);

			// Ahora insertamos en el mapa(diccionario)
			mContents.insert(std::make_pair(path, result));

			std::cout << "Loaded content: " << path << std::endl;
		}

		return result;
	}

	static bool ReadFileToBuffer(const std::string path, 
		std::vector<unsigned char>& buffer);
private:
	NFramework* mFramework;
	std::map<std::string, NBaseContent*> mContents;

	NBaseContent* GetContent(const std::string path) {
		std::map<std::string, NBaseContent*>::iterator mit = mContents.find(path);

		if (mit == mContents.end()) {
			std::cout << "Not found content in path: " << path << std::endl;
			return nullptr;
		}
		
		return mit->second;
	}
};

