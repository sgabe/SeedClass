#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include "bt.h"

enum RecordType_enum : DWORD {
	EMR_HEADER = (DWORD) 0x00000001,
	EMR_POLYBEZIER = (DWORD) 0x00000002,
	EMR_POLYGON = (DWORD) 0x00000003,
	EMR_POLYLINE = (DWORD) 0x00000004,
	EMR_POLYBEZIERTO = (DWORD) 0x00000005,
	EMR_POLYLINETO = (DWORD) 0x00000006,
	EMR_POLYPOLYLINE = (DWORD) 0x00000007,
	EMR_POLYPOLYGON = (DWORD) 0x00000008,
	EMR_SETWINDOWEXTEX = (DWORD) 0x00000009,
	EMR_SETWINDOWORGEX = (DWORD) 0x0000000A,
	EMR_SETVIEWPORTEXTEX = (DWORD) 0x0000000B,
	EMR_SETVIEWPORTORGEX = (DWORD) 0x0000000C,
	EMR_SETBRUSHORGEX = (DWORD) 0x0000000D,
	EMR_EOF = (DWORD) 0x0000000E,
	EMR_SETPIXELV = (DWORD) 0x0000000F,
	EMR_SETMAPPERFLAGS = (DWORD) 0x00000010,
	EMR_SETMAPMODE = (DWORD) 0x00000011,
	EMR_SETBKMODE = (DWORD) 0x00000012,
	EMR_SETPOLYFILLMODE = (DWORD) 0x00000013,
	EMR_SETROP2 = (DWORD) 0x00000014,
	EMR_SETSTRETCHBLTMODE = (DWORD) 0x00000015,
	EMR_SETTEXTALIGN = (DWORD) 0x00000016,
	EMR_SETCOLORADJUSTMENT = (DWORD) 0x00000017,
	EMR_SETTEXTCOLOR = (DWORD) 0x00000018,
	EMR_SETBKCOLOR = (DWORD) 0x00000019,
	EMR_OFFSETCLIPRGN = (DWORD) 0x0000001A,
	EMR_MOVETOEX = (DWORD) 0x0000001B,
	EMR_SETMETARGN = (DWORD) 0x0000001C,
	EMR_EXCLUDECLIPRECT = (DWORD) 0x0000001D,
	EMR_INTERSECTCLIPRECT = (DWORD) 0x0000001E,
	EMR_SCALEVIEWPORTEXTEX = (DWORD) 0x0000001F,
	EMR_SCALEWINDOWEXTEX = (DWORD) 0x00000020,
	EMR_SAVEDC = (DWORD) 0x00000021,
	EMR_RESTOREDC = (DWORD) 0x00000022,
	EMR_SETWORLDTRANSFORM = (DWORD) 0x00000023,
	EMR_MODIFYWORLDTRANSFORM = (DWORD) 0x00000024,
	EMR_SELECTOBJECT = (DWORD) 0x00000025,
	EMR_CREATEPEN = (DWORD) 0x00000026,
	EMR_CREATEBRUSHINDIRECT = (DWORD) 0x00000027,
	EMR_DELETEOBJECT = (DWORD) 0x00000028,
	EMR_ANGLEARC = (DWORD) 0x00000029,
	EMR_ELLIPSE = (DWORD) 0x0000002A,
	EMR_RECTANGLE = (DWORD) 0x0000002B,
	EMR_ROUNDRECT = (DWORD) 0x0000002C,
	EMR_ARC = (DWORD) 0x0000002D,
	EMR_CHORD = (DWORD) 0x0000002E,
	EMR_PIE = (DWORD) 0x0000002F,
	EMR_SELECTPALETTE = (DWORD) 0x00000030,
	EMR_CREATEPALETTE = (DWORD) 0x00000031,
	EMR_SETPALETTEENTRIES = (DWORD) 0x00000032,
	EMR_RESIZEPALETTE = (DWORD) 0x00000033,
	EMR_REALIZEPALETTE = (DWORD) 0x00000034,
	EMR_EXTFLOODFILL = (DWORD) 0x00000035,
	EMR_LINETO = (DWORD) 0x00000036,
	EMR_ARCTO = (DWORD) 0x00000037,
	EMR_POLYDRAW = (DWORD) 0x00000038,
	EMR_SETARCDIRECTION = (DWORD) 0x00000039,
	EMR_SETMITERLIMIT = (DWORD) 0x0000003A,
	EMR_BEGINPATH = (DWORD) 0x0000003B,
	EMR_ENDPATH = (DWORD) 0x0000003C,
	EMR_CLOSEFIGURE = (DWORD) 0x0000003D,
	EMR_FILLPATH = (DWORD) 0x0000003E,
	EMR_STROKEANDFILLPATH = (DWORD) 0x0000003F,
	EMR_STROKEPATH = (DWORD) 0x00000040,
	EMR_FLATTENPATH = (DWORD) 0x00000041,
	EMR_WIDENPATH = (DWORD) 0x00000042,
	EMR_SELECTCLIPPATH = (DWORD) 0x00000043,
	EMR_ABORTPATH = (DWORD) 0x00000044,
	EMR_RESERVED_69 = (DWORD) 0x00000045,
	EMR_COMMENT = (DWORD) 0x00000046,
	EMR_FILLRGN = (DWORD) 0x00000047,
	EMR_FRAMERGN = (DWORD) 0x00000048,
	EMR_INVERTRGN = (DWORD) 0x00000049,
	EMR_PAINTRGN = (DWORD) 0x0000004A,
	EMR_EXTSELECTCLIPRGN = (DWORD) 0x0000004B,
	EMR_BITBLT = (DWORD) 0x0000004C,
	EMR_STRETCHBLT = (DWORD) 0x0000004D,
	EMR_MASKBLT = (DWORD) 0x0000004E,
	EMR_PLGBLT = (DWORD) 0x0000004F,
	EMR_SETDIBITSTODEVICE = (DWORD) 0x00000050,
	EMR_STRETCHDIBITS = (DWORD) 0x00000051,
	EMR_EXTCREATEFONTINDIRECTW = (DWORD) 0x00000052,
	EMR_EXTTEXTOUTA = (DWORD) 0x00000053,
	EMR_EXTTEXTOUTW = (DWORD) 0x00000054,
	EMR_POLYBEZIER16 = (DWORD) 0x00000055,
	EMR_POLYGON16 = (DWORD) 0x00000056,
	EMR_POLYLINE16 = (DWORD) 0x00000057,
	EMR_POLYBEZIERTO16 = (DWORD) 0x00000058,
	EMR_POLYLINETO16 = (DWORD) 0x00000059,
	EMR_POLYPOLYLINE16 = (DWORD) 0x0000005A,
	EMR_POLYPOLYGON16 = (DWORD) 0x0000005B,
	EMR_POLYDRAW16 = (DWORD) 0x0000005C,
	EMR_CREATEMONOBRUSH = (DWORD) 0x0000005D,
	EMR_CREATEDIBPATTERNBRUSHPT = (DWORD) 0x0000005E,
	EMR_EXTCREATEPEN = (DWORD) 0x0000005F,
	EMR_POLYTEXTOUTA = (DWORD) 0x00000060,
	EMR_POLYTEXTOUTW = (DWORD) 0x00000061,
	EMR_SETICMMODE = (DWORD) 0x00000062,
	EMR_CREATECOLORSPACE = (DWORD) 0x00000063,
	EMR_SETCOLORSPACE = (DWORD) 0x00000064,
	EMR_DELETECOLORSPACE = (DWORD) 0x00000065,
	EMR_GLSRECORD = (DWORD) 0x00000066,
	EMR_GLSBOUNDEDRECORD = (DWORD) 0x00000067,
	EMR_PIXELFORMAT = (DWORD) 0x00000068,
	EMR_DRAWESCAPE = (DWORD) 0x00000069,
	EMR_EXTESCAPE = (DWORD) 0x0000006A,
	EMR_RESERVED_107 = (DWORD) 0x0000006B,
	EMR_SMALLTEXTOUT = (DWORD) 0x0000006C,
	EMR_FORCEUFIMAPPING = (DWORD) 0x0000006D,
	EMR_NAMEDESCAPE = (DWORD) 0x0000006E,
	EMR_COLORCORRECTPALETTE = (DWORD) 0x0000006F,
	EMR_SETICMPROFILEA = (DWORD) 0x00000070,
	EMR_SETICMPROFILEW = (DWORD) 0x00000071,
	EMR_ALPHABLEND = (DWORD) 0x00000072,
	EMR_SETLAYOUT = (DWORD) 0x00000073,
	EMR_TRANSPARENTBLT = (DWORD) 0x00000074,
	EMR_RESERVED_117 = (DWORD) 0x00000075,
	EMR_GRADIENTFILL = (DWORD) 0x00000076,
	EMR_SETLINKEDUFIS = (DWORD) 0x00000077,
	EMR_SETTEXTJUSTIFICATION = (DWORD) 0x00000078,
	EMR_COLORMATCHTOTARGETW = (DWORD) 0x00000079,
	EMR_CREATECOLORSPACEW = (DWORD) 0x0000007A,
};
std::vector<DWORD> RecordType_enum_values = { EMR_HEADER, EMR_POLYBEZIER, EMR_POLYGON, EMR_POLYLINE, EMR_POLYBEZIERTO, EMR_POLYLINETO, EMR_POLYPOLYLINE, EMR_POLYPOLYGON, EMR_SETWINDOWEXTEX, EMR_SETWINDOWORGEX, EMR_SETVIEWPORTEXTEX, EMR_SETVIEWPORTORGEX, EMR_SETBRUSHORGEX, EMR_EOF, EMR_SETPIXELV, EMR_SETMAPPERFLAGS, EMR_SETMAPMODE, EMR_SETBKMODE, EMR_SETPOLYFILLMODE, EMR_SETROP2, EMR_SETSTRETCHBLTMODE, EMR_SETTEXTALIGN, EMR_SETCOLORADJUSTMENT, EMR_SETTEXTCOLOR, EMR_SETBKCOLOR, EMR_OFFSETCLIPRGN, EMR_MOVETOEX, EMR_SETMETARGN, EMR_EXCLUDECLIPRECT, EMR_INTERSECTCLIPRECT, EMR_SCALEVIEWPORTEXTEX, EMR_SCALEWINDOWEXTEX, EMR_SAVEDC, EMR_RESTOREDC, EMR_SETWORLDTRANSFORM, EMR_MODIFYWORLDTRANSFORM, EMR_SELECTOBJECT, EMR_CREATEPEN, EMR_CREATEBRUSHINDIRECT, EMR_DELETEOBJECT, EMR_ANGLEARC, EMR_ELLIPSE, EMR_RECTANGLE, EMR_ROUNDRECT, EMR_ARC, EMR_CHORD, EMR_PIE, EMR_SELECTPALETTE, EMR_CREATEPALETTE, EMR_SETPALETTEENTRIES, EMR_RESIZEPALETTE, EMR_REALIZEPALETTE, EMR_EXTFLOODFILL, EMR_LINETO, EMR_ARCTO, EMR_POLYDRAW, EMR_SETARCDIRECTION, EMR_SETMITERLIMIT, EMR_BEGINPATH, EMR_ENDPATH, EMR_CLOSEFIGURE, EMR_FILLPATH, EMR_STROKEANDFILLPATH, EMR_STROKEPATH, EMR_FLATTENPATH, EMR_WIDENPATH, EMR_SELECTCLIPPATH, EMR_ABORTPATH, EMR_RESERVED_69, EMR_COMMENT, EMR_FILLRGN, EMR_FRAMERGN, EMR_INVERTRGN, EMR_PAINTRGN, EMR_EXTSELECTCLIPRGN, EMR_BITBLT, EMR_STRETCHBLT, EMR_MASKBLT, EMR_PLGBLT, EMR_SETDIBITSTODEVICE, EMR_STRETCHDIBITS, EMR_EXTCREATEFONTINDIRECTW, EMR_EXTTEXTOUTA, EMR_EXTTEXTOUTW, EMR_POLYBEZIER16, EMR_POLYGON16, EMR_POLYLINE16, EMR_POLYBEZIERTO16, EMR_POLYLINETO16, EMR_POLYPOLYLINE16, EMR_POLYPOLYGON16, EMR_POLYDRAW16, EMR_CREATEMONOBRUSH, EMR_CREATEDIBPATTERNBRUSHPT, EMR_EXTCREATEPEN, EMR_POLYTEXTOUTA, EMR_POLYTEXTOUTW, EMR_SETICMMODE, EMR_CREATECOLORSPACE, EMR_SETCOLORSPACE, EMR_DELETECOLORSPACE, EMR_GLSRECORD, EMR_GLSBOUNDEDRECORD, EMR_PIXELFORMAT, EMR_DRAWESCAPE, EMR_EXTESCAPE, EMR_RESERVED_107, EMR_SMALLTEXTOUT, EMR_FORCEUFIMAPPING, EMR_NAMEDESCAPE, EMR_COLORCORRECTPALETTE, EMR_SETICMPROFILEA, EMR_SETICMPROFILEW, EMR_ALPHABLEND, EMR_SETLAYOUT, EMR_TRANSPARENTBLT, EMR_RESERVED_117, EMR_GRADIENTFILL, EMR_SETLINKEDUFIS, EMR_SETTEXTJUSTIFICATION, EMR_COLORMATCHTOTARGETW, EMR_CREATECOLORSPACEW };

