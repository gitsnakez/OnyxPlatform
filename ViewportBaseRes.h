#pragma once

enum VPFALGS
{
	NOFLAGS = 0x1111,
	NOBORDERS = 0x0111,
	NOMINIMIZE = 0x1011,
	NOMAXIMIZE = 0x1101,
	NOCLOSE = 0x1110
};

/// <summary>
/// Viewport Handle
/// </summary>
typedef void* VPH;

struct VEC2D
{
public:
	unsigned short int1;
	unsigned short int2;
};

/// <summary>
/// Viewport description for initialization. General info.
/// </summary>
struct VPDESC
{
public:
	char Title[48];
	VEC2D Location;
	VEC2D Size;
	unsigned short Flags;
};

/// <summary>
/// Viewport description for styling appearance.
/// </summary>
struct VPADESC
{

};

/// <summary>
/// Viewport description for extra(additional) properties.
/// </summary>
struct VPEXDESC
{

};