#ifndef __MACROS_H__
#define __MACROS_H__

#include "Header.h"

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

#if CONFIG_PLATFORM==PLATFORM_ANDROID
#	include <android/log.h>
#	define  Log(...)  __android_log_print(ANDROID_LOG_INFO, "NativeLib" ,__VA_ARGS__)
#elif CONFIG_PLATFORM==PLATFORM_WIN32_VS
#	define  Log(...)  printf(__VA_ARGS__);printf("\n")
#	define Trace trace
#endif

#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
#	define TODO(x) __pragma(message("[TODO]:" __FILE__ "("TOSTRING(__LINE__)")" TOSTRING(x))); Log(x);
#	define WARNING(x) Log("[WARNING] %s (%s - %s)", x, __FILE__, TOSTRING(__LINE__));
#	define BREAK_IF(cond, _message) if (cond) {Log(_message); _asm int 3}
#	define BREAK(_message) BREAK_IF(true, _message)
#else
#	define TODO(x) ;
#endif

#if CONFIG_PLATFORM==PLATFORM_WIN32_VS
#	define SAFE_RELEASE(ptr)	{ if(ptr) { (ptr)->Release(); (ptr)=NULL; } }
#	define SAFE_DELETE(ptr)	{ if(ptr) {delete(ptr); (ptr)=NULL; } }
#	define SAFE_DEL_ARRAY(a)		{if(a){delete[] (a);(a) = NULL;}}
#	define SAFE_DEL_ARRAY_TYPE(a, t)	{if((t)a){delete[] ((t)(a));(a) = NULL;}}
#	define SAFE_DEL_ARRAY_OBJ(p, n)	{if ((p)!=NULL) {for (int __i = 0; __i < (n); __i++) SAFE_DEL((p)[__i]); SAFE_DEL_ARRAY(p);}}
#	define SAFE_DEL_ARRAY_ARRAY(p, n)	{if ((p)!=NULL) {for (int __i = 0; __i < (n); __i++) SAFE_DEL_ARRAY((p)[__i]); SAFE_DEL_ARRAY(p);}}
#else
#	define TODO(x) ;
#endif 

#endif