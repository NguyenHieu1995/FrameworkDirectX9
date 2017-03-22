#ifndef __HEADER_H__
#define __HEADER_H__

#define PLATFORM_WIN32_VS	1
#define PLATFORM_ANDROID	2

#include "Config.h"

#include <stdio.h>

#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
#	include <windows.h>
#	include <time.h>
#	include <d3d9.h>
#	include <d3dx9.h>
#endif

#include "Macros.h"
#include "CConstants.h"

#if (CONFIG_PLATFORM==PLATFORM_WIN32_VS) || (CONFIG_PLATFORM==PLATFORM_ANDROID)
typedef unsigned long long	__UINT64;
typedef long long			__INT64;
typedef int					__INT32;
typedef unsigned int		__UINT32;
typedef signed short		__INT16;
typedef unsigned short		__UINT16;
typedef signed char			__INT8;
typedef unsigned char		__UINT8;
#endif

#if (CONFIG_PLATFORM==PLATFORM_WIN32_VS)
#	define		VIEWCLASS	CVSView
#else
#	define		VIEWCLASS	
#endif

#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
int __cdecl trace(const char *format, ...);
#endif

#endif