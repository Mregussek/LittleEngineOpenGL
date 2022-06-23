
#include "path.h"
#include <filesystem>


namespace le
{


b8 Path::exists(const char* path) {
	std::filesystem::path p{ path };
	if (std::filesystem::exists(p)) {
		return LTRUE;
	}
	else {
		return LFALSE;
	}
}


b8 Path::readFile(const char* path, std::string* pOutput) {
	if (!Path::exists(path)) {
		LLOG("Couldnt load file!");
		return LFALSE;
	}

	FILE* file;
	fopen_s(&file, path, "rb");
	fseek(file, 0, SEEK_END);
	const long length = ftell(file);
	fseek(file, 0, SEEK_SET);
	pOutput->resize(length);
	const size_t rc = fread(pOutput->data(), 1, length, file);
	fclose(file);

	if (rc == length) {
		LLOG("Loaded file:\n" + *pOutput + "\n");
		return LTRUE;
	}
	else {
		LLOG("Couldnt load file!");
		return LFALSE;
	}
}


}
