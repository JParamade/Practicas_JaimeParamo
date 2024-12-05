#include <iostream>
#include "FileUtils.h"

void* OpenFile(const char* _sFileName, const char* _sMode) {
	std::FILE* pFile = nullptr;
	fopen_s(&pFile, _sFileName, _sMode);

	return pFile;
}

bool CloseFile(void* _pFile) {
	std::FILE* pFile = reinterpret_cast<std::FILE*> (_pFile);
	int iResult = fclose(pFile);

	return iResult == 0;
}

size_t ReadFile(char* _pBuffer, unsigned int _uSize, void* _pFile) {
	std::FILE* pFile = reinterpret_cast<std::FILE*> (_pFile);

	return fread(_pBuffer, sizeof(char), _uSize, pFile);
}

size_t WriteFile(char* _pBuffer, unsigned int _uSize, void* _pFile) {
	std::FILE* pFile = reinterpret_cast<std::FILE*> (_pFile);

	return fwrite(_pBuffer, sizeof(char), _uSize, pFile);
}

unsigned int CheckStringCount(char* _pBuffer, unsigned int _uSize, const char* _sString, void* _pFile) {
	std::FILE* pFile = reinterpret_cast<std::FILE*> (_pFile);
	
	for (unsigned int uIndex = 0; uIndex < _uSize; uIndex++) {

	}

	return 0;
}

unsigned int GetIntegerSum(char* _pBuffer, unsigned int _uSize, void* _pFile) {
	std::FILE* pFile = reinterpret_cast<std::FILE*> (_pFile);
	
	unsigned int uSum = 0;
	unsigned int uAccumulator = 0;
	bool bIsLastNumber = false;

	for (unsigned int uIndex = 0; uIndex < _uSize; uIndex++) {
		if (_pBuffer[uIndex] >= 48 && _pBuffer[uIndex] <= 57) {
			bIsLastNumber = true;
			uAccumulator = uAccumulator * 10 + (_pBuffer[uIndex] - '0');
		}
		else if (_pBuffer[uIndex] == ',') {
			uSum += uAccumulator;
			bIsLastNumber = false;
			uAccumulator = 0;
		}
		else if (bIsLastNumber) {
			uSum += uAccumulator;
			uAccumulator = 0;
		}
		else uAccumulator = 0;
	}

	return uSum;
}