typedef enum RecordType_enum RecordType;
std::vector<DWORD> RecordType_values = { EMR_HEADER, EMR_POLYBEZIER, EMR_POLYGON, EMR_POLYLINE, EMR_POLYBEZIERTO, EMR_POLYLINETO, EMR_POLYPOLYLINE, EMR_POLYPOLYGON, EMR_SETWINDOWEXTEX, EMR_SETWINDOWORGEX, EMR_SETVIEWPORTEXTEX, EMR_SETVIEWPORTORGEX, EMR_SETBRUSHORGEX, EMR_EOF, EMR_SETPIXELV, EMR_SETMAPPERFLAGS, EMR_SETMAPMODE, EMR_SETBKMODE, EMR_SETPOLYFILLMODE, EMR_SETROP2, EMR_SETSTRETCHBLTMODE, EMR_SETTEXTALIGN, EMR_SETCOLORADJUSTMENT, EMR_SETTEXTCOLOR, EMR_SETBKCOLOR, EMR_OFFSETCLIPRGN, EMR_MOVETOEX, EMR_SETMETARGN, EMR_EXCLUDECLIPRECT, EMR_INTERSECTCLIPRECT, EMR_SCALEVIEWPORTEXTEX, EMR_SCALEWINDOWEXTEX, EMR_SAVEDC, EMR_RESTOREDC, EMR_SETWORLDTRANSFORM, EMR_MODIFYWORLDTRANSFORM, EMR_SELECTOBJECT, EMR_CREATEPEN, EMR_CREATEBRUSHINDIRECT, EMR_DELETEOBJECT, EMR_ANGLEARC, EMR_ELLIPSE, EMR_RECTANGLE, EMR_ROUNDRECT, EMR_ARC, EMR_CHORD, EMR_PIE, EMR_SELECTPALETTE, EMR_CREATEPALETTE, EMR_SETPALETTEENTRIES, EMR_RESIZEPALETTE, EMR_REALIZEPALETTE, EMR_EXTFLOODFILL, EMR_LINETO, EMR_ARCTO, EMR_POLYDRAW, EMR_SETARCDIRECTION, EMR_SETMITERLIMIT, EMR_BEGINPATH, EMR_ENDPATH, EMR_CLOSEFIGURE, EMR_FILLPATH, EMR_STROKEANDFILLPATH, EMR_STROKEPATH, EMR_FLATTENPATH, EMR_WIDENPATH, EMR_SELECTCLIPPATH, EMR_ABORTPATH, EMR_RESERVED_69, EMR_COMMENT, EMR_FILLRGN, EMR_FRAMERGN, EMR_INVERTRGN, EMR_PAINTRGN, EMR_EXTSELECTCLIPRGN, EMR_BITBLT, EMR_STRETCHBLT, EMR_MASKBLT, EMR_PLGBLT, EMR_SETDIBITSTODEVICE, EMR_STRETCHDIBITS, EMR_EXTCREATEFONTINDIRECTW, EMR_EXTTEXTOUTA, EMR_EXTTEXTOUTW, EMR_POLYBEZIER16, EMR_POLYGON16, EMR_POLYLINE16, EMR_POLYBEZIERTO16, EMR_POLYLINETO16, EMR_POLYPOLYLINE16, EMR_POLYPOLYGON16, EMR_POLYDRAW16, EMR_CREATEMONOBRUSH, EMR_CREATEDIBPATTERNBRUSHPT, EMR_EXTCREATEPEN, EMR_POLYTEXTOUTA, EMR_POLYTEXTOUTW, EMR_SETICMMODE, EMR_CREATECOLORSPACE, EMR_SETCOLORSPACE, EMR_DELETECOLORSPACE, EMR_GLSRECORD, EMR_GLSBOUNDEDRECORD, EMR_PIXELFORMAT, EMR_DRAWESCAPE, EMR_EXTESCAPE, EMR_RESERVED_107, EMR_SMALLTEXTOUT, EMR_FORCEUFIMAPPING, EMR_NAMEDESCAPE, EMR_COLORCORRECTPALETTE, EMR_SETICMPROFILEA, EMR_SETICMPROFILEW, EMR_ALPHABLEND, EMR_SETLAYOUT, EMR_TRANSPARENTBLT, EMR_RESERVED_117, EMR_GRADIENTFILL, EMR_SETLINKEDUFIS, EMR_SETTEXTJUSTIFICATION, EMR_COLORMATCHTOTARGETW, EMR_CREATECOLORSPACEW };

enum MetafileEscapes_enum : DWORD {
	NEWFRAME = (DWORD) 0x00000001,
	ABORTDOC = (DWORD) 0x00000002,
	NEXTBAND = (DWORD) 0x00000003,
	SETCOLORTABLE = (DWORD) 0x00000004,
	GETCOLORTABLE = (DWORD) 0x00000005,
	FLUSHOUT = (DWORD) 0x00000006,
	DRAFTMODE = (DWORD) 0x00000007,
	QUERYESCSUPPORT = (DWORD) 0x00000008,
	SETABORTPROC = (DWORD) 0x00000009,
	STARTDOC = (DWORD) 0x0000000A,
	ENDDOC = (DWORD) 0x0000000B,
	GETPHYSPAGESIZE = (DWORD) 0x0000000C,
	GETPRINTINGOFFSET = (DWORD) 0x0000000D,
	GETSCALINGFACTOR = (DWORD) 0x0000000E,
	META_ESCAPE_ENHANCED_METAFILE = (DWORD) 0x0000000F,
	SETPENWIDTH = (DWORD) 0x00000010,
	SETCOPYCOUNT = (DWORD) 0x00000011,
	SETPAPERSOURCE = (DWORD) 0x00000012,
	PASSTHROUGH = (DWORD) 0x00000013,
	GETTECHNOLOGY = (DWORD) 0x00000014,
	SETLINECAP = (DWORD) 0x00000015,
	SETLINEJOIN = (DWORD) 0x00000016,
	SETMITERLIMIT = (DWORD) 0x00000017,
	BANDINFO = (DWORD) 0x00000018,
	DRAWPATTERNRECT = (DWORD) 0x00000019,
	GETVECTORPENSIZE = (DWORD) 0x0000001A,
	GETVECTORBRUSHSIZE = (DWORD) 0x0000001B,
	ENABLEDUPLEX = (DWORD) 0x0000001C,
	GETSETPAPERBINS = (DWORD) 0x0000001D,
	GETSETPRINTORIENT = (DWORD) 0x0000001E,
	ENUMPAPERBINS = (DWORD) 0x0000001F,
	SETDIBSCALING = (DWORD) 0x00000020,
	EPSPRINTING = (DWORD) 0x00000021,
	ENUMPAPERMETRICS = (DWORD) 0x00000022,
	GETSETPAPERMETRICS = (DWORD) 0x00000023,
	POSTSCRIPT_DATA = (DWORD) 0x00000025,
	POSTSCRIPT_IGNORE = (DWORD) 0x00000026,
	GETDEVICEUNITS = (DWORD) 0x0000002A,
	GETEXTENDEDTEXTMETRICS = (DWORD) 0x00000100,
	GETPAIRKERNTABLE = (DWORD) 0x00000102,
	EXTTEXTOUT = (DWORD) 0x00000200,
	GETFACENAME = (DWORD) 0x00000201,
	DOWNLOADFACE = (DWORD) 0x00000202,
	METAFILE_DRIVER = (DWORD) 0x00000801,
	QUERYDIBSUPPORT = (DWORD) 0x00000C01,
	BEGIN_PATH = (DWORD) 0x00001000,
	CLIP_TO_PATH = (DWORD) 0x00001001,
	END_PATH = (DWORD) 0x00001002,
	OPENCHANNEL = (DWORD) 0x0000100E,
	DOWNLOADHEADER = (DWORD) 0x0000100F,
	CLOSECHANNEL = (DWORD) 0x00001010,
	POSTSCRIPT_PASSTHROUGH = (DWORD) 0x00001013,
	ENCAPSULATED_POSTSCRIPT = (DWORD) 0x00001014,
	POSTSCRIPT_IDENTIFY = (DWORD) 0x00001015,
	POSTSCRIPT_INJECTION = (DWORD) 0x00001016,
	CHECKJPEGFORMAT = (DWORD) 0x00001017,
	CHECKPNGFORMAT = (DWORD) 0x00001018,
	GET_PS_FEATURESETTING = (DWORD) 0x00001019,
	MXDC_ESCAPE = (DWORD) 0x0000101A,
	SPCLPASSTHROUGH2 = (DWORD) 0x000011D8,
};
std::vector<DWORD> MetafileEscapes_enum_values = { NEWFRAME, ABORTDOC, NEXTBAND, SETCOLORTABLE, GETCOLORTABLE, FLUSHOUT, DRAFTMODE, QUERYESCSUPPORT, SETABORTPROC, STARTDOC, ENDDOC, GETPHYSPAGESIZE, GETPRINTINGOFFSET, GETSCALINGFACTOR, META_ESCAPE_ENHANCED_METAFILE, SETPENWIDTH, SETCOPYCOUNT, SETPAPERSOURCE, PASSTHROUGH, GETTECHNOLOGY, SETLINECAP, SETLINEJOIN, SETMITERLIMIT, BANDINFO, DRAWPATTERNRECT, GETVECTORPENSIZE, GETVECTORBRUSHSIZE, ENABLEDUPLEX, GETSETPAPERBINS, GETSETPRINTORIENT, ENUMPAPERBINS, SETDIBSCALING, EPSPRINTING, ENUMPAPERMETRICS, GETSETPAPERMETRICS, POSTSCRIPT_DATA, POSTSCRIPT_IGNORE, GETDEVICEUNITS, GETEXTENDEDTEXTMETRICS, GETPAIRKERNTABLE, EXTTEXTOUT, GETFACENAME, DOWNLOADFACE, METAFILE_DRIVER, QUERYDIBSUPPORT, BEGIN_PATH, CLIP_TO_PATH, END_PATH, OPENCHANNEL, DOWNLOADHEADER, CLOSECHANNEL, POSTSCRIPT_PASSTHROUGH, ENCAPSULATED_POSTSCRIPT, POSTSCRIPT_IDENTIFY, POSTSCRIPT_INJECTION, CHECKJPEGFORMAT, CHECKPNGFORMAT, GET_PS_FEATURESETTING, MXDC_ESCAPE, SPCLPASSTHROUGH2 };

typedef enum MetafileEscapes_enum MetafileEscapes;
std::vector<DWORD> MetafileEscapes_values = { NEWFRAME, ABORTDOC, NEXTBAND, SETCOLORTABLE, GETCOLORTABLE, FLUSHOUT, DRAFTMODE, QUERYESCSUPPORT, SETABORTPROC, STARTDOC, ENDDOC, GETPHYSPAGESIZE, GETPRINTINGOFFSET, GETSCALINGFACTOR, META_ESCAPE_ENHANCED_METAFILE, SETPENWIDTH, SETCOPYCOUNT, SETPAPERSOURCE, PASSTHROUGH, GETTECHNOLOGY, SETLINECAP, SETLINEJOIN, SETMITERLIMIT, BANDINFO, DRAWPATTERNRECT, GETVECTORPENSIZE, GETVECTORBRUSHSIZE, ENABLEDUPLEX, GETSETPAPERBINS, GETSETPRINTORIENT, ENUMPAPERBINS, SETDIBSCALING, EPSPRINTING, ENUMPAPERMETRICS, GETSETPAPERMETRICS, POSTSCRIPT_DATA, POSTSCRIPT_IGNORE, GETDEVICEUNITS, GETEXTENDEDTEXTMETRICS, GETPAIRKERNTABLE, EXTTEXTOUT, GETFACENAME, DOWNLOADFACE, METAFILE_DRIVER, QUERYDIBSUPPORT, BEGIN_PATH, CLIP_TO_PATH, END_PATH, OPENCHANNEL, DOWNLOADHEADER, CLOSECHANNEL, POSTSCRIPT_PASSTHROUGH, ENCAPSULATED_POSTSCRIPT, POSTSCRIPT_IDENTIFY, POSTSCRIPT_INJECTION, CHECKJPEGFORMAT, CHECKPNGFORMAT, GET_PS_FEATURESETTING, MXDC_ESCAPE, SPCLPASSTHROUGH2 };

enum Compression_enum : DWORD {
	BI_RGB = (DWORD) 0x00000000,
	BI_RLE8 = (DWORD) 0x00000001,
	BI_RLE4 = (DWORD) 0x00000002,
	BI_BITFIELDS = (DWORD) 0x00000003,
	BI_JPEG = (DWORD) 0x00000004,
	BI_PNG = (DWORD) 0x00000005,
	BI_CMYK = (DWORD) 0x0000000B,
	BI_CMYKRLE8 = (DWORD) 0x0000000C,
	BI_CMYKRLE4 = (DWORD) 0x0000000D,
};
std::vector<DWORD> Compression_enum_values = { BI_RGB, BI_RLE8, BI_RLE4, BI_BITFIELDS, BI_JPEG, BI_PNG, BI_CMYK, BI_CMYKRLE8, BI_CMYKRLE4 };

typedef enum Compression_enum Compression;
std::vector<DWORD> Compression_values = { BI_RGB, BI_RLE8, BI_RLE4, BI_BITFIELDS, BI_JPEG, BI_PNG, BI_CMYK, BI_CMYKRLE8, BI_CMYKRLE4 };

enum BitCount_enum : WORD {
	BI_BITCOUNT_1 = (WORD) 0x0001,
	BI_BITCOUNT_2 = (WORD) 0x0004,
	BI_BITCOUNT_3 = (WORD) 0x0008,
	BI_BITCOUNT_4 = (WORD) 0x0010,
	BI_BITCOUNT_5 = (WORD) 0x0018,
	BI_BITCOUNT_6 = (WORD) 0x0020,
};
std::vector<WORD> BitCount_enum_values = { BI_BITCOUNT_1, BI_BITCOUNT_2, BI_BITCOUNT_3, BI_BITCOUNT_4, BI_BITCOUNT_5, BI_BITCOUNT_6 };

typedef enum BitCount_enum BitCount;
std::vector<WORD> BitCount_values = { BI_BITCOUNT_1, BI_BITCOUNT_2, BI_BITCOUNT_3, BI_BITCOUNT_4, BI_BITCOUNT_5, BI_BITCOUNT_6 };

enum BrushStyle_enum : DWORD {
	BS_SOLID = (DWORD) 0x00000000,
	BS_NULL = (DWORD) 0x00000001,
	BS_HATCHED = (DWORD) 0x00000002,
};
std::vector<DWORD> BrushStyle_enum_values = { BS_SOLID, BS_NULL, BS_HATCHED };

