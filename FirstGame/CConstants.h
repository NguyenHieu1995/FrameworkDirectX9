#ifndef __CCONSTANTS_H__
#define __CCONSTANTS_H__

//=======================================================================================
// CONSTANT VIRTUAL KEY
//=======================================================================================
/*
* Arrow keys
*/
#define VK_SHIFT			0x10
#define VK_CONTROL			0x11
#define VK_ESCAPE			0x1B
#define VK_SPACE			0x20
#define VK_LEFT				0x25
#define VK_UP				0x26
#define VK_RIGHT			0x27
#define VK_DOWN				0x28

/* 
* VK_0 - VK_9 are the same as ASCII '0' – '9' (0x30 - 0x39) 
* 0x40 : unassigned 
* VK_A - VK_Z are the same as ASCII 'A' – 'Z' (0x41 - 0x5A) 
*/
#define VK_0				0x30
#define VK_1				0x30
#define VK_2				0x30
#define VK_3				0x30
#define VK_4				0x30
#define VK_5				0x30
#define VK_6				0x30
#define VK_7				0x30
#define VK_8				0x30
#define VK_9				0x30

#define VK_A				0x41
#define VK_B				0x42
#define VK_C				0x43
#define VK_D				0x44
#define VK_E				0x45
#define VK_F				0x46
#define VK_G				0x47
#define VK_H				0x48
#define VK_I				0x49
#define VK_J				0x4A
#define VK_K				0x4B
#define VK_L				0x4C
#define VK_M				0x4D
#define VK_N				0x4E
#define VK_O				0x4F
#define VK_P				0x50
#define VK_Q				0x51
#define VK_R				0x52
#define VK_S				0x53
#define VK_T				0x54
#define VK_U				0x55
#define VK_V				0x56
#define VK_W				0x57
#define VK_X				0x58
#define VK_Y				0x59
#define VK_Z				0x5A

/* 
* VK_L* & VK_R*: left and right Alt, Ctrl and Shift virtual keys. 
* Used only as parameters to GetAsyncKeyState() and GetKeyState(). 
* No other API or message will distinguish left and right keys in this way. 
*/
#define VK_LSHIFT			0xA0
#define VK_RSHIFT			0xA1
#define VK_LCONTROL			0xA2
#define VK_RCONTROL			0xA3
#define VK_LMENU			0xA4
#define VK_RMENU			0xA5

#define VK_NUMPAD0			0x60
#define VK_NUMPAD1			0x61
#define VK_NUMPAD2			0x62
#define VK_NUMPAD3			0x63
#define VK_NUMPAD4			0x64
#define VK_NUMPAD5			0x65
#define VK_NUMPAD6			0x66
#define VK_NUMPAD7			0x67
#define VK_NUMPAD8			0x68
#define VK_NUMPAD9			0x69

#define VK_F1				0x70
#define VK_F2				0x71
#define VK_F3				0x72
#define VK_F4				0x73
#define VK_F5				0x74
#define VK_F6				0x75
#define VK_F7				0x76
#define VK_F8				0x77
#define VK_F9				0x78
#define VK_F10				0x79
#define VK_F11				0x7A
#define VK_F12				0x7B

//========================================================================================
//
//========================================================================================

#define BUFSIZE 65535
#define SHIFTED 0x8000



#endif 