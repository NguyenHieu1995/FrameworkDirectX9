#include "Header.h"

int __cdecl trace(const char *format, ...)
{
	char str[1024];

	va_list argptr;
	va_start(argptr, format);
	int ret = vsnprintf_s(str, sizeof(str), format, argptr);
	va_end(argptr);

	OutputDebugString(str);

	return ret;
}