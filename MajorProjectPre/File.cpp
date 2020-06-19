#include "File.h"

#pragma region Constructors

File::File() {}

File::File(const char* fileName) : fileName(fileName) {}

#pragma endregion

#pragma region Properties

void File::SetName(const char* value) { fileName = value; }

void File::SetFile(FILE* file) { this->file = file; }

FILE* File::GetFile() { return file; }

const char* File::GetName() { return fileName; }

#pragma endregion


