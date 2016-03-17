#include "Debug.h"

void debug(LPCWSTR message, ...)
{
	va_list ap;
	va_start(ap, message);

	wchar_t buffer[256];
	wsprintfW(buffer, message, ap);
	va_end(ap);

	OutputDebugString(buffer);
}