typedef enum BrushStyle_enum BrushStyle;
std::vector<DWORD> BrushStyle_values = { BS_SOLID, BS_NULL, BS_HATCHED };

enum DIBColors_enum : DWORD {
	DIB_RGB_COLORS = (DWORD) 0x00000000,
	DIB_PAL_COLORS = (DWORD) 0x00000001,
	DIB_PAL_INDICES = (DWORD) 0x00000002,
};
std::vector<DWORD> DIBColors_enum_values = { DIB_RGB_COLORS, DIB_PAL_COLORS, DIB_PAL_INDICES };

typedef enum DIBColors_enum DIBColors;
std::vector<DWORD> DIBColors_values = { DIB_RGB_COLORS, DIB_PAL_COLORS, DIB_PAL_INDICES };

enum LogicalColorSpace_enum : DWORD {
	LCS_CALIBRATED_RGB = (DWORD) 0x00000000,
	LCS_sRGB = (DWORD) 0x73524742,
	LCS_WINDOWS_COLOR_SPACE = (DWORD) 0x57696E20,
};
std::vector<DWORD> LogicalColorSpace_enum_values = { LCS_CALIBRATED_RGB, LCS_sRGB, LCS_WINDOWS_COLOR_SPACE };

typedef enum LogicalColorSpace_enum LogicalColorSpace;
std::vector<DWORD> LogicalColorSpace_values = { LCS_CALIBRATED_RGB, LCS_sRGB, LCS_WINDOWS_COLOR_SPACE };

enum GamutMappingIntent_enum : DWORD {
	LCS_GM_ABS_COLORIMETRIC = (DWORD) 0x00000008,
	LCS_GM_BUSINESS = (DWORD) 0x00000001,
	LCS_GM_GRAPHICS = (DWORD) 0x00000002,
	LCS_GM_IMAGES = (DWORD) 0x00000004,
};
std::vector<DWORD> GamutMappingIntent_enum_values = { LCS_GM_ABS_COLORIMETRIC, LCS_GM_BUSINESS, LCS_GM_GRAPHICS, LCS_GM_IMAGES };

typedef enum GamutMappingIntent_enum GamutMappingIntent;
std::vector<DWORD> GamutMappingIntent_values = { LCS_GM_ABS_COLORIMETRIC, LCS_GM_BUSINESS, LCS_GM_GRAPHICS, LCS_GM_IMAGES };


class DWORD_class {
	int small;
	std::vector<DWORD> known_values;
	DWORD value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = sizeof(DWORD);
	DWORD operator () () { return value; }
	DWORD_class(int small, std::vector<DWORD> known_values = {}) : small(small), known_values(known_values) {}

	DWORD generate() {
		_startof = FTell();
		if (known_values.empty()) {
			value = file_acc.file_integer(sizeof(DWORD), 0, small);
		} else {
			value = file_acc.file_integer(sizeof(DWORD), 0, known_values);
		}
		return value;
	}

	DWORD generate(std::vector<DWORD> possible_values) {
		_startof = FTell();
		value = file_acc.file_integer(sizeof(DWORD), 0, possible_values);
		return value;
	}
};



class LONG_class {
	int small;
	std::vector<LONG> known_values;
	LONG value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = sizeof(LONG);
	LONG operator () () { return value; }
	LONG_class(int small, std::vector<LONG> known_values = {}) : small(small), known_values(known_values) {}

	LONG generate() {
		_startof = FTell();
		if (known_values.empty()) {
			value = file_acc.file_integer(sizeof(LONG), 0, small);
		} else {
			value = file_acc.file_integer(sizeof(LONG), 0, known_values);
		}
		return value;
	}

	LONG generate(std::vector<LONG> possible_values) {
		_startof = FTell();
		value = file_acc.file_integer(sizeof(LONG), 0, possible_values);
		return value;
	}
};



class RECTL {
	std::vector<RECTL*>& instances;

	LONG left_var;
	LONG top_var;
	LONG right_var;
	LONG bottom_var;

public:
	bool left_exists = false;
	bool top_exists = false;
	bool right_exists = false;
	bool bottom_exists = false;

