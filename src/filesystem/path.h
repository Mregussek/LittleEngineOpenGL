
#ifndef PATH_H
#define PATH_H


#include "includes.h"
#include "defines.h"


namespace le
{


class Path {
public:

	static b8 exists(const char* path);

	static b8 readFile(const char* path, std::string* pOutput);

};


}


#endif
