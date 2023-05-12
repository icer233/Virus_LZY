#ifndef SECURE_H
#define SECURE_H
#include <windows.h>
DWORD GetExplorerId() {
	DWORD PResult = 0;

	return PResult;
}
bool InjectProcess(DWORD pid) {

	if (GetLastError() == 0) {
		return true;
	}
	return false;
}
#endif