	LONG& left() {
		assert_cond(left_exists, "struct field left does not exist");
		return left_var;
	}
	LONG& top() {
		assert_cond(top_exists, "struct field top does not exist");
		return top_var;
	}
	LONG& right() {
		assert_cond(right_exists, "struct field right does not exist");
		return right_var;
	}
	LONG& bottom() {
		assert_cond(bottom_exists, "struct field bottom does not exist");
		return bottom_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	RECTL& operator () () { return *instances.back(); }
	RECTL& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	RECTL(std::vector<RECTL*>& instances) : instances(instances) { instances.push_back(this); }
	~RECTL() {
		if (generated == 2)
			return;
		while (instances.size()) {
			RECTL* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	RECTL* generate();
};

int RECTL::_parent_id = 0;
int RECTL::_index_start = 0;



class WORD_class {
	int small;
	std::vector<WORD> known_values;
	WORD value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = sizeof(WORD);
	WORD operator () () { return value; }
	WORD_class(int small, std::vector<WORD> known_values = {}) : small(small), known_values(known_values) {}

	WORD generate() {
		_startof = FTell();
		if (known_values.empty()) {
			value = file_acc.file_integer(sizeof(WORD), 0, small);
		} else {
			value = file_acc.file_integer(sizeof(WORD), 0, known_values);
		}
		return value;
	}

	WORD generate(std::vector<WORD> possible_values) {
		_startof = FTell();
		value = file_acc.file_integer(sizeof(WORD), 0, possible_values);
		return value;
	}
};



class SIZEL {
	std::vector<SIZEL*>& instances;

	LONG cx_var;
	LONG cy_var;

public:
	bool cx_exists = false;
	bool cy_exists = false;

	LONG& cx() {
		assert_cond(cx_exists, "struct field cx does not exist");
		return cx_var;
	}
	LONG& cy() {
		assert_cond(cy_exists, "struct field cy does not exist");
		return cy_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	SIZEL& operator () () { return *instances.back(); }
	SIZEL& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	SIZEL(std::vector<SIZEL*>& instances) : instances(instances) { instances.push_back(this); }
	~SIZEL() {
		if (generated == 2)
			return;
		while (instances.size()) {
			SIZEL* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	SIZEL* generate();
};

int SIZEL::_parent_id = 0;
int SIZEL::_index_start = 0;



class HeaderExtension1 {
	std::vector<HeaderExtension1*>& instances;

	DWORD cbPixelFormat_var;
	DWORD offPixelFormat_var;
	DWORD bOpenGL_var;

public:
	bool cbPixelFormat_exists = false;
	bool offPixelFormat_exists = false;
	bool bOpenGL_exists = false;

	DWORD& cbPixelFormat() {
		assert_cond(cbPixelFormat_exists, "struct field cbPixelFormat does not exist");
		return cbPixelFormat_var;
	}
	DWORD& offPixelFormat() {
		assert_cond(offPixelFormat_exists, "struct field offPixelFormat does not exist");
		return offPixelFormat_var;
	}
	DWORD& bOpenGL() {
		assert_cond(bOpenGL_exists, "struct field bOpenGL does not exist");
		return bOpenGL_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	HeaderExtension1& operator () () { return *instances.back(); }
	HeaderExtension1& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	HeaderExtension1(std::vector<HeaderExtension1*>& instances) : instances(instances) { instances.push_back(this); }
	~HeaderExtension1() {
		if (generated == 2)
			return;
		while (instances.size()) {
			HeaderExtension1* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	HeaderExtension1* generate();
};

int HeaderExtension1::_parent_id = 0;
int HeaderExtension1::_index_start = 0;



class HeaderExtension2 {
	std::vector<HeaderExtension2*>& instances;

	DWORD MicrometersX_var;
	DWORD MicrometersY_var;

public:
	bool MicrometersX_exists = false;
	bool MicrometersY_exists = false;

	DWORD& MicrometersX() {
		assert_cond(MicrometersX_exists, "struct field MicrometersX does not exist");
		return MicrometersX_var;
	}
	DWORD& MicrometersY() {
		assert_cond(MicrometersY_exists, "struct field MicrometersY does not exist");
		return MicrometersY_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	HeaderExtension2& operator () () { return *instances.back(); }
	HeaderExtension2& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	HeaderExtension2(std::vector<HeaderExtension2*>& instances) : instances(instances) { instances.push_back(this); }
	~HeaderExtension2() {
		if (generated == 2)
			return;
		while (instances.size()) {
			HeaderExtension2* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	HeaderExtension2* generate();
};

int HeaderExtension2::_parent_id = 0;
int HeaderExtension2::_index_start = 0;



class EMRHEADER {
	std::vector<EMRHEADER*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	RECTL* rclFrame_var;
	DWORD dSignature_var;
	DWORD nVersion_var;
	DWORD nBytes_var;
	DWORD nRecords_var;
	WORD nHandles_var;
	WORD sReserved_var;
	DWORD nDescription_var;
	DWORD offDescription_var;
	DWORD nPalEntries_var;
	SIZEL* szlDevice_var;
	SIZEL* szlMillimeters_var;
	HeaderExtension1* EmfHeaderExtension1_var;
	HeaderExtension2* EmfHeaderExtension2_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool rclFrame_exists = false;
	bool dSignature_exists = false;
	bool nVersion_exists = false;
	bool nBytes_exists = false;
	bool nRecords_exists = false;
	bool nHandles_exists = false;
	bool sReserved_exists = false;
	bool nDescription_exists = false;
	bool offDescription_exists = false;
	bool nPalEntries_exists = false;
	bool szlDevice_exists = false;
	bool szlMillimeters_exists = false;
	bool EmfHeaderExtension1_exists = false;
	bool EmfHeaderExtension2_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	RECTL& rclBounds() {
		assert_cond(rclBounds_exists, "struct field rclBounds does not exist");
		return *rclBounds_var;
	}
	RECTL& rclFrame() {
		assert_cond(rclFrame_exists, "struct field rclFrame does not exist");
		return *rclFrame_var;
	}
	DWORD& dSignature() {
		assert_cond(dSignature_exists, "struct field dSignature does not exist");
		return dSignature_var;
	}
	DWORD& nVersion() {
		assert_cond(nVersion_exists, "struct field nVersion does not exist");
		return nVersion_var;
	}
	DWORD& nBytes() {
		assert_cond(nBytes_exists, "struct field nBytes does not exist");
		return nBytes_var;
	}
	DWORD& nRecords() {
		assert_cond(nRecords_exists, "struct field nRecords does not exist");
		return nRecords_var;
	}
	WORD& nHandles() {
		assert_cond(nHandles_exists, "struct field nHandles does not exist");
		return nHandles_var;
	}
	WORD& sReserved() {
		assert_cond(sReserved_exists, "struct field sReserved does not exist");
		return sReserved_var;
	}
	DWORD& nDescription() {
		assert_cond(nDescription_exists, "struct field nDescription does not exist");
		return nDescription_var;
	}
	DWORD& offDescription() {
		assert_cond(offDescription_exists, "struct field offDescription does not exist");
		return offDescription_var;
	}
	DWORD& nPalEntries() {
		assert_cond(nPalEntries_exists, "struct field nPalEntries does not exist");
		return nPalEntries_var;
	}
	SIZEL& szlDevice() {
		assert_cond(szlDevice_exists, "struct field szlDevice does not exist");
		return *szlDevice_var;
	}
	SIZEL& szlMillimeters() {
		assert_cond(szlMillimeters_exists, "struct field szlMillimeters does not exist");
		return *szlMillimeters_var;
	}
	HeaderExtension1& EmfHeaderExtension1() {
		assert_cond(EmfHeaderExtension1_exists, "struct field EmfHeaderExtension1 does not exist");
		return *EmfHeaderExtension1_var;
	}
	HeaderExtension2& EmfHeaderExtension2() {
		assert_cond(EmfHeaderExtension2_exists, "struct field EmfHeaderExtension2 does not exist");
		return *EmfHeaderExtension2_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRHEADER& operator () () { return *instances.back(); }
	EMRHEADER& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRHEADER(std::vector<EMRHEADER*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRHEADER() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRHEADER* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRHEADER* generate();
};

int EMRHEADER::_parent_id = 0;
int EMRHEADER::_index_start = 0;



class WORD_array_class {
	WORD_class& element;
	std::unordered_map<int, std::vector<WORD>> element_known_values;
	std::vector<WORD> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<WORD>& operator () () { return value; }
	WORD operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return value[index];
	}
	WORD_array_class(WORD_class& element, std::unordered_map<int, std::vector<WORD>> element_known_values = {})
		: element(element), element_known_values(element_known_values) {}

	std::vector<WORD> generate(unsigned size) {
		check_array_length(size);
		_startof = FTell();
		value = {};
		for (unsigned i = 0; i < size; ++i) {
			auto known = element_known_values.find(i);
			if (known == element_known_values.end()) {
				value.push_back(element.generate());
				_sizeof += element._sizeof;
			} else {
				value.push_back(file_acc.file_integer(sizeof(WORD), 0, known->second));
				_sizeof += sizeof(WORD);
			}
		}
		return value;
	}
};



class EMRDESCRIPTION {
	std::vector<EMRDESCRIPTION*>& instances;

	std::vector<WORD> desc_var;

public:
	bool desc_exists = false;

	std::vector<WORD>& desc() {
		assert_cond(desc_exists, "struct field desc does not exist");
		return desc_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRDESCRIPTION& operator () () { return *instances.back(); }
	EMRDESCRIPTION& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRDESCRIPTION(std::vector<EMRDESCRIPTION*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRDESCRIPTION() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRDESCRIPTION* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRDESCRIPTION* generate();
};

int EMRDESCRIPTION::_parent_id = 0;
int EMRDESCRIPTION::_index_start = 0;



class EMFPLUSHEADER {
	std::vector<EMFPLUSHEADER*>& instances;

	DWORD cType_var;
	DWORD cSize_var;
	DWORD cDataSize_var;
	DWORD cIdentifier_var;
	WORD Type_var;
	WORD Flags_var;
	DWORD Size_var;
	DWORD DataSize_var;
	DWORD Version_var;
	DWORD EmfPlusFlags_var;
	DWORD LogicalDpiX_var;
	DWORD LogicalDpiY_var;

public:
	bool cType_exists = false;
	bool cSize_exists = false;
	bool cDataSize_exists = false;
	bool cIdentifier_exists = false;
	bool Type_exists = false;
	bool Flags_exists = false;
	bool Size_exists = false;
	bool DataSize_exists = false;
	bool Version_exists = false;
	bool EmfPlusFlags_exists = false;
	bool LogicalDpiX_exists = false;
	bool LogicalDpiY_exists = false;

	DWORD& cType() {
		assert_cond(cType_exists, "struct field cType does not exist");
		return cType_var;
	}
	DWORD& cSize() {
		assert_cond(cSize_exists, "struct field cSize does not exist");
		return cSize_var;
	}
	DWORD& cDataSize() {
		assert_cond(cDataSize_exists, "struct field cDataSize does not exist");
		return cDataSize_var;
	}
	DWORD& cIdentifier() {
		assert_cond(cIdentifier_exists, "struct field cIdentifier does not exist");
		return cIdentifier_var;
	}
	WORD& Type() {
		assert_cond(Type_exists, "struct field Type does not exist");
		return Type_var;
	}
	WORD& Flags() {
		assert_cond(Flags_exists, "struct field Flags does not exist");
		return Flags_var;
	}
	DWORD& Size() {
		assert_cond(Size_exists, "struct field Size does not exist");
		return Size_var;
	}
	DWORD& DataSize() {
		assert_cond(DataSize_exists, "struct field DataSize does not exist");
		return DataSize_var;
	}
	DWORD& Version() {
		assert_cond(Version_exists, "struct field Version does not exist");
		return Version_var;
	}
	DWORD& EmfPlusFlags() {
		assert_cond(EmfPlusFlags_exists, "struct field EmfPlusFlags does not exist");
		return EmfPlusFlags_var;
	}
	DWORD& LogicalDpiX() {
		assert_cond(LogicalDpiX_exists, "struct field LogicalDpiX does not exist");
		return LogicalDpiX_var;
	}
	DWORD& LogicalDpiY() {
		assert_cond(LogicalDpiY_exists, "struct field LogicalDpiY does not exist");
		return LogicalDpiY_var;
	}

	/* locals */
	uint _cSize;
	uint _cDataSize;
	uint _rSize;
	uint _rDataSize;
	uint start;
	uint end;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMFPLUSHEADER& operator () () { return *instances.back(); }
	EMFPLUSHEADER& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMFPLUSHEADER(std::vector<EMFPLUSHEADER*>& instances) : instances(instances) { instances.push_back(this); }
	~EMFPLUSHEADER() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMFPLUSHEADER* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMFPLUSHEADER* generate();
};

int EMFPLUSHEADER::_parent_id = 0;
int EMFPLUSHEADER::_index_start = 0;



class UBYTE_class {
	int small;
	std::vector<UBYTE> known_values;
	UBYTE value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = sizeof(UBYTE);
	UBYTE operator () () { return value; }
	UBYTE_class(int small, std::vector<UBYTE> known_values = {}) : small(small), known_values(known_values) {}

	UBYTE generate() {
		_startof = FTell();
		if (known_values.empty()) {
			value = file_acc.file_integer(sizeof(UBYTE), 0, small);
		} else {
			value = file_acc.file_integer(sizeof(UBYTE), 0, known_values);
		}
		return value;
	}

	UBYTE generate(std::vector<UBYTE> possible_values) {
		_startof = FTell();
		value = file_acc.file_integer(sizeof(UBYTE), 0, possible_values);
		return value;
	}
};



class COLORREF {
	std::vector<COLORREF*>& instances;

	UBYTE Red_var;
	UBYTE Green_var;
	UBYTE Blue_var;
	UBYTE Reserved_var;

public:
	bool Red_exists = false;
	bool Green_exists = false;
	bool Blue_exists = false;
	bool Reserved_exists = false;

	UBYTE& Red() {
		assert_cond(Red_exists, "struct field Red does not exist");
		return Red_var;
	}
	UBYTE& Green() {
		assert_cond(Green_exists, "struct field Green does not exist");
		return Green_var;
	}
	UBYTE& Blue() {
		assert_cond(Blue_exists, "struct field Blue does not exist");
		return Blue_var;
	}
	UBYTE& Reserved() {
		assert_cond(Reserved_exists, "struct field Reserved does not exist");
		return Reserved_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	COLORREF& operator () () { return *instances.back(); }
	COLORREF& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	COLORREF(std::vector<COLORREF*>& instances) : instances(instances) { instances.push_back(this); }
	~COLORREF() {
		if (generated == 2)
			return;
		while (instances.size()) {
			COLORREF* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	COLORREF* generate();
};

int COLORREF::_parent_id = 0;
int COLORREF::_index_start = 0;



class EmfPlusClear {
	std::vector<EmfPlusClear*>& instances;

	DWORD cType_var;
	DWORD cSize_var;
	DWORD cDataSize_var;
	DWORD cIdentifier_var;
	WORD Type_var;
	WORD Flags_var;
	DWORD Size_var;
	DWORD DataSize_var;
	COLORREF* Color_var;

public:
	bool cType_exists = false;
	bool cSize_exists = false;
	bool cDataSize_exists = false;
	bool cIdentifier_exists = false;
	bool Type_exists = false;
	bool Flags_exists = false;
	bool Size_exists = false;
	bool DataSize_exists = false;
	bool Color_exists = false;

	DWORD& cType() {
		assert_cond(cType_exists, "struct field cType does not exist");
		return cType_var;
	}
	DWORD& cSize() {
		assert_cond(cSize_exists, "struct field cSize does not exist");
		return cSize_var;
	}
	DWORD& cDataSize() {
		assert_cond(cDataSize_exists, "struct field cDataSize does not exist");
		return cDataSize_var;
	}
	DWORD& cIdentifier() {
		assert_cond(cIdentifier_exists, "struct field cIdentifier does not exist");
		return cIdentifier_var;
	}
	WORD& Type() {
		assert_cond(Type_exists, "struct field Type does not exist");
		return Type_var;
	}
	WORD& Flags() {
		assert_cond(Flags_exists, "struct field Flags does not exist");
		return Flags_var;
	}
	DWORD& Size() {
		assert_cond(Size_exists, "struct field Size does not exist");
		return Size_var;
	}
	DWORD& DataSize() {
		assert_cond(DataSize_exists, "struct field DataSize does not exist");
		return DataSize_var;
	}
	COLORREF& Color() {
		assert_cond(Color_exists, "struct field Color does not exist");
		return *Color_var;
	}

	/* locals */
	uint _cSize;
	uint _cDataSize;
	uint _rSize;
	uint _rDataSize;
	uint start;
	uint end;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EmfPlusClear& operator () () { return *instances.back(); }
	EmfPlusClear& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EmfPlusClear(std::vector<EmfPlusClear*>& instances) : instances(instances) { instances.push_back(this); }
	~EmfPlusClear() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EmfPlusClear* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EmfPlusClear* generate();
};

int EmfPlusClear::_parent_id = 0;
int EmfPlusClear::_index_start = 0;



class EmfPlusRect {
	std::vector<EmfPlusRect*>& instances;

	WORD X_var;
	WORD Y_var;
	WORD Width_var;
	WORD Height_var;

public:
	bool X_exists = false;
	bool Y_exists = false;
	bool Width_exists = false;
	bool Height_exists = false;

	WORD& X() {
		assert_cond(X_exists, "struct field X does not exist");
		return X_var;
	}
	WORD& Y() {
		assert_cond(Y_exists, "struct field Y does not exist");
		return Y_var;
	}
	WORD& Width() {
		assert_cond(Width_exists, "struct field Width does not exist");
		return Width_var;
	}
	WORD& Height() {
		assert_cond(Height_exists, "struct field Height does not exist");
		return Height_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EmfPlusRect& operator () () { return *instances.back(); }
	EmfPlusRect& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EmfPlusRect(std::vector<EmfPlusRect*>& instances) : instances(instances) { instances.push_back(this); }
	~EmfPlusRect() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EmfPlusRect* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EmfPlusRect* generate();
};

int EmfPlusRect::_parent_id = 0;
int EmfPlusRect::_index_start = 0;



class EmfPlusRect_array_class {
	EmfPlusRect& element;
	std::vector<EmfPlusRect*> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<EmfPlusRect*>& operator () () { return value; }
	EmfPlusRect operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return *value[index];
	}
	EmfPlusRect_array_class(EmfPlusRect& element) : element(element) {}

	std::vector<EmfPlusRect*> generate(unsigned size) {
		check_array_length(size);
		_startof = FTell();
		value = {};
		for (unsigned i = 0; i < size; ++i) {
			value.push_back(element.generate());
			_sizeof += element._sizeof;
		}
		return value;
	}
};



class EmfPlusFillRects {
	std::vector<EmfPlusFillRects*>& instances;

	DWORD cType_var;
	DWORD cSize_var;
	DWORD cDataSize_var;
	DWORD cIdentifier_var;
	WORD Type_var;
	WORD Flags_var;
	DWORD Size_var;
	DWORD DataSize_var;
	DWORD BrushID_var;
	DWORD Count_var;
	std::vector<EmfPlusRect*> RectData_var;

public:
	bool cType_exists = false;
	bool cSize_exists = false;
	bool cDataSize_exists = false;
	bool cIdentifier_exists = false;
	bool Type_exists = false;
	bool Flags_exists = false;
	bool Size_exists = false;
	bool DataSize_exists = false;
	bool BrushID_exists = false;
	bool Count_exists = false;
	bool RectData_exists = false;

	DWORD& cType() {
		assert_cond(cType_exists, "struct field cType does not exist");
		return cType_var;
	}
	DWORD& cSize() {
		assert_cond(cSize_exists, "struct field cSize does not exist");
		return cSize_var;
	}
	DWORD& cDataSize() {
		assert_cond(cDataSize_exists, "struct field cDataSize does not exist");
		return cDataSize_var;
	}
	DWORD& cIdentifier() {
		assert_cond(cIdentifier_exists, "struct field cIdentifier does not exist");
		return cIdentifier_var;
	}
	WORD& Type() {
		assert_cond(Type_exists, "struct field Type does not exist");
		return Type_var;
	}
	WORD& Flags() {
		assert_cond(Flags_exists, "struct field Flags does not exist");
		return Flags_var;
	}
	DWORD& Size() {
		assert_cond(Size_exists, "struct field Size does not exist");
		return Size_var;
	}
	DWORD& DataSize() {
		assert_cond(DataSize_exists, "struct field DataSize does not exist");
		return DataSize_var;
	}
	DWORD& BrushID() {
		assert_cond(BrushID_exists, "struct field BrushID does not exist");
		return BrushID_var;
	}
	DWORD& Count() {
		assert_cond(Count_exists, "struct field Count does not exist");
		return Count_var;
	}
	std::vector<EmfPlusRect*>& RectData() {
		assert_cond(RectData_exists, "struct field RectData does not exist");
		return RectData_var;
	}

	/* locals */
	uint _cSize;
	uint _cDataSize;
	uint _rSize;
	uint _rDataSize;
	uint start;
	uint end;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EmfPlusFillRects& operator () () { return *instances.back(); }
	EmfPlusFillRects& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EmfPlusFillRects(std::vector<EmfPlusFillRects*>& instances) : instances(instances) { instances.push_back(this); }
	~EmfPlusFillRects() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EmfPlusFillRects* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EmfPlusFillRects* generate();
};

int EmfPlusFillRects::_parent_id = 0;
int EmfPlusFillRects::_index_start = 0;



class EmfPlusPointF {
	std::vector<EmfPlusPointF*>& instances;

	DWORD X_var;
	DWORD Y_var;

public:
	bool X_exists = false;
	bool Y_exists = false;

	DWORD& X() {
		assert_cond(X_exists, "struct field X does not exist");
		return X_var;
	}
	DWORD& Y() {
		assert_cond(Y_exists, "struct field Y does not exist");
		return Y_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EmfPlusPointF& operator () () { return *instances.back(); }
	EmfPlusPointF& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EmfPlusPointF(std::vector<EmfPlusPointF*>& instances) : instances(instances) { instances.push_back(this); }
	~EmfPlusPointF() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EmfPlusPointF* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EmfPlusPointF* generate();
};

int EmfPlusPointF::_parent_id = 0;
int EmfPlusPointF::_index_start = 0;



class EmfPlusPointF_array_class {
	EmfPlusPointF& element;
	std::vector<EmfPlusPointF*> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<EmfPlusPointF*>& operator () () { return value; }
	EmfPlusPointF operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return *value[index];
	}
	EmfPlusPointF_array_class(EmfPlusPointF& element) : element(element) {}

	std::vector<EmfPlusPointF*> generate(unsigned size) {
		check_array_length(size);
		_startof = FTell();
		value = {};
		for (unsigned i = 0; i < size; ++i) {
			value.push_back(element.generate());
			_sizeof += element._sizeof;
		}
		return value;
	}
};



class EmfPlusDrawLines {
	std::vector<EmfPlusDrawLines*>& instances;

	DWORD cType_var;
	DWORD cSize_var;
	DWORD cDataSize_var;
	DWORD cIdentifier_var;
	WORD Type_var;
	WORD Flags_var;
	DWORD Size_var;
	DWORD DataSize_var;
	DWORD Count_var;
	std::vector<EmfPlusPointF*> Points_var;

public:
	bool cType_exists = false;
	bool cSize_exists = false;
	bool cDataSize_exists = false;
	bool cIdentifier_exists = false;
	bool Type_exists = false;
	bool Flags_exists = false;
	bool Size_exists = false;
	bool DataSize_exists = false;
	bool Count_exists = false;
	bool Points_exists = false;

	DWORD& cType() {
		assert_cond(cType_exists, "struct field cType does not exist");
		return cType_var;
	}
	DWORD& cSize() {
		assert_cond(cSize_exists, "struct field cSize does not exist");
		return cSize_var;
	}
	DWORD& cDataSize() {
		assert_cond(cDataSize_exists, "struct field cDataSize does not exist");
		return cDataSize_var;
	}
	DWORD& cIdentifier() {
		assert_cond(cIdentifier_exists, "struct field cIdentifier does not exist");
		return cIdentifier_var;
	}
	WORD& Type() {
		assert_cond(Type_exists, "struct field Type does not exist");
		return Type_var;
	}
	WORD& Flags() {
		assert_cond(Flags_exists, "struct field Flags does not exist");
		return Flags_var;
	}
	DWORD& Size() {
		assert_cond(Size_exists, "struct field Size does not exist");
		return Size_var;
	}
	DWORD& DataSize() {
		assert_cond(DataSize_exists, "struct field DataSize does not exist");
		return DataSize_var;
	}
	DWORD& Count() {
		assert_cond(Count_exists, "struct field Count does not exist");
		return Count_var;
	}
	std::vector<EmfPlusPointF*>& Points() {
		assert_cond(Points_exists, "struct field Points does not exist");
		return Points_var;
	}

	/* locals */
	uint _rCount;
	uint _cSize;
	uint _cDataSize;
	uint _rSize;
	uint _rDataSize;
	uint start;
	uint end;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EmfPlusDrawLines& operator () () { return *instances.back(); }
	EmfPlusDrawLines& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EmfPlusDrawLines(std::vector<EmfPlusDrawLines*>& instances) : instances(instances) { instances.push_back(this); }
	~EmfPlusDrawLines() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EmfPlusDrawLines* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EmfPlusDrawLines* generate();
};

int EmfPlusDrawLines::_parent_id = 0;
int EmfPlusDrawLines::_index_start = 0;



class EmfPlusSetTSClip {
	std::vector<EmfPlusSetTSClip*>& instances;

	DWORD cType_var;
	DWORD cSize_var;
	DWORD cDataSize_var;
	DWORD cIdentifier_var;
	WORD Type_var;
	WORD Flags_var;
	DWORD Size_var;
	DWORD DataSize_var;
	std::vector<EmfPlusRect*> Rects_var;

public:
	bool cType_exists = false;
	bool cSize_exists = false;
	bool cDataSize_exists = false;
	bool cIdentifier_exists = false;
	bool Type_exists = false;
	bool Flags_exists = false;
	bool Size_exists = false;
	bool DataSize_exists = false;
	bool Rects_exists = false;

	DWORD& cType() {
		assert_cond(cType_exists, "struct field cType does not exist");
		return cType_var;
	}
	DWORD& cSize() {
		assert_cond(cSize_exists, "struct field cSize does not exist");
		return cSize_var;
	}
	DWORD& cDataSize() {
		assert_cond(cDataSize_exists, "struct field cDataSize does not exist");
		return cDataSize_var;
	}
	DWORD& cIdentifier() {
		assert_cond(cIdentifier_exists, "struct field cIdentifier does not exist");
		return cIdentifier_var;
	}
	WORD& Type() {
		assert_cond(Type_exists, "struct field Type does not exist");
		return Type_var;
	}
	WORD& Flags() {
		assert_cond(Flags_exists, "struct field Flags does not exist");
		return Flags_var;
	}
	DWORD& Size() {
		assert_cond(Size_exists, "struct field Size does not exist");
		return Size_var;
	}
	DWORD& DataSize() {
		assert_cond(DataSize_exists, "struct field DataSize does not exist");
		return DataSize_var;
	}
	std::vector<EmfPlusRect*>& Rects() {
		assert_cond(Rects_exists, "struct field Rects does not exist");
		return Rects_var;
	}

	/* locals */
	uint _cSize;
	uint _cDataSize;
	uint _rSize;
	uint _rDataSize;
	uint start;
	uint end;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EmfPlusSetTSClip& operator () () { return *instances.back(); }
	EmfPlusSetTSClip& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EmfPlusSetTSClip(std::vector<EmfPlusSetTSClip*>& instances) : instances(instances) { instances.push_back(this); }
	~EmfPlusSetTSClip() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EmfPlusSetTSClip* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EmfPlusSetTSClip* generate();
};

int EmfPlusSetTSClip::_parent_id = 0;
int EmfPlusSetTSClip::_index_start = 0;



class DWORD_array_class {
	DWORD_class& element;
	std::unordered_map<int, std::vector<DWORD>> element_known_values;
	std::vector<DWORD> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<DWORD>& operator () () { return value; }
	DWORD operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return value[index];
	}
	DWORD_array_class(DWORD_class& element, std::unordered_map<int, std::vector<DWORD>> element_known_values = {})
		: element(element), element_known_values(element_known_values) {}

	std::vector<DWORD> generate(unsigned size) {
		check_array_length(size);
		_startof = FTell();
		value = {};
		for (unsigned i = 0; i < size; ++i) {
			auto known = element_known_values.find(i);
			if (known == element_known_values.end()) {
				value.push_back(element.generate());
				_sizeof += element._sizeof;
			} else {
				value.push_back(file_acc.file_integer(sizeof(DWORD), 0, known->second));
				_sizeof += sizeof(DWORD);
			}
		}
		return value;
	}
};



class EmfPlusDrawDriverString {
	std::vector<EmfPlusDrawDriverString*>& instances;

	DWORD cType_var;
	DWORD cSize_var;
	DWORD cDataSize_var;
	DWORD cIdentifier_var;
	WORD Type_var;
	WORD Flags_var;
	DWORD Size_var;
	DWORD DataSize_var;
	DWORD BrushId_var;
	DWORD DriverStringOptionsFlags_var;
	DWORD MatrixPresent_var;
	DWORD GlyphCount_var;
	std::vector<DWORD> Glyphs_var;

public:
	bool cType_exists = false;
	bool cSize_exists = false;
	bool cDataSize_exists = false;
	bool cIdentifier_exists = false;
	bool Type_exists = false;
	bool Flags_exists = false;
	bool Size_exists = false;
	bool DataSize_exists = false;
	bool BrushId_exists = false;
	bool DriverStringOptionsFlags_exists = false;
	bool MatrixPresent_exists = false;
	bool GlyphCount_exists = false;
	bool Glyphs_exists = false;

	DWORD& cType() {
		assert_cond(cType_exists, "struct field cType does not exist");
		return cType_var;
	}
	DWORD& cSize() {
		assert_cond(cSize_exists, "struct field cSize does not exist");
		return cSize_var;
	}
	DWORD& cDataSize() {
		assert_cond(cDataSize_exists, "struct field cDataSize does not exist");
		return cDataSize_var;
	}
	DWORD& cIdentifier() {
		assert_cond(cIdentifier_exists, "struct field cIdentifier does not exist");
		return cIdentifier_var;
	}
	WORD& Type() {
		assert_cond(Type_exists, "struct field Type does not exist");
		return Type_var;
	}
	WORD& Flags() {
		assert_cond(Flags_exists, "struct field Flags does not exist");
		return Flags_var;
	}
	DWORD& Size() {
		assert_cond(Size_exists, "struct field Size does not exist");
		return Size_var;
	}
	DWORD& DataSize() {
		assert_cond(DataSize_exists, "struct field DataSize does not exist");
		return DataSize_var;
	}
	DWORD& BrushId() {
		assert_cond(BrushId_exists, "struct field BrushId does not exist");
		return BrushId_var;
	}
	DWORD& DriverStringOptionsFlags() {
		assert_cond(DriverStringOptionsFlags_exists, "struct field DriverStringOptionsFlags does not exist");
		return DriverStringOptionsFlags_var;
	}
	DWORD& MatrixPresent() {
		assert_cond(MatrixPresent_exists, "struct field MatrixPresent does not exist");
		return MatrixPresent_var;
	}
	DWORD& GlyphCount() {
		assert_cond(GlyphCount_exists, "struct field GlyphCount does not exist");
		return GlyphCount_var;
	}
	std::vector<DWORD>& Glyphs() {
		assert_cond(Glyphs_exists, "struct field Glyphs does not exist");
		return Glyphs_var;
	}

	/* locals */
	uint _rGlyphCount;
	uint _cSize;
	uint _cDataSize;
	uint _rSize;
	uint _rDataSize;
	uint start;
	uint end;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EmfPlusDrawDriverString& operator () () { return *instances.back(); }
	EmfPlusDrawDriverString& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EmfPlusDrawDriverString(std::vector<EmfPlusDrawDriverString*>& instances) : instances(instances) { instances.push_back(this); }
	~EmfPlusDrawDriverString() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EmfPlusDrawDriverString* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EmfPlusDrawDriverString* generate();
};

int EmfPlusDrawDriverString::_parent_id = 0;
int EmfPlusDrawDriverString::_index_start = 0;



class QWORD_class {
	int small;
	std::vector<QWORD> known_values;
	QWORD value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = sizeof(QWORD);
	QWORD operator () () { return value; }
	QWORD_class(int small, std::vector<QWORD> known_values = {}) : small(small), known_values(known_values) {}

	QWORD generate() {
		_startof = FTell();
		if (known_values.empty()) {
			value = file_acc.file_integer(sizeof(QWORD), 0, small);
		} else {
			value = file_acc.file_integer(sizeof(QWORD), 0, known_values);
		}
		return value;
	}

	QWORD generate(std::vector<QWORD> possible_values) {
		_startof = FTell();
		value = file_acc.file_integer(sizeof(QWORD), 0, possible_values);
		return value;
	}
};



class GUID {
	std::vector<GUID*>& instances;

	DWORD Data1_var;
	WORD Data2_var;
	WORD Data3_var;
	QWORD Data4_var;

public:
	bool Data1_exists = false;
	bool Data2_exists = false;
	bool Data3_exists = false;
	bool Data4_exists = false;

	DWORD& Data1() {
		assert_cond(Data1_exists, "struct field Data1 does not exist");
		return Data1_var;
	}
	WORD& Data2() {
		assert_cond(Data2_exists, "struct field Data2 does not exist");
		return Data2_var;
	}
	WORD& Data3() {
		assert_cond(Data3_exists, "struct field Data3 does not exist");
		return Data3_var;
	}
	QWORD& Data4() {
		assert_cond(Data4_exists, "struct field Data4 does not exist");
		return Data4_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	GUID& operator () () { return *instances.back(); }
	GUID& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	GUID(std::vector<GUID*>& instances) : instances(instances) { instances.push_back(this); }
	~GUID() {
		if (generated == 2)
			return;
		while (instances.size()) {
			GUID* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	GUID* generate();
};

int GUID::_parent_id = 0;
int GUID::_index_start = 0;



class BYTE_class {
	int small;
	std::vector<BYTE> known_values;
	BYTE value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = sizeof(BYTE);
	BYTE operator () () { return value; }
	BYTE_class(int small, std::vector<BYTE> known_values = {}) : small(small), known_values(known_values) {}

	BYTE generate() {
		_startof = FTell();
		if (known_values.empty()) {
			value = file_acc.file_integer(sizeof(BYTE), 0, small);
		} else {
			value = file_acc.file_integer(sizeof(BYTE), 0, known_values);
		}
		return value;
	}

	BYTE generate(std::vector<BYTE> possible_values) {
		_startof = FTell();
		value = file_acc.file_integer(sizeof(BYTE), 0, possible_values);
		return value;
	}
};



class BYTE_array_class {
	BYTE_class& element;
	std::unordered_map<int, std::vector<BYTE>> element_known_values;
	std::vector<BYTE> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<BYTE>& operator () () { return value; }
	BYTE operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return value[index];
	}
	BYTE_array_class(BYTE_class& element, std::unordered_map<int, std::vector<BYTE>> element_known_values = {})
		: element(element), element_known_values(element_known_values) {}

	std::vector<BYTE> generate(unsigned size) {
		check_array_length(size);
		_startof = FTell();
		value = {};
		for (unsigned i = 0; i < size; ++i) {
			auto known = element_known_values.find(i);
			if (known == element_known_values.end()) {
				value.push_back(element.generate());
				_sizeof += element._sizeof;
			} else {
				value.push_back(file_acc.file_integer(sizeof(BYTE), 0, known->second));
				_sizeof += sizeof(BYTE);
			}
		}
		return value;
	}
};



class EmfPlusSerializableObject {
	std::vector<EmfPlusSerializableObject*>& instances;

	DWORD cType_var;
	DWORD cSize_var;
	DWORD cDataSize_var;
	DWORD cIdentifier_var;
	WORD Type_var;
	WORD Flags_var;
	DWORD Size_var;
	DWORD DataSize_var;
	GUID* ObjectGUID_var;
	DWORD BufferSize_var;
	std::vector<BYTE> Buffer_var;

public:
	bool cType_exists = false;
	bool cSize_exists = false;
	bool cDataSize_exists = false;
	bool cIdentifier_exists = false;
	bool Type_exists = false;
	bool Flags_exists = false;
	bool Size_exists = false;
	bool DataSize_exists = false;
	bool ObjectGUID_exists = false;
	bool BufferSize_exists = false;
	bool Buffer_exists = false;

	DWORD& cType() {
		assert_cond(cType_exists, "struct field cType does not exist");
		return cType_var;
	}
	DWORD& cSize() {
		assert_cond(cSize_exists, "struct field cSize does not exist");
		return cSize_var;
	}
	DWORD& cDataSize() {
		assert_cond(cDataSize_exists, "struct field cDataSize does not exist");
		return cDataSize_var;
	}
	DWORD& cIdentifier() {
		assert_cond(cIdentifier_exists, "struct field cIdentifier does not exist");
		return cIdentifier_var;
	}
	WORD& Type() {
		assert_cond(Type_exists, "struct field Type does not exist");
		return Type_var;
	}
	WORD& Flags() {
		assert_cond(Flags_exists, "struct field Flags does not exist");
		return Flags_var;
	}
	DWORD& Size() {
		assert_cond(Size_exists, "struct field Size does not exist");
		return Size_var;
	}
	DWORD& DataSize() {
		assert_cond(DataSize_exists, "struct field DataSize does not exist");
		return DataSize_var;
	}
	GUID& ObjectGUID() {
		assert_cond(ObjectGUID_exists, "struct field ObjectGUID does not exist");
		return *ObjectGUID_var;
	}
	DWORD& BufferSize() {
		assert_cond(BufferSize_exists, "struct field BufferSize does not exist");
		return BufferSize_var;
	}
	std::vector<BYTE>& Buffer() {
		assert_cond(Buffer_exists, "struct field Buffer does not exist");
		return Buffer_var;
	}

	/* locals */
	uint _cSize;
	uint _cDataSize;
	uint _rSize;
	uint _rDataSize;
	uint start;
	uint end;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EmfPlusSerializableObject& operator () () { return *instances.back(); }
	EmfPlusSerializableObject& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EmfPlusSerializableObject(std::vector<EmfPlusSerializableObject*>& instances) : instances(instances) { instances.push_back(this); }
	~EmfPlusSerializableObject() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EmfPlusSerializableObject* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EmfPlusSerializableObject* generate();
};

int EmfPlusSerializableObject::_parent_id = 0;
int EmfPlusSerializableObject::_index_start = 0;



class EMFPLUSEOF {
	std::vector<EMFPLUSEOF*>& instances;

	DWORD cType_var;
	DWORD cSize_var;
	DWORD cDataSize_var;
	DWORD cIdentifier_var;
	WORD Type_var;
	WORD Flags_var;
	DWORD Size_var;
	DWORD DataSize_var;

public:
	bool cType_exists = false;
	bool cSize_exists = false;
	bool cDataSize_exists = false;
	bool cIdentifier_exists = false;
	bool Type_exists = false;
	bool Flags_exists = false;
	bool Size_exists = false;
	bool DataSize_exists = false;

	DWORD& cType() {
		assert_cond(cType_exists, "struct field cType does not exist");
		return cType_var;
	}
	DWORD& cSize() {
		assert_cond(cSize_exists, "struct field cSize does not exist");
		return cSize_var;
	}
	DWORD& cDataSize() {
		assert_cond(cDataSize_exists, "struct field cDataSize does not exist");
		return cDataSize_var;
	}
	DWORD& cIdentifier() {
		assert_cond(cIdentifier_exists, "struct field cIdentifier does not exist");
		return cIdentifier_var;
	}
	WORD& Type() {
		assert_cond(Type_exists, "struct field Type does not exist");
		return Type_var;
	}
	WORD& Flags() {
		assert_cond(Flags_exists, "struct field Flags does not exist");
		return Flags_var;
	}
	DWORD& Size() {
		assert_cond(Size_exists, "struct field Size does not exist");
		return Size_var;
	}
	DWORD& DataSize() {
		assert_cond(DataSize_exists, "struct field DataSize does not exist");
		return DataSize_var;
	}

	/* locals */
	uint _cSize;
	uint _cDataSize;
	uint _rSize;
	uint _rDataSize;
	uint start;
	uint end;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMFPLUSEOF& operator () () { return *instances.back(); }
	EMFPLUSEOF& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMFPLUSEOF(std::vector<EMFPLUSEOF*>& instances) : instances(instances) { instances.push_back(this); }
	~EMFPLUSEOF() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMFPLUSEOF* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMFPLUSEOF* generate();
};

int EMFPLUSEOF::_parent_id = 0;
int EMFPLUSEOF::_index_start = 0;



class uchar_class {
	int small;
	std::vector<uchar> known_values;
	uchar value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = sizeof(uchar);
	uchar operator () () { return value; }
	uchar_class(int small, std::vector<uchar> known_values = {}) : small(small), known_values(known_values) {}

	uchar generate() {
		_startof = FTell();
		if (known_values.empty()) {
			value = file_acc.file_integer(sizeof(uchar), 0, small);
		} else {
			value = file_acc.file_integer(sizeof(uchar), 0, known_values);
		}
		return value;
	}

	uchar generate(std::vector<uchar> possible_values) {
		_startof = FTell();
		value = file_acc.file_integer(sizeof(uchar), 0, possible_values);
		return value;
	}
};



class PALETTEENTRY {
	std::vector<PALETTEENTRY*>& instances;

	uchar Reserved_var;
	uchar Blue_var;
	uchar Green_var;
	uchar Red_var;

public:
	bool Reserved_exists = false;
	bool Blue_exists = false;
	bool Green_exists = false;
	bool Red_exists = false;

	uchar& Reserved() {
		assert_cond(Reserved_exists, "struct field Reserved does not exist");
		return Reserved_var;
	}
	uchar& Blue() {
		assert_cond(Blue_exists, "struct field Blue does not exist");
		return Blue_var;
	}
	uchar& Green() {
		assert_cond(Green_exists, "struct field Green does not exist");
		return Green_var;
	}
	uchar& Red() {
		assert_cond(Red_exists, "struct field Red does not exist");
		return Red_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	PALETTEENTRY& operator () () { return *instances.back(); }
	PALETTEENTRY& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	PALETTEENTRY(std::vector<PALETTEENTRY*>& instances) : instances(instances) { instances.push_back(this); }
	~PALETTEENTRY() {
		if (generated == 2)
			return;
		while (instances.size()) {
			PALETTEENTRY* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	PALETTEENTRY* generate();
};

int PALETTEENTRY::_parent_id = 0;
int PALETTEENTRY::_index_start = 0;



class EMREOF {
	std::vector<EMREOF*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD nPalEntries_var;
	DWORD offPalEntries_var;
	PALETTEENTRY* palEntry_var;
	DWORD SizeLast_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool nPalEntries_exists = false;
	bool offPalEntries_exists = false;
	bool palEntry_exists = false;
	bool SizeLast_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& nPalEntries() {
		assert_cond(nPalEntries_exists, "struct field nPalEntries does not exist");
		return nPalEntries_var;
	}
	DWORD& offPalEntries() {
		assert_cond(offPalEntries_exists, "struct field offPalEntries does not exist");
		return offPalEntries_var;
	}
	PALETTEENTRY& palEntry() {
		assert_cond(palEntry_exists, "struct field palEntry does not exist");
		return *palEntry_var;
	}
	DWORD& SizeLast() {
		assert_cond(SizeLast_exists, "struct field SizeLast does not exist");
		return SizeLast_var;
	}

	/* locals */
	uint palCnt;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMREOF& operator () () { return *instances.back(); }
	EMREOF& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMREOF(std::vector<EMREOF*>& instances) : instances(instances) { instances.push_back(this); }
	~EMREOF() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMREOF* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMREOF* generate();
};

int EMREOF::_parent_id = 0;
int EMREOF::_index_start = 0;

std::vector<byte> ReadByteInitValues;
std::vector<ubyte> ReadUByteInitValues;
std::vector<short> ReadShortInitValues;
std::vector<ushort> ReadUShortInitValues;
std::vector<int> ReadIntInitValues;
std::vector<uint> ReadUIntInitValues;
std::vector<int64> ReadQuadInitValues;
std::vector<uint64> ReadUQuadInitValues;
std::vector<int64> ReadInt64InitValues;
std::vector<uint64> ReadUInt64InitValues;
std::vector<hfloat> ReadHFloatInitValues;
std::vector<float> ReadFloatInitValues;
std::vector<double> ReadDoubleInitValues;
std::vector<std::string> ReadBytesInitValues;


std::vector<RECTL*> RECTL_rclBounds_instances;
std::vector<RECTL*> RECTL_rclFrame_instances;
std::vector<SIZEL*> SIZEL_szlDevice_instances;
std::vector<SIZEL*> SIZEL_szlMillimeters_instances;
std::vector<HeaderExtension1*> HeaderExtension1_EmfHeaderExtension1_instances;
std::vector<HeaderExtension2*> HeaderExtension2_EmfHeaderExtension2_instances;
std::vector<EMRHEADER*> EMRHEADER_EmfHeader_instances;
std::vector<EMRDESCRIPTION*> EMRDESCRIPTION_EmfDescription_instances;
std::vector<EMFPLUSHEADER*> EMFPLUSHEADER_EmfPlusHeader_instances;
std::vector<COLORREF*> COLORREF_Color_instances;
std::vector<EmfPlusClear*> EmfPlusClear_Clear_instances;
std::vector<EmfPlusRect*> EmfPlusRect_RectData_element_instances;
std::vector<EmfPlusFillRects*> EmfPlusFillRects_FillRects_instances;
std::vector<EmfPlusPointF*> EmfPlusPointF_Points_element_instances;
std::vector<EmfPlusDrawLines*> EmfPlusDrawLines_DrawLines_instances;
std::vector<EmfPlusRect*> EmfPlusRect_Rects_element_instances;
std::vector<EmfPlusSetTSClip*> EmfPlusSetTSClip_SetTSClip_instances;
std::vector<EmfPlusDrawDriverString*> EmfPlusDrawDriverString_DrawDriverString_instances;
std::vector<GUID*> GUID_ObjectGUID_instances;
std::vector<EmfPlusSerializableObject*> EmfPlusSerializableObject_SerializableObject_instances;
std::vector<EMFPLUSEOF*> EMFPLUSEOF_EmfPlusEndOfFile_instances;
std::vector<PALETTEENTRY*> PALETTEENTRY_palEntry_instances;
std::vector<EMREOF*> EMREOF_EmfEndOfFile_instances;


std::unordered_map<std::string, std::string> variable_types = { { "iType", "DWORD_class" }, { "nSize", "DWORD_class" }, { "left", "LONG_class" }, { "top", "LONG_class" }, { "right", "LONG_class" }, { "bottom", "LONG_class" }, { "rclBounds", "RECTL" }, { "rclFrame", "RECTL" }, { "dSignature", "DWORD_class" }, { "nVersion", "DWORD_class" }, { "nBytes", "DWORD_class" }, { "nRecords", "DWORD_class" }, { "nHandles", "WORD_class" }, { "sReserved", "WORD_class" }, { "nDescription", "DWORD_class" }, { "offDescription", "DWORD_class" }, { "nPalEntries", "DWORD_class" }, { "cx", "LONG_class" }, { "cy", "LONG_class" }, { "szlDevice", "SIZEL" }, { "szlMillimeters", "SIZEL" }, { "cbPixelFormat", "DWORD_class" }, { "offPixelFormat", "DWORD_class" }, { "bOpenGL", "DWORD_class" }, { "EmfHeaderExtension1", "HeaderExtension1" }, { "MicrometersX", "DWORD_class" }, { "MicrometersY", "DWORD_class" }, { "EmfHeaderExtension2", "HeaderExtension2" }, { "EmfHeader", "EMRHEADER" }, { "desc", "WORD_array_class" }, { "EmfDescription", "EMRDESCRIPTION" }, { "cType", "DWORD_class" }, { "cSize", "DWORD_class" }, { "cDataSize", "DWORD_class" }, { "cIdentifier", "DWORD_class" }, { "Type", "WORD_class" }, { "Flags", "WORD_class" }, { "Size", "DWORD_class" }, { "DataSize", "DWORD_class" }, { "Version", "DWORD_class" }, { "EmfPlusFlags", "DWORD_class" }, { "LogicalDpiX", "DWORD_class" }, { "LogicalDpiY", "DWORD_class" }, { "EmfPlusHeader", "EMFPLUSHEADER" }, { "recType", "UBYTE_class" }, { "Red", "UBYTE_class" }, { "Green", "UBYTE_class" }, { "Blue", "UBYTE_class" }, { "Reserved", "UBYTE_class" }, { "Color", "COLORREF" }, { "Clear", "EmfPlusClear" }, { "BrushID", "DWORD_class" }, { "Count", "DWORD_class" }, { "X", "WORD_class" }, { "Y", "WORD_class" }, { "Width", "WORD_class" }, { "Height", "WORD_class" }, { "RectData", "EmfPlusRect_array_class" }, { "FillRects", "EmfPlusFillRects" }, { "X_", "DWORD_class" }, { "Y_", "DWORD_class" }, { "Points", "EmfPlusPointF_array_class" }, { "DrawLines", "EmfPlusDrawLines" }, { "Rects", "EmfPlusRect_array_class" }, { "SetTSClip", "EmfPlusSetTSClip" }, { "BrushId", "DWORD_class" }, { "DriverStringOptionsFlags", "DWORD_class" }, { "MatrixPresent", "DWORD_class" }, { "GlyphCount", "DWORD_class" }, { "Glyphs", "DWORD_array_class" }, { "DrawDriverString", "EmfPlusDrawDriverString" }, { "Data1", "DWORD_class" }, { "Data2", "WORD_class" }, { "Data3", "WORD_class" }, { "Data4", "QWORD_class" }, { "ObjectGUID", "GUID" }, { "BufferSize", "DWORD_class" }, { "Buffer", "BYTE_array_class" }, { "SerializableObject", "EmfPlusSerializableObject" }, { "EmfPlusEndOfFile", "EMFPLUSEOF" }, { "offPalEntries", "DWORD_class" }, { "Reserved_", "uchar_class" }, { "Blue_", "uchar_class" }, { "Green_", "uchar_class" }, { "Red_", "uchar_class" }, { "palEntry", "PALETTEENTRY" }, { "SizeLast", "DWORD_class" }, { "EmfEndOfFile", "EMREOF" } };

std::vector<std::vector<int>> integer_ranges = { { 1, 16 }, { 5, 5 } };

class globals_class {
public:
	int _struct_id = 0;
	int _struct_id_counter = 0;
	DWORD_class iType;
	DWORD_class nSize;
	LONG_class left;
	LONG_class top;
	LONG_class right;
	LONG_class bottom;
	RECTL rclBounds;
	RECTL rclFrame;
	DWORD_class dSignature;
	DWORD_class nVersion;
	DWORD_class nBytes;
	DWORD_class nRecords;
	WORD_class nHandles;
	WORD_class sReserved;
	DWORD_class nDescription;
	DWORD_class offDescription;
	DWORD_class nPalEntries;
	LONG_class cx;
	LONG_class cy;
	SIZEL szlDevice;
	SIZEL szlMillimeters;
	DWORD_class cbPixelFormat;
	DWORD_class offPixelFormat;
	DWORD_class bOpenGL;
	HeaderExtension1 EmfHeaderExtension1;
	DWORD_class MicrometersX;
	DWORD_class MicrometersY;
	HeaderExtension2 EmfHeaderExtension2;
	EMRHEADER EmfHeader;
	/*local*/ uint EmfHeaderSize;
	WORD_class desc_element;
	WORD_array_class desc;
	EMRDESCRIPTION EmfDescription;
	DWORD_class cType;
	DWORD_class cSize;
	DWORD_class cDataSize;
	DWORD_class cIdentifier;
	WORD_class Type;
	WORD_class Flags;
	DWORD_class Size;
	DWORD_class DataSize;
	DWORD_class Version;
	DWORD_class EmfPlusFlags;
	DWORD_class LogicalDpiX;
	DWORD_class LogicalDpiY;
	EMFPLUSHEADER EmfPlusHeader;
	/*local*/ uint recCnt;
	UBYTE_class recType;
	UBYTE_class Red;
	UBYTE_class Green;
	UBYTE_class Blue;
	UBYTE_class Reserved;
	COLORREF Color;
	EmfPlusClear Clear;
	DWORD_class BrushID;
	DWORD_class Count;
	WORD_class X;
	WORD_class Y;
	WORD_class Width;
	WORD_class Height;
	EmfPlusRect RectData_element;
	EmfPlusRect_array_class RectData;
	EmfPlusFillRects FillRects;
	DWORD_class X_;
	DWORD_class Y_;
	EmfPlusPointF Points_element;
	EmfPlusPointF_array_class Points;
	EmfPlusDrawLines DrawLines;
	EmfPlusRect Rects_element;
	EmfPlusRect_array_class Rects;
	EmfPlusSetTSClip SetTSClip;
	DWORD_class BrushId;
	DWORD_class DriverStringOptionsFlags;
	DWORD_class MatrixPresent;
	DWORD_class GlyphCount;
	DWORD_class Glyphs_element;
	DWORD_array_class Glyphs;
	EmfPlusDrawDriverString DrawDriverString;
	DWORD_class Data1;
	WORD_class Data2;
	WORD_class Data3;
	QWORD_class Data4;
	GUID ObjectGUID;
	DWORD_class BufferSize;
	BYTE_class Buffer_element;
	BYTE_array_class Buffer;
	EmfPlusSerializableObject SerializableObject;
	/*local*/ std::vector<UBYTE> possible;
	EMFPLUSEOF EmfPlusEndOfFile;
	DWORD_class offPalEntries;
	uchar_class Reserved_;
	uchar_class Blue_;
	uchar_class Green_;
	uchar_class Red_;
	PALETTEENTRY palEntry;
	DWORD_class SizeLast;
	EMREOF EmfEndOfFile;
	/*local*/ DWORD file_size;


	globals_class() :
		iType(1),
		nSize(1),
		left(1),
		top(1),
		right(1),
		bottom(1),
		rclBounds(RECTL_rclBounds_instances),
		rclFrame(RECTL_rclFrame_instances),
		dSignature(1, { 0x464D4520 }),
		nVersion(1),
		nBytes(1),
		nRecords(3),
		nHandles(1),
		sReserved(1),
		nDescription(1),
		offDescription(1),
		nPalEntries(1),
		cx(1),
		cy(1),
		szlDevice(SIZEL_szlDevice_instances),
		szlMillimeters(SIZEL_szlMillimeters_instances),
		cbPixelFormat(1),
		offPixelFormat(1),
		bOpenGL(1),
		EmfHeaderExtension1(HeaderExtension1_EmfHeaderExtension1_instances),
		MicrometersX(1),
		MicrometersY(1),
		EmfHeaderExtension2(HeaderExtension2_EmfHeaderExtension2_instances),
		EmfHeader(EMRHEADER_EmfHeader_instances),
		desc_element(false),
		desc(desc_element),
		EmfDescription(EMRDESCRIPTION_EmfDescription_instances),
		cType(1),
		cSize(1),
		cDataSize(1),
		cIdentifier(1),
		Type(1),
		Flags(1),
		Size(1),
		DataSize(1),
		Version(1),
		EmfPlusFlags(1),
		LogicalDpiX(1),
		LogicalDpiY(1),
		EmfPlusHeader(EMFPLUSHEADER_EmfPlusHeader_instances),
		recType(1, { 0x9, 0xa, 0xd, 0x3a, 0x36, 0x38 }),
		Red(1),
		Green(1),
		Blue(1),
		Reserved(1),
		Color(COLORREF_Color_instances),
		Clear(EmfPlusClear_Clear_instances),
		BrushID(1),
		Count(1),
		X(1),
		Y(1),
		Width(1),
		Height(1),
		RectData_element(EmfPlusRect_RectData_element_instances),
		RectData(RectData_element),
		FillRects(EmfPlusFillRects_FillRects_instances),
		X_(1),
		Y_(1),
		Points_element(EmfPlusPointF_Points_element_instances),
		Points(Points_element),
		DrawLines(EmfPlusDrawLines_DrawLines_instances),
		Rects_element(EmfPlusRect_Rects_element_instances),
		Rects(Rects_element),
		SetTSClip(EmfPlusSetTSClip_SetTSClip_instances),
		BrushId(1),
		DriverStringOptionsFlags(1),
		MatrixPresent(1),
		GlyphCount(1),
		Glyphs_element(false),
		Glyphs(Glyphs_element),
		DrawDriverString(EmfPlusDrawDriverString_DrawDriverString_instances),
		Data1(1),
		Data2(1),
		Data3(1),
		Data4(1),
		ObjectGUID(GUID_ObjectGUID_instances),
		BufferSize(1),
		Buffer_element(false),
		Buffer(Buffer_element),
		SerializableObject(EmfPlusSerializableObject_SerializableObject_instances),
		EmfPlusEndOfFile(EMFPLUSEOF_EmfPlusEndOfFile_instances),
		offPalEntries(1),
		Reserved_(1),
		Blue_(1),
		Green_(1),
		Red_(1),
		palEntry(PALETTEENTRY_palEntry_instances),
		SizeLast(1),
		EmfEndOfFile(EMREOF_EmfEndOfFile_instances)
	{}
};

globals_class* g;

uint SetEmfPlusSize(uint commentSize, uint dataSize) {
	/*local*/ uint nSize = 0;
	nSize = (commentSize + dataSize);
	if (((nSize % 4) != 0)) {
		Warning("Record size is invalid. Template stopped.");
		return (-1);
	};
	return (nSize);
}

RECTL* RECTL::generate() {
	if (generated == 1) {
		RECTL* new_instance = new RECTL(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(left, ::g->left.generate({ 20 }));
	GENERATE_VAR(top, ::g->top.generate({ 30 }));
	GENERATE_VAR(right, ::g->right.generate({ 180 }));
	GENERATE_VAR(bottom, ::g->bottom.generate({ 230 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


SIZEL* SIZEL::generate() {
	if (generated == 1) {
		SIZEL* new_instance = new SIZEL(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(cx, ::g->cx.generate());
	GENERATE_VAR(cy, ::g->cy.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


HeaderExtension1* HeaderExtension1::generate() {
	if (generated == 1) {
		HeaderExtension1* new_instance = new HeaderExtension1(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(cbPixelFormat, ::g->cbPixelFormat.generate());
	GENERATE_VAR(offPixelFormat, ::g->offPixelFormat.generate());
	GENERATE_VAR(bOpenGL, ::g->bOpenGL.generate({ {0}, {1} }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


HeaderExtension2* HeaderExtension2::generate() {
	if (generated == 1) {
		HeaderExtension2* new_instance = new HeaderExtension2(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(MicrometersX, ::g->MicrometersX.generate());
	GENERATE_VAR(MicrometersY, ::g->MicrometersY.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRHEADER* EMRHEADER::generate() {
	if (generated == 1) {
		EMRHEADER* new_instance = new EMRHEADER(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(iType, ::g->iType.generate({ 0x00000001 }));
	GENERATE_VAR(nSize, ::g->nSize.generate());
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(rclFrame, ::g->rclFrame.generate());
	GENERATE_VAR(dSignature, ::g->dSignature.generate({ 0x464D4520 }));
	GENERATE_VAR(nVersion, ::g->nVersion.generate({ 0x00010000 }));
	GENERATE_VAR(nBytes, ::g->nBytes.generate());
	GENERATE_VAR(nRecords, ::g->nRecords.generate());
	GENERATE_VAR(nHandles, ::g->nHandles.generate());
	GENERATE_VAR(sReserved, ::g->sReserved.generate({ 0 }));
	GENERATE_VAR(nDescription, ::g->nDescription.generate({ 0, 4, 8, 12, 16 }));
	GENERATE_VAR(offDescription, ::g->offDescription.generate({ 0x0000006c }));
	GENERATE_VAR(nPalEntries, ::g->nPalEntries.generate({ 0 }));
	GENERATE_VAR(szlDevice, ::g->szlDevice.generate());
	GENERATE_VAR(szlMillimeters, ::g->szlMillimeters.generate());
	GENERATE_VAR(EmfHeaderExtension1, ::g->EmfHeaderExtension1.generate());
	GENERATE_VAR(EmfHeaderExtension2, ::g->EmfHeaderExtension2.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRDESCRIPTION* EMRDESCRIPTION::generate() {
	if (generated == 1) {
		EMRDESCRIPTION* new_instance = new EMRDESCRIPTION(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(desc, ::g->desc.generate(::g->EmfHeader().nDescription()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMFPLUSHEADER* EMFPLUSHEADER::generate() {
	if (generated == 1) {
		EMFPLUSHEADER* new_instance = new EMFPLUSHEADER(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	_cSize = 0x00000010;
	_cDataSize = 0x00000004;
	_rSize = 0x0000001c;
	_rDataSize = 0x00000010;
	start = FTell();
	FSeek(start);
	GENERATE_VAR(cType, ::g->cType.generate({ 0x00000046 }));
	GENERATE_VAR(cSize, ::g->cSize.generate({ _cSize }));
	GENERATE_VAR(cDataSize, ::g->cDataSize.generate({ _cDataSize }));
	GENERATE_VAR(cIdentifier, ::g->cIdentifier.generate({ 0x2B464D45 }));
	GENERATE_VAR(Type, ::g->Type.generate({ 0x4001 }));
	GENERATE_VAR(Flags, ::g->Flags.generate({ 0x0001 }));
	GENERATE_VAR(Size, ::g->Size.generate({ _rSize }));
	GENERATE_VAR(DataSize, ::g->DataSize.generate({ _rDataSize }));
	GENERATE_VAR(Version, ::g->Version.generate({ 0xDBC01002 }));
	GENERATE_VAR(EmfPlusFlags, ::g->EmfPlusFlags.generate());
	GENERATE_VAR(LogicalDpiX, ::g->LogicalDpiX.generate());
	GENERATE_VAR(LogicalDpiY, ::g->LogicalDpiY.generate());
	end = FTell();
	FSeek((start + 4));
	GENERATE_VAR(cSize, ::g->cSize.generate({ SetEmfPlusSize(_cSize, _rSize) }));
	GENERATE_VAR(cDataSize, ::g->cDataSize.generate({ SetEmfPlusSize(_cDataSize, _rSize) }));
	FSeek(end);

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


COLORREF* COLORREF::generate() {
	if (generated == 1) {
		COLORREF* new_instance = new COLORREF(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(Red, ::g->Red.generate());
	GENERATE_VAR(Green, ::g->Green.generate());
	GENERATE_VAR(Blue, ::g->Blue.generate());
	GENERATE_VAR(Reserved, ::g->Reserved.generate({ 0x00 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EmfPlusClear* EmfPlusClear::generate() {
	if (generated == 1) {
		EmfPlusClear* new_instance = new EmfPlusClear(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	_cSize = 0x00000010;
	_cDataSize = 0x00000004;
	_rSize = 0x00000010;
	_rDataSize = 0x00000004;
	start = FTell();
	FSeek(start);
	GENERATE_VAR(cType, ::g->cType.generate({ 0x00000046 }));
	GENERATE_VAR(cSize, ::g->cSize.generate({ _cSize }));
	GENERATE_VAR(cDataSize, ::g->cDataSize.generate({ _cDataSize }));
	GENERATE_VAR(cIdentifier, ::g->cIdentifier.generate({ 0x2B464D45 }));
	GENERATE_VAR(Type, ::g->Type.generate({ 0x4009 }));
	GENERATE_VAR(Flags, ::g->Flags.generate({ 0x0000 }));
	GENERATE_VAR(Size, ::g->Size.generate({ _rSize }));
	GENERATE_VAR(DataSize, ::g->DataSize.generate({ _rDataSize }));
	GENERATE_VAR(Color, ::g->Color.generate());
	end = FTell();
	FSeek((start + 4));
	GENERATE_VAR(cSize, ::g->cSize.generate({ SetEmfPlusSize(_cSize, _rSize) }));
	GENERATE_VAR(cDataSize, ::g->cDataSize.generate({ SetEmfPlusSize(_cDataSize, _rSize) }));
	FSeek(end);

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EmfPlusRect* EmfPlusRect::generate() {
	if (generated == 1) {
		EmfPlusRect* new_instance = new EmfPlusRect(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(X, ::g->X.generate());
	GENERATE_VAR(Y, ::g->Y.generate());
	GENERATE_VAR(Width, ::g->Width.generate());
	GENERATE_VAR(Height, ::g->Height.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EmfPlusFillRects* EmfPlusFillRects::generate() {
	if (generated == 1) {
		EmfPlusFillRects* new_instance = new EmfPlusFillRects(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	_cSize = 0x00000010;
	_cDataSize = 0x00000004;
	_rSize = 0x00000024;
	_rDataSize = 0x00000018;
	start = FTell();
	FSeek(start);
	GENERATE_VAR(cType, ::g->cType.generate({ 0x00000046 }));
	GENERATE_VAR(cSize, ::g->cSize.generate({ _cSize }));
	GENERATE_VAR(cDataSize, ::g->cDataSize.generate({ _cDataSize }));
	GENERATE_VAR(cIdentifier, ::g->cIdentifier.generate({ 0x2B464D45 }));
	GENERATE_VAR(Type, ::g->Type.generate({ 0x400A }));
	GENERATE_VAR(Flags, ::g->Flags.generate());
	GENERATE_VAR(Size, ::g->Size.generate({ _rSize }));
	GENERATE_VAR(DataSize, ::g->DataSize.generate({ _rDataSize }));
	GENERATE_VAR(BrushID, ::g->BrushID.generate());
	GENERATE_VAR(Count, ::g->Count.generate({ 0x00000001 }));
	GENERATE_VAR(RectData, ::g->RectData.generate(1));
	end = FTell();
	FSeek((start + 4));
	GENERATE_VAR(cSize, ::g->cSize.generate({ SetEmfPlusSize(_cSize, _rSize) }));
	GENERATE_VAR(cDataSize, ::g->cDataSize.generate({ SetEmfPlusSize(_cDataSize, _rSize) }));
	FSeek(end);

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EmfPlusPointF* EmfPlusPointF::generate() {
	if (generated == 1) {
		EmfPlusPointF* new_instance = new EmfPlusPointF(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(X, ::g->X_.generate());
	GENERATE_VAR(Y, ::g->Y_.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EmfPlusDrawLines* EmfPlusDrawLines::generate() {
	if (generated == 1) {
		EmfPlusDrawLines* new_instance = new EmfPlusDrawLines(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	_rCount = 1;
	_cSize = 0x00000010;
	_cDataSize = 0x00000004;
	_rSize = ((_rCount * 0x00000008) + 0x00000010);
	_rDataSize = ((_rCount * 0x00000008) + 0x00000004);
	start = FTell();
	FSeek(start);
	GENERATE_VAR(cType, ::g->cType.generate({ 0x00000046 }));
	GENERATE_VAR(cSize, ::g->cSize.generate({ _cSize }));
	GENERATE_VAR(cDataSize, ::g->cDataSize.generate({ _cDataSize }));
	GENERATE_VAR(cIdentifier, ::g->cIdentifier.generate({ 0x2B464D45 }));
	GENERATE_VAR(Type, ::g->Type.generate({ 0x400d }));
	GENERATE_VAR(Flags, ::g->Flags.generate());
	GENERATE_VAR(Size, ::g->Size.generate({ _rSize }));
	GENERATE_VAR(DataSize, ::g->DataSize.generate({ _rDataSize }));
	GENERATE_VAR(Count, ::g->Count.generate({ _rCount }));
	GENERATE_VAR(Points, ::g->Points.generate(_rCount));
	end = FTell();
	FSeek((start + 4));
	GENERATE_VAR(cSize, ::g->cSize.generate({ SetEmfPlusSize(_cSize, _rSize) }));
	GENERATE_VAR(cDataSize, ::g->cDataSize.generate({ SetEmfPlusSize(_cDataSize, _rSize) }));
	FSeek(end);

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EmfPlusSetTSClip* EmfPlusSetTSClip::generate() {
	if (generated == 1) {
		EmfPlusSetTSClip* new_instance = new EmfPlusSetTSClip(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	_cSize = 0x00000010;
	_cDataSize = 0x00000004;
	_rSize = 0x00000014;
	_rDataSize = 0x00000008;
	start = FTell();
	FSeek(start);
	GENERATE_VAR(cType, ::g->cType.generate({ 0x00000046 }));
	GENERATE_VAR(cSize, ::g->cSize.generate({ _cSize }));
	GENERATE_VAR(cDataSize, ::g->cDataSize.generate({ _cDataSize }));
	GENERATE_VAR(cIdentifier, ::g->cIdentifier.generate({ 0x2B464D45 }));
	GENERATE_VAR(Type, ::g->Type.generate({ 0x403a }));
	GENERATE_VAR(Flags, ::g->Flags.generate({ 0x0001 }));
	GENERATE_VAR(Size, ::g->Size.generate({ _rSize }));
	GENERATE_VAR(DataSize, ::g->DataSize.generate({ _rDataSize }));
	GENERATE_VAR(Rects, ::g->Rects.generate(1));
	end = FTell();
	FSeek((start + 4));
	GENERATE_VAR(cSize, ::g->cSize.generate({ SetEmfPlusSize(_cSize, _rSize) }));
	GENERATE_VAR(cDataSize, ::g->cDataSize.generate({ SetEmfPlusSize(_cDataSize, _rSize) }));
	FSeek(end);

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EmfPlusDrawDriverString* EmfPlusDrawDriverString::generate() {
	if (generated == 1) {
		EmfPlusDrawDriverString* new_instance = new EmfPlusDrawDriverString(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	_rGlyphCount = 1;
	_cSize = 0x00000010;
	_cDataSize = 0x00000004;
	_rSize = ((_rGlyphCount * 0x0000000A) + 0x0000001C);
	_rDataSize = ((_rGlyphCount * 0x0000000A) + 0x00000010);
	start = FTell();
	FSeek(start);
	GENERATE_VAR(cType, ::g->cType.generate({ 0x00000046 }));
	GENERATE_VAR(cSize, ::g->cSize.generate({ _cSize }));
	GENERATE_VAR(cDataSize, ::g->cDataSize.generate({ _cDataSize }));
	GENERATE_VAR(cIdentifier, ::g->cIdentifier.generate({ 0x2B464D45 }));
	GENERATE_VAR(Type, ::g->Type.generate({ 0x4036 }));
	GENERATE_VAR(Flags, ::g->Flags.generate());
	GENERATE_VAR(Size, ::g->Size.generate({ _rSize }));
	GENERATE_VAR(DataSize, ::g->DataSize.generate({ _rDataSize }));
	GENERATE_VAR(BrushId, ::g->BrushId.generate());
	GENERATE_VAR(DriverStringOptionsFlags, ::g->DriverStringOptionsFlags.generate());
	GENERATE_VAR(MatrixPresent, ::g->MatrixPresent.generate());
	GENERATE_VAR(GlyphCount, ::g->GlyphCount.generate({ _rGlyphCount }));
	GENERATE_VAR(Glyphs, ::g->Glyphs.generate(_rGlyphCount));
	end = FTell();
	FSeek((start + 4));
	GENERATE_VAR(cSize, ::g->cSize.generate({ SetEmfPlusSize(_cSize, _rSize) }));
	GENERATE_VAR(cDataSize, ::g->cDataSize.generate({ SetEmfPlusSize(_cDataSize, _rSize) }));
	FSeek(end);

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


GUID* GUID::generate() {
	if (generated == 1) {
		GUID* new_instance = new GUID(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(Data1, ::g->Data1.generate());
	GENERATE_VAR(Data2, ::g->Data2.generate());
	GENERATE_VAR(Data3, ::g->Data3.generate());
	GENERATE_VAR(Data4, ::g->Data4.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EmfPlusSerializableObject* EmfPlusSerializableObject::generate() {
	if (generated == 1) {
		EmfPlusSerializableObject* new_instance = new EmfPlusSerializableObject(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	_cSize = 0x00000010;
	_cDataSize = 0x00000004;
	_rSize = 0x00000028;
	_rDataSize = 0x0000001c;
	start = FTell();
	FSeek(start);
	GENERATE_VAR(cType, ::g->cType.generate({ 0x00000046 }));
	GENERATE_VAR(cSize, ::g->cSize.generate({ _cSize }));
	GENERATE_VAR(cDataSize, ::g->cDataSize.generate({ _cDataSize }));
	GENERATE_VAR(cIdentifier, ::g->cIdentifier.generate({ 0x2B464D45 }));
	GENERATE_VAR(Type, ::g->Type.generate({ 0x4038 }));
	GENERATE_VAR(Flags, ::g->Flags.generate());
	GENERATE_VAR(Size, ::g->Size.generate({ _rSize }));
	GENERATE_VAR(DataSize, ::g->DataSize.generate({ _rDataSize }));
	GENERATE_VAR(ObjectGUID, ::g->ObjectGUID.generate());
	GENERATE_VAR(BufferSize, ::g->BufferSize.generate({ 0x00000008 }));
	GENERATE_VAR(Buffer, ::g->Buffer.generate(8));
	end = FTell();
	FSeek((start + 4));
	GENERATE_VAR(cSize, ::g->cSize.generate({ SetEmfPlusSize(_cSize, _rSize) }));
	GENERATE_VAR(cDataSize, ::g->cDataSize.generate({ SetEmfPlusSize(_cDataSize, _rSize) }));
	FSeek(end);

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMFPLUSEOF* EMFPLUSEOF::generate() {
	if (generated == 1) {
		EMFPLUSEOF* new_instance = new EMFPLUSEOF(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	_cSize = 0x00000010;
	_cDataSize = 0x00000004;
	_rSize = 0x0000000c;
	_rDataSize = 0x00000000;
	start = FTell();
	FSeek(start);
	GENERATE_VAR(cType, ::g->cType.generate({ 0x00000046 }));
	GENERATE_VAR(cSize, ::g->cSize.generate({ _cSize }));
	GENERATE_VAR(cDataSize, ::g->cDataSize.generate({ _cDataSize }));
	GENERATE_VAR(cIdentifier, ::g->cIdentifier.generate({ 0x2B464D45 }));
	GENERATE_VAR(Type, ::g->Type.generate({ 0x4002 }));
	GENERATE_VAR(Flags, ::g->Flags.generate({ 0x0000 }));
	GENERATE_VAR(Size, ::g->Size.generate({ _rSize }));
	GENERATE_VAR(DataSize, ::g->DataSize.generate({ _rDataSize }));
	end = FTell();
	FSeek((start + 4));
	GENERATE_VAR(cSize, ::g->cSize.generate({ SetEmfPlusSize(_cSize, _rSize) }));
	GENERATE_VAR(cDataSize, ::g->cDataSize.generate({ SetEmfPlusSize(_cDataSize, _rSize) }));
	FSeek(end);

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


PALETTEENTRY* PALETTEENTRY::generate() {
	if (generated == 1) {
		PALETTEENTRY* new_instance = new PALETTEENTRY(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(Reserved, ::g->Reserved_.generate());
	GENERATE_VAR(Blue, ::g->Blue_.generate());
	GENERATE_VAR(Green, ::g->Green_.generate());
	GENERATE_VAR(Red, ::g->Red_.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMREOF* EMREOF::generate() {
	if (generated == 1) {
		EMREOF* new_instance = new EMREOF(instances);
		new_instance->generated = 2;
		return new_instance->generate();
	}
	if (!generated)
		generated = 1;
	_startof = FTell();
	if (_parent_id != ::g->_struct_id && !global_indexing_of_arrays) {
		_index_start = instances.size() - 1;
	}
	_parent_id = ::g->_struct_id;
	::g->_struct_id = ++::g->_struct_id_counter;

	GENERATE_VAR(iType, ::g->iType.generate({ 0x0000000E }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x00000014 }));
	GENERATE_VAR(nPalEntries, ::g->nPalEntries.generate({ 0 }));
	GENERATE_VAR(offPalEntries, ::g->offPalEntries.generate({ 0 }));
	palCnt = 0;
	for (palCnt = 0; (palCnt < nPalEntries()); palCnt++) {
			GENERATE_VAR(palEntry, ::g->palEntry.generate());
	;
	};
	GENERATE_VAR(SizeLast, ::g->SizeLast.generate({ 0x00000014 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}



void generate_file() {
	::g = new globals_class();

	LittleEndian();
	GENERATE(EmfHeader, ::g->EmfHeader.generate());
	FSeek(4);
	::g->EmfHeaderSize = (0x6c + (::g->EmfHeader().nDescription() * 0x2));
	::g->EmfHeader().nSize() = ::g->EmfHeaderSize;
	GENERATE(nSize, ::g->nSize.generate({ ::g->EmfHeaderSize }));
	if ((::g->EmfHeader().dSignature() != 0x464D4520)) {
		Warning("File is not an enhanced metafile. Template stopped.");
		exit_template(-1);
	};
	if (((::g->EmfHeader().nDescription() % 4) != 0)) {
		Warning("Description size is invalid. Template stopped.");
		exit_template(-1);
	};
	FSeek(::g->EmfHeader().offDescription());
	GENERATE(EmfDescription, ::g->EmfDescription.generate());
	FSeek(::g->EmfHeader().nSize());
	GENERATE(EmfPlusHeader, ::g->EmfPlusHeader.generate());
	FSeek((::g->EmfHeader().nSize() + 0x2c));
	::g->recCnt = 0;
	for (::g->recCnt = 0; (::g->recCnt < (::g->EmfHeader().nRecords() - 4)); ::g->recCnt++) {
			::g->possible = { 0x9, 0xa, 0xd, 0x3a, 0x36, 0x38 };
		GENERATE(recType, ::g->recType.generate(::g->possible));
		FSkip(-1);
		if ((::g->recType() == 0x9)) {
			GENERATE(Clear, ::g->Clear.generate());
		} else {
		if ((::g->recType() == 0xa)) {
			GENERATE(FillRects, ::g->FillRects.generate());
		} else {
		if ((::g->recType() == 0xd)) {
			GENERATE(DrawLines, ::g->DrawLines.generate());
		} else {
		if ((::g->recType() == 0x3a)) {
			GENERATE(SetTSClip, ::g->SetTSClip.generate());
		} else {
		if ((::g->recType() == 0x36)) {
			GENERATE(DrawDriverString, ::g->DrawDriverString.generate());
		} else {
		if ((::g->recType() == 0x38)) {
			GENERATE(SerializableObject, ::g->SerializableObject.generate());
		};
		};
		};
		};
		};
		};
	;
	};
	GENERATE(EmfPlusEndOfFile, ::g->EmfPlusEndOfFile.generate());
	GENERATE(EmfEndOfFile, ::g->EmfEndOfFile.generate());
	::g->file_size = FTell();
	FSeek(0x30);
	GENERATE(nBytes, ::g->nBytes.generate({ ::g->file_size }));
	if (((::g->file_size % 4) != 0)) {
		Warning("File size is invalid. Template stopped.");
		exit_template(-1);
	};

	file_acc.finish();
	delete_globals();
}

void delete_globals() { delete ::g; }

