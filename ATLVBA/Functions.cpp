#include "ATLVBA_i.h"
//#include <string.h>
#include <windows.h>

// Экспортируемые функции
int memCmp(const void* buf1, const void* buf2, size_t Size) {
	return memcmp(buf1, buf2, Size);
}
void* memCpy(void* dst, const void* src, size_t sz) {
	return memcpy(dst, src, sz);
}
