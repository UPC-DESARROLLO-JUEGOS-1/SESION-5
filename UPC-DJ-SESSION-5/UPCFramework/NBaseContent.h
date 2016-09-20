#pragma once

#include <string>

class NContentManagment;

class NBaseContent
{
public:
	NBaseContent(NContentManagment* contentManagment) {
		mContentManagment = contentManagment;
	}
	~NBaseContent();

	virtual void Initialize(const std::string path);

	NContentManagment* GetContentManagment() { return mContentManagment; }
private:
	std::string mPath;
	NContentManagment* mContentManagment;
};

