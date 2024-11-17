#include <cstdlib>
#include <cstdio>
#include <string>
#include <vector>
#include <unordered_map>
#include "bt.h"

enum EmfRecordType_enum : DWORD {
	EMR_HEADER = (DWORD) 0x1,
	EMR_POLYBEZIER = (DWORD) 0x2,
	EMR_POLYGON = (DWORD) 0x3,
	EMR_POLYLINE = (DWORD) 0x4,
	EMR_POLYBEZIERTO = (DWORD) 0x5,
	EMR_POLYLINETO = (DWORD) 0x6,
	EMR_POLYPOLYLINE = (DWORD) 0x7,
	EMR_POLYPOLYGON = (DWORD) 0x8,
	EMR_SETWINDOWEXTEX = (DWORD) 0x9,
	EMR_SETWINDOWORGEX = (DWORD) 0xA,
	EMR_SETVIEWPORTEXTEX = (DWORD) 0xB,
	EMR_SETVIEWPORTORGEX = (DWORD) 0xC,
	EMR_SETBRUSHORGEX = (DWORD) 0xD,
	EMR_EOF = (DWORD) 0xE,
	EMR_SETPIXELV = (DWORD) 0xF,
	EMR_SETMAPPERFLAGS = (DWORD) 0x10,
	EMR_SETMAPMODE = (DWORD) 0x11,
	EMR_SETBKMODE = (DWORD) 0x12,
	EMR_SETPOLYFILLMODE = (DWORD) 0x13,
	EMR_SETROP2 = (DWORD) 0x14,
	EMR_SETSTRETCHBLTMODE = (DWORD) 0x15,
	EMR_SETTEXTALIGN = (DWORD) 0x16,
	EMR_SETCOLORADJUSTMENT = (DWORD) 0x17,
	EMR_SETTEXTCOLOR = (DWORD) 0x18,
	EMR_SETBKCOLOR = (DWORD) 0x19,
	EMR_OFFSETCLIPRGN = (DWORD) 0x1A,
	EMR_MOVETOEX = (DWORD) 0x1B,
	EMR_SETMETARGN = (DWORD) 0x1C,
	EMR_EXCLUDECLIPRECT = (DWORD) 0x1D,
	EMR_INTERSECTCLIPRECT = (DWORD) 0x1E,
	EMR_SCALEVIEWPORTEXTEX = (DWORD) 0x1F,
	EMR_SCALEWINDOWEXTEX = (DWORD) 0x20,
	EMR_SAVEDC = (DWORD) 0x21,
	EMR_RESTOREDC = (DWORD) 0x22,
	EMR_SETWORLDTRANSFORM = (DWORD) 0x23,
	EMR_MODIFYWORLDTRANSFORM = (DWORD) 0x24,
	EMR_SELECTOBJECT = (DWORD) 0x25,
	EMR_CREATEPEN = (DWORD) 0x26,
	EMR_CREATEBRUSHINDIRECT = (DWORD) 0x27,
	EMR_DELETEOBJECT = (DWORD) 0x28,
	EMR_ANGLEARC = (DWORD) 0x29,
	EMR_ELLIPSE = (DWORD) 0x2A,
	EMR_RECTANGLE = (DWORD) 0x2B,
	EMR_ROUNDRECT = (DWORD) 0x2C,
	EMR_ARC = (DWORD) 0x2D,
	EMR_CHORD = (DWORD) 0x2E,
	EMR_PIE = (DWORD) 0x2F,
	EMR_SELECTPALETTE = (DWORD) 0x30,
	EMR_CREATEPALETTE = (DWORD) 0x31,
	EMR_SETPALETTEENTRIES = (DWORD) 0x32,
	EMR_RESIZEPALETTE = (DWORD) 0x33,
	EMR_REALIZEPALETTE = (DWORD) 0x34,
	EMR_EXTFLOODFILL = (DWORD) 0x35,
	EMR_LINETO = (DWORD) 0x36,
	EMR_ARCTO = (DWORD) 0x37,
	EMR_POLYDRAW = (DWORD) 0x38,
	EMR_SETARCDIRECTION = (DWORD) 0x39,
	EMR_SETMITERLIMIT = (DWORD) 0x3A,
	EMR_BEGINPATH = (DWORD) 0x3B,
	EMR_ENDPATH = (DWORD) 0x3C,
	EMR_CLOSEFIGURE = (DWORD) 0x3D,
	EMR_FILLPATH = (DWORD) 0x3E,
	EMR_STROKEANDFILLPATH = (DWORD) 0x3F,
	EMR_STROKEPATH = (DWORD) 0x40,
	EMR_FLATTENPATH = (DWORD) 0x41,
	EMR_WIDENPATH = (DWORD) 0x42,
	EMR_SELECTCLIPPATH = (DWORD) 0x43,
	EMR_ABORTPATH = (DWORD) 0x44,
	EMR_RESERVED_69 = (DWORD) 0x45,
	EMR_COMMENT = (DWORD) 0x46,
	EMR_FILLRGN = (DWORD) 0x47,
	EMR_FRAMERGN = (DWORD) 0x48,
	EMR_INVERTRGN = (DWORD) 0x49,
	EMR_PAINTRGN = (DWORD) 0x4A,
	EMR_EXTSELECTCLIPRGN = (DWORD) 0x4B,
	EMR_BITBLT = (DWORD) 0x4C,
	EMR_STRETCHBLT = (DWORD) 0x4D,
	EMR_MASKBLT = (DWORD) 0x4E,
	EMR_PLGBLT = (DWORD) 0x4F,
	EMR_SETDIBITSTODEVICE = (DWORD) 0x50,
	EMR_STRETCHDIBITS = (DWORD) 0x51,
	EMR_EXTCREATEFONTINDIRECTW = (DWORD) 0x52,
	EMR_EXTTEXTOUTA = (DWORD) 0x53,
	EMR_EXTTEXTOUTW = (DWORD) 0x54,
	EMR_POLYBEZIER16 = (DWORD) 0x55,
	EMR_POLYGON16 = (DWORD) 0x56,
	EMR_POLYLINE16 = (DWORD) 0x57,
	EMR_POLYBEZIERTO16 = (DWORD) 0x58,
	EMR_POLYLINETO16 = (DWORD) 0x59,
	EMR_POLYPOLYLINE16 = (DWORD) 0x5A,
	EMR_POLYPOLYGON16 = (DWORD) 0x5B,
	EMR_POLYDRAW16 = (DWORD) 0x5C,
	EMR_CREATEMONOBRUSH = (DWORD) 0x5D,
	EMR_CREATEDIBPATTERNBRUSHPT = (DWORD) 0x5E,
	EMR_EXTCREATEPEN = (DWORD) 0x5F,
	EMR_POLYTEXTOUTA = (DWORD) 0x60,
	EMR_POLYTEXTOUTW = (DWORD) 0x61,
	EMR_SETICMMODE = (DWORD) 0x62,
	EMR_CREATECOLORSPACE = (DWORD) 0x63,
	EMR_SETCOLORSPACE = (DWORD) 0x64,
	EMR_DELETECOLORSPACE = (DWORD) 0x65,
	EMR_GLSRECORD = (DWORD) 0x66,
	EMR_GLSBOUNDEDRECORD = (DWORD) 0x67,
	EMR_PIXELFORMAT = (DWORD) 0x68,
	EMR_DRAWESCAPE = (DWORD) 0x69,
	EMR_EXTESCAPE = (DWORD) 0x6A,
	EMR_RESERVED_107 = (DWORD) 0x6B,
	EMR_SMALLTEXTOUT = (DWORD) 0x6C,
	EMR_FORCEUFIMAPPING = (DWORD) 0x6D,
	EMR_NAMEDESCAPE = (DWORD) 0x6E,
	EMR_COLORCORRECTPALETTE = (DWORD) 0x6F,
	EMR_SETICMPROFILEA = (DWORD) 0x70,
	EMR_SETICMPROFILEW = (DWORD) 0x71,
	EMR_ALPHABLEND = (DWORD) 0x72,
	EMR_SETLAYOUT = (DWORD) 0x73,
	EMR_TRANSPARENTBLT = (DWORD) 0x74,
	EMR_RESERVED_117 = (DWORD) 0x75,
	EMR_GRADIENTFILL = (DWORD) 0x76,
	EMR_SETLINKEDUFIS = (DWORD) 0x77,
	EMR_SETTEXTJUSTIFICATION = (DWORD) 0x78,
	EMR_COLORMATCHTOTARGETW = (DWORD) 0x79,
	EMR_CREATECOLORSPACEW = (DWORD) 0x7A,
};
std::vector<DWORD> EmfRecordType_enum_values = { EMR_HEADER, EMR_POLYBEZIER, EMR_POLYGON, EMR_POLYLINE, EMR_POLYBEZIERTO, EMR_POLYLINETO, EMR_POLYPOLYLINE, EMR_POLYPOLYGON, EMR_SETWINDOWEXTEX, EMR_SETWINDOWORGEX, EMR_SETVIEWPORTEXTEX, EMR_SETVIEWPORTORGEX, EMR_SETBRUSHORGEX, EMR_EOF, EMR_SETPIXELV, EMR_SETMAPPERFLAGS, EMR_SETMAPMODE, EMR_SETBKMODE, EMR_SETPOLYFILLMODE, EMR_SETROP2, EMR_SETSTRETCHBLTMODE, EMR_SETTEXTALIGN, EMR_SETCOLORADJUSTMENT, EMR_SETTEXTCOLOR, EMR_SETBKCOLOR, EMR_OFFSETCLIPRGN, EMR_MOVETOEX, EMR_SETMETARGN, EMR_EXCLUDECLIPRECT, EMR_INTERSECTCLIPRECT, EMR_SCALEVIEWPORTEXTEX, EMR_SCALEWINDOWEXTEX, EMR_SAVEDC, EMR_RESTOREDC, EMR_SETWORLDTRANSFORM, EMR_MODIFYWORLDTRANSFORM, EMR_SELECTOBJECT, EMR_CREATEPEN, EMR_CREATEBRUSHINDIRECT, EMR_DELETEOBJECT, EMR_ANGLEARC, EMR_ELLIPSE, EMR_RECTANGLE, EMR_ROUNDRECT, EMR_ARC, EMR_CHORD, EMR_PIE, EMR_SELECTPALETTE, EMR_CREATEPALETTE, EMR_SETPALETTEENTRIES, EMR_RESIZEPALETTE, EMR_REALIZEPALETTE, EMR_EXTFLOODFILL, EMR_LINETO, EMR_ARCTO, EMR_POLYDRAW, EMR_SETARCDIRECTION, EMR_SETMITERLIMIT, EMR_BEGINPATH, EMR_ENDPATH, EMR_CLOSEFIGURE, EMR_FILLPATH, EMR_STROKEANDFILLPATH, EMR_STROKEPATH, EMR_FLATTENPATH, EMR_WIDENPATH, EMR_SELECTCLIPPATH, EMR_ABORTPATH, EMR_RESERVED_69, EMR_COMMENT, EMR_FILLRGN, EMR_FRAMERGN, EMR_INVERTRGN, EMR_PAINTRGN, EMR_EXTSELECTCLIPRGN, EMR_BITBLT, EMR_STRETCHBLT, EMR_MASKBLT, EMR_PLGBLT, EMR_SETDIBITSTODEVICE, EMR_STRETCHDIBITS, EMR_EXTCREATEFONTINDIRECTW, EMR_EXTTEXTOUTA, EMR_EXTTEXTOUTW, EMR_POLYBEZIER16, EMR_POLYGON16, EMR_POLYLINE16, EMR_POLYBEZIERTO16, EMR_POLYLINETO16, EMR_POLYPOLYLINE16, EMR_POLYPOLYGON16, EMR_POLYDRAW16, EMR_CREATEMONOBRUSH, EMR_CREATEDIBPATTERNBRUSHPT, EMR_EXTCREATEPEN, EMR_POLYTEXTOUTA, EMR_POLYTEXTOUTW, EMR_SETICMMODE, EMR_CREATECOLORSPACE, EMR_SETCOLORSPACE, EMR_DELETECOLORSPACE, EMR_GLSRECORD, EMR_GLSBOUNDEDRECORD, EMR_PIXELFORMAT, EMR_DRAWESCAPE, EMR_EXTESCAPE, EMR_RESERVED_107, EMR_SMALLTEXTOUT, EMR_FORCEUFIMAPPING, EMR_NAMEDESCAPE, EMR_COLORCORRECTPALETTE, EMR_SETICMPROFILEA, EMR_SETICMPROFILEW, EMR_ALPHABLEND, EMR_SETLAYOUT, EMR_TRANSPARENTBLT, EMR_RESERVED_117, EMR_GRADIENTFILL, EMR_SETLINKEDUFIS, EMR_SETTEXTJUSTIFICATION, EMR_COLORMATCHTOTARGETW, EMR_CREATECOLORSPACEW };

typedef enum EmfRecordType_enum EmfRecordType;
std::vector<DWORD> EmfRecordType_values = { EMR_HEADER, EMR_POLYBEZIER, EMR_POLYGON, EMR_POLYLINE, EMR_POLYBEZIERTO, EMR_POLYLINETO, EMR_POLYPOLYLINE, EMR_POLYPOLYGON, EMR_SETWINDOWEXTEX, EMR_SETWINDOWORGEX, EMR_SETVIEWPORTEXTEX, EMR_SETVIEWPORTORGEX, EMR_SETBRUSHORGEX, EMR_EOF, EMR_SETPIXELV, EMR_SETMAPPERFLAGS, EMR_SETMAPMODE, EMR_SETBKMODE, EMR_SETPOLYFILLMODE, EMR_SETROP2, EMR_SETSTRETCHBLTMODE, EMR_SETTEXTALIGN, EMR_SETCOLORADJUSTMENT, EMR_SETTEXTCOLOR, EMR_SETBKCOLOR, EMR_OFFSETCLIPRGN, EMR_MOVETOEX, EMR_SETMETARGN, EMR_EXCLUDECLIPRECT, EMR_INTERSECTCLIPRECT, EMR_SCALEVIEWPORTEXTEX, EMR_SCALEWINDOWEXTEX, EMR_SAVEDC, EMR_RESTOREDC, EMR_SETWORLDTRANSFORM, EMR_MODIFYWORLDTRANSFORM, EMR_SELECTOBJECT, EMR_CREATEPEN, EMR_CREATEBRUSHINDIRECT, EMR_DELETEOBJECT, EMR_ANGLEARC, EMR_ELLIPSE, EMR_RECTANGLE, EMR_ROUNDRECT, EMR_ARC, EMR_CHORD, EMR_PIE, EMR_SELECTPALETTE, EMR_CREATEPALETTE, EMR_SETPALETTEENTRIES, EMR_RESIZEPALETTE, EMR_REALIZEPALETTE, EMR_EXTFLOODFILL, EMR_LINETO, EMR_ARCTO, EMR_POLYDRAW, EMR_SETARCDIRECTION, EMR_SETMITERLIMIT, EMR_BEGINPATH, EMR_ENDPATH, EMR_CLOSEFIGURE, EMR_FILLPATH, EMR_STROKEANDFILLPATH, EMR_STROKEPATH, EMR_FLATTENPATH, EMR_WIDENPATH, EMR_SELECTCLIPPATH, EMR_ABORTPATH, EMR_RESERVED_69, EMR_COMMENT, EMR_FILLRGN, EMR_FRAMERGN, EMR_INVERTRGN, EMR_PAINTRGN, EMR_EXTSELECTCLIPRGN, EMR_BITBLT, EMR_STRETCHBLT, EMR_MASKBLT, EMR_PLGBLT, EMR_SETDIBITSTODEVICE, EMR_STRETCHDIBITS, EMR_EXTCREATEFONTINDIRECTW, EMR_EXTTEXTOUTA, EMR_EXTTEXTOUTW, EMR_POLYBEZIER16, EMR_POLYGON16, EMR_POLYLINE16, EMR_POLYBEZIERTO16, EMR_POLYLINETO16, EMR_POLYPOLYLINE16, EMR_POLYPOLYGON16, EMR_POLYDRAW16, EMR_CREATEMONOBRUSH, EMR_CREATEDIBPATTERNBRUSHPT, EMR_EXTCREATEPEN, EMR_POLYTEXTOUTA, EMR_POLYTEXTOUTW, EMR_SETICMMODE, EMR_CREATECOLORSPACE, EMR_SETCOLORSPACE, EMR_DELETECOLORSPACE, EMR_GLSRECORD, EMR_GLSBOUNDEDRECORD, EMR_PIXELFORMAT, EMR_DRAWESCAPE, EMR_EXTESCAPE, EMR_RESERVED_107, EMR_SMALLTEXTOUT, EMR_FORCEUFIMAPPING, EMR_NAMEDESCAPE, EMR_COLORCORRECTPALETTE, EMR_SETICMPROFILEA, EMR_SETICMPROFILEW, EMR_ALPHABLEND, EMR_SETLAYOUT, EMR_TRANSPARENTBLT, EMR_RESERVED_117, EMR_GRADIENTFILL, EMR_SETLINKEDUFIS, EMR_SETTEXTJUSTIFICATION, EMR_COLORMATCHTOTARGETW, EMR_CREATECOLORSPACEW };

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

enum GradientFill_enum : DWORD {
	GRADIENT_FILL_RECT_H = (DWORD) 0x00000000,
	GRADIENT_FILL_RECT_V = (DWORD) 0x00000001,
	GRADIENT_FILL_TRIANGLE = (DWORD) 0x00000002,
};
std::vector<DWORD> GradientFill_enum_values = { GRADIENT_FILL_RECT_H, GRADIENT_FILL_RECT_V, GRADIENT_FILL_TRIANGLE };

typedef enum GradientFill_enum GradientFill;
std::vector<DWORD> GradientFill_values = { GRADIENT_FILL_RECT_H, GRADIENT_FILL_RECT_V, GRADIENT_FILL_TRIANGLE };

enum StockObject_enum : DWORD {
	WHITE_BRUSH = (DWORD) 0x80000000,
	LTGRAY_BRUSH = (DWORD) 0x80000001,
	GRAY_BRUSH = (DWORD) 0x80000002,
	DKGRAY_BRUSH = (DWORD) 0x80000003,
	BLACK_BRUSH = (DWORD) 0x80000004,
	NULL_BRUSH = (DWORD) 0x80000005,
	WHITE_PEN = (DWORD) 0x80000006,
	BLACK_PEN = (DWORD) 0x80000007,
	NULL_PEN = (DWORD) 0x80000008,
	OEM_FIXED_FONT = (DWORD) 0x8000000A,
	ANSI_FIXED_FONT = (DWORD) 0x8000000B,
	ANSI_VAR_FONT = (DWORD) 0x8000000C,
	SYSTEM_FONT = (DWORD) 0x8000000D,
	DEVICE_DEFAULT_FONT = (DWORD) 0x8000000E,
	DEFAULT_PALETTE = (DWORD) 0x8000000F,
	SYSTEM_FIXED_FONT = (DWORD) 0x80000010,
	DEFAULT_GUI_FONT = (DWORD) 0x80000011,
	DC_BRUSH = (DWORD) 0x80000012,
	DC_PEN = (DWORD) 0x80000013,
};
std::vector<DWORD> StockObject_enum_values = { WHITE_BRUSH, LTGRAY_BRUSH, GRAY_BRUSH, DKGRAY_BRUSH, BLACK_BRUSH, NULL_BRUSH, WHITE_PEN, BLACK_PEN, NULL_PEN, OEM_FIXED_FONT, ANSI_FIXED_FONT, ANSI_VAR_FONT, SYSTEM_FONT, DEVICE_DEFAULT_FONT, DEFAULT_PALETTE, SYSTEM_FIXED_FONT, DEFAULT_GUI_FONT, DC_BRUSH, DC_PEN };

typedef enum StockObject_enum StockObject;
std::vector<DWORD> StockObject_values = { WHITE_BRUSH, LTGRAY_BRUSH, GRAY_BRUSH, DKGRAY_BRUSH, BLACK_BRUSH, NULL_BRUSH, WHITE_PEN, BLACK_PEN, NULL_PEN, OEM_FIXED_FONT, ANSI_FIXED_FONT, ANSI_VAR_FONT, SYSTEM_FONT, DEVICE_DEFAULT_FONT, DEFAULT_PALETTE, SYSTEM_FIXED_FONT, DEFAULT_GUI_FONT, DC_BRUSH, DC_PEN };

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

enum ColorMatchToTarget_enum : DWORD {
	COLORMATCHTOTARGET_NOTEMBEDDED = (DWORD) 0x00000000,
	COLORMATCHTOTARGET_EMBEDDED = (DWORD) 0x00000001,
};
std::vector<DWORD> ColorMatchToTarget_enum_values = { COLORMATCHTOTARGET_NOTEMBEDDED, COLORMATCHTOTARGET_EMBEDDED };

typedef enum ColorMatchToTarget_enum ColorMatchToTarget;
std::vector<DWORD> ColorMatchToTarget_values = { COLORMATCHTOTARGET_NOTEMBEDDED, COLORMATCHTOTARGET_EMBEDDED };

enum ColorSpace_enum : DWORD {
	CS_ENABLE = (DWORD) 0x00000001,
	CS_DISABLE = (DWORD) 0x00000002,
	CS_DELETE_TRANSFORM = (DWORD) 0x00000003,
};
std::vector<DWORD> ColorSpace_enum_values = { CS_ENABLE, CS_DISABLE, CS_DELETE_TRANSFORM };

typedef enum ColorSpace_enum ColorSpace;
std::vector<DWORD> ColorSpace_values = { CS_ENABLE, CS_DISABLE, CS_DELETE_TRANSFORM };

enum BitCount_enum : WORD {
	BI_BITCOUNT_0 = (WORD) 0,
	BI_BITCOUNT_1 = (WORD) 1,
	BI_BITCOUNT_2 = (WORD) 4,
	BI_BITCOUNT_3 = (WORD) 8,
	BI_BITCOUNT_4 = (WORD) 0x10,
	BI_BITCOUNT_5 = (WORD) 0x18,
	BI_BITCOUNT_6 = (WORD) 0x20,
};
std::vector<WORD> BitCount_enum_values = { BI_BITCOUNT_0, BI_BITCOUNT_1, BI_BITCOUNT_2, BI_BITCOUNT_3, BI_BITCOUNT_4, BI_BITCOUNT_5, BI_BITCOUNT_6 };

typedef enum BitCount_enum BitCount;
std::vector<WORD> BitCount_values = { BI_BITCOUNT_0, BI_BITCOUNT_1, BI_BITCOUNT_2, BI_BITCOUNT_3, BI_BITCOUNT_4, BI_BITCOUNT_5, BI_BITCOUNT_6 };

enum BrushStyle_enum : DWORD {
	BS_SOLID = (DWORD) 0,
	BS_NULL = (DWORD) 1,
	BS_HATCHED = (DWORD) 2,
};
std::vector<DWORD> BrushStyle_enum_values = { BS_SOLID, BS_NULL, BS_HATCHED };

typedef enum BrushStyle_enum BrushStyle;
std::vector<DWORD> BrushStyle_values = { BS_SOLID, BS_NULL, BS_HATCHED };

enum DIBColors_enum : DWORD {
	DIB_RGB_COLORS = (DWORD) 0,
	DIB_PAL_COLORS = (DWORD) 1,
	DIB_PAL_INDICES = (DWORD) 2,
};
std::vector<DWORD> DIBColors_enum_values = { DIB_RGB_COLORS, DIB_PAL_COLORS, DIB_PAL_INDICES };

typedef enum DIBColors_enum DIBColors;
std::vector<DWORD> DIBColors_values = { DIB_RGB_COLORS, DIB_PAL_COLORS, DIB_PAL_INDICES };

enum GamutMappingIntent_enum : DWORD {
	LCS_GM_ABS_COLORIMETRIC = (DWORD) 8,
	LCS_GM_BUSINESS = (DWORD) 1,
	LCS_GM_GRAPHICS = (DWORD) 2,
	LCS_GM_IMAGES = (DWORD) 4,
};
std::vector<DWORD> GamutMappingIntent_enum_values = { LCS_GM_ABS_COLORIMETRIC, LCS_GM_BUSINESS, LCS_GM_GRAPHICS, LCS_GM_IMAGES };

typedef enum GamutMappingIntent_enum GamutMappingIntent;
std::vector<DWORD> GamutMappingIntent_values = { LCS_GM_ABS_COLORIMETRIC, LCS_GM_BUSINESS, LCS_GM_GRAPHICS, LCS_GM_IMAGES };

enum LogicalColorSpace_enum : DWORD {
	LCS_CALIBRATED_RGB = (DWORD) 0x00000000,
	LCS_sRGB = (DWORD) 0x73524742,
	LCS_WINDOWS_COLOR_SPACE = (DWORD) 0x57696E20,
};
std::vector<DWORD> LogicalColorSpace_enum_values = { LCS_CALIBRATED_RGB, LCS_sRGB, LCS_WINDOWS_COLOR_SPACE };

typedef enum LogicalColorSpace_enum LogicalColorSpace;
std::vector<DWORD> LogicalColorSpace_values = { LCS_CALIBRATED_RGB, LCS_sRGB, LCS_WINDOWS_COLOR_SPACE };

enum RegionMode_enum : DWORD {
	RGN_AND = (DWORD) 1,
	RGN_OR = (DWORD) 2,
	RGN_XOR = (DWORD) 3,
	RGN_DIFF = (DWORD) 4,
	RGN_COPY = (DWORD) 5,
};
std::vector<DWORD> RegionMode_enum_values = { RGN_AND, RGN_OR, RGN_XOR, RGN_DIFF, RGN_COPY };

typedef enum RegionMode_enum RegionMode;
std::vector<DWORD> RegionMode_values = { RGN_AND, RGN_OR, RGN_XOR, RGN_DIFF, RGN_COPY };

EmfRecordType EmfRecordType_generate() {
	return (EmfRecordType) file_acc.file_integer(sizeof(DWORD), 0, EmfRecordType_values);
}

EmfRecordType EmfRecordType_generate(std::vector<DWORD> known_values) {
	return (EmfRecordType) file_acc.file_integer(sizeof(DWORD), 0, known_values);
}


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



class EmfHeaderExtension1 {
	std::vector<EmfHeaderExtension1*>& instances;

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
	EmfHeaderExtension1& operator () () { return *instances.back(); }
	EmfHeaderExtension1& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EmfHeaderExtension1(std::vector<EmfHeaderExtension1*>& instances) : instances(instances) { instances.push_back(this); }
	~EmfHeaderExtension1() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EmfHeaderExtension1* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EmfHeaderExtension1* generate();
};

int EmfHeaderExtension1::_parent_id = 0;
int EmfHeaderExtension1::_index_start = 0;



class EmfHeaderExtension2 {
	std::vector<EmfHeaderExtension2*>& instances;

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
	EmfHeaderExtension2& operator () () { return *instances.back(); }
	EmfHeaderExtension2& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EmfHeaderExtension2(std::vector<EmfHeaderExtension2*>& instances) : instances(instances) { instances.push_back(this); }
	~EmfHeaderExtension2() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EmfHeaderExtension2* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EmfHeaderExtension2* generate();
};

int EmfHeaderExtension2::_parent_id = 0;
int EmfHeaderExtension2::_index_start = 0;



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
	EmfHeaderExtension1* headerExtension1_var;
	EmfHeaderExtension2* headerExtension2_var;

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
	bool headerExtension1_exists = false;
	bool headerExtension2_exists = false;

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
	EmfHeaderExtension1& headerExtension1() {
		assert_cond(headerExtension1_exists, "struct field headerExtension1 does not exist");
		return *headerExtension1_var;
	}
	EmfHeaderExtension2& headerExtension2() {
		assert_cond(headerExtension2_exists, "struct field headerExtension2 does not exist");
		return *headerExtension2_var;
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



class POINT {
	std::vector<POINT*>& instances;

	LONG x_var;
	LONG y_var;

public:
	bool x_exists = false;
	bool y_exists = false;

	LONG& x() {
		assert_cond(x_exists, "struct field x does not exist");
		return x_var;
	}
	LONG& y() {
		assert_cond(y_exists, "struct field y does not exist");
		return y_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	POINT& operator () () { return *instances.back(); }
	POINT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	POINT(std::vector<POINT*>& instances) : instances(instances) { instances.push_back(this); }
	~POINT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			POINT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	POINT* generate();
};

int POINT::_parent_id = 0;
int POINT::_index_start = 0;



class POINT_array_class {
	POINT& element;
	std::vector<POINT*> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<POINT*>& operator () () { return value; }
	POINT operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return *value[index];
	}
	POINT_array_class(POINT& element) : element(element) {}

	std::vector<POINT*> generate(unsigned size) {
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



class EMRPOLYBEZIER {
	std::vector<EMRPOLYBEZIER*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	DWORD cntPoints_var;
	std::vector<POINT*> aPoints_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool cntPoints_exists = false;
	bool aPoints_exists = false;

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
	DWORD& cntPoints() {
		assert_cond(cntPoints_exists, "struct field cntPoints does not exist");
		return cntPoints_var;
	}
	std::vector<POINT*>& aPoints() {
		assert_cond(aPoints_exists, "struct field aPoints does not exist");
		return aPoints_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRPOLYBEZIER& operator () () { return *instances.back(); }
	EMRPOLYBEZIER& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRPOLYBEZIER(std::vector<EMRPOLYBEZIER*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRPOLYBEZIER() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRPOLYBEZIER* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRPOLYBEZIER* generate();
};

int EMRPOLYBEZIER::_parent_id = 0;
int EMRPOLYBEZIER::_index_start = 0;



class EMRPOLYGON {
	std::vector<EMRPOLYGON*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	DWORD cntPoints_var;
	std::vector<POINT*> aPoints_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool cntPoints_exists = false;
	bool aPoints_exists = false;

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
	DWORD& cntPoints() {
		assert_cond(cntPoints_exists, "struct field cntPoints does not exist");
		return cntPoints_var;
	}
	std::vector<POINT*>& aPoints() {
		assert_cond(aPoints_exists, "struct field aPoints does not exist");
		return aPoints_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRPOLYGON& operator () () { return *instances.back(); }
	EMRPOLYGON& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRPOLYGON(std::vector<EMRPOLYGON*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRPOLYGON() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRPOLYGON* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRPOLYGON* generate();
};

int EMRPOLYGON::_parent_id = 0;
int EMRPOLYGON::_index_start = 0;



class EMRPOLYLINE {
	std::vector<EMRPOLYLINE*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	DWORD cntPoints_var;
	std::vector<POINT*> aPoints_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool cntPoints_exists = false;
	bool aPoints_exists = false;

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
	DWORD& cntPoints() {
		assert_cond(cntPoints_exists, "struct field cntPoints does not exist");
		return cntPoints_var;
	}
	std::vector<POINT*>& aPoints() {
		assert_cond(aPoints_exists, "struct field aPoints does not exist");
		return aPoints_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRPOLYLINE& operator () () { return *instances.back(); }
	EMRPOLYLINE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRPOLYLINE(std::vector<EMRPOLYLINE*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRPOLYLINE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRPOLYLINE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRPOLYLINE* generate();
};

int EMRPOLYLINE::_parent_id = 0;
int EMRPOLYLINE::_index_start = 0;



class EMRPOLYBEZIERTO {
	std::vector<EMRPOLYBEZIERTO*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	DWORD cntPoints_var;
	std::vector<POINT*> aPoints_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool cntPoints_exists = false;
	bool aPoints_exists = false;

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
	DWORD& cntPoints() {
		assert_cond(cntPoints_exists, "struct field cntPoints does not exist");
		return cntPoints_var;
	}
	std::vector<POINT*>& aPoints() {
		assert_cond(aPoints_exists, "struct field aPoints does not exist");
		return aPoints_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRPOLYBEZIERTO& operator () () { return *instances.back(); }
	EMRPOLYBEZIERTO& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRPOLYBEZIERTO(std::vector<EMRPOLYBEZIERTO*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRPOLYBEZIERTO() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRPOLYBEZIERTO* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRPOLYBEZIERTO* generate();
};

int EMRPOLYBEZIERTO::_parent_id = 0;
int EMRPOLYBEZIERTO::_index_start = 0;



class EMRPOLYLINETO {
	std::vector<EMRPOLYLINETO*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	DWORD cntPoints_var;
	std::vector<POINT*> aPoints_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool cntPoints_exists = false;
	bool aPoints_exists = false;

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
	DWORD& cntPoints() {
		assert_cond(cntPoints_exists, "struct field cntPoints does not exist");
		return cntPoints_var;
	}
	std::vector<POINT*>& aPoints() {
		assert_cond(aPoints_exists, "struct field aPoints does not exist");
		return aPoints_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRPOLYLINETO& operator () () { return *instances.back(); }
	EMRPOLYLINETO& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRPOLYLINETO(std::vector<EMRPOLYLINETO*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRPOLYLINETO() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRPOLYLINETO* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRPOLYLINETO* generate();
};

int EMRPOLYLINETO::_parent_id = 0;
int EMRPOLYLINETO::_index_start = 0;



class EMRPOLYPOLYLINE {
	std::vector<EMRPOLYPOLYLINE*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	DWORD nPolys_var;
	DWORD cntPoints_var;
	DWORD aPolyCounts_var;
	std::vector<POINT*> aPoints_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool nPolys_exists = false;
	bool cntPoints_exists = false;
	bool aPolyCounts_exists = false;
	bool aPoints_exists = false;

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
	DWORD& nPolys() {
		assert_cond(nPolys_exists, "struct field nPolys does not exist");
		return nPolys_var;
	}
	DWORD& cntPoints() {
		assert_cond(cntPoints_exists, "struct field cntPoints does not exist");
		return cntPoints_var;
	}
	DWORD& aPolyCounts() {
		assert_cond(aPolyCounts_exists, "struct field aPolyCounts does not exist");
		return aPolyCounts_var;
	}
	std::vector<POINT*>& aPoints() {
		assert_cond(aPoints_exists, "struct field aPoints does not exist");
		return aPoints_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRPOLYPOLYLINE& operator () () { return *instances.back(); }
	EMRPOLYPOLYLINE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRPOLYPOLYLINE(std::vector<EMRPOLYPOLYLINE*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRPOLYPOLYLINE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRPOLYPOLYLINE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRPOLYPOLYLINE* generate();
};

int EMRPOLYPOLYLINE::_parent_id = 0;
int EMRPOLYPOLYLINE::_index_start = 0;



class EMRPOLYPOLYGON {
	std::vector<EMRPOLYPOLYGON*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	DWORD nPolys_var;
	DWORD cntPoints_var;
	DWORD aPolyCounts_var;
	std::vector<POINT*> aPoints_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool nPolys_exists = false;
	bool cntPoints_exists = false;
	bool aPolyCounts_exists = false;
	bool aPoints_exists = false;

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
	DWORD& nPolys() {
		assert_cond(nPolys_exists, "struct field nPolys does not exist");
		return nPolys_var;
	}
	DWORD& cntPoints() {
		assert_cond(cntPoints_exists, "struct field cntPoints does not exist");
		return cntPoints_var;
	}
	DWORD& aPolyCounts() {
		assert_cond(aPolyCounts_exists, "struct field aPolyCounts does not exist");
		return aPolyCounts_var;
	}
	std::vector<POINT*>& aPoints() {
		assert_cond(aPoints_exists, "struct field aPoints does not exist");
		return aPoints_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRPOLYPOLYGON& operator () () { return *instances.back(); }
	EMRPOLYPOLYGON& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRPOLYPOLYGON(std::vector<EMRPOLYPOLYGON*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRPOLYPOLYGON() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRPOLYPOLYGON* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRPOLYPOLYGON* generate();
};

int EMRPOLYPOLYGON::_parent_id = 0;
int EMRPOLYPOLYGON::_index_start = 0;



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



class EMRSETPIXELV {
	std::vector<EMRSETPIXELV*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	POINT* ptlPixel_var;
	COLORREF* crColor_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ptlPixel_exists = false;
	bool crColor_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	POINT& ptlPixel() {
		assert_cond(ptlPixel_exists, "struct field ptlPixel does not exist");
		return *ptlPixel_var;
	}
	COLORREF& crColor() {
		assert_cond(crColor_exists, "struct field crColor does not exist");
		return *crColor_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRSETPIXELV& operator () () { return *instances.back(); }
	EMRSETPIXELV& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRSETPIXELV(std::vector<EMRSETPIXELV*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRSETPIXELV() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRSETPIXELV* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRSETPIXELV* generate();
};

int EMRSETPIXELV::_parent_id = 0;
int EMRSETPIXELV::_index_start = 0;



class EMROFFSETCLIPRGN {
	std::vector<EMROFFSETCLIPRGN*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	POINT* offset_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool offset_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	POINT& offset() {
		assert_cond(offset_exists, "struct field offset does not exist");
		return *offset_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMROFFSETCLIPRGN& operator () () { return *instances.back(); }
	EMROFFSETCLIPRGN& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMROFFSETCLIPRGN(std::vector<EMROFFSETCLIPRGN*>& instances) : instances(instances) { instances.push_back(this); }
	~EMROFFSETCLIPRGN() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMROFFSETCLIPRGN* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMROFFSETCLIPRGN* generate();
};

int EMROFFSETCLIPRGN::_parent_id = 0;
int EMROFFSETCLIPRGN::_index_start = 0;



class EMREXCLUDECLIPRECT {
	std::vector<EMREXCLUDECLIPRECT*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclClip_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclClip_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	RECTL& rclClip() {
		assert_cond(rclClip_exists, "struct field rclClip does not exist");
		return *rclClip_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMREXCLUDECLIPRECT& operator () () { return *instances.back(); }
	EMREXCLUDECLIPRECT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMREXCLUDECLIPRECT(std::vector<EMREXCLUDECLIPRECT*>& instances) : instances(instances) { instances.push_back(this); }
	~EMREXCLUDECLIPRECT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMREXCLUDECLIPRECT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMREXCLUDECLIPRECT* generate();
};

int EMREXCLUDECLIPRECT::_parent_id = 0;
int EMREXCLUDECLIPRECT::_index_start = 0;



class EMRINTERSECTCLIPRECT {
	std::vector<EMRINTERSECTCLIPRECT*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclClip_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclClip_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	RECTL& rclClip() {
		assert_cond(rclClip_exists, "struct field rclClip does not exist");
		return *rclClip_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRINTERSECTCLIPRECT& operator () () { return *instances.back(); }
	EMRINTERSECTCLIPRECT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRINTERSECTCLIPRECT(std::vector<EMRINTERSECTCLIPRECT*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRINTERSECTCLIPRECT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRINTERSECTCLIPRECT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRINTERSECTCLIPRECT* generate();
};

int EMRINTERSECTCLIPRECT::_parent_id = 0;
int EMRINTERSECTCLIPRECT::_index_start = 0;



class EMRSELECTOBJECT {
	std::vector<EMRSELECTOBJECT*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD ihObject_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ihObject_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& ihObject() {
		assert_cond(ihObject_exists, "struct field ihObject does not exist");
		return ihObject_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRSELECTOBJECT& operator () () { return *instances.back(); }
	EMRSELECTOBJECT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRSELECTOBJECT(std::vector<EMRSELECTOBJECT*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRSELECTOBJECT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRSELECTOBJECT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRSELECTOBJECT* generate();
};

int EMRSELECTOBJECT::_parent_id = 0;
int EMRSELECTOBJECT::_index_start = 0;



class UINT_class {
	int small;
	std::vector<UINT> known_values;
	UINT value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = sizeof(UINT);
	UINT operator () () { return value; }
	UINT_class(int small, std::vector<UINT> known_values = {}) : small(small), known_values(known_values) {}

	UINT generate() {
		_startof = FTell();
		if (known_values.empty()) {
			value = file_acc.file_integer(sizeof(UINT), 0, small);
		} else {
			value = file_acc.file_integer(sizeof(UINT), 0, known_values);
		}
		return value;
	}

	UINT generate(std::vector<UINT> possible_values) {
		_startof = FTell();
		value = file_acc.file_integer(sizeof(UINT), 0, possible_values);
		return value;
	}
};



class LOGPEN {
	std::vector<LOGPEN*>& instances;

	UINT lopnStyle_var;
	POINT* lopnWidth_var;
	COLORREF* lopnColor_var;

public:
	bool lopnStyle_exists = false;
	bool lopnWidth_exists = false;
	bool lopnColor_exists = false;

	UINT& lopnStyle() {
		assert_cond(lopnStyle_exists, "struct field lopnStyle does not exist");
		return lopnStyle_var;
	}
	POINT& lopnWidth() {
		assert_cond(lopnWidth_exists, "struct field lopnWidth does not exist");
		return *lopnWidth_var;
	}
	COLORREF& lopnColor() {
		assert_cond(lopnColor_exists, "struct field lopnColor does not exist");
		return *lopnColor_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	LOGPEN& operator () () { return *instances.back(); }
	LOGPEN& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	LOGPEN(std::vector<LOGPEN*>& instances) : instances(instances) { instances.push_back(this); }
	~LOGPEN() {
		if (generated == 2)
			return;
		while (instances.size()) {
			LOGPEN* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	LOGPEN* generate();
};

int LOGPEN::_parent_id = 0;
int LOGPEN::_index_start = 0;



class EMRCREATEPEN {
	std::vector<EMRCREATEPEN*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD ihPen_var;
	LOGPEN* lopn_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ihPen_exists = false;
	bool lopn_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& ihPen() {
		assert_cond(ihPen_exists, "struct field ihPen does not exist");
		return ihPen_var;
	}
	LOGPEN& lopn() {
		assert_cond(lopn_exists, "struct field lopn does not exist");
		return *lopn_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRCREATEPEN& operator () () { return *instances.back(); }
	EMRCREATEPEN& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRCREATEPEN(std::vector<EMRCREATEPEN*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRCREATEPEN() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRCREATEPEN* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRCREATEPEN* generate();
};

int EMRCREATEPEN::_parent_id = 0;
int EMRCREATEPEN::_index_start = 0;


BrushStyle BrushStyle_generate() {
	return (BrushStyle) file_acc.file_integer(sizeof(DWORD), 0, BrushStyle_values);
}

BrushStyle BrushStyle_generate(std::vector<DWORD> known_values) {
	return (BrushStyle) file_acc.file_integer(sizeof(DWORD), 0, known_values);
}


class LogBrushEx {
	std::vector<LogBrushEx*>& instances;

	DWORD lbStyle_var;
	COLORREF* lbColor_var;
	DWORD lbHatch_var;

public:
	bool lbStyle_exists = false;
	bool lbColor_exists = false;
	bool lbHatch_exists = false;

	DWORD& lbStyle() {
		assert_cond(lbStyle_exists, "struct field lbStyle does not exist");
		return lbStyle_var;
	}
	COLORREF& lbColor() {
		assert_cond(lbColor_exists, "struct field lbColor does not exist");
		return *lbColor_var;
	}
	DWORD& lbHatch() {
		assert_cond(lbHatch_exists, "struct field lbHatch does not exist");
		return lbHatch_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	LogBrushEx& operator () () { return *instances.back(); }
	LogBrushEx& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	LogBrushEx(std::vector<LogBrushEx*>& instances) : instances(instances) { instances.push_back(this); }
	~LogBrushEx() {
		if (generated == 2)
			return;
		while (instances.size()) {
			LogBrushEx* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	LogBrushEx* generate();
};

int LogBrushEx::_parent_id = 0;
int LogBrushEx::_index_start = 0;



class EMRCREATEBRUSHINDIRECT {
	std::vector<EMRCREATEBRUSHINDIRECT*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD ihBrush_var;
	LogBrushEx* LogBrush_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ihBrush_exists = false;
	bool LogBrush_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& ihBrush() {
		assert_cond(ihBrush_exists, "struct field ihBrush does not exist");
		return ihBrush_var;
	}
	LogBrushEx& LogBrush() {
		assert_cond(LogBrush_exists, "struct field LogBrush does not exist");
		return *LogBrush_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRCREATEBRUSHINDIRECT& operator () () { return *instances.back(); }
	EMRCREATEBRUSHINDIRECT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRCREATEBRUSHINDIRECT(std::vector<EMRCREATEBRUSHINDIRECT*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRCREATEBRUSHINDIRECT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRCREATEBRUSHINDIRECT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRCREATEBRUSHINDIRECT* generate();
};

int EMRCREATEBRUSHINDIRECT::_parent_id = 0;
int EMRCREATEBRUSHINDIRECT::_index_start = 0;



class EMRDELETEOBJECT {
	std::vector<EMRDELETEOBJECT*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD ihCS_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ihCS_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& ihCS() {
		assert_cond(ihCS_exists, "struct field ihCS does not exist");
		return ihCS_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRDELETEOBJECT& operator () () { return *instances.back(); }
	EMRDELETEOBJECT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRDELETEOBJECT(std::vector<EMRDELETEOBJECT*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRDELETEOBJECT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRDELETEOBJECT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRDELETEOBJECT* generate();
};

int EMRDELETEOBJECT::_parent_id = 0;
int EMRDELETEOBJECT::_index_start = 0;



class FLOAT_class {
	int small;
	std::vector<FLOAT> known_values;
	FLOAT value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = sizeof(FLOAT);
	FLOAT operator () () { return value; }
	FLOAT_class(int small, std::vector<FLOAT> known_values = {}) : small(small), known_values(known_values) {}

	FLOAT generate() {
		_startof = FTell();
		if (known_values.empty()) {
			value = file_acc.file_integer(sizeof(FLOAT), 0, small);
		} else {
			value = file_acc.file_integer(sizeof(FLOAT), 0, known_values);
		}
		return value;
	}

	FLOAT generate(std::vector<FLOAT> possible_values) {
		_startof = FTell();
		value = file_acc.file_integer(sizeof(FLOAT), 0, possible_values);
		return value;
	}
};



class EMRANGLEARC {
	std::vector<EMRANGLEARC*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	POINT* ptlCenter_var;
	DWORD nRadius_var;
	FLOAT eStartAngle_var;
	FLOAT eSweepAngle_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ptlCenter_exists = false;
	bool nRadius_exists = false;
	bool eStartAngle_exists = false;
	bool eSweepAngle_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	POINT& ptlCenter() {
		assert_cond(ptlCenter_exists, "struct field ptlCenter does not exist");
		return *ptlCenter_var;
	}
	DWORD& nRadius() {
		assert_cond(nRadius_exists, "struct field nRadius does not exist");
		return nRadius_var;
	}
	FLOAT& eStartAngle() {
		assert_cond(eStartAngle_exists, "struct field eStartAngle does not exist");
		return eStartAngle_var;
	}
	FLOAT& eSweepAngle() {
		assert_cond(eSweepAngle_exists, "struct field eSweepAngle does not exist");
		return eSweepAngle_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRANGLEARC& operator () () { return *instances.back(); }
	EMRANGLEARC& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRANGLEARC(std::vector<EMRANGLEARC*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRANGLEARC() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRANGLEARC* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRANGLEARC* generate();
};

int EMRANGLEARC::_parent_id = 0;
int EMRANGLEARC::_index_start = 0;



class EMRELLIPSE {
	std::vector<EMRELLIPSE*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBox_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBox_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	RECTL& rclBox() {
		assert_cond(rclBox_exists, "struct field rclBox does not exist");
		return *rclBox_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRELLIPSE& operator () () { return *instances.back(); }
	EMRELLIPSE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRELLIPSE(std::vector<EMRELLIPSE*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRELLIPSE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRELLIPSE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRELLIPSE* generate();
};

int EMRELLIPSE::_parent_id = 0;
int EMRELLIPSE::_index_start = 0;



class EMRRECTANGLE {
	std::vector<EMRRECTANGLE*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBox_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBox_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	RECTL& rclBox() {
		assert_cond(rclBox_exists, "struct field rclBox does not exist");
		return *rclBox_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRRECTANGLE& operator () () { return *instances.back(); }
	EMRRECTANGLE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRRECTANGLE(std::vector<EMRRECTANGLE*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRRECTANGLE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRRECTANGLE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRRECTANGLE* generate();
};

int EMRRECTANGLE::_parent_id = 0;
int EMRRECTANGLE::_index_start = 0;



class EMRROUNDRECT {
	std::vector<EMRROUNDRECT*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBox_var;
	SIZEL* szlCorner_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBox_exists = false;
	bool szlCorner_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	RECTL& rclBox() {
		assert_cond(rclBox_exists, "struct field rclBox does not exist");
		return *rclBox_var;
	}
	SIZEL& szlCorner() {
		assert_cond(szlCorner_exists, "struct field szlCorner does not exist");
		return *szlCorner_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRROUNDRECT& operator () () { return *instances.back(); }
	EMRROUNDRECT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRROUNDRECT(std::vector<EMRROUNDRECT*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRROUNDRECT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRROUNDRECT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRROUNDRECT* generate();
};

int EMRROUNDRECT::_parent_id = 0;
int EMRROUNDRECT::_index_start = 0;



class EMRARC {
	std::vector<EMRARC*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBox_var;
	POINT* ptlStart_var;
	POINT* ptlEnd_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBox_exists = false;
	bool ptlStart_exists = false;
	bool ptlEnd_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	RECTL& rclBox() {
		assert_cond(rclBox_exists, "struct field rclBox does not exist");
		return *rclBox_var;
	}
	POINT& ptlStart() {
		assert_cond(ptlStart_exists, "struct field ptlStart does not exist");
		return *ptlStart_var;
	}
	POINT& ptlEnd() {
		assert_cond(ptlEnd_exists, "struct field ptlEnd does not exist");
		return *ptlEnd_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRARC& operator () () { return *instances.back(); }
	EMRARC& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRARC(std::vector<EMRARC*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRARC() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRARC* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRARC* generate();
};

int EMRARC::_parent_id = 0;
int EMRARC::_index_start = 0;



class EMRCHORD {
	std::vector<EMRCHORD*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBox_var;
	POINT* ptlStart_var;
	POINT* ptlEnd_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBox_exists = false;
	bool ptlStart_exists = false;
	bool ptlEnd_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	RECTL& rclBox() {
		assert_cond(rclBox_exists, "struct field rclBox does not exist");
		return *rclBox_var;
	}
	POINT& ptlStart() {
		assert_cond(ptlStart_exists, "struct field ptlStart does not exist");
		return *ptlStart_var;
	}
	POINT& ptlEnd() {
		assert_cond(ptlEnd_exists, "struct field ptlEnd does not exist");
		return *ptlEnd_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRCHORD& operator () () { return *instances.back(); }
	EMRCHORD& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRCHORD(std::vector<EMRCHORD*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRCHORD() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRCHORD* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRCHORD* generate();
};

int EMRCHORD::_parent_id = 0;
int EMRCHORD::_index_start = 0;



class EMRPIE {
	std::vector<EMRPIE*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* box_var;
	POINT* start_var;
	POINT* stop_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool box_exists = false;
	bool start_exists = false;
	bool stop_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	RECTL& box() {
		assert_cond(box_exists, "struct field box does not exist");
		return *box_var;
	}
	POINT& start() {
		assert_cond(start_exists, "struct field start does not exist");
		return *start_var;
	}
	POINT& stop() {
		assert_cond(stop_exists, "struct field stop does not exist");
		return *stop_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRPIE& operator () () { return *instances.back(); }
	EMRPIE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRPIE(std::vector<EMRPIE*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRPIE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRPIE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRPIE* generate();
};

int EMRPIE::_parent_id = 0;
int EMRPIE::_index_start = 0;



class EMRSELECTPALETTE {
	std::vector<EMRSELECTPALETTE*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD ihPal_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ihPal_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& ihPal() {
		assert_cond(ihPal_exists, "struct field ihPal does not exist");
		return ihPal_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRSELECTPALETTE& operator () () { return *instances.back(); }
	EMRSELECTPALETTE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRSELECTPALETTE(std::vector<EMRSELECTPALETTE*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRSELECTPALETTE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRSELECTPALETTE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRSELECTPALETTE* generate();
};

int EMRSELECTPALETTE::_parent_id = 0;
int EMRSELECTPALETTE::_index_start = 0;



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



class LOGPALETTEENTRY {
	std::vector<LOGPALETTEENTRY*>& instances;

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
	LOGPALETTEENTRY& operator () () { return *instances.back(); }
	LOGPALETTEENTRY& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	LOGPALETTEENTRY(std::vector<LOGPALETTEENTRY*>& instances) : instances(instances) { instances.push_back(this); }
	~LOGPALETTEENTRY() {
		if (generated == 2)
			return;
		while (instances.size()) {
			LOGPALETTEENTRY* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	LOGPALETTEENTRY* generate();
};

int LOGPALETTEENTRY::_parent_id = 0;
int LOGPALETTEENTRY::_index_start = 0;



class LOGPALETTEENTRY_array_class {
	LOGPALETTEENTRY& element;
	std::vector<LOGPALETTEENTRY*> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<LOGPALETTEENTRY*>& operator () () { return value; }
	LOGPALETTEENTRY operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return *value[index];
	}
	LOGPALETTEENTRY_array_class(LOGPALETTEENTRY& element) : element(element) {}

	std::vector<LOGPALETTEENTRY*> generate(unsigned size) {
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



class LOGPALETTE {
	std::vector<LOGPALETTE*>& instances;

	WORD palVersion_var;
	WORD palNumEntries_var;
	std::vector<LOGPALETTEENTRY*> palPalEntry_var;

public:
	bool palVersion_exists = false;
	bool palNumEntries_exists = false;
	bool palPalEntry_exists = false;

	WORD& palVersion() {
		assert_cond(palVersion_exists, "struct field palVersion does not exist");
		return palVersion_var;
	}
	WORD& palNumEntries() {
		assert_cond(palNumEntries_exists, "struct field palNumEntries does not exist");
		return palNumEntries_var;
	}
	std::vector<LOGPALETTEENTRY*>& palPalEntry() {
		assert_cond(palPalEntry_exists, "struct field palPalEntry does not exist");
		return palPalEntry_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	LOGPALETTE& operator () () { return *instances.back(); }
	LOGPALETTE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	LOGPALETTE(std::vector<LOGPALETTE*>& instances) : instances(instances) { instances.push_back(this); }
	~LOGPALETTE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			LOGPALETTE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	LOGPALETTE* generate();
};

int LOGPALETTE::_parent_id = 0;
int LOGPALETTE::_index_start = 0;



class EMRCREATEPALETTE {
	std::vector<EMRCREATEPALETTE*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD ihPal_var;
	LOGPALETTE* lgpl_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ihPal_exists = false;
	bool lgpl_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& ihPal() {
		assert_cond(ihPal_exists, "struct field ihPal does not exist");
		return ihPal_var;
	}
	LOGPALETTE& lgpl() {
		assert_cond(lgpl_exists, "struct field lgpl does not exist");
		return *lgpl_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRCREATEPALETTE& operator () () { return *instances.back(); }
	EMRCREATEPALETTE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRCREATEPALETTE(std::vector<EMRCREATEPALETTE*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRCREATEPALETTE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRCREATEPALETTE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRCREATEPALETTE* generate();
};

int EMRCREATEPALETTE::_parent_id = 0;
int EMRCREATEPALETTE::_index_start = 0;



class EMRSETPALETTEENTRIES {
	std::vector<EMRSETPALETTEENTRIES*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD ihPal_var;
	DWORD iStart_var;
	DWORD cEntries_var;
	std::vector<LOGPALETTEENTRY*> aPalEntries_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ihPal_exists = false;
	bool iStart_exists = false;
	bool cEntries_exists = false;
	bool aPalEntries_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& ihPal() {
		assert_cond(ihPal_exists, "struct field ihPal does not exist");
		return ihPal_var;
	}
	DWORD& iStart() {
		assert_cond(iStart_exists, "struct field iStart does not exist");
		return iStart_var;
	}
	DWORD& cEntries() {
		assert_cond(cEntries_exists, "struct field cEntries does not exist");
		return cEntries_var;
	}
	std::vector<LOGPALETTEENTRY*>& aPalEntries() {
		assert_cond(aPalEntries_exists, "struct field aPalEntries does not exist");
		return aPalEntries_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRSETPALETTEENTRIES& operator () () { return *instances.back(); }
	EMRSETPALETTEENTRIES& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRSETPALETTEENTRIES(std::vector<EMRSETPALETTEENTRIES*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRSETPALETTEENTRIES() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRSETPALETTEENTRIES* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRSETPALETTEENTRIES* generate();
};

int EMRSETPALETTEENTRIES::_parent_id = 0;
int EMRSETPALETTEENTRIES::_index_start = 0;



class EMRRESIZEPALETTE {
	std::vector<EMRRESIZEPALETTE*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD ihPal_var;
	DWORD NumberOfEntries_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ihPal_exists = false;
	bool NumberOfEntries_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& ihPal() {
		assert_cond(ihPal_exists, "struct field ihPal does not exist");
		return ihPal_var;
	}
	DWORD& NumberOfEntries() {
		assert_cond(NumberOfEntries_exists, "struct field NumberOfEntries does not exist");
		return NumberOfEntries_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRRESIZEPALETTE& operator () () { return *instances.back(); }
	EMRRESIZEPALETTE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRRESIZEPALETTE(std::vector<EMRRESIZEPALETTE*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRRESIZEPALETTE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRRESIZEPALETTE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRRESIZEPALETTE* generate();
};

int EMRRESIZEPALETTE::_parent_id = 0;
int EMRRESIZEPALETTE::_index_start = 0;



class EMREXTFLOODFILL {
	std::vector<EMREXTFLOODFILL*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	POINT* ptlStart_var;
	COLORREF* crColor_var;
	DWORD iMode_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ptlStart_exists = false;
	bool crColor_exists = false;
	bool iMode_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	POINT& ptlStart() {
		assert_cond(ptlStart_exists, "struct field ptlStart does not exist");
		return *ptlStart_var;
	}
	COLORREF& crColor() {
		assert_cond(crColor_exists, "struct field crColor does not exist");
		return *crColor_var;
	}
	DWORD& iMode() {
		assert_cond(iMode_exists, "struct field iMode does not exist");
		return iMode_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMREXTFLOODFILL& operator () () { return *instances.back(); }
	EMREXTFLOODFILL& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMREXTFLOODFILL(std::vector<EMREXTFLOODFILL*>& instances) : instances(instances) { instances.push_back(this); }
	~EMREXTFLOODFILL() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMREXTFLOODFILL* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMREXTFLOODFILL* generate();
};

int EMREXTFLOODFILL::_parent_id = 0;
int EMREXTFLOODFILL::_index_start = 0;



class EMRLINETO {
	std::vector<EMRLINETO*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	POINT* ptl_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ptl_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	POINT& ptl() {
		assert_cond(ptl_exists, "struct field ptl does not exist");
		return *ptl_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRLINETO& operator () () { return *instances.back(); }
	EMRLINETO& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRLINETO(std::vector<EMRLINETO*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRLINETO() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRLINETO* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRLINETO* generate();
};

int EMRLINETO::_parent_id = 0;
int EMRLINETO::_index_start = 0;



class EMRARCTO {
	std::vector<EMRARCTO*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBox_var;
	POINT* ptlStart_var;
	POINT* ptlEnd_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBox_exists = false;
	bool ptlStart_exists = false;
	bool ptlEnd_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	RECTL& rclBox() {
		assert_cond(rclBox_exists, "struct field rclBox does not exist");
		return *rclBox_var;
	}
	POINT& ptlStart() {
		assert_cond(ptlStart_exists, "struct field ptlStart does not exist");
		return *ptlStart_var;
	}
	POINT& ptlEnd() {
		assert_cond(ptlEnd_exists, "struct field ptlEnd does not exist");
		return *ptlEnd_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRARCTO& operator () () { return *instances.back(); }
	EMRARCTO& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRARCTO(std::vector<EMRARCTO*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRARCTO() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRARCTO* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRARCTO* generate();
};

int EMRARCTO::_parent_id = 0;
int EMRARCTO::_index_start = 0;



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



class EMRPOLYDRAW {
	std::vector<EMRPOLYDRAW*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	DWORD cntPoints_var;
	std::vector<POINT*> aPoints_var;
	std::vector<BYTE> abTypes_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool cntPoints_exists = false;
	bool aPoints_exists = false;
	bool abTypes_exists = false;

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
	DWORD& cntPoints() {
		assert_cond(cntPoints_exists, "struct field cntPoints does not exist");
		return cntPoints_var;
	}
	std::vector<POINT*>& aPoints() {
		assert_cond(aPoints_exists, "struct field aPoints does not exist");
		return aPoints_var;
	}
	std::vector<BYTE>& abTypes() {
		assert_cond(abTypes_exists, "struct field abTypes does not exist");
		return abTypes_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRPOLYDRAW& operator () () { return *instances.back(); }
	EMRPOLYDRAW& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRPOLYDRAW(std::vector<EMRPOLYDRAW*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRPOLYDRAW() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRPOLYDRAW* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRPOLYDRAW* generate();
};

int EMRPOLYDRAW::_parent_id = 0;
int EMRPOLYDRAW::_index_start = 0;



class EMRBEGINPATH {
	std::vector<EMRBEGINPATH*>& instances;

	DWORD iType_var;
	DWORD nSize_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRBEGINPATH& operator () () { return *instances.back(); }
	EMRBEGINPATH& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRBEGINPATH(std::vector<EMRBEGINPATH*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRBEGINPATH() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRBEGINPATH* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRBEGINPATH* generate();
};

int EMRBEGINPATH::_parent_id = 0;
int EMRBEGINPATH::_index_start = 0;



class EMRENDPATH {
	std::vector<EMRENDPATH*>& instances;

	DWORD iType_var;
	DWORD nSize_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRENDPATH& operator () () { return *instances.back(); }
	EMRENDPATH& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRENDPATH(std::vector<EMRENDPATH*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRENDPATH() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRENDPATH* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRENDPATH* generate();
};

int EMRENDPATH::_parent_id = 0;
int EMRENDPATH::_index_start = 0;



class EMRCLOSEFIGURE {
	std::vector<EMRCLOSEFIGURE*>& instances;

	DWORD iType_var;
	DWORD nSize_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRCLOSEFIGURE& operator () () { return *instances.back(); }
	EMRCLOSEFIGURE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRCLOSEFIGURE(std::vector<EMRCLOSEFIGURE*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRCLOSEFIGURE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRCLOSEFIGURE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRCLOSEFIGURE* generate();
};

int EMRCLOSEFIGURE::_parent_id = 0;
int EMRCLOSEFIGURE::_index_start = 0;



class EMRFILLPATH {
	std::vector<EMRFILLPATH*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;

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

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRFILLPATH& operator () () { return *instances.back(); }
	EMRFILLPATH& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRFILLPATH(std::vector<EMRFILLPATH*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRFILLPATH() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRFILLPATH* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRFILLPATH* generate();
};

int EMRFILLPATH::_parent_id = 0;
int EMRFILLPATH::_index_start = 0;



class EMRSTROKEANDFILLPATH {
	std::vector<EMRSTROKEANDFILLPATH*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;

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

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRSTROKEANDFILLPATH& operator () () { return *instances.back(); }
	EMRSTROKEANDFILLPATH& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRSTROKEANDFILLPATH(std::vector<EMRSTROKEANDFILLPATH*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRSTROKEANDFILLPATH() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRSTROKEANDFILLPATH* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRSTROKEANDFILLPATH* generate();
};

int EMRSTROKEANDFILLPATH::_parent_id = 0;
int EMRSTROKEANDFILLPATH::_index_start = 0;



class EMRSTROKEPATH {
	std::vector<EMRSTROKEPATH*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;

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

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRSTROKEPATH& operator () () { return *instances.back(); }
	EMRSTROKEPATH& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRSTROKEPATH(std::vector<EMRSTROKEPATH*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRSTROKEPATH() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRSTROKEPATH* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRSTROKEPATH* generate();
};

int EMRSTROKEPATH::_parent_id = 0;
int EMRSTROKEPATH::_index_start = 0;



class EMRFLATTENPATH {
	std::vector<EMRFLATTENPATH*>& instances;

	DWORD iType_var;
	DWORD nSize_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRFLATTENPATH& operator () () { return *instances.back(); }
	EMRFLATTENPATH& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRFLATTENPATH(std::vector<EMRFLATTENPATH*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRFLATTENPATH() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRFLATTENPATH* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRFLATTENPATH* generate();
};

int EMRFLATTENPATH::_parent_id = 0;
int EMRFLATTENPATH::_index_start = 0;



class EMRWIDENPATH {
	std::vector<EMRWIDENPATH*>& instances;

	DWORD iType_var;
	DWORD nSize_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRWIDENPATH& operator () () { return *instances.back(); }
	EMRWIDENPATH& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRWIDENPATH(std::vector<EMRWIDENPATH*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRWIDENPATH() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRWIDENPATH* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRWIDENPATH* generate();
};

int EMRWIDENPATH::_parent_id = 0;
int EMRWIDENPATH::_index_start = 0;


RegionMode RegionMode_generate() {
	return (RegionMode) file_acc.file_integer(sizeof(DWORD), 0, RegionMode_values);
}

RegionMode RegionMode_generate(std::vector<DWORD> known_values) {
	return (RegionMode) file_acc.file_integer(sizeof(DWORD), 0, known_values);
}


class EMRSELECTCLIPPATH {
	std::vector<EMRSELECTCLIPPATH*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD rgnMode_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rgnMode_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& rgnMode() {
		assert_cond(rgnMode_exists, "struct field rgnMode does not exist");
		return rgnMode_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRSELECTCLIPPATH& operator () () { return *instances.back(); }
	EMRSELECTCLIPPATH& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRSELECTCLIPPATH(std::vector<EMRSELECTCLIPPATH*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRSELECTCLIPPATH() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRSELECTCLIPPATH* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRSELECTCLIPPATH* generate();
};

int EMRSELECTCLIPPATH::_parent_id = 0;
int EMRSELECTCLIPPATH::_index_start = 0;



class EMRABORTPATH {
	std::vector<EMRABORTPATH*>& instances;

	DWORD iType_var;
	DWORD nSize_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRABORTPATH& operator () () { return *instances.back(); }
	EMRABORTPATH& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRABORTPATH(std::vector<EMRABORTPATH*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRABORTPATH() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRABORTPATH* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRABORTPATH* generate();
};

int EMRABORTPATH::_parent_id = 0;
int EMRABORTPATH::_index_start = 0;



class EMRCOMMENT {
	std::vector<EMRCOMMENT*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD dataSize_var;
	std::vector<BYTE> privateData_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool dataSize_exists = false;
	bool privateData_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& dataSize() {
		assert_cond(dataSize_exists, "struct field dataSize does not exist");
		return dataSize_var;
	}
	std::vector<BYTE>& privateData() {
		assert_cond(privateData_exists, "struct field privateData does not exist");
		return privateData_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRCOMMENT& operator () () { return *instances.back(); }
	EMRCOMMENT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRCOMMENT(std::vector<EMRCOMMENT*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRCOMMENT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRCOMMENT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRCOMMENT* generate();
};

int EMRCOMMENT::_parent_id = 0;
int EMRCOMMENT::_index_start = 0;



class REGIONDATAHEADER {
	std::vector<REGIONDATAHEADER*>& instances;

	DWORD nSize_var;
	DWORD iType_var;
	DWORD cntRects_var;
	DWORD rgnSize_var;
	RECTL* rgnBounds_var;

public:
	bool nSize_exists = false;
	bool iType_exists = false;
	bool cntRects_exists = false;
	bool rgnSize_exists = false;
	bool rgnBounds_exists = false;

	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& cntRects() {
		assert_cond(cntRects_exists, "struct field cntRects does not exist");
		return cntRects_var;
	}
	DWORD& rgnSize() {
		assert_cond(rgnSize_exists, "struct field rgnSize does not exist");
		return rgnSize_var;
	}
	RECTL& rgnBounds() {
		assert_cond(rgnBounds_exists, "struct field rgnBounds does not exist");
		return *rgnBounds_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	REGIONDATAHEADER& operator () () { return *instances.back(); }
	REGIONDATAHEADER& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	REGIONDATAHEADER(std::vector<REGIONDATAHEADER*>& instances) : instances(instances) { instances.push_back(this); }
	~REGIONDATAHEADER() {
		if (generated == 2)
			return;
		while (instances.size()) {
			REGIONDATAHEADER* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	REGIONDATAHEADER* generate();
};

int REGIONDATAHEADER::_parent_id = 0;
int REGIONDATAHEADER::_index_start = 0;



class RECTL_array_class {
	RECTL& element;
	std::vector<RECTL*> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<RECTL*>& operator () () { return value; }
	RECTL operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return *value[index];
	}
	RECTL_array_class(RECTL& element) : element(element) {}

	std::vector<RECTL*> generate(unsigned size) {
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



class REGIONDATA {
	std::vector<REGIONDATA*>& instances;

	REGIONDATAHEADER* rgnDataHeader_var;
	std::vector<RECTL*> data_var;

public:
	bool rgnDataHeader_exists = false;
	bool data_exists = false;

	REGIONDATAHEADER& rgnDataHeader() {
		assert_cond(rgnDataHeader_exists, "struct field rgnDataHeader does not exist");
		return *rgnDataHeader_var;
	}
	std::vector<RECTL*>& data() {
		assert_cond(data_exists, "struct field data does not exist");
		return data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	REGIONDATA& operator () () { return *instances.back(); }
	REGIONDATA& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	REGIONDATA(std::vector<REGIONDATA*>& instances) : instances(instances) { instances.push_back(this); }
	~REGIONDATA() {
		if (generated == 2)
			return;
		while (instances.size()) {
			REGIONDATA* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	REGIONDATA* generate();
};

int REGIONDATA::_parent_id = 0;
int REGIONDATA::_index_start = 0;



class EMRFILLRGN {
	std::vector<EMRFILLRGN*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	DWORD rgnDataSize_var;
	DWORD ihBrush_var;
	REGIONDATA* rgnData_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool rgnDataSize_exists = false;
	bool ihBrush_exists = false;
	bool rgnData_exists = false;

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
	DWORD& rgnDataSize() {
		assert_cond(rgnDataSize_exists, "struct field rgnDataSize does not exist");
		return rgnDataSize_var;
	}
	DWORD& ihBrush() {
		assert_cond(ihBrush_exists, "struct field ihBrush does not exist");
		return ihBrush_var;
	}
	REGIONDATA& rgnData() {
		assert_cond(rgnData_exists, "struct field rgnData does not exist");
		return *rgnData_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRFILLRGN& operator () () { return *instances.back(); }
	EMRFILLRGN& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRFILLRGN(std::vector<EMRFILLRGN*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRFILLRGN() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRFILLRGN* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRFILLRGN* generate();
};

int EMRFILLRGN::_parent_id = 0;
int EMRFILLRGN::_index_start = 0;



class EMRFRAMERGN {
	std::vector<EMRFRAMERGN*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	DWORD rgnDataSize_var;
	DWORD ihBrush_var;
	DWORD width_var;
	DWORD height_var;
	REGIONDATA* rgnData_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool rgnDataSize_exists = false;
	bool ihBrush_exists = false;
	bool width_exists = false;
	bool height_exists = false;
	bool rgnData_exists = false;

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
	DWORD& rgnDataSize() {
		assert_cond(rgnDataSize_exists, "struct field rgnDataSize does not exist");
		return rgnDataSize_var;
	}
	DWORD& ihBrush() {
		assert_cond(ihBrush_exists, "struct field ihBrush does not exist");
		return ihBrush_var;
	}
	DWORD& width() {
		assert_cond(width_exists, "struct field width does not exist");
		return width_var;
	}
	DWORD& height() {
		assert_cond(height_exists, "struct field height does not exist");
		return height_var;
	}
	REGIONDATA& rgnData() {
		assert_cond(rgnData_exists, "struct field rgnData does not exist");
		return *rgnData_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRFRAMERGN& operator () () { return *instances.back(); }
	EMRFRAMERGN& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRFRAMERGN(std::vector<EMRFRAMERGN*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRFRAMERGN() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRFRAMERGN* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRFRAMERGN* generate();
};

int EMRFRAMERGN::_parent_id = 0;
int EMRFRAMERGN::_index_start = 0;



class EMRINVERTRGN {
	std::vector<EMRINVERTRGN*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	DWORD nRgnDataSize_var;
	std::vector<BYTE> rgnData_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool nRgnDataSize_exists = false;
	bool rgnData_exists = false;

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
	DWORD& nRgnDataSize() {
		assert_cond(nRgnDataSize_exists, "struct field nRgnDataSize does not exist");
		return nRgnDataSize_var;
	}
	std::vector<BYTE>& rgnData() {
		assert_cond(rgnData_exists, "struct field rgnData does not exist");
		return rgnData_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRINVERTRGN& operator () () { return *instances.back(); }
	EMRINVERTRGN& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRINVERTRGN(std::vector<EMRINVERTRGN*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRINVERTRGN() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRINVERTRGN* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRINVERTRGN* generate();
};

int EMRINVERTRGN::_parent_id = 0;
int EMRINVERTRGN::_index_start = 0;



class EMRPAINTRGN {
	std::vector<EMRPAINTRGN*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	DWORD rgnDataSize_var;
	REGIONDATA* rgnData_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool rgnDataSize_exists = false;
	bool rgnData_exists = false;

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
	DWORD& rgnDataSize() {
		assert_cond(rgnDataSize_exists, "struct field rgnDataSize does not exist");
		return rgnDataSize_var;
	}
	REGIONDATA& rgnData() {
		assert_cond(rgnData_exists, "struct field rgnData does not exist");
		return *rgnData_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRPAINTRGN& operator () () { return *instances.back(); }
	EMRPAINTRGN& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRPAINTRGN(std::vector<EMRPAINTRGN*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRPAINTRGN() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRPAINTRGN* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRPAINTRGN* generate();
};

int EMRPAINTRGN::_parent_id = 0;
int EMRPAINTRGN::_index_start = 0;



class EMREXTSELECTCLIPRGN {
	std::vector<EMREXTSELECTCLIPRGN*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD rgnDataSize_var;
	DWORD rgnMode_var;
	REGIONDATA* rgnData_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rgnDataSize_exists = false;
	bool rgnMode_exists = false;
	bool rgnData_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& rgnDataSize() {
		assert_cond(rgnDataSize_exists, "struct field rgnDataSize does not exist");
		return rgnDataSize_var;
	}
	DWORD& rgnMode() {
		assert_cond(rgnMode_exists, "struct field rgnMode does not exist");
		return rgnMode_var;
	}
	REGIONDATA& rgnData() {
		assert_cond(rgnData_exists, "struct field rgnData does not exist");
		return *rgnData_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMREXTSELECTCLIPRGN& operator () () { return *instances.back(); }
	EMREXTSELECTCLIPRGN& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMREXTSELECTCLIPRGN(std::vector<EMREXTSELECTCLIPRGN*>& instances) : instances(instances) { instances.push_back(this); }
	~EMREXTSELECTCLIPRGN() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMREXTSELECTCLIPRGN* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMREXTSELECTCLIPRGN* generate();
};

int EMREXTSELECTCLIPRGN::_parent_id = 0;
int EMREXTSELECTCLIPRGN::_index_start = 0;



class XFORM {
	std::vector<XFORM*>& instances;

	FLOAT eM11_var;
	FLOAT eM12_var;
	FLOAT eM21_var;
	FLOAT eM22_var;
	FLOAT eDx_var;
	FLOAT eDy_var;

public:
	bool eM11_exists = false;
	bool eM12_exists = false;
	bool eM21_exists = false;
	bool eM22_exists = false;
	bool eDx_exists = false;
	bool eDy_exists = false;

	FLOAT& eM11() {
		assert_cond(eM11_exists, "struct field eM11 does not exist");
		return eM11_var;
	}
	FLOAT& eM12() {
		assert_cond(eM12_exists, "struct field eM12 does not exist");
		return eM12_var;
	}
	FLOAT& eM21() {
		assert_cond(eM21_exists, "struct field eM21 does not exist");
		return eM21_var;
	}
	FLOAT& eM22() {
		assert_cond(eM22_exists, "struct field eM22 does not exist");
		return eM22_var;
	}
	FLOAT& eDx() {
		assert_cond(eDx_exists, "struct field eDx does not exist");
		return eDx_var;
	}
	FLOAT& eDy() {
		assert_cond(eDy_exists, "struct field eDy does not exist");
		return eDy_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	XFORM& operator () () { return *instances.back(); }
	XFORM& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	XFORM(std::vector<XFORM*>& instances) : instances(instances) { instances.push_back(this); }
	~XFORM() {
		if (generated == 2)
			return;
		while (instances.size()) {
			XFORM* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	XFORM* generate();
};

int XFORM::_parent_id = 0;
int XFORM::_index_start = 0;


DIBColors DIBColors_generate() {
	return (DIBColors) file_acc.file_integer(sizeof(DWORD), 0, DIBColors_values);
}

DIBColors DIBColors_generate(std::vector<DWORD> known_values) {
	return (DIBColors) file_acc.file_integer(sizeof(DWORD), 0, known_values);
}

BitCount BitCount_generate() {
	return (BitCount) file_acc.file_integer(sizeof(WORD), 0, BitCount_values);
}

BitCount BitCount_generate(std::vector<WORD> known_values) {
	return (BitCount) file_acc.file_integer(sizeof(WORD), 0, known_values);
}


class BITMAPINFOHEADER {
	std::vector<BITMAPINFOHEADER*>& instances;

	DWORD biSize_var;
	LONG biWidth_var;
	LONG biHeight_var;
	WORD biPlanes_var;
	WORD biBitCount_var;
	DWORD biCompression_var;
	DWORD biSizeImage_var;
	LONG biXPelsPerMeter_var;
	LONG biYPelsPerMeter_var;
	DWORD biClrUsed_var;
	DWORD biClrImportant_var;

public:
	bool biSize_exists = false;
	bool biWidth_exists = false;
	bool biHeight_exists = false;
	bool biPlanes_exists = false;
	bool biBitCount_exists = false;
	bool biCompression_exists = false;
	bool biSizeImage_exists = false;
	bool biXPelsPerMeter_exists = false;
	bool biYPelsPerMeter_exists = false;
	bool biClrUsed_exists = false;
	bool biClrImportant_exists = false;

	DWORD& biSize() {
		assert_cond(biSize_exists, "struct field biSize does not exist");
		return biSize_var;
	}
	LONG& biWidth() {
		assert_cond(biWidth_exists, "struct field biWidth does not exist");
		return biWidth_var;
	}
	LONG& biHeight() {
		assert_cond(biHeight_exists, "struct field biHeight does not exist");
		return biHeight_var;
	}
	WORD& biPlanes() {
		assert_cond(biPlanes_exists, "struct field biPlanes does not exist");
		return biPlanes_var;
	}
	WORD& biBitCount() {
		assert_cond(biBitCount_exists, "struct field biBitCount does not exist");
		return biBitCount_var;
	}
	DWORD& biCompression() {
		assert_cond(biCompression_exists, "struct field biCompression does not exist");
		return biCompression_var;
	}
	DWORD& biSizeImage() {
		assert_cond(biSizeImage_exists, "struct field biSizeImage does not exist");
		return biSizeImage_var;
	}
	LONG& biXPelsPerMeter() {
		assert_cond(biXPelsPerMeter_exists, "struct field biXPelsPerMeter does not exist");
		return biXPelsPerMeter_var;
	}
	LONG& biYPelsPerMeter() {
		assert_cond(biYPelsPerMeter_exists, "struct field biYPelsPerMeter does not exist");
		return biYPelsPerMeter_var;
	}
	DWORD& biClrUsed() {
		assert_cond(biClrUsed_exists, "struct field biClrUsed does not exist");
		return biClrUsed_var;
	}
	DWORD& biClrImportant() {
		assert_cond(biClrImportant_exists, "struct field biClrImportant does not exist");
		return biClrImportant_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	BITMAPINFOHEADER& operator () () { return *instances.back(); }
	BITMAPINFOHEADER& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	BITMAPINFOHEADER(std::vector<BITMAPINFOHEADER*>& instances) : instances(instances) { instances.push_back(this); }
	~BITMAPINFOHEADER() {
		if (generated == 2)
			return;
		while (instances.size()) {
			BITMAPINFOHEADER* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	BITMAPINFOHEADER* generate();
};

int BITMAPINFOHEADER::_parent_id = 0;
int BITMAPINFOHEADER::_index_start = 0;



class RGBQUAD {
	std::vector<RGBQUAD*>& instances;

	UBYTE rgbBlue_var;
	UBYTE rgbGreen_var;
	UBYTE rgbRed_var;
	UBYTE rgbReserved_var;

public:
	bool rgbBlue_exists = false;
	bool rgbGreen_exists = false;
	bool rgbRed_exists = false;
	bool rgbReserved_exists = false;

	UBYTE& rgbBlue() {
		assert_cond(rgbBlue_exists, "struct field rgbBlue does not exist");
		return rgbBlue_var;
	}
	UBYTE& rgbGreen() {
		assert_cond(rgbGreen_exists, "struct field rgbGreen does not exist");
		return rgbGreen_var;
	}
	UBYTE& rgbRed() {
		assert_cond(rgbRed_exists, "struct field rgbRed does not exist");
		return rgbRed_var;
	}
	UBYTE& rgbReserved() {
		assert_cond(rgbReserved_exists, "struct field rgbReserved does not exist");
		return rgbReserved_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	RGBQUAD& operator () () { return *instances.back(); }
	RGBQUAD& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	RGBQUAD(std::vector<RGBQUAD*>& instances) : instances(instances) { instances.push_back(this); }
	~RGBQUAD() {
		if (generated == 2)
			return;
		while (instances.size()) {
			RGBQUAD* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	RGBQUAD* generate();
};

int RGBQUAD::_parent_id = 0;
int RGBQUAD::_index_start = 0;



class RGBQUAD_array_class {
	RGBQUAD& element;
	std::vector<RGBQUAD*> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<RGBQUAD*>& operator () () { return value; }
	RGBQUAD operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return *value[index];
	}
	RGBQUAD_array_class(RGBQUAD& element) : element(element) {}

	std::vector<RGBQUAD*> generate(unsigned size) {
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



class BITMAPINFO {
	std::vector<BITMAPINFO*>& instances;

	BITMAPINFOHEADER* bmiHeader_var;
	std::vector<RGBQUAD*> bmiColors_var;

public:
	bool bmiHeader_exists = false;
	bool bmiColors_exists = false;

	BITMAPINFOHEADER& bmiHeader() {
		assert_cond(bmiHeader_exists, "struct field bmiHeader does not exist");
		return *bmiHeader_var;
	}
	std::vector<RGBQUAD*>& bmiColors() {
		assert_cond(bmiColors_exists, "struct field bmiColors does not exist");
		return bmiColors_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	BITMAPINFO& operator () () { return *instances.back(); }
	BITMAPINFO& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	BITMAPINFO(std::vector<BITMAPINFO*>& instances) : instances(instances) { instances.push_back(this); }
	~BITMAPINFO() {
		if (generated == 2)
			return;
		while (instances.size()) {
			BITMAPINFO* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	BITMAPINFO* generate();
};

int BITMAPINFO::_parent_id = 0;
int BITMAPINFO::_index_start = 0;



class EMRBITBLT {
	std::vector<EMRBITBLT*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	DWORD xDest_var;
	DWORD yDest_var;
	DWORD cxDest_var;
	DWORD cyDest_var;
	DWORD BitBltRasterOperation_var;
	DWORD xSrc_var;
	DWORD ySrc_var;
	XFORM* xformSrc_var;
	DWORD BkColorSrc_var;
	DWORD iUsageSrc_var;
	DWORD offBmiSrc_var;
	DWORD cbBmiSrc_var;
	DWORD offBitsSrc_var;
	DWORD cbBitsSrc_var;
	BITMAPINFO* BmiSrc_var;
	std::vector<BYTE> BitsSrc_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool xDest_exists = false;
	bool yDest_exists = false;
	bool cxDest_exists = false;
	bool cyDest_exists = false;
	bool BitBltRasterOperation_exists = false;
	bool xSrc_exists = false;
	bool ySrc_exists = false;
	bool xformSrc_exists = false;
	bool BkColorSrc_exists = false;
	bool iUsageSrc_exists = false;
	bool offBmiSrc_exists = false;
	bool cbBmiSrc_exists = false;
	bool offBitsSrc_exists = false;
	bool cbBitsSrc_exists = false;
	bool BmiSrc_exists = false;
	bool BitsSrc_exists = false;

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
	DWORD& xDest() {
		assert_cond(xDest_exists, "struct field xDest does not exist");
		return xDest_var;
	}
	DWORD& yDest() {
		assert_cond(yDest_exists, "struct field yDest does not exist");
		return yDest_var;
	}
	DWORD& cxDest() {
		assert_cond(cxDest_exists, "struct field cxDest does not exist");
		return cxDest_var;
	}
	DWORD& cyDest() {
		assert_cond(cyDest_exists, "struct field cyDest does not exist");
		return cyDest_var;
	}
	DWORD& BitBltRasterOperation() {
		assert_cond(BitBltRasterOperation_exists, "struct field BitBltRasterOperation does not exist");
		return BitBltRasterOperation_var;
	}
	DWORD& xSrc() {
		assert_cond(xSrc_exists, "struct field xSrc does not exist");
		return xSrc_var;
	}
	DWORD& ySrc() {
		assert_cond(ySrc_exists, "struct field ySrc does not exist");
		return ySrc_var;
	}
	XFORM& xformSrc() {
		assert_cond(xformSrc_exists, "struct field xformSrc does not exist");
		return *xformSrc_var;
	}
	DWORD& BkColorSrc() {
		assert_cond(BkColorSrc_exists, "struct field BkColorSrc does not exist");
		return BkColorSrc_var;
	}
	DWORD& iUsageSrc() {
		assert_cond(iUsageSrc_exists, "struct field iUsageSrc does not exist");
		return iUsageSrc_var;
	}
	DWORD& offBmiSrc() {
		assert_cond(offBmiSrc_exists, "struct field offBmiSrc does not exist");
		return offBmiSrc_var;
	}
	DWORD& cbBmiSrc() {
		assert_cond(cbBmiSrc_exists, "struct field cbBmiSrc does not exist");
		return cbBmiSrc_var;
	}
	DWORD& offBitsSrc() {
		assert_cond(offBitsSrc_exists, "struct field offBitsSrc does not exist");
		return offBitsSrc_var;
	}
	DWORD& cbBitsSrc() {
		assert_cond(cbBitsSrc_exists, "struct field cbBitsSrc does not exist");
		return cbBitsSrc_var;
	}
	BITMAPINFO& BmiSrc() {
		assert_cond(BmiSrc_exists, "struct field BmiSrc does not exist");
		return *BmiSrc_var;
	}
	std::vector<BYTE>& BitsSrc() {
		assert_cond(BitsSrc_exists, "struct field BitsSrc does not exist");
		return BitsSrc_var;
	}

	/* locals */
	uint emrSize;
	uint bmiSize;
	uint emrOffset;
	uint end;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRBITBLT& operator () () { return *instances.back(); }
	EMRBITBLT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRBITBLT(std::vector<EMRBITBLT*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRBITBLT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRBITBLT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRBITBLT* generate();
};

int EMRBITBLT::_parent_id = 0;
int EMRBITBLT::_index_start = 0;



class EMRSTRETCHBLT {
	std::vector<EMRSTRETCHBLT*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	LONG xDest_var;
	LONG yDest_var;
	LONG cxDest_var;
	LONG cyDest_var;
	DWORD dwRop_var;
	LONG xSrc_var;
	LONG ySrc_var;
	XFORM* xformSrc_var;
	COLORREF* crBkColorSrc_var;
	DWORD iUsageSrc_var;
	DWORD offBmiSrc_var;
	DWORD cbBmiSrc_var;
	DWORD offBitsSrc_var;
	DWORD cbBitsSrc_var;
	LONG cxSrc_var;
	LONG cySrc_var;
	BITMAPINFO* BmiSrc_var;
	std::vector<BYTE> BitsSrc_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool xDest_exists = false;
	bool yDest_exists = false;
	bool cxDest_exists = false;
	bool cyDest_exists = false;
	bool dwRop_exists = false;
	bool xSrc_exists = false;
	bool ySrc_exists = false;
	bool xformSrc_exists = false;
	bool crBkColorSrc_exists = false;
	bool iUsageSrc_exists = false;
	bool offBmiSrc_exists = false;
	bool cbBmiSrc_exists = false;
	bool offBitsSrc_exists = false;
	bool cbBitsSrc_exists = false;
	bool cxSrc_exists = false;
	bool cySrc_exists = false;
	bool BmiSrc_exists = false;
	bool BitsSrc_exists = false;

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
	LONG& xDest() {
		assert_cond(xDest_exists, "struct field xDest does not exist");
		return xDest_var;
	}
	LONG& yDest() {
		assert_cond(yDest_exists, "struct field yDest does not exist");
		return yDest_var;
	}
	LONG& cxDest() {
		assert_cond(cxDest_exists, "struct field cxDest does not exist");
		return cxDest_var;
	}
	LONG& cyDest() {
		assert_cond(cyDest_exists, "struct field cyDest does not exist");
		return cyDest_var;
	}
	DWORD& dwRop() {
		assert_cond(dwRop_exists, "struct field dwRop does not exist");
		return dwRop_var;
	}
	LONG& xSrc() {
		assert_cond(xSrc_exists, "struct field xSrc does not exist");
		return xSrc_var;
	}
	LONG& ySrc() {
		assert_cond(ySrc_exists, "struct field ySrc does not exist");
		return ySrc_var;
	}
	XFORM& xformSrc() {
		assert_cond(xformSrc_exists, "struct field xformSrc does not exist");
		return *xformSrc_var;
	}
	COLORREF& crBkColorSrc() {
		assert_cond(crBkColorSrc_exists, "struct field crBkColorSrc does not exist");
		return *crBkColorSrc_var;
	}
	DWORD& iUsageSrc() {
		assert_cond(iUsageSrc_exists, "struct field iUsageSrc does not exist");
		return iUsageSrc_var;
	}
	DWORD& offBmiSrc() {
		assert_cond(offBmiSrc_exists, "struct field offBmiSrc does not exist");
		return offBmiSrc_var;
	}
	DWORD& cbBmiSrc() {
		assert_cond(cbBmiSrc_exists, "struct field cbBmiSrc does not exist");
		return cbBmiSrc_var;
	}
	DWORD& offBitsSrc() {
		assert_cond(offBitsSrc_exists, "struct field offBitsSrc does not exist");
		return offBitsSrc_var;
	}
	DWORD& cbBitsSrc() {
		assert_cond(cbBitsSrc_exists, "struct field cbBitsSrc does not exist");
		return cbBitsSrc_var;
	}
	LONG& cxSrc() {
		assert_cond(cxSrc_exists, "struct field cxSrc does not exist");
		return cxSrc_var;
	}
	LONG& cySrc() {
		assert_cond(cySrc_exists, "struct field cySrc does not exist");
		return cySrc_var;
	}
	BITMAPINFO& BmiSrc() {
		assert_cond(BmiSrc_exists, "struct field BmiSrc does not exist");
		return *BmiSrc_var;
	}
	std::vector<BYTE>& BitsSrc() {
		assert_cond(BitsSrc_exists, "struct field BitsSrc does not exist");
		return BitsSrc_var;
	}

	/* locals */
	uint emrSize;
	uint bmiSize;
	uint emrOffset;
	uint end;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRSTRETCHBLT& operator () () { return *instances.back(); }
	EMRSTRETCHBLT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRSTRETCHBLT(std::vector<EMRSTRETCHBLT*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRSTRETCHBLT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRSTRETCHBLT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRSTRETCHBLT* generate();
};

int EMRSTRETCHBLT::_parent_id = 0;
int EMRSTRETCHBLT::_index_start = 0;



class EMRMASKBLT {
	std::vector<EMRMASKBLT*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	LONG xDest_var;
	LONG yDest_var;
	LONG cxDest_var;
	LONG cyDest_var;
	DWORD dwRop_var;
	LONG xSrc_var;
	LONG ySrc_var;
	XFORM* xformSrc_var;
	COLORREF* crBkColorSrc_var;
	DWORD iUsageSrc_var;
	DWORD offBmiSrc_var;
	DWORD cbBmiSrc_var;
	DWORD offBitsSrc_var;
	DWORD cbBitsSrc_var;
	LONG xMask_var;
	LONG yMask_var;
	DWORD iUsageMask_var;
	DWORD offBmiMask_var;
	DWORD cbBmiMask_var;
	DWORD offBitsMask_var;
	DWORD cbBitsMask_var;
	BITMAPINFO* BmiSrc_var;
	std::vector<BYTE> BitsSrc_var;
	BITMAPINFO* BmiMask_var;
	std::vector<BYTE> BitsMask_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool xDest_exists = false;
	bool yDest_exists = false;
	bool cxDest_exists = false;
	bool cyDest_exists = false;
	bool dwRop_exists = false;
	bool xSrc_exists = false;
	bool ySrc_exists = false;
	bool xformSrc_exists = false;
	bool crBkColorSrc_exists = false;
	bool iUsageSrc_exists = false;
	bool offBmiSrc_exists = false;
	bool cbBmiSrc_exists = false;
	bool offBitsSrc_exists = false;
	bool cbBitsSrc_exists = false;
	bool xMask_exists = false;
	bool yMask_exists = false;
	bool iUsageMask_exists = false;
	bool offBmiMask_exists = false;
	bool cbBmiMask_exists = false;
	bool offBitsMask_exists = false;
	bool cbBitsMask_exists = false;
	bool BmiSrc_exists = false;
	bool BitsSrc_exists = false;
	bool BmiMask_exists = false;
	bool BitsMask_exists = false;

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
	LONG& xDest() {
		assert_cond(xDest_exists, "struct field xDest does not exist");
		return xDest_var;
	}
	LONG& yDest() {
		assert_cond(yDest_exists, "struct field yDest does not exist");
		return yDest_var;
	}
	LONG& cxDest() {
		assert_cond(cxDest_exists, "struct field cxDest does not exist");
		return cxDest_var;
	}
	LONG& cyDest() {
		assert_cond(cyDest_exists, "struct field cyDest does not exist");
		return cyDest_var;
	}
	DWORD& dwRop() {
		assert_cond(dwRop_exists, "struct field dwRop does not exist");
		return dwRop_var;
	}
	LONG& xSrc() {
		assert_cond(xSrc_exists, "struct field xSrc does not exist");
		return xSrc_var;
	}
	LONG& ySrc() {
		assert_cond(ySrc_exists, "struct field ySrc does not exist");
		return ySrc_var;
	}
	XFORM& xformSrc() {
		assert_cond(xformSrc_exists, "struct field xformSrc does not exist");
		return *xformSrc_var;
	}
	COLORREF& crBkColorSrc() {
		assert_cond(crBkColorSrc_exists, "struct field crBkColorSrc does not exist");
		return *crBkColorSrc_var;
	}
	DWORD& iUsageSrc() {
		assert_cond(iUsageSrc_exists, "struct field iUsageSrc does not exist");
		return iUsageSrc_var;
	}
	DWORD& offBmiSrc() {
		assert_cond(offBmiSrc_exists, "struct field offBmiSrc does not exist");
		return offBmiSrc_var;
	}
	DWORD& cbBmiSrc() {
		assert_cond(cbBmiSrc_exists, "struct field cbBmiSrc does not exist");
		return cbBmiSrc_var;
	}
	DWORD& offBitsSrc() {
		assert_cond(offBitsSrc_exists, "struct field offBitsSrc does not exist");
		return offBitsSrc_var;
	}
	DWORD& cbBitsSrc() {
		assert_cond(cbBitsSrc_exists, "struct field cbBitsSrc does not exist");
		return cbBitsSrc_var;
	}
	LONG& xMask() {
		assert_cond(xMask_exists, "struct field xMask does not exist");
		return xMask_var;
	}
	LONG& yMask() {
		assert_cond(yMask_exists, "struct field yMask does not exist");
		return yMask_var;
	}
	DWORD& iUsageMask() {
		assert_cond(iUsageMask_exists, "struct field iUsageMask does not exist");
		return iUsageMask_var;
	}
	DWORD& offBmiMask() {
		assert_cond(offBmiMask_exists, "struct field offBmiMask does not exist");
		return offBmiMask_var;
	}
	DWORD& cbBmiMask() {
		assert_cond(cbBmiMask_exists, "struct field cbBmiMask does not exist");
		return cbBmiMask_var;
	}
	DWORD& offBitsMask() {
		assert_cond(offBitsMask_exists, "struct field offBitsMask does not exist");
		return offBitsMask_var;
	}
	DWORD& cbBitsMask() {
		assert_cond(cbBitsMask_exists, "struct field cbBitsMask does not exist");
		return cbBitsMask_var;
	}
	BITMAPINFO& BmiSrc() {
		assert_cond(BmiSrc_exists, "struct field BmiSrc does not exist");
		return *BmiSrc_var;
	}
	std::vector<BYTE>& BitsSrc() {
		assert_cond(BitsSrc_exists, "struct field BitsSrc does not exist");
		return BitsSrc_var;
	}
	BITMAPINFO& BmiMask() {
		assert_cond(BmiMask_exists, "struct field BmiMask does not exist");
		return *BmiMask_var;
	}
	std::vector<BYTE>& BitsMask() {
		assert_cond(BitsMask_exists, "struct field BitsMask does not exist");
		return BitsMask_var;
	}

	/* locals */
	uint emrSize;
	uint bmiSize;
	uint emrOffset;
	uint end;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRMASKBLT& operator () () { return *instances.back(); }
	EMRMASKBLT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRMASKBLT(std::vector<EMRMASKBLT*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRMASKBLT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRMASKBLT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRMASKBLT* generate();
};

int EMRMASKBLT::_parent_id = 0;
int EMRMASKBLT::_index_start = 0;



class EMRPLGBLT {
	std::vector<EMRPLGBLT*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	std::vector<POINT*> aptlDest_var;
	LONG xSrc_var;
	LONG ySrc_var;
	LONG cxSrc_var;
	LONG cySrc_var;
	XFORM* xformSrc_var;
	COLORREF* crBkColorSrc_var;
	DWORD iUsageSrc_var;
	DWORD offBmiSrc_var;
	DWORD cbBmiSrc_var;
	DWORD offBitsSrc_var;
	DWORD cbBitsSrc_var;
	LONG xMask_var;
	LONG yMask_var;
	DWORD iUsageMask_var;
	DWORD offBmiMask_var;
	DWORD cbBmiMask_var;
	DWORD offBitsMask_var;
	DWORD cbBitsMask_var;
	BITMAPINFO* BmiSrc_var;
	std::vector<BYTE> BitsSrc_var;
	BITMAPINFO* BmiMask_var;
	std::vector<BYTE> BitsMask_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool aptlDest_exists = false;
	bool xSrc_exists = false;
	bool ySrc_exists = false;
	bool cxSrc_exists = false;
	bool cySrc_exists = false;
	bool xformSrc_exists = false;
	bool crBkColorSrc_exists = false;
	bool iUsageSrc_exists = false;
	bool offBmiSrc_exists = false;
	bool cbBmiSrc_exists = false;
	bool offBitsSrc_exists = false;
	bool cbBitsSrc_exists = false;
	bool xMask_exists = false;
	bool yMask_exists = false;
	bool iUsageMask_exists = false;
	bool offBmiMask_exists = false;
	bool cbBmiMask_exists = false;
	bool offBitsMask_exists = false;
	bool cbBitsMask_exists = false;
	bool BmiSrc_exists = false;
	bool BitsSrc_exists = false;
	bool BmiMask_exists = false;
	bool BitsMask_exists = false;

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
	std::vector<POINT*>& aptlDest() {
		assert_cond(aptlDest_exists, "struct field aptlDest does not exist");
		return aptlDest_var;
	}
	LONG& xSrc() {
		assert_cond(xSrc_exists, "struct field xSrc does not exist");
		return xSrc_var;
	}
	LONG& ySrc() {
		assert_cond(ySrc_exists, "struct field ySrc does not exist");
		return ySrc_var;
	}
	LONG& cxSrc() {
		assert_cond(cxSrc_exists, "struct field cxSrc does not exist");
		return cxSrc_var;
	}
	LONG& cySrc() {
		assert_cond(cySrc_exists, "struct field cySrc does not exist");
		return cySrc_var;
	}
	XFORM& xformSrc() {
		assert_cond(xformSrc_exists, "struct field xformSrc does not exist");
		return *xformSrc_var;
	}
	COLORREF& crBkColorSrc() {
		assert_cond(crBkColorSrc_exists, "struct field crBkColorSrc does not exist");
		return *crBkColorSrc_var;
	}
	DWORD& iUsageSrc() {
		assert_cond(iUsageSrc_exists, "struct field iUsageSrc does not exist");
		return iUsageSrc_var;
	}
	DWORD& offBmiSrc() {
		assert_cond(offBmiSrc_exists, "struct field offBmiSrc does not exist");
		return offBmiSrc_var;
	}
	DWORD& cbBmiSrc() {
		assert_cond(cbBmiSrc_exists, "struct field cbBmiSrc does not exist");
		return cbBmiSrc_var;
	}
	DWORD& offBitsSrc() {
		assert_cond(offBitsSrc_exists, "struct field offBitsSrc does not exist");
		return offBitsSrc_var;
	}
	DWORD& cbBitsSrc() {
		assert_cond(cbBitsSrc_exists, "struct field cbBitsSrc does not exist");
		return cbBitsSrc_var;
	}
	LONG& xMask() {
		assert_cond(xMask_exists, "struct field xMask does not exist");
		return xMask_var;
	}
	LONG& yMask() {
		assert_cond(yMask_exists, "struct field yMask does not exist");
		return yMask_var;
	}
	DWORD& iUsageMask() {
		assert_cond(iUsageMask_exists, "struct field iUsageMask does not exist");
		return iUsageMask_var;
	}
	DWORD& offBmiMask() {
		assert_cond(offBmiMask_exists, "struct field offBmiMask does not exist");
		return offBmiMask_var;
	}
	DWORD& cbBmiMask() {
		assert_cond(cbBmiMask_exists, "struct field cbBmiMask does not exist");
		return cbBmiMask_var;
	}
	DWORD& offBitsMask() {
		assert_cond(offBitsMask_exists, "struct field offBitsMask does not exist");
		return offBitsMask_var;
	}
	DWORD& cbBitsMask() {
		assert_cond(cbBitsMask_exists, "struct field cbBitsMask does not exist");
		return cbBitsMask_var;
	}
	BITMAPINFO& BmiSrc() {
		assert_cond(BmiSrc_exists, "struct field BmiSrc does not exist");
		return *BmiSrc_var;
	}
	std::vector<BYTE>& BitsSrc() {
		assert_cond(BitsSrc_exists, "struct field BitsSrc does not exist");
		return BitsSrc_var;
	}
	BITMAPINFO& BmiMask() {
		assert_cond(BmiMask_exists, "struct field BmiMask does not exist");
		return *BmiMask_var;
	}
	std::vector<BYTE>& BitsMask() {
		assert_cond(BitsMask_exists, "struct field BitsMask does not exist");
		return BitsMask_var;
	}

	/* locals */
	uint emrSize;
	uint bmiSize;
	uint emrOffset;
	uint end;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRPLGBLT& operator () () { return *instances.back(); }
	EMRPLGBLT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRPLGBLT(std::vector<EMRPLGBLT*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRPLGBLT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRPLGBLT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRPLGBLT* generate();
};

int EMRPLGBLT::_parent_id = 0;
int EMRPLGBLT::_index_start = 0;



class EMRSETDIBITSTODEVICE {
	std::vector<EMRSETDIBITSTODEVICE*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	DWORD xDest_var;
	DWORD yDest_var;
	DWORD xSrc_var;
	DWORD ySrc_var;
	DWORD cxSrc_var;
	DWORD cySrc_var;
	DWORD offBmiSrc_var;
	DWORD cbBmiSrc_var;
	DWORD offBitsSrc_var;
	DWORD cbBitsSrc_var;
	DWORD iUsageSrc_var;
	DWORD iStartScan_var;
	DWORD cScans_var;
	BITMAPINFO* BmiSrc_var;
	std::vector<BYTE> BitsSrc_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool xDest_exists = false;
	bool yDest_exists = false;
	bool xSrc_exists = false;
	bool ySrc_exists = false;
	bool cxSrc_exists = false;
	bool cySrc_exists = false;
	bool offBmiSrc_exists = false;
	bool cbBmiSrc_exists = false;
	bool offBitsSrc_exists = false;
	bool cbBitsSrc_exists = false;
	bool iUsageSrc_exists = false;
	bool iStartScan_exists = false;
	bool cScans_exists = false;
	bool BmiSrc_exists = false;
	bool BitsSrc_exists = false;

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
	DWORD& xDest() {
		assert_cond(xDest_exists, "struct field xDest does not exist");
		return xDest_var;
	}
	DWORD& yDest() {
		assert_cond(yDest_exists, "struct field yDest does not exist");
		return yDest_var;
	}
	DWORD& xSrc() {
		assert_cond(xSrc_exists, "struct field xSrc does not exist");
		return xSrc_var;
	}
	DWORD& ySrc() {
		assert_cond(ySrc_exists, "struct field ySrc does not exist");
		return ySrc_var;
	}
	DWORD& cxSrc() {
		assert_cond(cxSrc_exists, "struct field cxSrc does not exist");
		return cxSrc_var;
	}
	DWORD& cySrc() {
		assert_cond(cySrc_exists, "struct field cySrc does not exist");
		return cySrc_var;
	}
	DWORD& offBmiSrc() {
		assert_cond(offBmiSrc_exists, "struct field offBmiSrc does not exist");
		return offBmiSrc_var;
	}
	DWORD& cbBmiSrc() {
		assert_cond(cbBmiSrc_exists, "struct field cbBmiSrc does not exist");
		return cbBmiSrc_var;
	}
	DWORD& offBitsSrc() {
		assert_cond(offBitsSrc_exists, "struct field offBitsSrc does not exist");
		return offBitsSrc_var;
	}
	DWORD& cbBitsSrc() {
		assert_cond(cbBitsSrc_exists, "struct field cbBitsSrc does not exist");
		return cbBitsSrc_var;
	}
	DWORD& iUsageSrc() {
		assert_cond(iUsageSrc_exists, "struct field iUsageSrc does not exist");
		return iUsageSrc_var;
	}
	DWORD& iStartScan() {
		assert_cond(iStartScan_exists, "struct field iStartScan does not exist");
		return iStartScan_var;
	}
	DWORD& cScans() {
		assert_cond(cScans_exists, "struct field cScans does not exist");
		return cScans_var;
	}
	BITMAPINFO& BmiSrc() {
		assert_cond(BmiSrc_exists, "struct field BmiSrc does not exist");
		return *BmiSrc_var;
	}
	std::vector<BYTE>& BitsSrc() {
		assert_cond(BitsSrc_exists, "struct field BitsSrc does not exist");
		return BitsSrc_var;
	}

	/* locals */
	uint emrSize;
	uint bmiSize;
	uint emrOffset;
	uint end;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRSETDIBITSTODEVICE& operator () () { return *instances.back(); }
	EMRSETDIBITSTODEVICE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRSETDIBITSTODEVICE(std::vector<EMRSETDIBITSTODEVICE*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRSETDIBITSTODEVICE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRSETDIBITSTODEVICE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRSETDIBITSTODEVICE* generate();
};

int EMRSETDIBITSTODEVICE::_parent_id = 0;
int EMRSETDIBITSTODEVICE::_index_start = 0;



class EMRSTRETCHDIBITS {
	std::vector<EMRSTRETCHDIBITS*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	DWORD xDest_var;
	DWORD yDest_var;
	DWORD xSrc_var;
	DWORD ySrc_var;
	DWORD cxSrc_var;
	DWORD cySrc_var;
	DWORD offBmiSrc_var;
	DWORD cbBmiSrc_var;
	DWORD offBitsSrc_var;
	DWORD cbBitsSrc_var;
	DWORD iUsageSrc_var;
	DWORD dwRop_var;
	DWORD cxDest_var;
	DWORD cyDest_var;
	BITMAPINFO* BmiSrc_var;
	std::vector<BYTE> BitsSrc_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool xDest_exists = false;
	bool yDest_exists = false;
	bool xSrc_exists = false;
	bool ySrc_exists = false;
	bool cxSrc_exists = false;
	bool cySrc_exists = false;
	bool offBmiSrc_exists = false;
	bool cbBmiSrc_exists = false;
	bool offBitsSrc_exists = false;
	bool cbBitsSrc_exists = false;
	bool iUsageSrc_exists = false;
	bool dwRop_exists = false;
	bool cxDest_exists = false;
	bool cyDest_exists = false;
	bool BmiSrc_exists = false;
	bool BitsSrc_exists = false;

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
	DWORD& xDest() {
		assert_cond(xDest_exists, "struct field xDest does not exist");
		return xDest_var;
	}
	DWORD& yDest() {
		assert_cond(yDest_exists, "struct field yDest does not exist");
		return yDest_var;
	}
	DWORD& xSrc() {
		assert_cond(xSrc_exists, "struct field xSrc does not exist");
		return xSrc_var;
	}
	DWORD& ySrc() {
		assert_cond(ySrc_exists, "struct field ySrc does not exist");
		return ySrc_var;
	}
	DWORD& cxSrc() {
		assert_cond(cxSrc_exists, "struct field cxSrc does not exist");
		return cxSrc_var;
	}
	DWORD& cySrc() {
		assert_cond(cySrc_exists, "struct field cySrc does not exist");
		return cySrc_var;
	}
	DWORD& offBmiSrc() {
		assert_cond(offBmiSrc_exists, "struct field offBmiSrc does not exist");
		return offBmiSrc_var;
	}
	DWORD& cbBmiSrc() {
		assert_cond(cbBmiSrc_exists, "struct field cbBmiSrc does not exist");
		return cbBmiSrc_var;
	}
	DWORD& offBitsSrc() {
		assert_cond(offBitsSrc_exists, "struct field offBitsSrc does not exist");
		return offBitsSrc_var;
	}
	DWORD& cbBitsSrc() {
		assert_cond(cbBitsSrc_exists, "struct field cbBitsSrc does not exist");
		return cbBitsSrc_var;
	}
	DWORD& iUsageSrc() {
		assert_cond(iUsageSrc_exists, "struct field iUsageSrc does not exist");
		return iUsageSrc_var;
	}
	DWORD& dwRop() {
		assert_cond(dwRop_exists, "struct field dwRop does not exist");
		return dwRop_var;
	}
	DWORD& cxDest() {
		assert_cond(cxDest_exists, "struct field cxDest does not exist");
		return cxDest_var;
	}
	DWORD& cyDest() {
		assert_cond(cyDest_exists, "struct field cyDest does not exist");
		return cyDest_var;
	}
	BITMAPINFO& BmiSrc() {
		assert_cond(BmiSrc_exists, "struct field BmiSrc does not exist");
		return *BmiSrc_var;
	}
	std::vector<BYTE>& BitsSrc() {
		assert_cond(BitsSrc_exists, "struct field BitsSrc does not exist");
		return BitsSrc_var;
	}

	/* locals */
	uint emrSize;
	uint bmiSize;
	uint emrOffset;
	uint end;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRSTRETCHDIBITS& operator () () { return *instances.back(); }
	EMRSTRETCHDIBITS& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRSTRETCHDIBITS(std::vector<EMRSTRETCHDIBITS*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRSTRETCHDIBITS() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRSTRETCHDIBITS* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRSTRETCHDIBITS* generate();
};

int EMRSTRETCHDIBITS::_parent_id = 0;
int EMRSTRETCHDIBITS::_index_start = 0;



class EMRTEXT {
	std::vector<EMRTEXT*>& instances;

	POINT* ptlReference_var;
	DWORD nChars_var;
	DWORD offString_var;
	DWORD fOptions_var;
	RECTL* rcl_var;
	DWORD offDx_var;
	std::vector<BYTE> bStringBuffer_var;

public:
	bool ptlReference_exists = false;
	bool nChars_exists = false;
	bool offString_exists = false;
	bool fOptions_exists = false;
	bool rcl_exists = false;
	bool offDx_exists = false;
	bool bStringBuffer_exists = false;

	POINT& ptlReference() {
		assert_cond(ptlReference_exists, "struct field ptlReference does not exist");
		return *ptlReference_var;
	}
	DWORD& nChars() {
		assert_cond(nChars_exists, "struct field nChars does not exist");
		return nChars_var;
	}
	DWORD& offString() {
		assert_cond(offString_exists, "struct field offString does not exist");
		return offString_var;
	}
	DWORD& fOptions() {
		assert_cond(fOptions_exists, "struct field fOptions does not exist");
		return fOptions_var;
	}
	RECTL& rcl() {
		assert_cond(rcl_exists, "struct field rcl does not exist");
		return *rcl_var;
	}
	DWORD& offDx() {
		assert_cond(offDx_exists, "struct field offDx does not exist");
		return offDx_var;
	}
	std::vector<BYTE>& bStringBuffer() {
		assert_cond(bStringBuffer_exists, "struct field bStringBuffer does not exist");
		return bStringBuffer_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRTEXT& operator () () { return *instances.back(); }
	EMRTEXT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRTEXT(std::vector<EMRTEXT*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRTEXT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRTEXT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRTEXT* generate();
};

int EMRTEXT::_parent_id = 0;
int EMRTEXT::_index_start = 0;



class EMREXTTEXTOUTA {
	std::vector<EMREXTTEXTOUTA*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	DWORD iGraphicsMode_var;
	FLOAT exScale_var;
	FLOAT eyScale_var;
	EMRTEXT* emrtext_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool iGraphicsMode_exists = false;
	bool exScale_exists = false;
	bool eyScale_exists = false;
	bool emrtext_exists = false;

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
	DWORD& iGraphicsMode() {
		assert_cond(iGraphicsMode_exists, "struct field iGraphicsMode does not exist");
		return iGraphicsMode_var;
	}
	FLOAT& exScale() {
		assert_cond(exScale_exists, "struct field exScale does not exist");
		return exScale_var;
	}
	FLOAT& eyScale() {
		assert_cond(eyScale_exists, "struct field eyScale does not exist");
		return eyScale_var;
	}
	EMRTEXT& emrtext() {
		assert_cond(emrtext_exists, "struct field emrtext does not exist");
		return *emrtext_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMREXTTEXTOUTA& operator () () { return *instances.back(); }
	EMREXTTEXTOUTA& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMREXTTEXTOUTA(std::vector<EMREXTTEXTOUTA*>& instances) : instances(instances) { instances.push_back(this); }
	~EMREXTTEXTOUTA() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMREXTTEXTOUTA* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMREXTTEXTOUTA* generate();
};

int EMREXTTEXTOUTA::_parent_id = 0;
int EMREXTTEXTOUTA::_index_start = 0;



class EMRCREATEMONOBRUSH {
	std::vector<EMRCREATEMONOBRUSH*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD ihBrush_var;
	DWORD iUsage_var;
	DWORD offBmi_var;
	DWORD cbBmi_var;
	DWORD offBits_var;
	DWORD cbBits_var;
	BITMAPINFO* BmiSrc_var;
	std::vector<BYTE> BitsSrc_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ihBrush_exists = false;
	bool iUsage_exists = false;
	bool offBmi_exists = false;
	bool cbBmi_exists = false;
	bool offBits_exists = false;
	bool cbBits_exists = false;
	bool BmiSrc_exists = false;
	bool BitsSrc_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& ihBrush() {
		assert_cond(ihBrush_exists, "struct field ihBrush does not exist");
		return ihBrush_var;
	}
	DWORD& iUsage() {
		assert_cond(iUsage_exists, "struct field iUsage does not exist");
		return iUsage_var;
	}
	DWORD& offBmi() {
		assert_cond(offBmi_exists, "struct field offBmi does not exist");
		return offBmi_var;
	}
	DWORD& cbBmi() {
		assert_cond(cbBmi_exists, "struct field cbBmi does not exist");
		return cbBmi_var;
	}
	DWORD& offBits() {
		assert_cond(offBits_exists, "struct field offBits does not exist");
		return offBits_var;
	}
	DWORD& cbBits() {
		assert_cond(cbBits_exists, "struct field cbBits does not exist");
		return cbBits_var;
	}
	BITMAPINFO& BmiSrc() {
		assert_cond(BmiSrc_exists, "struct field BmiSrc does not exist");
		return *BmiSrc_var;
	}
	std::vector<BYTE>& BitsSrc() {
		assert_cond(BitsSrc_exists, "struct field BitsSrc does not exist");
		return BitsSrc_var;
	}

	/* locals */
	uint emrSize;
	uint bmiSize;
	uint emrOffset;
	uint end;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRCREATEMONOBRUSH& operator () () { return *instances.back(); }
	EMRCREATEMONOBRUSH& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRCREATEMONOBRUSH(std::vector<EMRCREATEMONOBRUSH*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRCREATEMONOBRUSH() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRCREATEMONOBRUSH* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRCREATEMONOBRUSH* generate();
};

int EMRCREATEMONOBRUSH::_parent_id = 0;
int EMRCREATEMONOBRUSH::_index_start = 0;



class EMRCREATEDIBPATTERNBRUSHPT {
	std::vector<EMRCREATEDIBPATTERNBRUSHPT*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD ihBrush_var;
	DWORD iUsage_var;
	DWORD offBmi_var;
	DWORD cbBmi_var;
	DWORD offBits_var;
	DWORD cbBits_var;
	BITMAPINFO* BmiSrc_var;
	std::vector<BYTE> BitsSrc_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ihBrush_exists = false;
	bool iUsage_exists = false;
	bool offBmi_exists = false;
	bool cbBmi_exists = false;
	bool offBits_exists = false;
	bool cbBits_exists = false;
	bool BmiSrc_exists = false;
	bool BitsSrc_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& ihBrush() {
		assert_cond(ihBrush_exists, "struct field ihBrush does not exist");
		return ihBrush_var;
	}
	DWORD& iUsage() {
		assert_cond(iUsage_exists, "struct field iUsage does not exist");
		return iUsage_var;
	}
	DWORD& offBmi() {
		assert_cond(offBmi_exists, "struct field offBmi does not exist");
		return offBmi_var;
	}
	DWORD& cbBmi() {
		assert_cond(cbBmi_exists, "struct field cbBmi does not exist");
		return cbBmi_var;
	}
	DWORD& offBits() {
		assert_cond(offBits_exists, "struct field offBits does not exist");
		return offBits_var;
	}
	DWORD& cbBits() {
		assert_cond(cbBits_exists, "struct field cbBits does not exist");
		return cbBits_var;
	}
	BITMAPINFO& BmiSrc() {
		assert_cond(BmiSrc_exists, "struct field BmiSrc does not exist");
		return *BmiSrc_var;
	}
	std::vector<BYTE>& BitsSrc() {
		assert_cond(BitsSrc_exists, "struct field BitsSrc does not exist");
		return BitsSrc_var;
	}

	/* locals */
	uint emrSize;
	uint bmiSize;
	uint emrOffset;
	uint end;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRCREATEDIBPATTERNBRUSHPT& operator () () { return *instances.back(); }
	EMRCREATEDIBPATTERNBRUSHPT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRCREATEDIBPATTERNBRUSHPT(std::vector<EMRCREATEDIBPATTERNBRUSHPT*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRCREATEDIBPATTERNBRUSHPT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRCREATEDIBPATTERNBRUSHPT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRCREATEDIBPATTERNBRUSHPT* generate();
};

int EMRCREATEDIBPATTERNBRUSHPT::_parent_id = 0;
int EMRCREATEDIBPATTERNBRUSHPT::_index_start = 0;



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



class LOGPENEX {
	std::vector<LOGPENEX*>& instances;

	DWORD PenStyle_var;
	DWORD Width_var;
	DWORD lbStyle_var;
	COLORREF* lbColor_var;
	DWORD lbHatch_var;
	DWORD NumStyleEntries_var;
	std::vector<DWORD> StyleEntry_var;

public:
	bool PenStyle_exists = false;
	bool Width_exists = false;
	bool lbStyle_exists = false;
	bool lbColor_exists = false;
	bool lbHatch_exists = false;
	bool NumStyleEntries_exists = false;
	bool StyleEntry_exists = false;

	DWORD& PenStyle() {
		assert_cond(PenStyle_exists, "struct field PenStyle does not exist");
		return PenStyle_var;
	}
	DWORD& Width() {
		assert_cond(Width_exists, "struct field Width does not exist");
		return Width_var;
	}
	DWORD& lbStyle() {
		assert_cond(lbStyle_exists, "struct field lbStyle does not exist");
		return lbStyle_var;
	}
	COLORREF& lbColor() {
		assert_cond(lbColor_exists, "struct field lbColor does not exist");
		return *lbColor_var;
	}
	DWORD& lbHatch() {
		assert_cond(lbHatch_exists, "struct field lbHatch does not exist");
		return lbHatch_var;
	}
	DWORD& NumStyleEntries() {
		assert_cond(NumStyleEntries_exists, "struct field NumStyleEntries does not exist");
		return NumStyleEntries_var;
	}
	std::vector<DWORD>& StyleEntry() {
		assert_cond(StyleEntry_exists, "struct field StyleEntry does not exist");
		return StyleEntry_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	LOGPENEX& operator () () { return *instances.back(); }
	LOGPENEX& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	LOGPENEX(std::vector<LOGPENEX*>& instances) : instances(instances) { instances.push_back(this); }
	~LOGPENEX() {
		if (generated == 2)
			return;
		while (instances.size()) {
			LOGPENEX* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	LOGPENEX* generate();
};

int LOGPENEX::_parent_id = 0;
int LOGPENEX::_index_start = 0;



class EMREXTCREATEPEN {
	std::vector<EMREXTCREATEPEN*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD ihPen_var;
	DWORD offBmi_var;
	DWORD cbBmi_var;
	DWORD offBits_var;
	DWORD cbBits_var;
	LOGPENEX* elp_var;
	BITMAPINFO* BmiSrc_var;
	std::vector<BYTE> BitsSrc_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ihPen_exists = false;
	bool offBmi_exists = false;
	bool cbBmi_exists = false;
	bool offBits_exists = false;
	bool cbBits_exists = false;
	bool elp_exists = false;
	bool BmiSrc_exists = false;
	bool BitsSrc_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& ihPen() {
		assert_cond(ihPen_exists, "struct field ihPen does not exist");
		return ihPen_var;
	}
	DWORD& offBmi() {
		assert_cond(offBmi_exists, "struct field offBmi does not exist");
		return offBmi_var;
	}
	DWORD& cbBmi() {
		assert_cond(cbBmi_exists, "struct field cbBmi does not exist");
		return cbBmi_var;
	}
	DWORD& offBits() {
		assert_cond(offBits_exists, "struct field offBits does not exist");
		return offBits_var;
	}
	DWORD& cbBits() {
		assert_cond(cbBits_exists, "struct field cbBits does not exist");
		return cbBits_var;
	}
	LOGPENEX& elp() {
		assert_cond(elp_exists, "struct field elp does not exist");
		return *elp_var;
	}
	BITMAPINFO& BmiSrc() {
		assert_cond(BmiSrc_exists, "struct field BmiSrc does not exist");
		return *BmiSrc_var;
	}
	std::vector<BYTE>& BitsSrc() {
		assert_cond(BitsSrc_exists, "struct field BitsSrc does not exist");
		return BitsSrc_var;
	}

	/* locals */
	uint emrSize;
	uint bmiSize;
	uint emrOffset;
	uint end;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMREXTCREATEPEN& operator () () { return *instances.back(); }
	EMREXTCREATEPEN& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMREXTCREATEPEN(std::vector<EMREXTCREATEPEN*>& instances) : instances(instances) { instances.push_back(this); }
	~EMREXTCREATEPEN() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMREXTCREATEPEN* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMREXTCREATEPEN* generate();
};

int EMREXTCREATEPEN::_parent_id = 0;
int EMREXTCREATEPEN::_index_start = 0;



class EMRTEXT_array_class {
	EMRTEXT& element;
	std::vector<EMRTEXT*> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<EMRTEXT*>& operator () () { return value; }
	EMRTEXT operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return *value[index];
	}
	EMRTEXT_array_class(EMRTEXT& element) : element(element) {}

	std::vector<EMRTEXT*> generate(unsigned size) {
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



class EMRPOLYTEXTOUTA {
	std::vector<EMRPOLYTEXTOUTA*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	DWORD iGraphicsMode_var;
	FLOAT exScale_var;
	FLOAT eyScale_var;
	LONG cStrings_var;
	std::vector<EMRTEXT*> aemrtext_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool iGraphicsMode_exists = false;
	bool exScale_exists = false;
	bool eyScale_exists = false;
	bool cStrings_exists = false;
	bool aemrtext_exists = false;

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
	DWORD& iGraphicsMode() {
		assert_cond(iGraphicsMode_exists, "struct field iGraphicsMode does not exist");
		return iGraphicsMode_var;
	}
	FLOAT& exScale() {
		assert_cond(exScale_exists, "struct field exScale does not exist");
		return exScale_var;
	}
	FLOAT& eyScale() {
		assert_cond(eyScale_exists, "struct field eyScale does not exist");
		return eyScale_var;
	}
	LONG& cStrings() {
		assert_cond(cStrings_exists, "struct field cStrings does not exist");
		return cStrings_var;
	}
	std::vector<EMRTEXT*>& aemrtext() {
		assert_cond(aemrtext_exists, "struct field aemrtext does not exist");
		return aemrtext_var;
	}

	/* locals */
	uint emrOffset;
	uint end;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRPOLYTEXTOUTA& operator () () { return *instances.back(); }
	EMRPOLYTEXTOUTA& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRPOLYTEXTOUTA(std::vector<EMRPOLYTEXTOUTA*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRPOLYTEXTOUTA() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRPOLYTEXTOUTA* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRPOLYTEXTOUTA* generate();
};

int EMRPOLYTEXTOUTA::_parent_id = 0;
int EMRPOLYTEXTOUTA::_index_start = 0;


LogicalColorSpace LogicalColorSpace_generate() {
	return (LogicalColorSpace) file_acc.file_integer(sizeof(DWORD), 0, LogicalColorSpace_values);
}

LogicalColorSpace LogicalColorSpace_generate(std::vector<DWORD> known_values) {
	return (LogicalColorSpace) file_acc.file_integer(sizeof(DWORD), 0, known_values);
}

GamutMappingIntent GamutMappingIntent_generate() {
	return (GamutMappingIntent) file_acc.file_integer(sizeof(DWORD), 0, GamutMappingIntent_values);
}

GamutMappingIntent GamutMappingIntent_generate(std::vector<DWORD> known_values) {
	return (GamutMappingIntent) file_acc.file_integer(sizeof(DWORD), 0, known_values);
}


class CIEXYZ {
	std::vector<CIEXYZ*>& instances;

	LONG ciexyzX_var;
	LONG ciexyzY_var;
	LONG ciexyzZ_var;

public:
	bool ciexyzX_exists = false;
	bool ciexyzY_exists = false;
	bool ciexyzZ_exists = false;

	LONG& ciexyzX() {
		assert_cond(ciexyzX_exists, "struct field ciexyzX does not exist");
		return ciexyzX_var;
	}
	LONG& ciexyzY() {
		assert_cond(ciexyzY_exists, "struct field ciexyzY does not exist");
		return ciexyzY_var;
	}
	LONG& ciexyzZ() {
		assert_cond(ciexyzZ_exists, "struct field ciexyzZ does not exist");
		return ciexyzZ_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CIEXYZ& operator () () { return *instances.back(); }
	CIEXYZ& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CIEXYZ(std::vector<CIEXYZ*>& instances) : instances(instances) { instances.push_back(this); }
	~CIEXYZ() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CIEXYZ* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CIEXYZ* generate();
};

int CIEXYZ::_parent_id = 0;
int CIEXYZ::_index_start = 0;



class CIEXYZTRIPLE {
	std::vector<CIEXYZTRIPLE*>& instances;

	CIEXYZ* ciexyzRed_var;
	CIEXYZ* ciexyzGreen_var;
	CIEXYZ* ciexyzBlue_var;

public:
	bool ciexyzRed_exists = false;
	bool ciexyzGreen_exists = false;
	bool ciexyzBlue_exists = false;

	CIEXYZ& ciexyzRed() {
		assert_cond(ciexyzRed_exists, "struct field ciexyzRed does not exist");
		return *ciexyzRed_var;
	}
	CIEXYZ& ciexyzGreen() {
		assert_cond(ciexyzGreen_exists, "struct field ciexyzGreen does not exist");
		return *ciexyzGreen_var;
	}
	CIEXYZ& ciexyzBlue() {
		assert_cond(ciexyzBlue_exists, "struct field ciexyzBlue does not exist");
		return *ciexyzBlue_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	CIEXYZTRIPLE& operator () () { return *instances.back(); }
	CIEXYZTRIPLE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	CIEXYZTRIPLE(std::vector<CIEXYZTRIPLE*>& instances) : instances(instances) { instances.push_back(this); }
	~CIEXYZTRIPLE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			CIEXYZTRIPLE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	CIEXYZTRIPLE* generate();
};

int CIEXYZTRIPLE::_parent_id = 0;
int CIEXYZTRIPLE::_index_start = 0;



class CHAR_class {
	int small;
	std::vector<CHAR> known_values;
	CHAR value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = sizeof(CHAR);
	CHAR operator () () { return value; }
	CHAR_class(int small, std::vector<CHAR> known_values = {}) : small(small), known_values(known_values) {}

	CHAR generate() {
		_startof = FTell();
		if (known_values.empty()) {
			value = file_acc.file_integer(sizeof(CHAR), 0, small);
		} else {
			value = file_acc.file_integer(sizeof(CHAR), 0, known_values);
		}
		return value;
	}

	CHAR generate(std::vector<CHAR> possible_values) {
		_startof = FTell();
		value = file_acc.file_integer(sizeof(CHAR), 0, possible_values);
		return value;
	}
};



class CHAR_array_class {
	CHAR_class& element;
	std::vector<std::string> known_values;
	std::unordered_map<int, std::vector<CHAR>> element_known_values;
	std::string value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::string& operator () () { return value; }
	CHAR operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return value[index];
	}
	CHAR_array_class(CHAR_class& element, std::unordered_map<int, std::vector<CHAR>> element_known_values = {})
		: element(element), element_known_values(element_known_values) {}
	CHAR_array_class(CHAR_class& element, std::vector<std::string> known_values)
		: element(element), known_values(known_values) {}

	std::string generate(unsigned size, std::vector<std::string> possible_values = {}) {
		check_array_length(size);
		_startof = FTell();
		value = "";
		if (possible_values.size()) {
			value = file_acc.file_string(possible_values);
			assert(value.length() == size);
			_sizeof = size;
			return value;
		}
		if (known_values.size()) {
			value = file_acc.file_string(known_values);
			assert(value.length() == size);
			_sizeof = size;
			return value;
		}
		if (!element_known_values.size()) {
			if (size == 0)
				 return "";
			value = file_acc.file_string(size);
			_sizeof = size;
			return value;
		}
		for (unsigned i = 0; i < size; ++i) {
			auto known = element_known_values.find(i);
			if (known == element_known_values.end()) {
				value.push_back(element.generate());
				_sizeof += element._sizeof;
			} else {
				value.push_back(file_acc.file_integer(sizeof(CHAR), 0, known->second));
				_sizeof += sizeof(CHAR);
			}
		}
		return value;
	}
};



class LOGCOLORSPACEA {
	std::vector<LOGCOLORSPACEA*>& instances;

	DWORD lcsSignature_var;
	DWORD lcsVersion_var;
	DWORD lcsSize_var;
	DWORD lcsCSType_var;
	DWORD lcsIntent_var;
	CIEXYZTRIPLE* lcsEndpoints_var;
	DWORD lcsGammaRed_var;
	DWORD lcsGammaGreen_var;
	DWORD lcsGammaBlue_var;
	std::string lcsFilename_var;

public:
	bool lcsSignature_exists = false;
	bool lcsVersion_exists = false;
	bool lcsSize_exists = false;
	bool lcsCSType_exists = false;
	bool lcsIntent_exists = false;
	bool lcsEndpoints_exists = false;
	bool lcsGammaRed_exists = false;
	bool lcsGammaGreen_exists = false;
	bool lcsGammaBlue_exists = false;
	bool lcsFilename_exists = false;

	DWORD& lcsSignature() {
		assert_cond(lcsSignature_exists, "struct field lcsSignature does not exist");
		return lcsSignature_var;
	}
	DWORD& lcsVersion() {
		assert_cond(lcsVersion_exists, "struct field lcsVersion does not exist");
		return lcsVersion_var;
	}
	DWORD& lcsSize() {
		assert_cond(lcsSize_exists, "struct field lcsSize does not exist");
		return lcsSize_var;
	}
	DWORD& lcsCSType() {
		assert_cond(lcsCSType_exists, "struct field lcsCSType does not exist");
		return lcsCSType_var;
	}
	DWORD& lcsIntent() {
		assert_cond(lcsIntent_exists, "struct field lcsIntent does not exist");
		return lcsIntent_var;
	}
	CIEXYZTRIPLE& lcsEndpoints() {
		assert_cond(lcsEndpoints_exists, "struct field lcsEndpoints does not exist");
		return *lcsEndpoints_var;
	}
	DWORD& lcsGammaRed() {
		assert_cond(lcsGammaRed_exists, "struct field lcsGammaRed does not exist");
		return lcsGammaRed_var;
	}
	DWORD& lcsGammaGreen() {
		assert_cond(lcsGammaGreen_exists, "struct field lcsGammaGreen does not exist");
		return lcsGammaGreen_var;
	}
	DWORD& lcsGammaBlue() {
		assert_cond(lcsGammaBlue_exists, "struct field lcsGammaBlue does not exist");
		return lcsGammaBlue_var;
	}
	std::string& lcsFilename() {
		assert_cond(lcsFilename_exists, "struct field lcsFilename does not exist");
		return lcsFilename_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	LOGCOLORSPACEA& operator () () { return *instances.back(); }
	LOGCOLORSPACEA& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	LOGCOLORSPACEA(std::vector<LOGCOLORSPACEA*>& instances) : instances(instances) { instances.push_back(this); }
	~LOGCOLORSPACEA() {
		if (generated == 2)
			return;
		while (instances.size()) {
			LOGCOLORSPACEA* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	LOGCOLORSPACEA* generate();
};

int LOGCOLORSPACEA::_parent_id = 0;
int LOGCOLORSPACEA::_index_start = 0;



class EMRCREATECOLORSPACE {
	std::vector<EMRCREATECOLORSPACE*>& instances;

	DWORD iType_var;
	DWORD ihCS_var;
	DWORD ics_var;
	LOGCOLORSPACEA* lcs_var;

public:
	bool iType_exists = false;
	bool ihCS_exists = false;
	bool ics_exists = false;
	bool lcs_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& ihCS() {
		assert_cond(ihCS_exists, "struct field ihCS does not exist");
		return ihCS_var;
	}
	DWORD& ics() {
		assert_cond(ics_exists, "struct field ics does not exist");
		return ics_var;
	}
	LOGCOLORSPACEA& lcs() {
		assert_cond(lcs_exists, "struct field lcs does not exist");
		return *lcs_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRCREATECOLORSPACE& operator () () { return *instances.back(); }
	EMRCREATECOLORSPACE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRCREATECOLORSPACE(std::vector<EMRCREATECOLORSPACE*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRCREATECOLORSPACE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRCREATECOLORSPACE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRCREATECOLORSPACE* generate();
};

int EMRCREATECOLORSPACE::_parent_id = 0;
int EMRCREATECOLORSPACE::_index_start = 0;



class EMRSETCOLORSPACE {
	std::vector<EMRSETCOLORSPACE*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD ihCS_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ihCS_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& ihCS() {
		assert_cond(ihCS_exists, "struct field ihCS does not exist");
		return ihCS_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRSETCOLORSPACE& operator () () { return *instances.back(); }
	EMRSETCOLORSPACE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRSETCOLORSPACE(std::vector<EMRSETCOLORSPACE*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRSETCOLORSPACE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRSETCOLORSPACE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRSETCOLORSPACE* generate();
};

int EMRSETCOLORSPACE::_parent_id = 0;
int EMRSETCOLORSPACE::_index_start = 0;



class EMRDELETECOLORSPACE {
	std::vector<EMRDELETECOLORSPACE*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD ihCS_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ihCS_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& ihCS() {
		assert_cond(ihCS_exists, "struct field ihCS does not exist");
		return ihCS_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRDELETECOLORSPACE& operator () () { return *instances.back(); }
	EMRDELETECOLORSPACE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRDELETECOLORSPACE(std::vector<EMRDELETECOLORSPACE*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRDELETECOLORSPACE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRDELETECOLORSPACE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRDELETECOLORSPACE* generate();
};

int EMRDELETECOLORSPACE::_parent_id = 0;
int EMRDELETECOLORSPACE::_index_start = 0;



class EMRGLSRECORD {
	std::vector<EMRGLSRECORD*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD cbData_var;
	std::vector<BYTE> Data_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool cbData_exists = false;
	bool Data_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& cbData() {
		assert_cond(cbData_exists, "struct field cbData does not exist");
		return cbData_var;
	}
	std::vector<BYTE>& Data() {
		assert_cond(Data_exists, "struct field Data does not exist");
		return Data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRGLSRECORD& operator () () { return *instances.back(); }
	EMRGLSRECORD& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRGLSRECORD(std::vector<EMRGLSRECORD*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRGLSRECORD() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRGLSRECORD* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRGLSRECORD* generate();
};

int EMRGLSRECORD::_parent_id = 0;
int EMRGLSRECORD::_index_start = 0;



class EMRGLSBOUNDEDRECORD {
	std::vector<EMRGLSBOUNDEDRECORD*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	DWORD cbData_var;
	std::vector<BYTE> Data_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool cbData_exists = false;
	bool Data_exists = false;

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
	DWORD& cbData() {
		assert_cond(cbData_exists, "struct field cbData does not exist");
		return cbData_var;
	}
	std::vector<BYTE>& Data() {
		assert_cond(Data_exists, "struct field Data does not exist");
		return Data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRGLSBOUNDEDRECORD& operator () () { return *instances.back(); }
	EMRGLSBOUNDEDRECORD& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRGLSBOUNDEDRECORD(std::vector<EMRGLSBOUNDEDRECORD*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRGLSBOUNDEDRECORD() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRGLSBOUNDEDRECORD* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRGLSBOUNDEDRECORD* generate();
};

int EMRGLSBOUNDEDRECORD::_parent_id = 0;
int EMRGLSBOUNDEDRECORD::_index_start = 0;


MetafileEscapes MetafileEscapes_generate() {
	return (MetafileEscapes) file_acc.file_integer(sizeof(DWORD), 0, MetafileEscapes_values);
}

MetafileEscapes MetafileEscapes_generate(std::vector<DWORD> known_values) {
	return (MetafileEscapes) file_acc.file_integer(sizeof(DWORD), 0, known_values);
}


class EMRDRAWESCAPE {
	std::vector<EMRDRAWESCAPE*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD iEscape_var;
	DWORD cjln_var;
	std::vector<BYTE> data_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool iEscape_exists = false;
	bool cjln_exists = false;
	bool data_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& iEscape() {
		assert_cond(iEscape_exists, "struct field iEscape does not exist");
		return iEscape_var;
	}
	DWORD& cjln() {
		assert_cond(cjln_exists, "struct field cjln does not exist");
		return cjln_var;
	}
	std::vector<BYTE>& data() {
		assert_cond(data_exists, "struct field data does not exist");
		return data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRDRAWESCAPE& operator () () { return *instances.back(); }
	EMRDRAWESCAPE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRDRAWESCAPE(std::vector<EMRDRAWESCAPE*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRDRAWESCAPE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRDRAWESCAPE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRDRAWESCAPE* generate();
};

int EMRDRAWESCAPE::_parent_id = 0;
int EMRDRAWESCAPE::_index_start = 0;



class EMREXTESCAPE {
	std::vector<EMREXTESCAPE*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD iEscape_var;
	DWORD cjln_var;
	std::vector<BYTE> data_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool iEscape_exists = false;
	bool cjln_exists = false;
	bool data_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& iEscape() {
		assert_cond(iEscape_exists, "struct field iEscape does not exist");
		return iEscape_var;
	}
	DWORD& cjln() {
		assert_cond(cjln_exists, "struct field cjln does not exist");
		return cjln_var;
	}
	std::vector<BYTE>& data() {
		assert_cond(data_exists, "struct field data does not exist");
		return data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMREXTESCAPE& operator () () { return *instances.back(); }
	EMREXTESCAPE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMREXTESCAPE(std::vector<EMREXTESCAPE*>& instances) : instances(instances) { instances.push_back(this); }
	~EMREXTESCAPE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMREXTESCAPE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMREXTESCAPE* generate();
};

int EMREXTESCAPE::_parent_id = 0;
int EMREXTESCAPE::_index_start = 0;



class EMRRESERVED107 {
	std::vector<EMRRESERVED107*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	std::vector<DWORD> ReservedData_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ReservedData_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	std::vector<DWORD>& ReservedData() {
		assert_cond(ReservedData_exists, "struct field ReservedData does not exist");
		return ReservedData_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRRESERVED107& operator () () { return *instances.back(); }
	EMRRESERVED107& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRRESERVED107(std::vector<EMRRESERVED107*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRRESERVED107() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRRESERVED107* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRRESERVED107* generate();
};

int EMRRESERVED107::_parent_id = 0;
int EMRRESERVED107::_index_start = 0;



class UniversalFontId {
	std::vector<UniversalFontId*>& instances;

	DWORD checksum_var;
	DWORD index_var;

public:
	bool checksum_exists = false;
	bool index_exists = false;

	DWORD& checksum() {
		assert_cond(checksum_exists, "struct field checksum does not exist");
		return checksum_var;
	}
	DWORD& index() {
		assert_cond(index_exists, "struct field index does not exist");
		return index_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	UniversalFontId& operator () () { return *instances.back(); }
	UniversalFontId& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	UniversalFontId(std::vector<UniversalFontId*>& instances) : instances(instances) { instances.push_back(this); }
	~UniversalFontId() {
		if (generated == 2)
			return;
		while (instances.size()) {
			UniversalFontId* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	UniversalFontId* generate();
};

int UniversalFontId::_parent_id = 0;
int UniversalFontId::_index_start = 0;



class EMRFORCEUFIMAPPING {
	std::vector<EMRFORCEUFIMAPPING*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	UniversalFontId* ufi_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ufi_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	UniversalFontId& ufi() {
		assert_cond(ufi_exists, "struct field ufi does not exist");
		return *ufi_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRFORCEUFIMAPPING& operator () () { return *instances.back(); }
	EMRFORCEUFIMAPPING& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRFORCEUFIMAPPING(std::vector<EMRFORCEUFIMAPPING*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRFORCEUFIMAPPING() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRFORCEUFIMAPPING* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRFORCEUFIMAPPING* generate();
};

int EMRFORCEUFIMAPPING::_parent_id = 0;
int EMRFORCEUFIMAPPING::_index_start = 0;



class EMRNAMEDESCAPE {
	std::vector<EMRNAMEDESCAPE*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD iEscape_var;
	DWORD cjDriver_var;
	DWORD cjln_var;
	WORD driverName_var;
	std::vector<BYTE> data_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool iEscape_exists = false;
	bool cjDriver_exists = false;
	bool cjln_exists = false;
	bool driverName_exists = false;
	bool data_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& iEscape() {
		assert_cond(iEscape_exists, "struct field iEscape does not exist");
		return iEscape_var;
	}
	DWORD& cjDriver() {
		assert_cond(cjDriver_exists, "struct field cjDriver does not exist");
		return cjDriver_var;
	}
	DWORD& cjln() {
		assert_cond(cjln_exists, "struct field cjln does not exist");
		return cjln_var;
	}
	WORD& driverName() {
		assert_cond(driverName_exists, "struct field driverName does not exist");
		return driverName_var;
	}
	std::vector<BYTE>& data() {
		assert_cond(data_exists, "struct field data does not exist");
		return data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRNAMEDESCAPE& operator () () { return *instances.back(); }
	EMRNAMEDESCAPE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRNAMEDESCAPE(std::vector<EMRNAMEDESCAPE*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRNAMEDESCAPE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRNAMEDESCAPE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRNAMEDESCAPE* generate();
};

int EMRNAMEDESCAPE::_parent_id = 0;
int EMRNAMEDESCAPE::_index_start = 0;



class EMRCOLORCORRECTPALETTE {
	std::vector<EMRCOLORCORRECTPALETTE*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD ihPalette_var;
	DWORD nFirstEntry_var;
	DWORD nPalEntries_var;
	DWORD nReserved_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ihPalette_exists = false;
	bool nFirstEntry_exists = false;
	bool nPalEntries_exists = false;
	bool nReserved_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& ihPalette() {
		assert_cond(ihPalette_exists, "struct field ihPalette does not exist");
		return ihPalette_var;
	}
	DWORD& nFirstEntry() {
		assert_cond(nFirstEntry_exists, "struct field nFirstEntry does not exist");
		return nFirstEntry_var;
	}
	DWORD& nPalEntries() {
		assert_cond(nPalEntries_exists, "struct field nPalEntries does not exist");
		return nPalEntries_var;
	}
	DWORD& nReserved() {
		assert_cond(nReserved_exists, "struct field nReserved does not exist");
		return nReserved_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRCOLORCORRECTPALETTE& operator () () { return *instances.back(); }
	EMRCOLORCORRECTPALETTE& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRCOLORCORRECTPALETTE(std::vector<EMRCOLORCORRECTPALETTE*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRCOLORCORRECTPALETTE() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRCOLORCORRECTPALETTE* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRCOLORCORRECTPALETTE* generate();
};

int EMRCOLORCORRECTPALETTE::_parent_id = 0;
int EMRCOLORCORRECTPALETTE::_index_start = 0;



class BLENDFUNCTION {
	std::vector<BLENDFUNCTION*>& instances;

	BYTE BlendOp_var;
	BYTE BlendFlags_var;
	BYTE SourceConstantAlpha_var;
	BYTE AlphaFormat_var;

public:
	bool BlendOp_exists = false;
	bool BlendFlags_exists = false;
	bool SourceConstantAlpha_exists = false;
	bool AlphaFormat_exists = false;

	BYTE& BlendOp() {
		assert_cond(BlendOp_exists, "struct field BlendOp does not exist");
		return BlendOp_var;
	}
	BYTE& BlendFlags() {
		assert_cond(BlendFlags_exists, "struct field BlendFlags does not exist");
		return BlendFlags_var;
	}
	BYTE& SourceConstantAlpha() {
		assert_cond(SourceConstantAlpha_exists, "struct field SourceConstantAlpha does not exist");
		return SourceConstantAlpha_var;
	}
	BYTE& AlphaFormat() {
		assert_cond(AlphaFormat_exists, "struct field AlphaFormat does not exist");
		return AlphaFormat_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	BLENDFUNCTION& operator () () { return *instances.back(); }
	BLENDFUNCTION& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	BLENDFUNCTION(std::vector<BLENDFUNCTION*>& instances) : instances(instances) { instances.push_back(this); }
	~BLENDFUNCTION() {
		if (generated == 2)
			return;
		while (instances.size()) {
			BLENDFUNCTION* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	BLENDFUNCTION* generate();
};

int BLENDFUNCTION::_parent_id = 0;
int BLENDFUNCTION::_index_start = 0;



class EMRALPHABLEND {
	std::vector<EMRALPHABLEND*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	LONG xDest_var;
	LONG yDest_var;
	LONG cxDest_var;
	LONG cyDest_var;
	BLENDFUNCTION* dwRop_var;
	LONG xSrc_var;
	LONG ySrc_var;
	XFORM* xformSrc_var;
	COLORREF* crBkColorSrc_var;
	DWORD iUsageSrc_var;
	DWORD offBmiSrc_var;
	DWORD cbBmiSrc_var;
	DWORD offBitsSrc_var;
	DWORD cbBitsSrc_var;
	LONG cxSrc_var;
	LONG cySrc_var;
	BITMAPINFO* BmiSrc_var;
	std::vector<BYTE> BitsSrc_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool xDest_exists = false;
	bool yDest_exists = false;
	bool cxDest_exists = false;
	bool cyDest_exists = false;
	bool dwRop_exists = false;
	bool xSrc_exists = false;
	bool ySrc_exists = false;
	bool xformSrc_exists = false;
	bool crBkColorSrc_exists = false;
	bool iUsageSrc_exists = false;
	bool offBmiSrc_exists = false;
	bool cbBmiSrc_exists = false;
	bool offBitsSrc_exists = false;
	bool cbBitsSrc_exists = false;
	bool cxSrc_exists = false;
	bool cySrc_exists = false;
	bool BmiSrc_exists = false;
	bool BitsSrc_exists = false;

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
	LONG& xDest() {
		assert_cond(xDest_exists, "struct field xDest does not exist");
		return xDest_var;
	}
	LONG& yDest() {
		assert_cond(yDest_exists, "struct field yDest does not exist");
		return yDest_var;
	}
	LONG& cxDest() {
		assert_cond(cxDest_exists, "struct field cxDest does not exist");
		return cxDest_var;
	}
	LONG& cyDest() {
		assert_cond(cyDest_exists, "struct field cyDest does not exist");
		return cyDest_var;
	}
	BLENDFUNCTION& dwRop() {
		assert_cond(dwRop_exists, "struct field dwRop does not exist");
		return *dwRop_var;
	}
	LONG& xSrc() {
		assert_cond(xSrc_exists, "struct field xSrc does not exist");
		return xSrc_var;
	}
	LONG& ySrc() {
		assert_cond(ySrc_exists, "struct field ySrc does not exist");
		return ySrc_var;
	}
	XFORM& xformSrc() {
		assert_cond(xformSrc_exists, "struct field xformSrc does not exist");
		return *xformSrc_var;
	}
	COLORREF& crBkColorSrc() {
		assert_cond(crBkColorSrc_exists, "struct field crBkColorSrc does not exist");
		return *crBkColorSrc_var;
	}
	DWORD& iUsageSrc() {
		assert_cond(iUsageSrc_exists, "struct field iUsageSrc does not exist");
		return iUsageSrc_var;
	}
	DWORD& offBmiSrc() {
		assert_cond(offBmiSrc_exists, "struct field offBmiSrc does not exist");
		return offBmiSrc_var;
	}
	DWORD& cbBmiSrc() {
		assert_cond(cbBmiSrc_exists, "struct field cbBmiSrc does not exist");
		return cbBmiSrc_var;
	}
	DWORD& offBitsSrc() {
		assert_cond(offBitsSrc_exists, "struct field offBitsSrc does not exist");
		return offBitsSrc_var;
	}
	DWORD& cbBitsSrc() {
		assert_cond(cbBitsSrc_exists, "struct field cbBitsSrc does not exist");
		return cbBitsSrc_var;
	}
	LONG& cxSrc() {
		assert_cond(cxSrc_exists, "struct field cxSrc does not exist");
		return cxSrc_var;
	}
	LONG& cySrc() {
		assert_cond(cySrc_exists, "struct field cySrc does not exist");
		return cySrc_var;
	}
	BITMAPINFO& BmiSrc() {
		assert_cond(BmiSrc_exists, "struct field BmiSrc does not exist");
		return *BmiSrc_var;
	}
	std::vector<BYTE>& BitsSrc() {
		assert_cond(BitsSrc_exists, "struct field BitsSrc does not exist");
		return BitsSrc_var;
	}

	/* locals */
	uint emrSize;
	uint bmiSize;
	uint emrOffset;
	uint end;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRALPHABLEND& operator () () { return *instances.back(); }
	EMRALPHABLEND& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRALPHABLEND(std::vector<EMRALPHABLEND*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRALPHABLEND() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRALPHABLEND* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRALPHABLEND* generate();
};

int EMRALPHABLEND::_parent_id = 0;
int EMRALPHABLEND::_index_start = 0;



class EMRTRANSPARENTBLT {
	std::vector<EMRTRANSPARENTBLT*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	LONG xDest_var;
	LONG yDest_var;
	LONG cxDest_var;
	LONG cyDest_var;
	DWORD dwRop_var;
	LONG xSrc_var;
	LONG ySrc_var;
	XFORM* xformSrc_var;
	COLORREF* crBkColorSrc_var;
	DWORD iUsageSrc_var;
	DWORD offBmiSrc_var;
	DWORD cbBmiSrc_var;
	DWORD offBitsSrc_var;
	DWORD cbBitsSrc_var;
	LONG cxSrc_var;
	LONG cySrc_var;
	BITMAPINFO* BmiSrc_var;
	std::vector<BYTE> BitsSrc_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool xDest_exists = false;
	bool yDest_exists = false;
	bool cxDest_exists = false;
	bool cyDest_exists = false;
	bool dwRop_exists = false;
	bool xSrc_exists = false;
	bool ySrc_exists = false;
	bool xformSrc_exists = false;
	bool crBkColorSrc_exists = false;
	bool iUsageSrc_exists = false;
	bool offBmiSrc_exists = false;
	bool cbBmiSrc_exists = false;
	bool offBitsSrc_exists = false;
	bool cbBitsSrc_exists = false;
	bool cxSrc_exists = false;
	bool cySrc_exists = false;
	bool BmiSrc_exists = false;
	bool BitsSrc_exists = false;

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
	LONG& xDest() {
		assert_cond(xDest_exists, "struct field xDest does not exist");
		return xDest_var;
	}
	LONG& yDest() {
		assert_cond(yDest_exists, "struct field yDest does not exist");
		return yDest_var;
	}
	LONG& cxDest() {
		assert_cond(cxDest_exists, "struct field cxDest does not exist");
		return cxDest_var;
	}
	LONG& cyDest() {
		assert_cond(cyDest_exists, "struct field cyDest does not exist");
		return cyDest_var;
	}
	DWORD& dwRop() {
		assert_cond(dwRop_exists, "struct field dwRop does not exist");
		return dwRop_var;
	}
	LONG& xSrc() {
		assert_cond(xSrc_exists, "struct field xSrc does not exist");
		return xSrc_var;
	}
	LONG& ySrc() {
		assert_cond(ySrc_exists, "struct field ySrc does not exist");
		return ySrc_var;
	}
	XFORM& xformSrc() {
		assert_cond(xformSrc_exists, "struct field xformSrc does not exist");
		return *xformSrc_var;
	}
	COLORREF& crBkColorSrc() {
		assert_cond(crBkColorSrc_exists, "struct field crBkColorSrc does not exist");
		return *crBkColorSrc_var;
	}
	DWORD& iUsageSrc() {
		assert_cond(iUsageSrc_exists, "struct field iUsageSrc does not exist");
		return iUsageSrc_var;
	}
	DWORD& offBmiSrc() {
		assert_cond(offBmiSrc_exists, "struct field offBmiSrc does not exist");
		return offBmiSrc_var;
	}
	DWORD& cbBmiSrc() {
		assert_cond(cbBmiSrc_exists, "struct field cbBmiSrc does not exist");
		return cbBmiSrc_var;
	}
	DWORD& offBitsSrc() {
		assert_cond(offBitsSrc_exists, "struct field offBitsSrc does not exist");
		return offBitsSrc_var;
	}
	DWORD& cbBitsSrc() {
		assert_cond(cbBitsSrc_exists, "struct field cbBitsSrc does not exist");
		return cbBitsSrc_var;
	}
	LONG& cxSrc() {
		assert_cond(cxSrc_exists, "struct field cxSrc does not exist");
		return cxSrc_var;
	}
	LONG& cySrc() {
		assert_cond(cySrc_exists, "struct field cySrc does not exist");
		return cySrc_var;
	}
	BITMAPINFO& BmiSrc() {
		assert_cond(BmiSrc_exists, "struct field BmiSrc does not exist");
		return *BmiSrc_var;
	}
	std::vector<BYTE>& BitsSrc() {
		assert_cond(BitsSrc_exists, "struct field BitsSrc does not exist");
		return BitsSrc_var;
	}

	/* locals */
	uint emrSize;
	uint bmiSize;
	uint emrOffset;
	uint end;

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRTRANSPARENTBLT& operator () () { return *instances.back(); }
	EMRTRANSPARENTBLT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRTRANSPARENTBLT(std::vector<EMRTRANSPARENTBLT*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRTRANSPARENTBLT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRTRANSPARENTBLT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRTRANSPARENTBLT* generate();
};

int EMRTRANSPARENTBLT::_parent_id = 0;
int EMRTRANSPARENTBLT::_index_start = 0;



class EMRRESERVED117 {
	std::vector<EMRRESERVED117*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	std::vector<DWORD> ReservedData_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ReservedData_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	std::vector<DWORD>& ReservedData() {
		assert_cond(ReservedData_exists, "struct field ReservedData does not exist");
		return ReservedData_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRRESERVED117& operator () () { return *instances.back(); }
	EMRRESERVED117& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRRESERVED117(std::vector<EMRRESERVED117*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRRESERVED117() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRRESERVED117* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRRESERVED117* generate();
};

int EMRRESERVED117::_parent_id = 0;
int EMRRESERVED117::_index_start = 0;


GradientFill GradientFill_generate() {
	return (GradientFill) file_acc.file_integer(sizeof(DWORD), 0, GradientFill_values);
}

GradientFill GradientFill_generate(std::vector<DWORD> known_values) {
	return (GradientFill) file_acc.file_integer(sizeof(DWORD), 0, known_values);
}


class TRIVERTEX {
	std::vector<TRIVERTEX*>& instances;

	LONG x_var;
	LONG y_var;
	WORD Red_var;
	WORD Green_var;
	WORD Blue_var;
	WORD Alpha_var;

public:
	bool x_exists = false;
	bool y_exists = false;
	bool Red_exists = false;
	bool Green_exists = false;
	bool Blue_exists = false;
	bool Alpha_exists = false;

	LONG& x() {
		assert_cond(x_exists, "struct field x does not exist");
		return x_var;
	}
	LONG& y() {
		assert_cond(y_exists, "struct field y does not exist");
		return y_var;
	}
	WORD& Red() {
		assert_cond(Red_exists, "struct field Red does not exist");
		return Red_var;
	}
	WORD& Green() {
		assert_cond(Green_exists, "struct field Green does not exist");
		return Green_var;
	}
	WORD& Blue() {
		assert_cond(Blue_exists, "struct field Blue does not exist");
		return Blue_var;
	}
	WORD& Alpha() {
		assert_cond(Alpha_exists, "struct field Alpha does not exist");
		return Alpha_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	TRIVERTEX& operator () () { return *instances.back(); }
	TRIVERTEX& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	TRIVERTEX(std::vector<TRIVERTEX*>& instances) : instances(instances) { instances.push_back(this); }
	~TRIVERTEX() {
		if (generated == 2)
			return;
		while (instances.size()) {
			TRIVERTEX* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	TRIVERTEX* generate();
};

int TRIVERTEX::_parent_id = 0;
int TRIVERTEX::_index_start = 0;



class TRIVERTEX_array_class {
	TRIVERTEX& element;
	std::vector<TRIVERTEX*> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<TRIVERTEX*>& operator () () { return value; }
	TRIVERTEX operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return *value[index];
	}
	TRIVERTEX_array_class(TRIVERTEX& element) : element(element) {}

	std::vector<TRIVERTEX*> generate(unsigned size) {
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



class ULONG_class {
	int small;
	std::vector<ULONG> known_values;
	ULONG value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = sizeof(ULONG);
	ULONG operator () () { return value; }
	ULONG_class(int small, std::vector<ULONG> known_values = {}) : small(small), known_values(known_values) {}

	ULONG generate() {
		_startof = FTell();
		if (known_values.empty()) {
			value = file_acc.file_integer(sizeof(ULONG), 0, small);
		} else {
			value = file_acc.file_integer(sizeof(ULONG), 0, known_values);
		}
		return value;
	}

	ULONG generate(std::vector<ULONG> possible_values) {
		_startof = FTell();
		value = file_acc.file_integer(sizeof(ULONG), 0, possible_values);
		return value;
	}
};



class GRADIENT_RECT {
	std::vector<GRADIENT_RECT*>& instances;

	ULONG UpperLeft_var;
	ULONG LowerRight_var;

public:
	bool UpperLeft_exists = false;
	bool LowerRight_exists = false;

	ULONG& UpperLeft() {
		assert_cond(UpperLeft_exists, "struct field UpperLeft does not exist");
		return UpperLeft_var;
	}
	ULONG& LowerRight() {
		assert_cond(LowerRight_exists, "struct field LowerRight does not exist");
		return LowerRight_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	GRADIENT_RECT& operator () () { return *instances.back(); }
	GRADIENT_RECT& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	GRADIENT_RECT(std::vector<GRADIENT_RECT*>& instances) : instances(instances) { instances.push_back(this); }
	~GRADIENT_RECT() {
		if (generated == 2)
			return;
		while (instances.size()) {
			GRADIENT_RECT* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	GRADIENT_RECT* generate();
};

int GRADIENT_RECT::_parent_id = 0;
int GRADIENT_RECT::_index_start = 0;



class GRADIENT_RECT_array_class {
	GRADIENT_RECT& element;
	std::vector<GRADIENT_RECT*> value;
public:
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	std::vector<GRADIENT_RECT*>& operator () () { return value; }
	GRADIENT_RECT operator [] (int index) {
		assert_cond((unsigned)index < value.size(), "array index out of bounds");
		return *value[index];
	}
	GRADIENT_RECT_array_class(GRADIENT_RECT& element) : element(element) {}

	std::vector<GRADIENT_RECT*> generate(unsigned size) {
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



class EMRGRADIENTFILL {
	std::vector<EMRGRADIENTFILL*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	RECTL* rclBounds_var;
	DWORD nVer_var;
	DWORD nTri_var;
	DWORD ulMode_var;
	std::vector<TRIVERTEX*> vObjects_var;
	std::vector<GRADIENT_RECT*> vIndexes_var;
	std::vector<DWORD> vPadding_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool rclBounds_exists = false;
	bool nVer_exists = false;
	bool nTri_exists = false;
	bool ulMode_exists = false;
	bool vObjects_exists = false;
	bool vIndexes_exists = false;
	bool vPadding_exists = false;

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
	DWORD& nVer() {
		assert_cond(nVer_exists, "struct field nVer does not exist");
		return nVer_var;
	}
	DWORD& nTri() {
		assert_cond(nTri_exists, "struct field nTri does not exist");
		return nTri_var;
	}
	DWORD& ulMode() {
		assert_cond(ulMode_exists, "struct field ulMode does not exist");
		return ulMode_var;
	}
	std::vector<TRIVERTEX*>& vObjects() {
		assert_cond(vObjects_exists, "struct field vObjects does not exist");
		return vObjects_var;
	}
	std::vector<GRADIENT_RECT*>& vIndexes() {
		assert_cond(vIndexes_exists, "struct field vIndexes does not exist");
		return vIndexes_var;
	}
	std::vector<DWORD>& vPadding() {
		assert_cond(vPadding_exists, "struct field vPadding does not exist");
		return vPadding_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRGRADIENTFILL& operator () () { return *instances.back(); }
	EMRGRADIENTFILL& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRGRADIENTFILL(std::vector<EMRGRADIENTFILL*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRGRADIENTFILL() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRGRADIENTFILL* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRGRADIENTFILL* generate();
};

int EMRGRADIENTFILL::_parent_id = 0;
int EMRGRADIENTFILL::_index_start = 0;


ColorSpace ColorSpace_generate() {
	return (ColorSpace) file_acc.file_integer(sizeof(DWORD), 0, ColorSpace_values);
}

ColorSpace ColorSpace_generate(std::vector<DWORD> known_values) {
	return (ColorSpace) file_acc.file_integer(sizeof(DWORD), 0, known_values);
}

ColorMatchToTarget ColorMatchToTarget_generate() {
	return (ColorMatchToTarget) file_acc.file_integer(sizeof(DWORD), 0, ColorMatchToTarget_values);
}

ColorMatchToTarget ColorMatchToTarget_generate(std::vector<DWORD> known_values) {
	return (ColorMatchToTarget) file_acc.file_integer(sizeof(DWORD), 0, known_values);
}


class EMRCOLORMATCHTOTARGETW {
	std::vector<EMRCOLORMATCHTOTARGETW*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD dwAction_var;
	DWORD dwFlags_var;
	DWORD cbName_var;
	DWORD cbData_var;
	std::vector<BYTE> data_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool dwAction_exists = false;
	bool dwFlags_exists = false;
	bool cbName_exists = false;
	bool cbData_exists = false;
	bool data_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& dwAction() {
		assert_cond(dwAction_exists, "struct field dwAction does not exist");
		return dwAction_var;
	}
	DWORD& dwFlags() {
		assert_cond(dwFlags_exists, "struct field dwFlags does not exist");
		return dwFlags_var;
	}
	DWORD& cbName() {
		assert_cond(cbName_exists, "struct field cbName does not exist");
		return cbName_var;
	}
	DWORD& cbData() {
		assert_cond(cbData_exists, "struct field cbData does not exist");
		return cbData_var;
	}
	std::vector<BYTE>& data() {
		assert_cond(data_exists, "struct field data does not exist");
		return data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRCOLORMATCHTOTARGETW& operator () () { return *instances.back(); }
	EMRCOLORMATCHTOTARGETW& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRCOLORMATCHTOTARGETW(std::vector<EMRCOLORMATCHTOTARGETW*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRCOLORMATCHTOTARGETW() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRCOLORMATCHTOTARGETW* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRCOLORMATCHTOTARGETW* generate();
};

int EMRCOLORMATCHTOTARGETW::_parent_id = 0;
int EMRCOLORMATCHTOTARGETW::_index_start = 0;



class LOGCOLORSPACEW {
	std::vector<LOGCOLORSPACEW*>& instances;

	DWORD lcsSignature_var;
	DWORD lcsVersion_var;
	DWORD lcsSize_var;
	DWORD lcsCSType_var;
	DWORD lcsIntent_var;
	CIEXYZTRIPLE* lcsEndpoints_var;
	DWORD lcsGammaRed_var;
	DWORD lcsGammaGreen_var;
	DWORD lcsGammaBlue_var;
	std::vector<BYTE> lcsFilename_var;

public:
	bool lcsSignature_exists = false;
	bool lcsVersion_exists = false;
	bool lcsSize_exists = false;
	bool lcsCSType_exists = false;
	bool lcsIntent_exists = false;
	bool lcsEndpoints_exists = false;
	bool lcsGammaRed_exists = false;
	bool lcsGammaGreen_exists = false;
	bool lcsGammaBlue_exists = false;
	bool lcsFilename_exists = false;

	DWORD& lcsSignature() {
		assert_cond(lcsSignature_exists, "struct field lcsSignature does not exist");
		return lcsSignature_var;
	}
	DWORD& lcsVersion() {
		assert_cond(lcsVersion_exists, "struct field lcsVersion does not exist");
		return lcsVersion_var;
	}
	DWORD& lcsSize() {
		assert_cond(lcsSize_exists, "struct field lcsSize does not exist");
		return lcsSize_var;
	}
	DWORD& lcsCSType() {
		assert_cond(lcsCSType_exists, "struct field lcsCSType does not exist");
		return lcsCSType_var;
	}
	DWORD& lcsIntent() {
		assert_cond(lcsIntent_exists, "struct field lcsIntent does not exist");
		return lcsIntent_var;
	}
	CIEXYZTRIPLE& lcsEndpoints() {
		assert_cond(lcsEndpoints_exists, "struct field lcsEndpoints does not exist");
		return *lcsEndpoints_var;
	}
	DWORD& lcsGammaRed() {
		assert_cond(lcsGammaRed_exists, "struct field lcsGammaRed does not exist");
		return lcsGammaRed_var;
	}
	DWORD& lcsGammaGreen() {
		assert_cond(lcsGammaGreen_exists, "struct field lcsGammaGreen does not exist");
		return lcsGammaGreen_var;
	}
	DWORD& lcsGammaBlue() {
		assert_cond(lcsGammaBlue_exists, "struct field lcsGammaBlue does not exist");
		return lcsGammaBlue_var;
	}
	std::vector<BYTE>& lcsFilename() {
		assert_cond(lcsFilename_exists, "struct field lcsFilename does not exist");
		return lcsFilename_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	LOGCOLORSPACEW& operator () () { return *instances.back(); }
	LOGCOLORSPACEW& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	LOGCOLORSPACEW(std::vector<LOGCOLORSPACEW*>& instances) : instances(instances) { instances.push_back(this); }
	~LOGCOLORSPACEW() {
		if (generated == 2)
			return;
		while (instances.size()) {
			LOGCOLORSPACEW* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	LOGCOLORSPACEW* generate();
};

int LOGCOLORSPACEW::_parent_id = 0;
int LOGCOLORSPACEW::_index_start = 0;



class EMRCREATECOLORSPACEW {
	std::vector<EMRCREATECOLORSPACEW*>& instances;

	DWORD iType_var;
	DWORD nSize_var;
	DWORD ihCS_var;
	LOGCOLORSPACEW* lcs_var;
	DWORD dwFlags_var;
	DWORD cbData_var;
	std::vector<BYTE> Data_var;

public:
	bool iType_exists = false;
	bool nSize_exists = false;
	bool ihCS_exists = false;
	bool lcs_exists = false;
	bool dwFlags_exists = false;
	bool cbData_exists = false;
	bool Data_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& nSize() {
		assert_cond(nSize_exists, "struct field nSize does not exist");
		return nSize_var;
	}
	DWORD& ihCS() {
		assert_cond(ihCS_exists, "struct field ihCS does not exist");
		return ihCS_var;
	}
	LOGCOLORSPACEW& lcs() {
		assert_cond(lcs_exists, "struct field lcs does not exist");
		return *lcs_var;
	}
	DWORD& dwFlags() {
		assert_cond(dwFlags_exists, "struct field dwFlags does not exist");
		return dwFlags_var;
	}
	DWORD& cbData() {
		assert_cond(cbData_exists, "struct field cbData does not exist");
		return cbData_var;
	}
	std::vector<BYTE>& Data() {
		assert_cond(Data_exists, "struct field Data does not exist");
		return Data_var;
	}

	unsigned char generated = 0;
	static int _parent_id;
	static int _index_start;
	int64 _startof = 0;
	std::size_t _sizeof = 0;
	EMRCREATECOLORSPACEW& operator () () { return *instances.back(); }
	EMRCREATECOLORSPACEW& operator [] (int index) {
		assert_cond((unsigned)(_index_start + index) < instances.size(), "instance index out of bounds");
		return *instances[_index_start + index];
	}
	std::size_t array_size() {
		return instances.size() - _index_start;
	}
	EMRCREATECOLORSPACEW(std::vector<EMRCREATECOLORSPACEW*>& instances) : instances(instances) { instances.push_back(this); }
	~EMRCREATECOLORSPACEW() {
		if (generated == 2)
			return;
		while (instances.size()) {
			EMRCREATECOLORSPACEW* instance = instances.back();
			instances.pop_back();
			if (instance->generated == 2)
				delete instance;
		}
	}
	EMRCREATECOLORSPACEW* generate();
};

int EMRCREATECOLORSPACEW::_parent_id = 0;
int EMRCREATECOLORSPACEW::_index_start = 0;



class EMREOF {
	std::vector<EMREOF*>& instances;

	DWORD iType_var;
	DWORD Size_var;
	DWORD nPalEntries_var;
	DWORD offPalEntries_var;
	std::vector<LOGPALETTEENTRY*> paletteBuffer_var;
	DWORD SizeLast_var;

public:
	bool iType_exists = false;
	bool Size_exists = false;
	bool nPalEntries_exists = false;
	bool offPalEntries_exists = false;
	bool paletteBuffer_exists = false;
	bool SizeLast_exists = false;

	DWORD& iType() {
		assert_cond(iType_exists, "struct field iType does not exist");
		return iType_var;
	}
	DWORD& Size() {
		assert_cond(Size_exists, "struct field Size does not exist");
		return Size_var;
	}
	DWORD& nPalEntries() {
		assert_cond(nPalEntries_exists, "struct field nPalEntries does not exist");
		return nPalEntries_var;
	}
	DWORD& offPalEntries() {
		assert_cond(offPalEntries_exists, "struct field offPalEntries does not exist");
		return offPalEntries_var;
	}
	std::vector<LOGPALETTEENTRY*>& paletteBuffer() {
		assert_cond(paletteBuffer_exists, "struct field paletteBuffer does not exist");
		return paletteBuffer_var;
	}
	DWORD& SizeLast() {
		assert_cond(SizeLast_exists, "struct field SizeLast does not exist");
		return SizeLast_var;
	}

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
std::vector<EmfHeaderExtension1*> EmfHeaderExtension1_headerExtension1_instances;
std::vector<EmfHeaderExtension2*> EmfHeaderExtension2_headerExtension2_instances;
std::vector<EMRHEADER*> EMRHEADER_EmfHeader_instances;
std::vector<EMRDESCRIPTION*> EMRDESCRIPTION_EmfDescription_instances;
std::vector<POINT*> POINT_aPoints_element_instances;
std::vector<EMRPOLYBEZIER*> EMRPOLYBEZIER_PolyBezier_instances;
std::vector<EMRPOLYGON*> EMRPOLYGON_Polygon_instances;
std::vector<EMRPOLYLINE*> EMRPOLYLINE_Polyline_instances;
std::vector<EMRPOLYBEZIERTO*> EMRPOLYBEZIERTO_PolyBezierTo_instances;
std::vector<EMRPOLYLINETO*> EMRPOLYLINETO_PolyBezierTo__instances;
std::vector<EMRPOLYPOLYLINE*> EMRPOLYPOLYLINE_PolyPolyline_instances;
std::vector<EMRPOLYPOLYGON*> EMRPOLYPOLYGON_PolyPolygon_instances;
std::vector<POINT*> POINT_ptlPixel_instances;
std::vector<COLORREF*> COLORREF_crColor_instances;
std::vector<EMRSETPIXELV*> EMRSETPIXELV_SetPixelV_instances;
std::vector<POINT*> POINT_offset_instances;
std::vector<EMROFFSETCLIPRGN*> EMROFFSETCLIPRGN_OffsetClipRgn_instances;
std::vector<RECTL*> RECTL_rclClip_instances;
std::vector<EMREXCLUDECLIPRECT*> EMREXCLUDECLIPRECT_ExcludeClipRect_instances;
std::vector<EMRINTERSECTCLIPRECT*> EMRINTERSECTCLIPRECT_InterSectClipRect_instances;
std::vector<EMRSELECTOBJECT*> EMRSELECTOBJECT_SelectObject_instances;
std::vector<POINT*> POINT_lopnWidth_instances;
std::vector<COLORREF*> COLORREF_lopnColor_instances;
std::vector<LOGPEN*> LOGPEN_lopn_instances;
std::vector<EMRCREATEPEN*> EMRCREATEPEN_CreatePen_instances;
std::vector<COLORREF*> COLORREF_lbColor_instances;
std::vector<LogBrushEx*> LogBrushEx_LogBrush_instances;
std::vector<EMRCREATEBRUSHINDIRECT*> EMRCREATEBRUSHINDIRECT_CreateBrushIndirect_instances;
std::vector<EMRDELETEOBJECT*> EMRDELETEOBJECT_DeleteObject_instances;
std::vector<POINT*> POINT_ptlCenter_instances;
std::vector<EMRANGLEARC*> EMRANGLEARC_AngleArc_instances;
std::vector<RECTL*> RECTL_rclBox_instances;
std::vector<EMRELLIPSE*> EMRELLIPSE_Ellipse_instances;
std::vector<EMRRECTANGLE*> EMRRECTANGLE_Rectangle_instances;
std::vector<SIZEL*> SIZEL_szlCorner_instances;
std::vector<EMRROUNDRECT*> EMRROUNDRECT_RoundRect_instances;
std::vector<POINT*> POINT_ptlStart_instances;
std::vector<POINT*> POINT_ptlEnd_instances;
std::vector<EMRARC*> EMRARC_Arc_instances;
std::vector<EMRCHORD*> EMRCHORD_Chord_instances;
std::vector<RECTL*> RECTL_box_instances;
std::vector<POINT*> POINT_start_instances;
std::vector<POINT*> POINT_stop_instances;
std::vector<EMRPIE*> EMRPIE_Pie_instances;
std::vector<EMRSELECTPALETTE*> EMRSELECTPALETTE_SelectPalette_instances;
std::vector<LOGPALETTEENTRY*> LOGPALETTEENTRY_palPalEntry_element_instances;
std::vector<LOGPALETTE*> LOGPALETTE_lgpl_instances;
std::vector<EMRCREATEPALETTE*> EMRCREATEPALETTE_CreatePalette_instances;
std::vector<LOGPALETTEENTRY*> LOGPALETTEENTRY_aPalEntries_element_instances;
std::vector<EMRSETPALETTEENTRIES*> EMRSETPALETTEENTRIES_SetPaletteEntries_instances;
std::vector<EMRRESIZEPALETTE*> EMRRESIZEPALETTE_ResizePalette_instances;
std::vector<EMREXTFLOODFILL*> EMREXTFLOODFILL_ExtFloodFill_instances;
std::vector<POINT*> POINT_ptl_instances;
std::vector<EMRLINETO*> EMRLINETO_LineTo_instances;
std::vector<EMRARCTO*> EMRARCTO_ArcTo_instances;
std::vector<EMRPOLYDRAW*> EMRPOLYDRAW_PolyDraw_instances;
std::vector<EMRBEGINPATH*> EMRBEGINPATH_BeginPath_instances;
std::vector<EMRENDPATH*> EMRENDPATH_EndPath_instances;
std::vector<EMRCLOSEFIGURE*> EMRCLOSEFIGURE_CloseFigure_instances;
std::vector<EMRFILLPATH*> EMRFILLPATH_FillPath_instances;
std::vector<EMRSTROKEANDFILLPATH*> EMRSTROKEANDFILLPATH_FillPath__instances;
std::vector<EMRSTROKEPATH*> EMRSTROKEPATH_StrokePath_instances;
std::vector<EMRFLATTENPATH*> EMRFLATTENPATH_FlattenPath_instances;
std::vector<EMRWIDENPATH*> EMRWIDENPATH_WidenPath_instances;
std::vector<EMRSELECTCLIPPATH*> EMRSELECTCLIPPATH_SelectClipPath_instances;
std::vector<EMRABORTPATH*> EMRABORTPATH_AbortPath_instances;
std::vector<EMRCOMMENT*> EMRCOMMENT_Comment_instances;
std::vector<RECTL*> RECTL_rgnBounds_instances;
std::vector<REGIONDATAHEADER*> REGIONDATAHEADER_rgnDataHeader_instances;
std::vector<RECTL*> RECTL_data_element_instances;
std::vector<REGIONDATA*> REGIONDATA_rgnData_instances;
std::vector<EMRFILLRGN*> EMRFILLRGN_FillRgn_instances;
std::vector<EMRFRAMERGN*> EMRFRAMERGN_FrameRgn_instances;
std::vector<EMRINVERTRGN*> EMRINVERTRGN_InvertRgn_instances;
std::vector<EMRPAINTRGN*> EMRPAINTRGN_PaintRgn_instances;
std::vector<EMREXTSELECTCLIPRGN*> EMREXTSELECTCLIPRGN_ExtSelectClipRgn_instances;
std::vector<XFORM*> XFORM_xformSrc_instances;
std::vector<BITMAPINFOHEADER*> BITMAPINFOHEADER_bmiHeader_instances;
std::vector<RGBQUAD*> RGBQUAD_bmiColors_element_instances;
std::vector<BITMAPINFO*> BITMAPINFO_BmiSrc_instances;
std::vector<EMRBITBLT*> EMRBITBLT_BitBlt_instances;
std::vector<COLORREF*> COLORREF_crBkColorSrc_instances;
std::vector<EMRSTRETCHBLT*> EMRSTRETCHBLT_StretchBlt_instances;
std::vector<BITMAPINFO*> BITMAPINFO_BmiMask_instances;
std::vector<EMRMASKBLT*> EMRMASKBLT_MaskBlt_instances;
std::vector<POINT*> POINT_aptlDest_element_instances;
std::vector<EMRPLGBLT*> EMRPLGBLT_PlgBlt_instances;
std::vector<EMRSETDIBITSTODEVICE*> EMRSETDIBITSTODEVICE_SetDiBitsToDevice_instances;
std::vector<EMRSTRETCHDIBITS*> EMRSTRETCHDIBITS_StretchDIBits_instances;
std::vector<POINT*> POINT_ptlReference_instances;
std::vector<RECTL*> RECTL_rcl_instances;
std::vector<EMRTEXT*> EMRTEXT_emrtext_instances;
std::vector<EMREXTTEXTOUTA*> EMREXTTEXTOUTA_ExtTextOutA_instances;
std::vector<EMRCREATEMONOBRUSH*> EMRCREATEMONOBRUSH_CreateMonoBrush_instances;
std::vector<EMRCREATEDIBPATTERNBRUSHPT*> EMRCREATEDIBPATTERNBRUSHPT_CreateDIBPatternBrushPt_instances;
std::vector<LOGPENEX*> LOGPENEX_elp_instances;
std::vector<EMREXTCREATEPEN*> EMREXTCREATEPEN_CreatePenEx_instances;
std::vector<EMRTEXT*> EMRTEXT_aemrtext_element_instances;
std::vector<EMRPOLYTEXTOUTA*> EMRPOLYTEXTOUTA_PolyTextOutA_instances;
std::vector<CIEXYZ*> CIEXYZ_ciexyzRed_instances;
std::vector<CIEXYZ*> CIEXYZ_ciexyzGreen_instances;
std::vector<CIEXYZ*> CIEXYZ_ciexyzBlue_instances;
std::vector<CIEXYZTRIPLE*> CIEXYZTRIPLE_lcsEndpoints_instances;
std::vector<LOGCOLORSPACEA*> LOGCOLORSPACEA_lcs_instances;
std::vector<EMRCREATECOLORSPACE*> EMRCREATECOLORSPACE_CreateColorSpace_instances;
std::vector<EMRSETCOLORSPACE*> EMRSETCOLORSPACE_SetColorSpace_instances;
std::vector<EMRDELETECOLORSPACE*> EMRDELETECOLORSPACE_DeleteColorSpace_instances;
std::vector<EMRGLSRECORD*> EMRGLSRECORD_GlsRecord_instances;
std::vector<EMRGLSBOUNDEDRECORD*> EMRGLSBOUNDEDRECORD_GlsBoundedRecord_instances;
std::vector<EMRDRAWESCAPE*> EMRDRAWESCAPE_DrawEscape_instances;
std::vector<EMREXTESCAPE*> EMREXTESCAPE_ExtEscape_instances;
std::vector<EMRRESERVED107*> EMRRESERVED107_Reserved___instances;
std::vector<UniversalFontId*> UniversalFontId_ufi_instances;
std::vector<EMRFORCEUFIMAPPING*> EMRFORCEUFIMAPPING_ForceUfiMapping_instances;
std::vector<EMRNAMEDESCAPE*> EMRNAMEDESCAPE_NamedEscape_instances;
std::vector<EMRCOLORCORRECTPALETTE*> EMRCOLORCORRECTPALETTE_ColorCorrectPalette_instances;
std::vector<BLENDFUNCTION*> BLENDFUNCTION_dwRop__instances;
std::vector<EMRALPHABLEND*> EMRALPHABLEND_AlphaBlend_instances;
std::vector<EMRTRANSPARENTBLT*> EMRTRANSPARENTBLT_TransparentBlt_instances;
std::vector<EMRRESERVED117*> EMRRESERVED117_Reserved____instances;
std::vector<TRIVERTEX*> TRIVERTEX_vObjects_element_instances;
std::vector<GRADIENT_RECT*> GRADIENT_RECT_vIndexes_element_instances;
std::vector<EMRGRADIENTFILL*> EMRGRADIENTFILL_GradientFill_instances;
std::vector<EMRCOLORMATCHTOTARGETW*> EMRCOLORMATCHTOTARGETW_ColorMatchToTargetW_instances;
std::vector<LOGCOLORSPACEW*> LOGCOLORSPACEW_lcs__instances;
std::vector<EMRCREATECOLORSPACEW*> EMRCREATECOLORSPACEW_CreateColorSpaceW_instances;
std::vector<LOGPALETTEENTRY*> LOGPALETTEENTRY_paletteBuffer_element_instances;
std::vector<EMREOF*> EMREOF_EmfEndOfFile_instances;


std::unordered_map<std::string, std::string> variable_types = { { "iType", "EmfRecordType" }, { "nSize", "DWORD_class" }, { "left", "LONG_class" }, { "top", "LONG_class" }, { "right", "LONG_class" }, { "bottom", "LONG_class" }, { "rclBounds", "RECTL" }, { "rclFrame", "RECTL" }, { "dSignature", "DWORD_class" }, { "nVersion", "DWORD_class" }, { "nBytes", "DWORD_class" }, { "nRecords", "DWORD_class" }, { "nHandles", "WORD_class" }, { "sReserved", "WORD_class" }, { "nDescription", "DWORD_class" }, { "offDescription", "DWORD_class" }, { "nPalEntries", "DWORD_class" }, { "cx", "LONG_class" }, { "cy", "LONG_class" }, { "szlDevice", "SIZEL" }, { "szlMillimeters", "SIZEL" }, { "cbPixelFormat", "DWORD_class" }, { "offPixelFormat", "DWORD_class" }, { "bOpenGL", "DWORD_class" }, { "headerExtension1", "EmfHeaderExtension1" }, { "MicrometersX", "DWORD_class" }, { "MicrometersY", "DWORD_class" }, { "headerExtension2", "EmfHeaderExtension2" }, { "EmfHeader", "EMRHEADER" }, { "desc", "WORD_array_class" }, { "EmfDescription", "EMRDESCRIPTION" }, { "recType", "UBYTE_class" }, { "cntPoints", "DWORD_class" }, { "x", "LONG_class" }, { "y", "LONG_class" }, { "aPoints", "POINT_array_class" }, { "PolyBezier", "EMRPOLYBEZIER" }, { "Polygon", "EMRPOLYGON" }, { "Polyline", "EMRPOLYLINE" }, { "PolyBezierTo", "EMRPOLYBEZIERTO" }, { "PolyBezierTo_", "EMRPOLYLINETO" }, { "nPolys", "DWORD_class" }, { "aPolyCounts", "DWORD_class" }, { "PolyPolyline", "EMRPOLYPOLYLINE" }, { "PolyPolygon", "EMRPOLYPOLYGON" }, { "ptlPixel", "POINT" }, { "Red", "UBYTE_class" }, { "Green", "UBYTE_class" }, { "Blue", "UBYTE_class" }, { "Reserved", "UBYTE_class" }, { "crColor", "COLORREF" }, { "SetPixelV", "EMRSETPIXELV" }, { "offset", "POINT" }, { "OffsetClipRgn", "EMROFFSETCLIPRGN" }, { "rclClip", "RECTL" }, { "ExcludeClipRect", "EMREXCLUDECLIPRECT" }, { "InterSectClipRect", "EMRINTERSECTCLIPRECT" }, { "ihObject", "DWORD_class" }, { "SelectObject", "EMRSELECTOBJECT" }, { "ihPen", "DWORD_class" }, { "lopnStyle", "UINT_class" }, { "lopnWidth", "POINT" }, { "lopnColor", "COLORREF" }, { "lopn", "LOGPEN" }, { "CreatePen", "EMRCREATEPEN" }, { "ihBrush", "DWORD_class" }, { "lbStyle", "BrushStyle" }, { "lbColor", "COLORREF" }, { "lbHatch", "DWORD_class" }, { "LogBrush", "LogBrushEx" }, { "CreateBrushIndirect", "EMRCREATEBRUSHINDIRECT" }, { "ihCS", "DWORD_class" }, { "DeleteObject", "EMRDELETEOBJECT" }, { "ptlCenter", "POINT" }, { "nRadius", "DWORD_class" }, { "eStartAngle", "FLOAT_class" }, { "eSweepAngle", "FLOAT_class" }, { "AngleArc", "EMRANGLEARC" }, { "rclBox", "RECTL" }, { "Ellipse", "EMRELLIPSE" }, { "Rectangle", "EMRRECTANGLE" }, { "szlCorner", "SIZEL" }, { "RoundRect", "EMRROUNDRECT" }, { "ptlStart", "POINT" }, { "ptlEnd", "POINT" }, { "Arc", "EMRARC" }, { "Chord", "EMRCHORD" }, { "box", "RECTL" }, { "start", "POINT" }, { "stop", "POINT" }, { "Pie", "EMRPIE" }, { "ihPal", "DWORD_class" }, { "SelectPalette", "EMRSELECTPALETTE" }, { "palVersion", "WORD_class" }, { "palNumEntries", "WORD_class" }, { "Reserved_", "uchar_class" }, { "Blue_", "uchar_class" }, { "Green_", "uchar_class" }, { "Red_", "uchar_class" }, { "palPalEntry", "LOGPALETTEENTRY_array_class" }, { "lgpl", "LOGPALETTE" }, { "CreatePalette", "EMRCREATEPALETTE" }, { "iStart", "DWORD_class" }, { "cEntries", "DWORD_class" }, { "aPalEntries", "LOGPALETTEENTRY_array_class" }, { "SetPaletteEntries", "EMRSETPALETTEENTRIES" }, { "NumberOfEntries", "DWORD_class" }, { "ResizePalette", "EMRRESIZEPALETTE" }, { "iMode", "DWORD_class" }, { "ExtFloodFill", "EMREXTFLOODFILL" }, { "ptl", "POINT" }, { "LineTo", "EMRLINETO" }, { "ArcTo", "EMRARCTO" }, { "abTypes", "BYTE_array_class" }, { "PolyDraw", "EMRPOLYDRAW" }, { "BeginPath", "EMRBEGINPATH" }, { "EndPath", "EMRENDPATH" }, { "CloseFigure", "EMRCLOSEFIGURE" }, { "FillPath", "EMRFILLPATH" }, { "FillPath_", "EMRSTROKEANDFILLPATH" }, { "StrokePath", "EMRSTROKEPATH" }, { "FlattenPath", "EMRFLATTENPATH" }, { "WidenPath", "EMRWIDENPATH" }, { "rgnMode", "RegionMode" }, { "SelectClipPath", "EMRSELECTCLIPPATH" }, { "AbortPath", "EMRABORTPATH" }, { "dataSize", "DWORD_class" }, { "privateData", "BYTE_array_class" }, { "Comment", "EMRCOMMENT" }, { "rgnDataSize", "DWORD_class" }, { "cntRects", "DWORD_class" }, { "rgnSize", "DWORD_class" }, { "rgnBounds", "RECTL" }, { "rgnDataHeader", "REGIONDATAHEADER" }, { "data", "RECTL_array_class" }, { "rgnData", "REGIONDATA" }, { "FillRgn", "EMRFILLRGN" }, { "width", "DWORD_class" }, { "height", "DWORD_class" }, { "FrameRgn", "EMRFRAMERGN" }, { "nRgnDataSize", "DWORD_class" }, { "rgnData_", "BYTE_array_class" }, { "InvertRgn", "EMRINVERTRGN" }, { "PaintRgn", "EMRPAINTRGN" }, { "ExtSelectClipRgn", "EMREXTSELECTCLIPRGN" }, { "xDest", "DWORD_class" }, { "yDest", "DWORD_class" }, { "cxDest", "DWORD_class" }, { "cyDest", "DWORD_class" }, { "BitBltRasterOperation", "DWORD_class" }, { "xSrc", "DWORD_class" }, { "ySrc", "DWORD_class" }, { "eM11", "FLOAT_class" }, { "eM12", "FLOAT_class" }, { "eM21", "FLOAT_class" }, { "eM22", "FLOAT_class" }, { "eDx", "FLOAT_class" }, { "eDy", "FLOAT_class" }, { "xformSrc", "XFORM" }, { "BkColorSrc", "DWORD_class" }, { "iUsageSrc", "DIBColors" }, { "offBmiSrc", "DWORD_class" }, { "cbBmiSrc", "DWORD_class" }, { "offBitsSrc", "DWORD_class" }, { "cbBitsSrc", "DWORD_class" }, { "biSize", "DWORD_class" }, { "biWidth", "LONG_class" }, { "biHeight", "LONG_class" }, { "biPlanes", "WORD_class" }, { "biBitCount", "BitCount" }, { "biCompression", "DWORD_class" }, { "biSizeImage", "DWORD_class" }, { "biXPelsPerMeter", "LONG_class" }, { "biYPelsPerMeter", "LONG_class" }, { "biClrUsed", "DWORD_class" }, { "biClrImportant", "DWORD_class" }, { "bmiHeader", "BITMAPINFOHEADER" }, { "rgbBlue", "UBYTE_class" }, { "rgbGreen", "UBYTE_class" }, { "rgbRed", "UBYTE_class" }, { "rgbReserved", "UBYTE_class" }, { "bmiColors", "RGBQUAD_array_class" }, { "BmiSrc", "BITMAPINFO" }, { "BitsSrc", "BYTE_array_class" }, { "BitBlt", "EMRBITBLT" }, { "xDest_", "LONG_class" }, { "yDest_", "LONG_class" }, { "cxDest_", "LONG_class" }, { "cyDest_", "LONG_class" }, { "dwRop", "DWORD_class" }, { "xSrc_", "LONG_class" }, { "ySrc_", "LONG_class" }, { "crBkColorSrc", "COLORREF" }, { "cxSrc", "LONG_class" }, { "cySrc", "LONG_class" }, { "StretchBlt", "EMRSTRETCHBLT" }, { "xMask", "LONG_class" }, { "yMask", "LONG_class" }, { "iUsageMask", "DWORD_class" }, { "offBmiMask", "DWORD_class" }, { "cbBmiMask", "DWORD_class" }, { "offBitsMask", "DWORD_class" }, { "cbBitsMask", "DWORD_class" }, { "BmiMask", "BITMAPINFO" }, { "BitsMask", "BYTE_array_class" }, { "MaskBlt", "EMRMASKBLT" }, { "aptlDest", "POINT_array_class" }, { "PlgBlt", "EMRPLGBLT" }, { "cxSrc_", "DWORD_class" }, { "cySrc_", "DWORD_class" }, { "iStartScan", "DWORD_class" }, { "cScans", "DWORD_class" }, { "SetDiBitsToDevice", "EMRSETDIBITSTODEVICE" }, { "StretchDIBits", "EMRSTRETCHDIBITS" }, { "iGraphicsMode", "DWORD_class" }, { "exScale", "FLOAT_class" }, { "eyScale", "FLOAT_class" }, { "ptlReference", "POINT" }, { "nChars", "DWORD_class" }, { "offString", "DWORD_class" }, { "fOptions", "DWORD_class" }, { "rcl", "RECTL" }, { "offDx", "DWORD_class" }, { "bStringBuffer", "BYTE_array_class" }, { "emrtext", "EMRTEXT" }, { "ExtTextOutA", "EMREXTTEXTOUTA" }, { "iUsage", "DWORD_class" }, { "offBmi", "DWORD_class" }, { "cbBmi", "DWORD_class" }, { "offBits", "DWORD_class" }, { "cbBits", "DWORD_class" }, { "CreateMonoBrush", "EMRCREATEMONOBRUSH" }, { "CreateDIBPatternBrushPt", "EMRCREATEDIBPATTERNBRUSHPT" }, { "PenStyle", "DWORD_class" }, { "Width", "DWORD_class" }, { "NumStyleEntries", "DWORD_class" }, { "StyleEntry", "DWORD_array_class" }, { "elp", "LOGPENEX" }, { "CreatePenEx", "EMREXTCREATEPEN" }, { "cStrings", "LONG_class" }, { "aemrtext", "EMRTEXT_array_class" }, { "PolyTextOutA", "EMRPOLYTEXTOUTA" }, { "ics", "DWORD_class" }, { "lcsSignature", "DWORD_class" }, { "lcsVersion", "DWORD_class" }, { "lcsSize", "DWORD_class" }, { "lcsCSType", "LogicalColorSpace" }, { "lcsIntent", "GamutMappingIntent" }, { "ciexyzX", "LONG_class" }, { "ciexyzY", "LONG_class" }, { "ciexyzZ", "LONG_class" }, { "ciexyzRed", "CIEXYZ" }, { "ciexyzGreen", "CIEXYZ" }, { "ciexyzBlue", "CIEXYZ" }, { "lcsEndpoints", "CIEXYZTRIPLE" }, { "lcsGammaRed", "DWORD_class" }, { "lcsGammaGreen", "DWORD_class" }, { "lcsGammaBlue", "DWORD_class" }, { "lcsFilename", "CHAR_array_class" }, { "lcs", "LOGCOLORSPACEA" }, { "CreateColorSpace", "EMRCREATECOLORSPACE" }, { "SetColorSpace", "EMRSETCOLORSPACE" }, { "DeleteColorSpace", "EMRDELETECOLORSPACE" }, { "cbData", "DWORD_class" }, { "Data", "BYTE_array_class" }, { "GlsRecord", "EMRGLSRECORD" }, { "GlsBoundedRecord", "EMRGLSBOUNDEDRECORD" }, { "iEscape", "MetafileEscapes" }, { "cjln", "DWORD_class" }, { "data_", "BYTE_array_class" }, { "DrawEscape", "EMRDRAWESCAPE" }, { "ExtEscape", "EMREXTESCAPE" }, { "ReservedData", "DWORD_array_class" }, { "Reserved__", "EMRRESERVED107" }, { "checksum", "DWORD_class" }, { "index", "DWORD_class" }, { "ufi", "UniversalFontId" }, { "ForceUfiMapping", "EMRFORCEUFIMAPPING" }, { "cjDriver", "DWORD_class" }, { "driverName", "WORD_class" }, { "NamedEscape", "EMRNAMEDESCAPE" }, { "ihPalette", "DWORD_class" }, { "nFirstEntry", "DWORD_class" }, { "nReserved", "DWORD_class" }, { "ColorCorrectPalette", "EMRCOLORCORRECTPALETTE" }, { "BlendOp", "BYTE_class" }, { "BlendFlags", "BYTE_class" }, { "SourceConstantAlpha", "BYTE_class" }, { "AlphaFormat", "BYTE_class" }, { "dwRop_", "BLENDFUNCTION" }, { "AlphaBlend", "EMRALPHABLEND" }, { "TransparentBlt", "EMRTRANSPARENTBLT" }, { "Reserved___", "EMRRESERVED117" }, { "nVer", "DWORD_class" }, { "nTri", "DWORD_class" }, { "ulMode", "GradientFill" }, { "Red__", "WORD_class" }, { "Green__", "WORD_class" }, { "Blue__", "WORD_class" }, { "Alpha", "WORD_class" }, { "vObjects", "TRIVERTEX_array_class" }, { "UpperLeft", "ULONG_class" }, { "LowerRight", "ULONG_class" }, { "vIndexes", "GRADIENT_RECT_array_class" }, { "vPadding", "DWORD_array_class" }, { "GradientFill", "EMRGRADIENTFILL" }, { "dwAction", "ColorSpace" }, { "dwFlags", "DWORD_class" }, { "cbName", "DWORD_class" }, { "ColorMatchToTargetW", "EMRCOLORMATCHTOTARGETW" }, { "lcsFilename_", "BYTE_array_class" }, { "lcs_", "LOGCOLORSPACEW" }, { "CreateColorSpaceW", "EMRCREATECOLORSPACEW" }, { "Size", "DWORD_class" }, { "offPalEntries", "DWORD_class" }, { "paletteBuffer", "LOGPALETTEENTRY_array_class" }, { "SizeLast", "DWORD_class" }, { "EmfEndOfFile", "EMREOF" } };

std::vector<std::vector<int>> integer_ranges = { { 1, 16 }, { 3, 4 }, { 0x0, 0x400 }, { 1, INT_MAX }, { 1, INT_MAX }, { 0, 256 } };

class globals_class {
public:
	int _struct_id = 0;
	int _struct_id_counter = 0;
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
	EmfHeaderExtension1 headerExtension1;
	DWORD_class MicrometersX;
	DWORD_class MicrometersY;
	EmfHeaderExtension2 headerExtension2;
	EMRHEADER EmfHeader;
	/*local*/ uint EmfHeaderSize;
	WORD_class desc_element;
	WORD_array_class desc;
	EMRDESCRIPTION EmfDescription;
	/*local*/ uint recCnt;
	UBYTE_class recType;
	DWORD_class cntPoints;
	LONG_class x;
	LONG_class y;
	POINT aPoints_element;
	POINT_array_class aPoints;
	EMRPOLYBEZIER PolyBezier;
	EMRPOLYGON Polygon;
	EMRPOLYLINE Polyline;
	EMRPOLYBEZIERTO PolyBezierTo;
	EMRPOLYLINETO PolyBezierTo_;
	DWORD_class nPolys;
	DWORD_class aPolyCounts;
	EMRPOLYPOLYLINE PolyPolyline;
	EMRPOLYPOLYGON PolyPolygon;
	POINT ptlPixel;
	UBYTE_class Red;
	UBYTE_class Green;
	UBYTE_class Blue;
	UBYTE_class Reserved;
	COLORREF crColor;
	EMRSETPIXELV SetPixelV;
	POINT offset;
	EMROFFSETCLIPRGN OffsetClipRgn;
	RECTL rclClip;
	EMREXCLUDECLIPRECT ExcludeClipRect;
	EMRINTERSECTCLIPRECT InterSectClipRect;
	DWORD_class ihObject;
	EMRSELECTOBJECT SelectObject;
	DWORD_class ihPen;
	UINT_class lopnStyle;
	POINT lopnWidth;
	COLORREF lopnColor;
	LOGPEN lopn;
	EMRCREATEPEN CreatePen;
	DWORD_class ihBrush;
	COLORREF lbColor;
	DWORD_class lbHatch;
	LogBrushEx LogBrush;
	EMRCREATEBRUSHINDIRECT CreateBrushIndirect;
	DWORD_class ihCS;
	EMRDELETEOBJECT DeleteObject;
	POINT ptlCenter;
	DWORD_class nRadius;
	FLOAT_class eStartAngle;
	FLOAT_class eSweepAngle;
	EMRANGLEARC AngleArc;
	RECTL rclBox;
	EMRELLIPSE Ellipse;
	EMRRECTANGLE Rectangle;
	SIZEL szlCorner;
	EMRROUNDRECT RoundRect;
	POINT ptlStart;
	POINT ptlEnd;
	EMRARC Arc;
	EMRCHORD Chord;
	RECTL box;
	POINT start;
	POINT stop;
	EMRPIE Pie;
	DWORD_class ihPal;
	EMRSELECTPALETTE SelectPalette;
	WORD_class palVersion;
	WORD_class palNumEntries;
	uchar_class Reserved_;
	uchar_class Blue_;
	uchar_class Green_;
	uchar_class Red_;
	LOGPALETTEENTRY palPalEntry_element;
	LOGPALETTEENTRY_array_class palPalEntry;
	LOGPALETTE lgpl;
	EMRCREATEPALETTE CreatePalette;
	DWORD_class iStart;
	DWORD_class cEntries;
	LOGPALETTEENTRY aPalEntries_element;
	LOGPALETTEENTRY_array_class aPalEntries;
	EMRSETPALETTEENTRIES SetPaletteEntries;
	DWORD_class NumberOfEntries;
	EMRRESIZEPALETTE ResizePalette;
	DWORD_class iMode;
	EMREXTFLOODFILL ExtFloodFill;
	POINT ptl;
	EMRLINETO LineTo;
	EMRARCTO ArcTo;
	BYTE_class abTypes_element;
	BYTE_array_class abTypes;
	EMRPOLYDRAW PolyDraw;
	EMRBEGINPATH BeginPath;
	EMRENDPATH EndPath;
	EMRCLOSEFIGURE CloseFigure;
	EMRFILLPATH FillPath;
	EMRSTROKEANDFILLPATH FillPath_;
	EMRSTROKEPATH StrokePath;
	EMRFLATTENPATH FlattenPath;
	EMRWIDENPATH WidenPath;
	EMRSELECTCLIPPATH SelectClipPath;
	EMRABORTPATH AbortPath;
	DWORD_class dataSize;
	BYTE_class privateData_element;
	BYTE_array_class privateData;
	EMRCOMMENT Comment;
	DWORD_class rgnDataSize;
	DWORD_class iType;
	DWORD_class cntRects;
	DWORD_class rgnSize;
	RECTL rgnBounds;
	REGIONDATAHEADER rgnDataHeader;
	RECTL data_element;
	RECTL_array_class data;
	REGIONDATA rgnData;
	EMRFILLRGN FillRgn;
	DWORD_class width;
	DWORD_class height;
	EMRFRAMERGN FrameRgn;
	DWORD_class nRgnDataSize;
	BYTE_class rgnData__element;
	BYTE_array_class rgnData_;
	EMRINVERTRGN InvertRgn;
	EMRPAINTRGN PaintRgn;
	EMREXTSELECTCLIPRGN ExtSelectClipRgn;
	DWORD_class xDest;
	DWORD_class yDest;
	DWORD_class cxDest;
	DWORD_class cyDest;
	DWORD_class BitBltRasterOperation;
	DWORD_class xSrc;
	DWORD_class ySrc;
	FLOAT_class eM11;
	FLOAT_class eM12;
	FLOAT_class eM21;
	FLOAT_class eM22;
	FLOAT_class eDx;
	FLOAT_class eDy;
	XFORM xformSrc;
	DWORD_class BkColorSrc;
	DWORD_class offBmiSrc;
	DWORD_class cbBmiSrc;
	DWORD_class offBitsSrc;
	DWORD_class cbBitsSrc;
	DWORD_class biSize;
	LONG_class biWidth;
	LONG_class biHeight;
	WORD_class biPlanes;
	DWORD_class biCompression;
	DWORD_class biSizeImage;
	LONG_class biXPelsPerMeter;
	LONG_class biYPelsPerMeter;
	DWORD_class biClrUsed;
	DWORD_class biClrImportant;
	BITMAPINFOHEADER bmiHeader;
	UBYTE_class rgbBlue;
	UBYTE_class rgbGreen;
	UBYTE_class rgbRed;
	UBYTE_class rgbReserved;
	RGBQUAD bmiColors_element;
	RGBQUAD_array_class bmiColors;
	BITMAPINFO BmiSrc;
	BYTE_class BitsSrc_element;
	BYTE_array_class BitsSrc;
	EMRBITBLT BitBlt;
	LONG_class xDest_;
	LONG_class yDest_;
	LONG_class cxDest_;
	LONG_class cyDest_;
	DWORD_class dwRop;
	LONG_class xSrc_;
	LONG_class ySrc_;
	COLORREF crBkColorSrc;
	LONG_class cxSrc;
	LONG_class cySrc;
	EMRSTRETCHBLT StretchBlt;
	LONG_class xMask;
	LONG_class yMask;
	DWORD_class iUsageMask;
	DWORD_class offBmiMask;
	DWORD_class cbBmiMask;
	DWORD_class offBitsMask;
	DWORD_class cbBitsMask;
	BITMAPINFO BmiMask;
	BYTE_class BitsMask_element;
	BYTE_array_class BitsMask;
	EMRMASKBLT MaskBlt;
	POINT aptlDest_element;
	POINT_array_class aptlDest;
	EMRPLGBLT PlgBlt;
	DWORD_class cxSrc_;
	DWORD_class cySrc_;
	DWORD_class iStartScan;
	DWORD_class cScans;
	EMRSETDIBITSTODEVICE SetDiBitsToDevice;
	EMRSTRETCHDIBITS StretchDIBits;
	DWORD_class iGraphicsMode;
	FLOAT_class exScale;
	FLOAT_class eyScale;
	POINT ptlReference;
	DWORD_class nChars;
	DWORD_class offString;
	DWORD_class fOptions;
	RECTL rcl;
	DWORD_class offDx;
	BYTE_class bStringBuffer_element;
	BYTE_array_class bStringBuffer;
	EMRTEXT emrtext;
	EMREXTTEXTOUTA ExtTextOutA;
	DWORD_class iUsage;
	DWORD_class offBmi;
	DWORD_class cbBmi;
	DWORD_class offBits;
	DWORD_class cbBits;
	EMRCREATEMONOBRUSH CreateMonoBrush;
	EMRCREATEDIBPATTERNBRUSHPT CreateDIBPatternBrushPt;
	DWORD_class PenStyle;
	DWORD_class Width;
	DWORD_class NumStyleEntries;
	DWORD_class StyleEntry_element;
	DWORD_array_class StyleEntry;
	LOGPENEX elp;
	EMREXTCREATEPEN CreatePenEx;
	LONG_class cStrings;
	EMRTEXT aemrtext_element;
	EMRTEXT_array_class aemrtext;
	EMRPOLYTEXTOUTA PolyTextOutA;
	DWORD_class ics;
	DWORD_class lcsSignature;
	DWORD_class lcsVersion;
	DWORD_class lcsSize;
	LONG_class ciexyzX;
	LONG_class ciexyzY;
	LONG_class ciexyzZ;
	CIEXYZ ciexyzRed;
	CIEXYZ ciexyzGreen;
	CIEXYZ ciexyzBlue;
	CIEXYZTRIPLE lcsEndpoints;
	DWORD_class lcsGammaRed;
	DWORD_class lcsGammaGreen;
	DWORD_class lcsGammaBlue;
	CHAR_class lcsFilename_element;
	CHAR_array_class lcsFilename;
	LOGCOLORSPACEA lcs;
	EMRCREATECOLORSPACE CreateColorSpace;
	EMRSETCOLORSPACE SetColorSpace;
	EMRDELETECOLORSPACE DeleteColorSpace;
	DWORD_class cbData;
	BYTE_class Data_element;
	BYTE_array_class Data;
	EMRGLSRECORD GlsRecord;
	EMRGLSBOUNDEDRECORD GlsBoundedRecord;
	DWORD_class cjln;
	BYTE_class data__element;
	BYTE_array_class data_;
	EMRDRAWESCAPE DrawEscape;
	EMREXTESCAPE ExtEscape;
	DWORD_class ReservedData_element;
	DWORD_array_class ReservedData;
	EMRRESERVED107 Reserved__;
	DWORD_class checksum;
	DWORD_class index;
	UniversalFontId ufi;
	EMRFORCEUFIMAPPING ForceUfiMapping;
	DWORD_class cjDriver;
	WORD_class driverName;
	EMRNAMEDESCAPE NamedEscape;
	DWORD_class ihPalette;
	DWORD_class nFirstEntry;
	DWORD_class nReserved;
	EMRCOLORCORRECTPALETTE ColorCorrectPalette;
	BYTE_class BlendOp;
	BYTE_class BlendFlags;
	BYTE_class SourceConstantAlpha;
	BYTE_class AlphaFormat;
	BLENDFUNCTION dwRop_;
	EMRALPHABLEND AlphaBlend;
	EMRTRANSPARENTBLT TransparentBlt;
	EMRRESERVED117 Reserved___;
	DWORD_class nVer;
	DWORD_class nTri;
	WORD_class Red__;
	WORD_class Green__;
	WORD_class Blue__;
	WORD_class Alpha;
	TRIVERTEX vObjects_element;
	TRIVERTEX_array_class vObjects;
	ULONG_class UpperLeft;
	ULONG_class LowerRight;
	GRADIENT_RECT vIndexes_element;
	GRADIENT_RECT_array_class vIndexes;
	DWORD_class vPadding_element;
	DWORD_array_class vPadding;
	EMRGRADIENTFILL GradientFill;
	DWORD_class cbName;
	EMRCOLORMATCHTOTARGETW ColorMatchToTargetW;
	BYTE_class lcsFilename__element;
	BYTE_array_class lcsFilename_;
	LOGCOLORSPACEW lcs_;
	DWORD_class dwFlags;
	EMRCREATECOLORSPACEW CreateColorSpaceW;
	/*local*/ std::vector<UBYTE> bitmapRecords;
	/*local*/ std::vector<UBYTE> clippingRecords;
	/*local*/ std::vector<UBYTE> commentRecords;
	/*local*/ std::vector<UBYTE> controlRecords;
	/*local*/ std::vector<UBYTE> drawingRecords;
	/*local*/ std::vector<UBYTE> escapeRecords;
	/*local*/ std::vector<UBYTE> objectCreationRecords;
	/*local*/ std::vector<UBYTE> objectManipulationRecords;
	/*local*/ std::vector<UBYTE> openGLRecords;
	/*local*/ std::vector<UBYTE> pathBracketRecords;
	/*local*/ std::vector<UBYTE> stateRecords;
	/*local*/ std::vector<UBYTE> transformRecords;
	/*local*/ std::vector<UBYTE> possible;
	DWORD_class Size;
	DWORD_class offPalEntries;
	LOGPALETTEENTRY paletteBuffer_element;
	LOGPALETTEENTRY_array_class paletteBuffer;
	DWORD_class SizeLast;
	EMREOF EmfEndOfFile;
	/*local*/ DWORD file_size;


	globals_class() :
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
		nDescription(1, { 0 }),
		offDescription(1),
		nPalEntries(1),
		cx(1),
		cy(1),
		szlDevice(SIZEL_szlDevice_instances),
		szlMillimeters(SIZEL_szlMillimeters_instances),
		cbPixelFormat(1),
		offPixelFormat(1),
		bOpenGL(1),
		headerExtension1(EmfHeaderExtension1_headerExtension1_instances),
		MicrometersX(1),
		MicrometersY(1),
		headerExtension2(EmfHeaderExtension2_headerExtension2_instances),
		EmfHeader(EMRHEADER_EmfHeader_instances),
		desc_element(false),
		desc(desc_element),
		EmfDescription(EMRDESCRIPTION_EmfDescription_instances),
		recType(1),
		cntPoints(1),
		x(1),
		y(1),
		aPoints_element(POINT_aPoints_element_instances),
		aPoints(aPoints_element),
		PolyBezier(EMRPOLYBEZIER_PolyBezier_instances),
		Polygon(EMRPOLYGON_Polygon_instances),
		Polyline(EMRPOLYLINE_Polyline_instances),
		PolyBezierTo(EMRPOLYBEZIERTO_PolyBezierTo_instances),
		PolyBezierTo_(EMRPOLYLINETO_PolyBezierTo__instances),
		nPolys(1),
		aPolyCounts(1),
		PolyPolyline(EMRPOLYPOLYLINE_PolyPolyline_instances),
		PolyPolygon(EMRPOLYPOLYGON_PolyPolygon_instances),
		ptlPixel(POINT_ptlPixel_instances),
		Red(1),
		Green(1),
		Blue(1),
		Reserved(1),
		crColor(COLORREF_crColor_instances),
		SetPixelV(EMRSETPIXELV_SetPixelV_instances),
		offset(POINT_offset_instances),
		OffsetClipRgn(EMROFFSETCLIPRGN_OffsetClipRgn_instances),
		rclClip(RECTL_rclClip_instances),
		ExcludeClipRect(EMREXCLUDECLIPRECT_ExcludeClipRect_instances),
		InterSectClipRect(EMRINTERSECTCLIPRECT_InterSectClipRect_instances),
		ihObject(1),
		SelectObject(EMRSELECTOBJECT_SelectObject_instances),
		ihPen(1),
		lopnStyle(1),
		lopnWidth(POINT_lopnWidth_instances),
		lopnColor(COLORREF_lopnColor_instances),
		lopn(LOGPEN_lopn_instances),
		CreatePen(EMRCREATEPEN_CreatePen_instances),
		ihBrush(1),
		lbColor(COLORREF_lbColor_instances),
		lbHatch(1),
		LogBrush(LogBrushEx_LogBrush_instances),
		CreateBrushIndirect(EMRCREATEBRUSHINDIRECT_CreateBrushIndirect_instances),
		ihCS(1),
		DeleteObject(EMRDELETEOBJECT_DeleteObject_instances),
		ptlCenter(POINT_ptlCenter_instances),
		nRadius(1),
		eStartAngle(1),
		eSweepAngle(1),
		AngleArc(EMRANGLEARC_AngleArc_instances),
		rclBox(RECTL_rclBox_instances),
		Ellipse(EMRELLIPSE_Ellipse_instances),
		Rectangle(EMRRECTANGLE_Rectangle_instances),
		szlCorner(SIZEL_szlCorner_instances),
		RoundRect(EMRROUNDRECT_RoundRect_instances),
		ptlStart(POINT_ptlStart_instances),
		ptlEnd(POINT_ptlEnd_instances),
		Arc(EMRARC_Arc_instances),
		Chord(EMRCHORD_Chord_instances),
		box(RECTL_box_instances),
		start(POINT_start_instances),
		stop(POINT_stop_instances),
		Pie(EMRPIE_Pie_instances),
		ihPal(1),
		SelectPalette(EMRSELECTPALETTE_SelectPalette_instances),
		palVersion(1),
		palNumEntries(1),
		Reserved_(1),
		Blue_(1),
		Green_(1),
		Red_(1),
		palPalEntry_element(LOGPALETTEENTRY_palPalEntry_element_instances),
		palPalEntry(palPalEntry_element),
		lgpl(LOGPALETTE_lgpl_instances),
		CreatePalette(EMRCREATEPALETTE_CreatePalette_instances),
		iStart(1),
		cEntries(1),
		aPalEntries_element(LOGPALETTEENTRY_aPalEntries_element_instances),
		aPalEntries(aPalEntries_element),
		SetPaletteEntries(EMRSETPALETTEENTRIES_SetPaletteEntries_instances),
		NumberOfEntries(4),
		ResizePalette(EMRRESIZEPALETTE_ResizePalette_instances),
		iMode(1),
		ExtFloodFill(EMREXTFLOODFILL_ExtFloodFill_instances),
		ptl(POINT_ptl_instances),
		LineTo(EMRLINETO_LineTo_instances),
		ArcTo(EMRARCTO_ArcTo_instances),
		abTypes_element(false),
		abTypes(abTypes_element),
		PolyDraw(EMRPOLYDRAW_PolyDraw_instances),
		BeginPath(EMRBEGINPATH_BeginPath_instances),
		EndPath(EMRENDPATH_EndPath_instances),
		CloseFigure(EMRCLOSEFIGURE_CloseFigure_instances),
		FillPath(EMRFILLPATH_FillPath_instances),
		FillPath_(EMRSTROKEANDFILLPATH_FillPath__instances),
		StrokePath(EMRSTROKEPATH_StrokePath_instances),
		FlattenPath(EMRFLATTENPATH_FlattenPath_instances),
		WidenPath(EMRWIDENPATH_WidenPath_instances),
		SelectClipPath(EMRSELECTCLIPPATH_SelectClipPath_instances),
		AbortPath(EMRABORTPATH_AbortPath_instances),
		dataSize(1),
		privateData_element(false),
		privateData(privateData_element),
		Comment(EMRCOMMENT_Comment_instances),
		rgnDataSize(1),
		iType(1),
		cntRects(1),
		rgnSize(1),
		rgnBounds(RECTL_rgnBounds_instances),
		rgnDataHeader(REGIONDATAHEADER_rgnDataHeader_instances),
		data_element(RECTL_data_element_instances),
		data(data_element),
		rgnData(REGIONDATA_rgnData_instances),
		FillRgn(EMRFILLRGN_FillRgn_instances),
		width(1),
		height(1),
		FrameRgn(EMRFRAMERGN_FrameRgn_instances),
		nRgnDataSize(1),
		rgnData__element(false),
		rgnData_(rgnData__element),
		InvertRgn(EMRINVERTRGN_InvertRgn_instances),
		PaintRgn(EMRPAINTRGN_PaintRgn_instances),
		ExtSelectClipRgn(EMREXTSELECTCLIPRGN_ExtSelectClipRgn_instances),
		xDest(1),
		yDest(1),
		cxDest(1),
		cyDest(1),
		BitBltRasterOperation(1),
		xSrc(1),
		ySrc(1),
		eM11(1),
		eM12(1),
		eM21(1),
		eM22(1),
		eDx(1),
		eDy(1),
		xformSrc(XFORM_xformSrc_instances),
		BkColorSrc(1),
		offBmiSrc(1),
		cbBmiSrc(1),
		offBitsSrc(1),
		cbBitsSrc(1),
		biSize(1),
		biWidth(5),
		biHeight(6),
		biPlanes(1),
		biCompression(1),
		biSizeImage(1),
		biXPelsPerMeter(1),
		biYPelsPerMeter(1),
		biClrUsed(7),
		biClrImportant(1),
		bmiHeader(BITMAPINFOHEADER_bmiHeader_instances),
		rgbBlue(1),
		rgbGreen(1),
		rgbRed(1),
		rgbReserved(1),
		bmiColors_element(RGBQUAD_bmiColors_element_instances),
		bmiColors(bmiColors_element),
		BmiSrc(BITMAPINFO_BmiSrc_instances),
		BitsSrc_element(false),
		BitsSrc(BitsSrc_element),
		BitBlt(EMRBITBLT_BitBlt_instances),
		xDest_(1),
		yDest_(1),
		cxDest_(1),
		cyDest_(1),
		dwRop(1),
		xSrc_(1),
		ySrc_(1),
		crBkColorSrc(COLORREF_crBkColorSrc_instances),
		cxSrc(1),
		cySrc(1),
		StretchBlt(EMRSTRETCHBLT_StretchBlt_instances),
		xMask(1),
		yMask(1),
		iUsageMask(1),
		offBmiMask(1),
		cbBmiMask(1),
		offBitsMask(1),
		cbBitsMask(1),
		BmiMask(BITMAPINFO_BmiMask_instances),
		BitsMask_element(false),
		BitsMask(BitsMask_element),
		MaskBlt(EMRMASKBLT_MaskBlt_instances),
		aptlDest_element(POINT_aptlDest_element_instances),
		aptlDest(aptlDest_element),
		PlgBlt(EMRPLGBLT_PlgBlt_instances),
		cxSrc_(1),
		cySrc_(1),
		iStartScan(1),
		cScans(1),
		SetDiBitsToDevice(EMRSETDIBITSTODEVICE_SetDiBitsToDevice_instances),
		StretchDIBits(EMRSTRETCHDIBITS_StretchDIBits_instances),
		iGraphicsMode(1),
		exScale(1),
		eyScale(1),
		ptlReference(POINT_ptlReference_instances),
		nChars(1),
		offString(1),
		fOptions(1),
		rcl(RECTL_rcl_instances),
		offDx(1),
		bStringBuffer_element(false),
		bStringBuffer(bStringBuffer_element),
		emrtext(EMRTEXT_emrtext_instances),
		ExtTextOutA(EMREXTTEXTOUTA_ExtTextOutA_instances),
		iUsage(1),
		offBmi(1),
		cbBmi(1),
		offBits(1),
		cbBits(1),
		CreateMonoBrush(EMRCREATEMONOBRUSH_CreateMonoBrush_instances),
		CreateDIBPatternBrushPt(EMRCREATEDIBPATTERNBRUSHPT_CreateDIBPatternBrushPt_instances),
		PenStyle(1),
		Width(1),
		NumStyleEntries(1),
		StyleEntry_element(false),
		StyleEntry(StyleEntry_element),
		elp(LOGPENEX_elp_instances),
		CreatePenEx(EMREXTCREATEPEN_CreatePenEx_instances),
		cStrings(1),
		aemrtext_element(EMRTEXT_aemrtext_element_instances),
		aemrtext(aemrtext_element),
		PolyTextOutA(EMRPOLYTEXTOUTA_PolyTextOutA_instances),
		ics(1),
		lcsSignature(1),
		lcsVersion(1),
		lcsSize(1),
		ciexyzX(1),
		ciexyzY(1),
		ciexyzZ(1),
		ciexyzRed(CIEXYZ_ciexyzRed_instances),
		ciexyzGreen(CIEXYZ_ciexyzGreen_instances),
		ciexyzBlue(CIEXYZ_ciexyzBlue_instances),
		lcsEndpoints(CIEXYZTRIPLE_lcsEndpoints_instances),
		lcsGammaRed(1),
		lcsGammaGreen(1),
		lcsGammaBlue(1),
		lcsFilename_element(false),
		lcsFilename(lcsFilename_element),
		lcs(LOGCOLORSPACEA_lcs_instances),
		CreateColorSpace(EMRCREATECOLORSPACE_CreateColorSpace_instances),
		SetColorSpace(EMRSETCOLORSPACE_SetColorSpace_instances),
		DeleteColorSpace(EMRDELETECOLORSPACE_DeleteColorSpace_instances),
		cbData(1),
		Data_element(false),
		Data(Data_element),
		GlsRecord(EMRGLSRECORD_GlsRecord_instances),
		GlsBoundedRecord(EMRGLSBOUNDEDRECORD_GlsBoundedRecord_instances),
		cjln(1),
		data__element(false),
		data_(data__element),
		DrawEscape(EMRDRAWESCAPE_DrawEscape_instances),
		ExtEscape(EMREXTESCAPE_ExtEscape_instances),
		ReservedData_element(false),
		ReservedData(ReservedData_element),
		Reserved__(EMRRESERVED107_Reserved___instances),
		checksum(1),
		index(1),
		ufi(UniversalFontId_ufi_instances),
		ForceUfiMapping(EMRFORCEUFIMAPPING_ForceUfiMapping_instances),
		cjDriver(1),
		driverName(1),
		NamedEscape(EMRNAMEDESCAPE_NamedEscape_instances),
		ihPalette(1),
		nFirstEntry(1),
		nReserved(1),
		ColorCorrectPalette(EMRCOLORCORRECTPALETTE_ColorCorrectPalette_instances),
		BlendOp(1),
		BlendFlags(1),
		SourceConstantAlpha(1),
		AlphaFormat(1),
		dwRop_(BLENDFUNCTION_dwRop__instances),
		AlphaBlend(EMRALPHABLEND_AlphaBlend_instances),
		TransparentBlt(EMRTRANSPARENTBLT_TransparentBlt_instances),
		Reserved___(EMRRESERVED117_Reserved____instances),
		nVer(1),
		nTri(1),
		Red__(1),
		Green__(1),
		Blue__(1),
		Alpha(1),
		vObjects_element(TRIVERTEX_vObjects_element_instances),
		vObjects(vObjects_element),
		UpperLeft(1),
		LowerRight(1),
		vIndexes_element(GRADIENT_RECT_vIndexes_element_instances),
		vIndexes(vIndexes_element),
		vPadding_element(false),
		vPadding(vPadding_element),
		GradientFill(EMRGRADIENTFILL_GradientFill_instances),
		cbName(1),
		ColorMatchToTargetW(EMRCOLORMATCHTOTARGETW_ColorMatchToTargetW_instances),
		lcsFilename__element(false),
		lcsFilename_(lcsFilename__element),
		lcs_(LOGCOLORSPACEW_lcs__instances),
		dwFlags(1),
		CreateColorSpaceW(EMRCREATECOLORSPACEW_CreateColorSpaceW_instances),
		Size(1),
		offPalEntries(1),
		paletteBuffer_element(LOGPALETTEENTRY_paletteBuffer_element_instances),
		paletteBuffer(paletteBuffer_element),
		SizeLast(1),
		EmfEndOfFile(EMREOF_EmfEndOfFile_instances)
	{}
};

globals_class* g;


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

	GENERATE_VAR(cx, ::g->cx.generate({ 1 }));
	GENERATE_VAR(cy, ::g->cy.generate({ 2 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EmfHeaderExtension1* EmfHeaderExtension1::generate() {
	if (generated == 1) {
		EmfHeaderExtension1* new_instance = new EmfHeaderExtension1(instances);
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


EmfHeaderExtension2* EmfHeaderExtension2::generate() {
	if (generated == 1) {
		EmfHeaderExtension2* new_instance = new EmfHeaderExtension2(instances);
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

	GENERATE_VAR(MicrometersX, ::g->MicrometersX.generate({ 0x000A55D5 }));
	GENERATE_VAR(MicrometersY, ::g->MicrometersY.generate({ 0x000675A5 }));

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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_HEADER }));
	GENERATE_VAR(nSize, ::g->nSize.generate());
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(rclFrame, ::g->rclFrame.generate());
	GENERATE_VAR(dSignature, ::g->dSignature.generate({ 0x464D4520 }));
	GENERATE_VAR(nVersion, ::g->nVersion.generate());
	GENERATE_VAR(nBytes, ::g->nBytes.generate());
	GENERATE_VAR(nRecords, ::g->nRecords.generate());
	GENERATE_VAR(nHandles, ::g->nHandles.generate());
	GENERATE_VAR(sReserved, ::g->sReserved.generate());
	GENERATE_VAR(nDescription, ::g->nDescription.generate({ 0, 4, 8, 12, 16 }));
	GENERATE_VAR(offDescription, ::g->offDescription.generate({ 0x6c }));
	GENERATE_VAR(nPalEntries, ::g->nPalEntries.generate({ 1 }));
	GENERATE_VAR(szlDevice, ::g->szlDevice.generate());
	GENERATE_VAR(szlMillimeters, ::g->szlMillimeters.generate());
	GENERATE_VAR(headerExtension1, ::g->headerExtension1.generate());
	GENERATE_VAR(headerExtension2, ::g->headerExtension2.generate());

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


POINT* POINT::generate() {
	if (generated == 1) {
		POINT* new_instance = new POINT(instances);
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

	GENERATE_VAR(x, ::g->x.generate({ 1 }));
	GENERATE_VAR(y, ::g->y.generate({ 2 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRPOLYBEZIER* EMRPOLYBEZIER::generate() {
	if (generated == 1) {
		EMRPOLYBEZIER* new_instance = new EMRPOLYBEZIER(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_POLYBEZIER }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x24 }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(cntPoints, ::g->cntPoints.generate({ 1 }));
	GENERATE_VAR(aPoints, ::g->aPoints.generate(cntPoints()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRPOLYGON* EMRPOLYGON::generate() {
	if (generated == 1) {
		EMRPOLYGON* new_instance = new EMRPOLYGON(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_POLYGON }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x24 }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(cntPoints, ::g->cntPoints.generate({ 1 }));
	GENERATE_VAR(aPoints, ::g->aPoints.generate(cntPoints()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRPOLYLINE* EMRPOLYLINE::generate() {
	if (generated == 1) {
		EMRPOLYLINE* new_instance = new EMRPOLYLINE(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_POLYLINE }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x24 }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(cntPoints, ::g->cntPoints.generate({ 1 }));
	GENERATE_VAR(aPoints, ::g->aPoints.generate(cntPoints()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRPOLYBEZIERTO* EMRPOLYBEZIERTO::generate() {
	if (generated == 1) {
		EMRPOLYBEZIERTO* new_instance = new EMRPOLYBEZIERTO(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_POLYBEZIERTO }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x24 }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(cntPoints, ::g->cntPoints.generate({ 1 }));
	GENERATE_VAR(aPoints, ::g->aPoints.generate(cntPoints()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRPOLYLINETO* EMRPOLYLINETO::generate() {
	if (generated == 1) {
		EMRPOLYLINETO* new_instance = new EMRPOLYLINETO(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_POLYLINETO }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x24 }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(cntPoints, ::g->cntPoints.generate({ 1 }));
	GENERATE_VAR(aPoints, ::g->aPoints.generate(cntPoints()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRPOLYPOLYLINE* EMRPOLYPOLYLINE::generate() {
	if (generated == 1) {
		EMRPOLYPOLYLINE* new_instance = new EMRPOLYPOLYLINE(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_POLYPOLYLINE }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x2c }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(nPolys, ::g->nPolys.generate({ 1 }));
	GENERATE_VAR(cntPoints, ::g->cntPoints.generate({ 1 }));
	GENERATE_VAR(aPolyCounts, ::g->aPolyCounts.generate({ 1 }));
	GENERATE_VAR(aPoints, ::g->aPoints.generate(cntPoints()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRPOLYPOLYGON* EMRPOLYPOLYGON::generate() {
	if (generated == 1) {
		EMRPOLYPOLYGON* new_instance = new EMRPOLYPOLYGON(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_POLYPOLYGON }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x2c }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(nPolys, ::g->nPolys.generate({ 1 }));
	GENERATE_VAR(cntPoints, ::g->cntPoints.generate({ 1 }));
	GENERATE_VAR(aPolyCounts, ::g->aPolyCounts.generate({ 1 }));
	GENERATE_VAR(aPoints, ::g->aPoints.generate(cntPoints()));

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
	GENERATE_VAR(Reserved, ::g->Reserved.generate({ 0 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRSETPIXELV* EMRSETPIXELV::generate() {
	if (generated == 1) {
		EMRSETPIXELV* new_instance = new EMRSETPIXELV(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_SETPIXELV }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x14 }));
	GENERATE_VAR(ptlPixel, ::g->ptlPixel.generate());
	GENERATE_VAR(crColor, ::g->crColor.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMROFFSETCLIPRGN* EMROFFSETCLIPRGN::generate() {
	if (generated == 1) {
		EMROFFSETCLIPRGN* new_instance = new EMROFFSETCLIPRGN(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_OFFSETCLIPRGN }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x10 }));
	GENERATE_VAR(offset, ::g->offset.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMREXCLUDECLIPRECT* EMREXCLUDECLIPRECT::generate() {
	if (generated == 1) {
		EMREXCLUDECLIPRECT* new_instance = new EMREXCLUDECLIPRECT(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_EXCLUDECLIPRECT }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x18 }));
	GENERATE_VAR(rclClip, ::g->rclClip.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRINTERSECTCLIPRECT* EMRINTERSECTCLIPRECT::generate() {
	if (generated == 1) {
		EMRINTERSECTCLIPRECT* new_instance = new EMRINTERSECTCLIPRECT(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_INTERSECTCLIPRECT }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x18 }));
	GENERATE_VAR(rclClip, ::g->rclClip.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRSELECTOBJECT* EMRSELECTOBJECT::generate() {
	if (generated == 1) {
		EMRSELECTOBJECT* new_instance = new EMRSELECTOBJECT(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_SELECTOBJECT }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0xc }));
	GENERATE_VAR(ihObject, ::g->ihObject.generate({ 1 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


LOGPEN* LOGPEN::generate() {
	if (generated == 1) {
		LOGPEN* new_instance = new LOGPEN(instances);
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

	GENERATE_VAR(lopnStyle, ::g->lopnStyle.generate());
	GENERATE_VAR(lopnWidth, ::g->lopnWidth.generate());
	GENERATE_VAR(lopnColor, ::g->lopnColor.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRCREATEPEN* EMRCREATEPEN::generate() {
	if (generated == 1) {
		EMRCREATEPEN* new_instance = new EMRCREATEPEN(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_CREATEPEN }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x1c }));
	GENERATE_VAR(ihPen, ::g->ihPen.generate());
	GENERATE_VAR(lopn, ::g->lopn.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


LogBrushEx* LogBrushEx::generate() {
	if (generated == 1) {
		LogBrushEx* new_instance = new LogBrushEx(instances);
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

	GENERATE_VAR(lbStyle, BrushStyle_generate());
	GENERATE_VAR(lbColor, ::g->lbColor.generate());
	GENERATE_VAR(lbHatch, ::g->lbHatch.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRCREATEBRUSHINDIRECT* EMRCREATEBRUSHINDIRECT::generate() {
	if (generated == 1) {
		EMRCREATEBRUSHINDIRECT* new_instance = new EMRCREATEBRUSHINDIRECT(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_CREATEBRUSHINDIRECT }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x18 }));
	GENERATE_VAR(ihBrush, ::g->ihBrush.generate());
	GENERATE_VAR(LogBrush, ::g->LogBrush.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRDELETEOBJECT* EMRDELETEOBJECT::generate() {
	if (generated == 1) {
		EMRDELETEOBJECT* new_instance = new EMRDELETEOBJECT(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_DELETEOBJECT }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0xc }));
	GENERATE_VAR(ihCS, ::g->ihCS.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRANGLEARC* EMRANGLEARC::generate() {
	if (generated == 1) {
		EMRANGLEARC* new_instance = new EMRANGLEARC(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_ANGLEARC }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x1c }));
	GENERATE_VAR(ptlCenter, ::g->ptlCenter.generate());
	GENERATE_VAR(nRadius, ::g->nRadius.generate());
	GENERATE_VAR(eStartAngle, ::g->eStartAngle.generate());
	GENERATE_VAR(eSweepAngle, ::g->eSweepAngle.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRELLIPSE* EMRELLIPSE::generate() {
	if (generated == 1) {
		EMRELLIPSE* new_instance = new EMRELLIPSE(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_ELLIPSE }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x18 }));
	GENERATE_VAR(rclBox, ::g->rclBox.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRRECTANGLE* EMRRECTANGLE::generate() {
	if (generated == 1) {
		EMRRECTANGLE* new_instance = new EMRRECTANGLE(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_RECTANGLE }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x18 }));
	GENERATE_VAR(rclBox, ::g->rclBox.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRROUNDRECT* EMRROUNDRECT::generate() {
	if (generated == 1) {
		EMRROUNDRECT* new_instance = new EMRROUNDRECT(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_ROUNDRECT }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x20 }));
	GENERATE_VAR(rclBox, ::g->rclBox.generate());
	GENERATE_VAR(szlCorner, ::g->szlCorner.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRARC* EMRARC::generate() {
	if (generated == 1) {
		EMRARC* new_instance = new EMRARC(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_ARC }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x28 }));
	GENERATE_VAR(rclBox, ::g->rclBox.generate());
	GENERATE_VAR(ptlStart, ::g->ptlStart.generate());
	GENERATE_VAR(ptlEnd, ::g->ptlEnd.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRCHORD* EMRCHORD::generate() {
	if (generated == 1) {
		EMRCHORD* new_instance = new EMRCHORD(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_CHORD }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x28 }));
	GENERATE_VAR(rclBox, ::g->rclBox.generate());
	GENERATE_VAR(ptlStart, ::g->ptlStart.generate());
	GENERATE_VAR(ptlEnd, ::g->ptlEnd.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRPIE* EMRPIE::generate() {
	if (generated == 1) {
		EMRPIE* new_instance = new EMRPIE(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_PIE }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x28 }));
	GENERATE_VAR(box, ::g->box.generate());
	GENERATE_VAR(start, ::g->start.generate());
	GENERATE_VAR(stop, ::g->stop.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRSELECTPALETTE* EMRSELECTPALETTE::generate() {
	if (generated == 1) {
		EMRSELECTPALETTE* new_instance = new EMRSELECTPALETTE(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_SELECTPALETTE }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0xc }));
	GENERATE_VAR(ihPal, ::g->ihPal.generate({ DEFAULT_PALETTE }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


LOGPALETTEENTRY* LOGPALETTEENTRY::generate() {
	if (generated == 1) {
		LOGPALETTEENTRY* new_instance = new LOGPALETTEENTRY(instances);
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


LOGPALETTE* LOGPALETTE::generate() {
	if (generated == 1) {
		LOGPALETTE* new_instance = new LOGPALETTE(instances);
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

	GENERATE_VAR(palVersion, ::g->palVersion.generate({ 0x0300 }));
	GENERATE_VAR(palNumEntries, ::g->palNumEntries.generate({ 1 }));
	GENERATE_VAR(palPalEntry, ::g->palPalEntry.generate(palNumEntries()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRCREATEPALETTE* EMRCREATEPALETTE::generate() {
	if (generated == 1) {
		EMRCREATEPALETTE* new_instance = new EMRCREATEPALETTE(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_CREATEPALETTE }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x14 }));
	GENERATE_VAR(ihPal, ::g->ihPal.generate());
	GENERATE_VAR(lgpl, ::g->lgpl.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRSETPALETTEENTRIES* EMRSETPALETTEENTRIES::generate() {
	if (generated == 1) {
		EMRSETPALETTEENTRIES* new_instance = new EMRSETPALETTEENTRIES(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_SETPALETTEENTRIES }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x18 }));
	GENERATE_VAR(ihPal, ::g->ihPal.generate());
	GENERATE_VAR(iStart, ::g->iStart.generate());
	GENERATE_VAR(cEntries, ::g->cEntries.generate({ 1 }));
	GENERATE_VAR(aPalEntries, ::g->aPalEntries.generate(cEntries()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRRESIZEPALETTE* EMRRESIZEPALETTE::generate() {
	if (generated == 1) {
		EMRRESIZEPALETTE* new_instance = new EMRRESIZEPALETTE(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_RESIZEPALETTE }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x10 }));
	GENERATE_VAR(ihPal, ::g->ihPal.generate());
	GENERATE_VAR(NumberOfEntries, ::g->NumberOfEntries.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMREXTFLOODFILL* EMREXTFLOODFILL::generate() {
	if (generated == 1) {
		EMREXTFLOODFILL* new_instance = new EMREXTFLOODFILL(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_EXTFLOODFILL }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x18 }));
	GENERATE_VAR(ptlStart, ::g->ptlStart.generate());
	GENERATE_VAR(crColor, ::g->crColor.generate());
	GENERATE_VAR(iMode, ::g->iMode.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRLINETO* EMRLINETO::generate() {
	if (generated == 1) {
		EMRLINETO* new_instance = new EMRLINETO(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_LINETO }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x10 }));
	GENERATE_VAR(ptl, ::g->ptl.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRARCTO* EMRARCTO::generate() {
	if (generated == 1) {
		EMRARCTO* new_instance = new EMRARCTO(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_ARCTO }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x28 }));
	GENERATE_VAR(rclBox, ::g->rclBox.generate());
	GENERATE_VAR(ptlStart, ::g->ptlStart.generate());
	GENERATE_VAR(ptlEnd, ::g->ptlEnd.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRPOLYDRAW* EMRPOLYDRAW::generate() {
	if (generated == 1) {
		EMRPOLYDRAW* new_instance = new EMRPOLYDRAW(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_POLYDRAW }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x1c }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(cntPoints, ::g->cntPoints.generate({ 1 }));
	GENERATE_VAR(aPoints, ::g->aPoints.generate(cntPoints()));
	GENERATE_VAR(abTypes, ::g->abTypes.generate(cntPoints()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRBEGINPATH* EMRBEGINPATH::generate() {
	if (generated == 1) {
		EMRBEGINPATH* new_instance = new EMRBEGINPATH(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_BEGINPATH }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 8 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRENDPATH* EMRENDPATH::generate() {
	if (generated == 1) {
		EMRENDPATH* new_instance = new EMRENDPATH(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_ENDPATH }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 8 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRCLOSEFIGURE* EMRCLOSEFIGURE::generate() {
	if (generated == 1) {
		EMRCLOSEFIGURE* new_instance = new EMRCLOSEFIGURE(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_CLOSEFIGURE }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 8 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRFILLPATH* EMRFILLPATH::generate() {
	if (generated == 1) {
		EMRFILLPATH* new_instance = new EMRFILLPATH(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_FILLPATH }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x18 }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRSTROKEANDFILLPATH* EMRSTROKEANDFILLPATH::generate() {
	if (generated == 1) {
		EMRSTROKEANDFILLPATH* new_instance = new EMRSTROKEANDFILLPATH(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_STROKEANDFILLPATH }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x14 }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRSTROKEPATH* EMRSTROKEPATH::generate() {
	if (generated == 1) {
		EMRSTROKEPATH* new_instance = new EMRSTROKEPATH(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_STROKEPATH }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x18 }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRFLATTENPATH* EMRFLATTENPATH::generate() {
	if (generated == 1) {
		EMRFLATTENPATH* new_instance = new EMRFLATTENPATH(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_FLATTENPATH }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 8 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRWIDENPATH* EMRWIDENPATH::generate() {
	if (generated == 1) {
		EMRWIDENPATH* new_instance = new EMRWIDENPATH(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_WIDENPATH }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 8 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRSELECTCLIPPATH* EMRSELECTCLIPPATH::generate() {
	if (generated == 1) {
		EMRSELECTCLIPPATH* new_instance = new EMRSELECTCLIPPATH(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_SELECTCLIPPATH }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0xc }));
	GENERATE_VAR(rgnMode, RegionMode_generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRABORTPATH* EMRABORTPATH::generate() {
	if (generated == 1) {
		EMRABORTPATH* new_instance = new EMRABORTPATH(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_ABORTPATH }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 8 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRCOMMENT* EMRCOMMENT::generate() {
	if (generated == 1) {
		EMRCOMMENT* new_instance = new EMRCOMMENT(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_COMMENT }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0xc }));
	GENERATE_VAR(dataSize, ::g->dataSize.generate({ 1 }));
	GENERATE_VAR(privateData, ::g->privateData.generate(dataSize()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


REGIONDATAHEADER* REGIONDATAHEADER::generate() {
	if (generated == 1) {
		REGIONDATAHEADER* new_instance = new REGIONDATAHEADER(instances);
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

	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x20 }));
	GENERATE_VAR(iType, ::g->iType.generate({ 1 }));
	GENERATE_VAR(cntRects, ::g->cntRects.generate({ 1 }));
	GENERATE_VAR(rgnSize, ::g->rgnSize.generate());
	GENERATE_VAR(rgnBounds, ::g->rgnBounds.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


REGIONDATA* REGIONDATA::generate() {
	if (generated == 1) {
		REGIONDATA* new_instance = new REGIONDATA(instances);
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

	GENERATE_VAR(rgnDataHeader, ::g->rgnDataHeader.generate());
	GENERATE_VAR(data, ::g->data.generate(rgnDataHeader().cntRects()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRFILLRGN* EMRFILLRGN::generate() {
	if (generated == 1) {
		EMRFILLRGN* new_instance = new EMRFILLRGN(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_FILLRGN }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x50 }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(rgnDataSize, ::g->rgnDataSize.generate({ 0x30 }));
	GENERATE_VAR(ihBrush, ::g->ihBrush.generate());
	GENERATE_VAR(rgnData, ::g->rgnData.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRFRAMERGN* EMRFRAMERGN::generate() {
	if (generated == 1) {
		EMRFRAMERGN* new_instance = new EMRFRAMERGN(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_FRAMERGN }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x58 }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(rgnDataSize, ::g->rgnDataSize.generate({ 0x30 }));
	GENERATE_VAR(ihBrush, ::g->ihBrush.generate());
	GENERATE_VAR(width, ::g->width.generate());
	GENERATE_VAR(height, ::g->height.generate());
	GENERATE_VAR(rgnData, ::g->rgnData.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRINVERTRGN* EMRINVERTRGN::generate() {
	if (generated == 1) {
		EMRINVERTRGN* new_instance = new EMRINVERTRGN(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_INVERTRGN }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x3c }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(nRgnDataSize, ::g->nRgnDataSize.generate({ 0x20 }));
	GENERATE_VAR(rgnData, ::g->rgnData_.generate(nRgnDataSize()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRPAINTRGN* EMRPAINTRGN::generate() {
	if (generated == 1) {
		EMRPAINTRGN* new_instance = new EMRPAINTRGN(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_PAINTRGN }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x4c }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(rgnDataSize, ::g->rgnDataSize.generate({ 0x30 }));
	GENERATE_VAR(rgnData, ::g->rgnData.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMREXTSELECTCLIPRGN* EMREXTSELECTCLIPRGN::generate() {
	if (generated == 1) {
		EMREXTSELECTCLIPRGN* new_instance = new EMREXTSELECTCLIPRGN(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_EXTSELECTCLIPRGN }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x40 }));
	GENERATE_VAR(rgnDataSize, ::g->rgnDataSize.generate({ 0x30 }));
	GENERATE_VAR(rgnMode, RegionMode_generate());
	GENERATE_VAR(rgnData, ::g->rgnData.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


XFORM* XFORM::generate() {
	if (generated == 1) {
		XFORM* new_instance = new XFORM(instances);
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

	GENERATE_VAR(eM11, ::g->eM11.generate());
	GENERATE_VAR(eM12, ::g->eM12.generate());
	GENERATE_VAR(eM21, ::g->eM21.generate());
	GENERATE_VAR(eM22, ::g->eM22.generate());
	GENERATE_VAR(eDx, ::g->eDx.generate());
	GENERATE_VAR(eDy, ::g->eDy.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


BITMAPINFOHEADER* BITMAPINFOHEADER::generate() {
	if (generated == 1) {
		BITMAPINFOHEADER* new_instance = new BITMAPINFOHEADER(instances);
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

	GENERATE_VAR(biSize, ::g->biSize.generate({ 0x28 }));
	GENERATE_VAR(biWidth, ::g->biWidth.generate());
	GENERATE_VAR(biHeight, ::g->biHeight.generate());
	GENERATE_VAR(biPlanes, ::g->biPlanes.generate({ 1 }));
	GENERATE_VAR(biBitCount, BitCount_generate({ 1 }));
	if ((biBitCount() == BI_BITCOUNT_1)) {
		GENERATE_VAR(biCompression, ::g->biCompression.generate({ BI_RGB }));
	} else {
	if ((biBitCount() == BI_BITCOUNT_2)) {
		GENERATE_VAR(biCompression, ::g->biCompression.generate({ BI_RLE4 }));
	} else {
	if ((biBitCount() == BI_BITCOUNT_3)) {
		GENERATE_VAR(biCompression, ::g->biCompression.generate({ BI_RLE8 }));
	} else {
	if ((biBitCount() == BI_BITCOUNT_4)) {
		GENERATE_VAR(biCompression, ::g->biCompression.generate({ BI_BITFIELDS }));
	} else {
	if ((biBitCount() == BI_BITCOUNT_5)) {
		GENERATE_VAR(biCompression, ::g->biCompression.generate({ BI_RGB }));
	} else {
	if ((biBitCount() == BI_BITCOUNT_6)) {
		GENERATE_VAR(biCompression, ::g->biCompression.generate({ BI_RGB }));
	};
	};
	};
	};
	};
	};
	if ((biCompression() == BI_RGB)) {
		GENERATE_VAR(biSizeImage, ::g->biSizeImage.generate({ 0 }));
	} else {
		GENERATE_VAR(biSizeImage, ::g->biSizeImage.generate());
	};
	GENERATE_VAR(biXPelsPerMeter, ::g->biXPelsPerMeter.generate());
	GENERATE_VAR(biYPelsPerMeter, ::g->biYPelsPerMeter.generate());
	switch (biBitCount()) {
	case 8:
		GENERATE_VAR(biClrUsed, ::g->biClrUsed.generate());
		break;
	case 4:
		GENERATE_VAR(biClrUsed, ::g->biClrUsed.generate({ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 }));
		break;
	case 2:
		GENERATE_VAR(biClrUsed, ::g->biClrUsed.generate({ 0, 1, 2, 3, 4 }));
		break;
	case 1:
		GENERATE_VAR(biClrUsed, ::g->biClrUsed.generate({ 0, 1, 2 }));
		break;
	default:
		GENERATE_VAR(biClrUsed, ::g->biClrUsed.generate({ 0 }));
	};
	GENERATE_VAR(biClrImportant, ::g->biClrImportant.generate({ 0 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


RGBQUAD* RGBQUAD::generate() {
	if (generated == 1) {
		RGBQUAD* new_instance = new RGBQUAD(instances);
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

	GENERATE_VAR(rgbBlue, ::g->rgbBlue.generate());
	GENERATE_VAR(rgbGreen, ::g->rgbGreen.generate());
	GENERATE_VAR(rgbRed, ::g->rgbRed.generate());
	GENERATE_VAR(rgbReserved, ::g->rgbReserved.generate({ 0 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


BITMAPINFO* BITMAPINFO::generate() {
	if (generated == 1) {
		BITMAPINFO* new_instance = new BITMAPINFO(instances);
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

	GENERATE_VAR(bmiHeader, ::g->bmiHeader.generate());
	if ((bmiHeader().biBitCount() == BI_BITCOUNT_1)) {
		GENERATE_VAR(bmiColors, ::g->bmiColors.generate(2));
	} else {
	if ((bmiHeader().biBitCount() == BI_BITCOUNT_2)) {
		GENERATE_VAR(bmiColors, ::g->bmiColors.generate(16));
	} else {
	if ((bmiHeader().biBitCount() == BI_BITCOUNT_3)) {
		GENERATE_VAR(bmiColors, ::g->bmiColors.generate(256));
	} else {
	if ((bmiHeader().biBitCount() == BI_BITCOUNT_4)) {
		GENERATE_VAR(bmiColors, ::g->bmiColors.generate(1));
	} else {
	if ((bmiHeader().biBitCount() == BI_BITCOUNT_5)) {
		GENERATE_VAR(bmiColors, ::g->bmiColors.generate(1));
	} else {
	if ((bmiHeader().biBitCount() == BI_BITCOUNT_6)) {
		if ((bmiHeader().biCompression() == BI_RGB)) {
			GENERATE_VAR(bmiColors, ::g->bmiColors.generate(1));
		} else {
		if ((bmiHeader().biCompression() == BI_BITFIELDS)) {
			GENERATE_VAR(bmiColors, ::g->bmiColors.generate(3));
		};
		};
	};
	};
	};
	};
	};
	};

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRBITBLT* EMRBITBLT::generate() {
	if (generated == 1) {
		EMRBITBLT* new_instance = new EMRBITBLT(instances);
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

	emrSize = 0x64;
	bmiSize = 0x30;
	emrOffset = FTell();
	FSeek(emrOffset);
	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_BITBLT }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ emrSize }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(xDest, ::g->xDest.generate());
	GENERATE_VAR(yDest, ::g->yDest.generate());
	GENERATE_VAR(cxDest, ::g->cxDest.generate());
	GENERATE_VAR(cyDest, ::g->cyDest.generate());
	GENERATE_VAR(BitBltRasterOperation, ::g->BitBltRasterOperation.generate({ 0x00CC0020 }));
	GENERATE_VAR(xSrc, ::g->xSrc.generate());
	GENERATE_VAR(ySrc, ::g->ySrc.generate());
	GENERATE_VAR(xformSrc, ::g->xformSrc.generate());
	GENERATE_VAR(BkColorSrc, ::g->BkColorSrc.generate());
	GENERATE_VAR(iUsageSrc, DIBColors_generate());
	GENERATE_VAR(offBmiSrc, ::g->offBmiSrc.generate({ emrSize }));
	GENERATE_VAR(cbBmiSrc, ::g->cbBmiSrc.generate({ bmiSize }));
	GENERATE_VAR(offBitsSrc, ::g->offBitsSrc.generate({ (emrSize + bmiSize) }));
	GENERATE_VAR(cbBitsSrc, ::g->cbBitsSrc.generate({ 4 }));
	GENERATE_VAR(BmiSrc, ::g->BmiSrc.generate());
	GENERATE_VAR(BitsSrc, ::g->BitsSrc.generate(cbBitsSrc()));
	end = FTell();
	FSeek((emrOffset + 4));
	GENERATE_VAR(nSize, ::g->nSize.generate({ ((emrSize + bmiSize) + cbBitsSrc()) }));
	FSeek(end);

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRSTRETCHBLT* EMRSTRETCHBLT::generate() {
	if (generated == 1) {
		EMRSTRETCHBLT* new_instance = new EMRSTRETCHBLT(instances);
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

	emrSize = 0x6c;
	bmiSize = 0x30;
	emrOffset = FTell();
	FSeek(emrOffset);
	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_STRETCHBLT }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ emrSize }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(xDest, ::g->xDest_.generate());
	GENERATE_VAR(yDest, ::g->yDest_.generate());
	GENERATE_VAR(cxDest, ::g->cxDest_.generate());
	GENERATE_VAR(cyDest, ::g->cyDest_.generate());
	GENERATE_VAR(dwRop, ::g->dwRop.generate());
	GENERATE_VAR(xSrc, ::g->xSrc_.generate());
	GENERATE_VAR(ySrc, ::g->ySrc_.generate());
	GENERATE_VAR(xformSrc, ::g->xformSrc.generate());
	GENERATE_VAR(crBkColorSrc, ::g->crBkColorSrc.generate());
	GENERATE_VAR(iUsageSrc, DIBColors_generate());
	GENERATE_VAR(offBmiSrc, ::g->offBmiSrc.generate({ emrSize }));
	GENERATE_VAR(cbBmiSrc, ::g->cbBmiSrc.generate({ bmiSize }));
	GENERATE_VAR(offBitsSrc, ::g->offBitsSrc.generate({ (emrSize + bmiSize) }));
	GENERATE_VAR(cbBitsSrc, ::g->cbBitsSrc.generate({ 4 }));
	GENERATE_VAR(cxSrc, ::g->cxSrc.generate());
	GENERATE_VAR(cySrc, ::g->cySrc.generate());
	GENERATE_VAR(BmiSrc, ::g->BmiSrc.generate());
	GENERATE_VAR(BitsSrc, ::g->BitsSrc.generate(cbBitsSrc()));
	end = FTell();
	FSeek((emrOffset + 4));
	GENERATE_VAR(nSize, ::g->nSize.generate({ ((emrSize + bmiSize) + cbBitsSrc()) }));
	FSeek(end);

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRMASKBLT* EMRMASKBLT::generate() {
	if (generated == 1) {
		EMRMASKBLT* new_instance = new EMRMASKBLT(instances);
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

	emrSize = 0x80;
	bmiSize = 0x30;
	emrOffset = FTell();
	FSeek(emrOffset);
	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_MASKBLT }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ emrSize }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(xDest, ::g->xDest_.generate());
	GENERATE_VAR(yDest, ::g->yDest_.generate());
	GENERATE_VAR(cxDest, ::g->cxDest_.generate());
	GENERATE_VAR(cyDest, ::g->cyDest_.generate());
	GENERATE_VAR(dwRop, ::g->dwRop.generate());
	GENERATE_VAR(xSrc, ::g->xSrc_.generate());
	GENERATE_VAR(ySrc, ::g->ySrc_.generate());
	GENERATE_VAR(xformSrc, ::g->xformSrc.generate());
	GENERATE_VAR(crBkColorSrc, ::g->crBkColorSrc.generate());
	GENERATE_VAR(iUsageSrc, DIBColors_generate());
	GENERATE_VAR(offBmiSrc, ::g->offBmiSrc.generate({ emrSize }));
	GENERATE_VAR(cbBmiSrc, ::g->cbBmiSrc.generate({ bmiSize }));
	GENERATE_VAR(offBitsSrc, ::g->offBitsSrc.generate({ (emrSize + bmiSize) }));
	GENERATE_VAR(cbBitsSrc, ::g->cbBitsSrc.generate({ 4 }));
	GENERATE_VAR(xMask, ::g->xMask.generate());
	GENERATE_VAR(yMask, ::g->yMask.generate());
	GENERATE_VAR(iUsageMask, ::g->iUsageMask.generate());
	GENERATE_VAR(offBmiMask, ::g->offBmiMask.generate({ ((emrSize + bmiSize) + cbBitsSrc()) }));
	GENERATE_VAR(cbBmiMask, ::g->cbBmiMask.generate({ bmiSize }));
	GENERATE_VAR(offBitsMask, ::g->offBitsMask.generate({ (((emrSize + bmiSize) + cbBitsSrc()) + bmiSize) }));
	GENERATE_VAR(cbBitsMask, ::g->cbBitsMask.generate({ 4 }));
	GENERATE_VAR(BmiSrc, ::g->BmiSrc.generate());
	GENERATE_VAR(BitsSrc, ::g->BitsSrc.generate(cbBitsSrc()));
	GENERATE_VAR(BmiMask, ::g->BmiMask.generate());
	GENERATE_VAR(BitsMask, ::g->BitsMask.generate(cbBitsMask()));
	end = FTell();
	FSeek((emrOffset + 4));
	GENERATE_VAR(nSize, ::g->nSize.generate({ ((((emrSize + bmiSize) + cbBitsSrc()) + bmiSize) + cbBitsMask()) }));
	FSeek(end);

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRPLGBLT* EMRPLGBLT::generate() {
	if (generated == 1) {
		EMRPLGBLT* new_instance = new EMRPLGBLT(instances);
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

	emrSize = 0x8c;
	bmiSize = 0x30;
	emrOffset = FTell();
	FSeek(emrOffset);
	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_PLGBLT }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ emrSize }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(aptlDest, ::g->aptlDest.generate(3));
	GENERATE_VAR(xSrc, ::g->xSrc_.generate());
	GENERATE_VAR(ySrc, ::g->ySrc_.generate());
	GENERATE_VAR(cxSrc, ::g->cxSrc.generate());
	GENERATE_VAR(cySrc, ::g->cySrc.generate());
	GENERATE_VAR(xformSrc, ::g->xformSrc.generate());
	GENERATE_VAR(crBkColorSrc, ::g->crBkColorSrc.generate());
	GENERATE_VAR(iUsageSrc, DIBColors_generate());
	GENERATE_VAR(offBmiSrc, ::g->offBmiSrc.generate({ emrSize }));
	GENERATE_VAR(cbBmiSrc, ::g->cbBmiSrc.generate({ bmiSize }));
	GENERATE_VAR(offBitsSrc, ::g->offBitsSrc.generate({ (emrSize + bmiSize) }));
	GENERATE_VAR(cbBitsSrc, ::g->cbBitsSrc.generate({ 4 }));
	GENERATE_VAR(xMask, ::g->xMask.generate());
	GENERATE_VAR(yMask, ::g->yMask.generate());
	GENERATE_VAR(iUsageMask, ::g->iUsageMask.generate());
	GENERATE_VAR(offBmiMask, ::g->offBmiMask.generate({ ((emrSize + bmiSize) + cbBitsSrc()) }));
	GENERATE_VAR(cbBmiMask, ::g->cbBmiMask.generate({ bmiSize }));
	GENERATE_VAR(offBitsMask, ::g->offBitsMask.generate({ (((emrSize + bmiSize) + cbBitsSrc()) + bmiSize) }));
	GENERATE_VAR(cbBitsMask, ::g->cbBitsMask.generate({ 4 }));
	GENERATE_VAR(BmiSrc, ::g->BmiSrc.generate());
	GENERATE_VAR(BitsSrc, ::g->BitsSrc.generate(cbBitsSrc()));
	GENERATE_VAR(BmiMask, ::g->BmiMask.generate());
	GENERATE_VAR(BitsMask, ::g->BitsMask.generate(cbBitsMask()));
	end = FTell();
	FSeek((emrOffset + 4));
	GENERATE_VAR(nSize, ::g->nSize.generate({ ((((emrSize + bmiSize) + cbBitsSrc()) + bmiSize) + cbBitsMask()) }));
	FSeek(end);

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRSETDIBITSTODEVICE* EMRSETDIBITSTODEVICE::generate() {
	if (generated == 1) {
		EMRSETDIBITSTODEVICE* new_instance = new EMRSETDIBITSTODEVICE(instances);
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

	emrSize = 0x4c;
	bmiSize = 0x30;
	emrOffset = FTell();
	FSeek(emrOffset);
	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_SETDIBITSTODEVICE }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ emrSize }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(xDest, ::g->xDest.generate());
	GENERATE_VAR(yDest, ::g->yDest.generate());
	GENERATE_VAR(xSrc, ::g->xSrc.generate());
	GENERATE_VAR(ySrc, ::g->ySrc.generate());
	GENERATE_VAR(cxSrc, ::g->cxSrc_.generate());
	GENERATE_VAR(cySrc, ::g->cySrc_.generate());
	GENERATE_VAR(offBmiSrc, ::g->offBmiSrc.generate({ emrSize }));
	GENERATE_VAR(cbBmiSrc, ::g->cbBmiSrc.generate({ bmiSize }));
	GENERATE_VAR(offBitsSrc, ::g->offBitsSrc.generate({ (emrSize + bmiSize) }));
	GENERATE_VAR(cbBitsSrc, ::g->cbBitsSrc.generate({ 4 }));
	GENERATE_VAR(iUsageSrc, DIBColors_generate());
	GENERATE_VAR(iStartScan, ::g->iStartScan.generate());
	GENERATE_VAR(cScans, ::g->cScans.generate());
	GENERATE_VAR(BmiSrc, ::g->BmiSrc.generate());
	GENERATE_VAR(BitsSrc, ::g->BitsSrc.generate(cbBitsSrc()));
	end = FTell();
	FSeek((emrOffset + 4));
	GENERATE_VAR(nSize, ::g->nSize.generate({ ((emrSize + bmiSize) + cbBitsSrc()) }));
	FSeek(end);

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRSTRETCHDIBITS* EMRSTRETCHDIBITS::generate() {
	if (generated == 1) {
		EMRSTRETCHDIBITS* new_instance = new EMRSTRETCHDIBITS(instances);
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

	emrSize = 0x50;
	bmiSize = 0x30;
	emrOffset = FTell();
	FSeek(emrOffset);
	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_STRETCHDIBITS }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ emrSize }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(xDest, ::g->xDest.generate());
	GENERATE_VAR(yDest, ::g->yDest.generate());
	GENERATE_VAR(xSrc, ::g->xSrc.generate());
	GENERATE_VAR(ySrc, ::g->ySrc.generate());
	GENERATE_VAR(cxSrc, ::g->cxSrc_.generate());
	GENERATE_VAR(cySrc, ::g->cySrc_.generate());
	GENERATE_VAR(offBmiSrc, ::g->offBmiSrc.generate({ emrSize }));
	GENERATE_VAR(cbBmiSrc, ::g->cbBmiSrc.generate({ bmiSize }));
	GENERATE_VAR(offBitsSrc, ::g->offBitsSrc.generate({ (emrSize + bmiSize) }));
	GENERATE_VAR(cbBitsSrc, ::g->cbBitsSrc.generate({ 4 }));
	GENERATE_VAR(iUsageSrc, DIBColors_generate());
	GENERATE_VAR(dwRop, ::g->dwRop.generate());
	GENERATE_VAR(cxDest, ::g->cxDest.generate());
	GENERATE_VAR(cyDest, ::g->cyDest.generate());
	GENERATE_VAR(BmiSrc, ::g->BmiSrc.generate());
	GENERATE_VAR(BitsSrc, ::g->BitsSrc.generate(cbBitsSrc()));
	end = FTell();
	FSeek((emrOffset + 4));
	GENERATE_VAR(nSize, ::g->nSize.generate({ ((emrSize + bmiSize) + cbBitsSrc()) }));
	FSeek(end);

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRTEXT* EMRTEXT::generate() {
	if (generated == 1) {
		EMRTEXT* new_instance = new EMRTEXT(instances);
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

	GENERATE_VAR(ptlReference, ::g->ptlReference.generate());
	GENERATE_VAR(nChars, ::g->nChars.generate({ 0x4 }));
	GENERATE_VAR(offString, ::g->offString.generate({ 0x2c }));
	GENERATE_VAR(fOptions, ::g->fOptions.generate());
	GENERATE_VAR(rcl, ::g->rcl.generate());
	GENERATE_VAR(offDx, ::g->offDx.generate({ 0x0 }));
	GENERATE_VAR(bStringBuffer, ::g->bStringBuffer.generate(nChars()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMREXTTEXTOUTA* EMREXTTEXTOUTA::generate() {
	if (generated == 1) {
		EMREXTTEXTOUTA* new_instance = new EMREXTTEXTOUTA(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_EXTTEXTOUTA }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x4c }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(iGraphicsMode, ::g->iGraphicsMode.generate());
	GENERATE_VAR(exScale, ::g->exScale.generate());
	GENERATE_VAR(eyScale, ::g->eyScale.generate());
	GENERATE_VAR(emrtext, ::g->emrtext.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRCREATEMONOBRUSH* EMRCREATEMONOBRUSH::generate() {
	if (generated == 1) {
		EMRCREATEMONOBRUSH* new_instance = new EMRCREATEMONOBRUSH(instances);
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

	emrSize = 0x20;
	bmiSize = 0x30;
	emrOffset = FTell();
	FSeek(emrOffset);
	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_CREATEMONOBRUSH }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ emrSize }));
	GENERATE_VAR(ihBrush, ::g->ihBrush.generate());
	GENERATE_VAR(iUsage, ::g->iUsage.generate());
	GENERATE_VAR(offBmi, ::g->offBmi.generate({ emrSize }));
	GENERATE_VAR(cbBmi, ::g->cbBmi.generate({ bmiSize }));
	GENERATE_VAR(offBits, ::g->offBits.generate({ (emrSize + bmiSize) }));
	GENERATE_VAR(cbBits, ::g->cbBits.generate({ 4 }));
	GENERATE_VAR(BmiSrc, ::g->BmiSrc.generate());
	GENERATE_VAR(BitsSrc, ::g->BitsSrc.generate(cbBits()));
	end = FTell();
	FSeek((emrOffset + 4));
	GENERATE_VAR(nSize, ::g->nSize.generate({ ((emrSize + bmiSize) + cbBits()) }));
	FSeek(end);

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRCREATEDIBPATTERNBRUSHPT* EMRCREATEDIBPATTERNBRUSHPT::generate() {
	if (generated == 1) {
		EMRCREATEDIBPATTERNBRUSHPT* new_instance = new EMRCREATEDIBPATTERNBRUSHPT(instances);
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

	emrSize = 0x20;
	bmiSize = 0x30;
	emrOffset = FTell();
	FSeek(emrOffset);
	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_CREATEDIBPATTERNBRUSHPT }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ emrSize }));
	GENERATE_VAR(ihBrush, ::g->ihBrush.generate());
	GENERATE_VAR(iUsage, ::g->iUsage.generate());
	GENERATE_VAR(offBmi, ::g->offBmi.generate({ emrSize }));
	GENERATE_VAR(cbBmi, ::g->cbBmi.generate({ bmiSize }));
	GENERATE_VAR(offBits, ::g->offBits.generate({ (emrSize + bmiSize) }));
	GENERATE_VAR(cbBits, ::g->cbBits.generate({ 4 }));
	GENERATE_VAR(BmiSrc, ::g->BmiSrc.generate());
	GENERATE_VAR(BitsSrc, ::g->BitsSrc.generate(cbBits()));
	end = FTell();
	FSeek((emrOffset + 4));
	GENERATE_VAR(nSize, ::g->nSize.generate({ ((emrSize + bmiSize) + cbBits()) }));
	FSeek(end);

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


LOGPENEX* LOGPENEX::generate() {
	if (generated == 1) {
		LOGPENEX* new_instance = new LOGPENEX(instances);
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

	GENERATE_VAR(PenStyle, ::g->PenStyle.generate());
	GENERATE_VAR(Width, ::g->Width.generate());
	GENERATE_VAR(lbStyle, BrushStyle_generate());
	GENERATE_VAR(lbColor, ::g->lbColor.generate());
	GENERATE_VAR(lbHatch, ::g->lbHatch.generate());
	GENERATE_VAR(NumStyleEntries, ::g->NumStyleEntries.generate({ 2 }));
	GENERATE_VAR(StyleEntry, ::g->StyleEntry.generate(NumStyleEntries()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMREXTCREATEPEN* EMREXTCREATEPEN::generate() {
	if (generated == 1) {
		EMREXTCREATEPEN* new_instance = new EMREXTCREATEPEN(instances);
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

	emrSize = 0x3c;
	bmiSize = 0x30;
	emrOffset = FTell();
	FSeek(emrOffset);
	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_EXTCREATEPEN }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ emrSize }));
	GENERATE_VAR(ihPen, ::g->ihPen.generate());
	GENERATE_VAR(offBmi, ::g->offBmi.generate({ emrSize }));
	GENERATE_VAR(cbBmi, ::g->cbBmi.generate({ bmiSize }));
	GENERATE_VAR(offBits, ::g->offBits.generate({ (emrSize + bmiSize) }));
	GENERATE_VAR(cbBits, ::g->cbBits.generate({ 4 }));
	GENERATE_VAR(elp, ::g->elp.generate());
	GENERATE_VAR(BmiSrc, ::g->BmiSrc.generate());
	GENERATE_VAR(BitsSrc, ::g->BitsSrc.generate(cbBits()));
	end = FTell();
	FSeek((emrOffset + 4));
	GENERATE_VAR(nSize, ::g->nSize.generate({ ((emrSize + bmiSize) + cbBits()) }));
	FSeek(end);

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRPOLYTEXTOUTA* EMRPOLYTEXTOUTA::generate() {
	if (generated == 1) {
		EMRPOLYTEXTOUTA* new_instance = new EMRPOLYTEXTOUTA(instances);
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

	emrOffset = FTell();
	FSeek(emrOffset);
	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_POLYTEXTOUTA }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x24 }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(iGraphicsMode, ::g->iGraphicsMode.generate());
	GENERATE_VAR(exScale, ::g->exScale.generate());
	GENERATE_VAR(eyScale, ::g->eyScale.generate());
	GENERATE_VAR(cStrings, ::g->cStrings.generate({ 0, 1 }));
	GENERATE_VAR(aemrtext, ::g->aemrtext.generate(cStrings()));
	end = FTell();
	FSeek((emrOffset + 4));
	GENERATE_VAR(nSize, ::g->nSize.generate({ (end - emrOffset) }));
	FSeek(end);

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CIEXYZ* CIEXYZ::generate() {
	if (generated == 1) {
		CIEXYZ* new_instance = new CIEXYZ(instances);
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

	GENERATE_VAR(ciexyzX, ::g->ciexyzX.generate());
	GENERATE_VAR(ciexyzY, ::g->ciexyzY.generate());
	GENERATE_VAR(ciexyzZ, ::g->ciexyzZ.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


CIEXYZTRIPLE* CIEXYZTRIPLE::generate() {
	if (generated == 1) {
		CIEXYZTRIPLE* new_instance = new CIEXYZTRIPLE(instances);
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

	GENERATE_VAR(ciexyzRed, ::g->ciexyzRed.generate());
	GENERATE_VAR(ciexyzGreen, ::g->ciexyzGreen.generate());
	GENERATE_VAR(ciexyzBlue, ::g->ciexyzBlue.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


LOGCOLORSPACEA* LOGCOLORSPACEA::generate() {
	if (generated == 1) {
		LOGCOLORSPACEA* new_instance = new LOGCOLORSPACEA(instances);
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

	GENERATE_VAR(lcsSignature, ::g->lcsSignature.generate({ 0x50534F43 }));
	GENERATE_VAR(lcsVersion, ::g->lcsVersion.generate({ 0x00000400 }));
	GENERATE_VAR(lcsSize, ::g->lcsSize.generate());
	GENERATE_VAR(lcsCSType, LogicalColorSpace_generate());
	GENERATE_VAR(lcsIntent, GamutMappingIntent_generate());
	GENERATE_VAR(lcsEndpoints, ::g->lcsEndpoints.generate());
	GENERATE_VAR(lcsGammaRed, ::g->lcsGammaRed.generate());
	GENERATE_VAR(lcsGammaGreen, ::g->lcsGammaGreen.generate());
	GENERATE_VAR(lcsGammaBlue, ::g->lcsGammaBlue.generate());
	GENERATE_VAR(lcsFilename, ::g->lcsFilename.generate(260));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRCREATECOLORSPACE* EMRCREATECOLORSPACE::generate() {
	if (generated == 1) {
		EMRCREATECOLORSPACE* new_instance = new EMRCREATECOLORSPACE(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_CREATECOLORSPACE }));
	GENERATE_VAR(ihCS, ::g->ihCS.generate({ 0x18 }));
	GENERATE_VAR(ics, ::g->ics.generate());
	GENERATE_VAR(lcs, ::g->lcs.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRSETCOLORSPACE* EMRSETCOLORSPACE::generate() {
	if (generated == 1) {
		EMRSETCOLORSPACE* new_instance = new EMRSETCOLORSPACE(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_SETCOLORSPACE }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0xc }));
	GENERATE_VAR(ihCS, ::g->ihCS.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRDELETECOLORSPACE* EMRDELETECOLORSPACE::generate() {
	if (generated == 1) {
		EMRDELETECOLORSPACE* new_instance = new EMRDELETECOLORSPACE(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_DELETECOLORSPACE }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0xc }));
	GENERATE_VAR(ihCS, ::g->ihCS.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRGLSRECORD* EMRGLSRECORD::generate() {
	if (generated == 1) {
		EMRGLSRECORD* new_instance = new EMRGLSRECORD(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_GLSRECORD }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x10 }));
	GENERATE_VAR(cbData, ::g->cbData.generate({ 4 }));
	GENERATE_VAR(Data, ::g->Data.generate(cbData()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRGLSBOUNDEDRECORD* EMRGLSBOUNDEDRECORD::generate() {
	if (generated == 1) {
		EMRGLSBOUNDEDRECORD* new_instance = new EMRGLSBOUNDEDRECORD(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_GLSBOUNDEDRECORD }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x20 }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(cbData, ::g->cbData.generate({ 4 }));
	GENERATE_VAR(Data, ::g->Data.generate(cbData()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRDRAWESCAPE* EMRDRAWESCAPE::generate() {
	if (generated == 1) {
		EMRDRAWESCAPE* new_instance = new EMRDRAWESCAPE(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_DRAWESCAPE }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x14 }));
	GENERATE_VAR(iEscape, MetafileEscapes_generate());
	GENERATE_VAR(cjln, ::g->cjln.generate({ 4 }));
	GENERATE_VAR(data, ::g->data_.generate(cjln()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMREXTESCAPE* EMREXTESCAPE::generate() {
	if (generated == 1) {
		EMREXTESCAPE* new_instance = new EMREXTESCAPE(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_EXTESCAPE }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x14 }));
	GENERATE_VAR(iEscape, MetafileEscapes_generate());
	GENERATE_VAR(cjln, ::g->cjln.generate({ 4 }));
	GENERATE_VAR(data, ::g->data_.generate(cjln()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRRESERVED107* EMRRESERVED107::generate() {
	if (generated == 1) {
		EMRRESERVED107* new_instance = new EMRRESERVED107(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_RESERVED_107 }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x28 }));
	GENERATE_VAR(ReservedData, ::g->ReservedData.generate(8));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


UniversalFontId* UniversalFontId::generate() {
	if (generated == 1) {
		UniversalFontId* new_instance = new UniversalFontId(instances);
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

	GENERATE_VAR(checksum, ::g->checksum.generate());
	GENERATE_VAR(index, ::g->index.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRFORCEUFIMAPPING* EMRFORCEUFIMAPPING::generate() {
	if (generated == 1) {
		EMRFORCEUFIMAPPING* new_instance = new EMRFORCEUFIMAPPING(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_FORCEUFIMAPPING }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x10 }));
	GENERATE_VAR(ufi, ::g->ufi.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRNAMEDESCAPE* EMRNAMEDESCAPE::generate() {
	if (generated == 1) {
		EMRNAMEDESCAPE* new_instance = new EMRNAMEDESCAPE(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_NAMEDESCAPE }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x18 }));
	GENERATE_VAR(iEscape, MetafileEscapes_generate());
	GENERATE_VAR(cjDriver, ::g->cjDriver.generate());
	GENERATE_VAR(cjln, ::g->cjln.generate({ 4 }));
	GENERATE_VAR(driverName, ::g->driverName.generate({ 0xFF00 }));
	GENERATE_VAR(data, ::g->data_.generate(cjln()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRCOLORCORRECTPALETTE* EMRCOLORCORRECTPALETTE::generate() {
	if (generated == 1) {
		EMRCOLORCORRECTPALETTE* new_instance = new EMRCOLORCORRECTPALETTE(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_COLORCORRECTPALETTE }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x18 }));
	GENERATE_VAR(ihPalette, ::g->ihPalette.generate());
	GENERATE_VAR(nFirstEntry, ::g->nFirstEntry.generate());
	GENERATE_VAR(nPalEntries, ::g->nPalEntries.generate());
	GENERATE_VAR(nReserved, ::g->nReserved.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


BLENDFUNCTION* BLENDFUNCTION::generate() {
	if (generated == 1) {
		BLENDFUNCTION* new_instance = new BLENDFUNCTION(instances);
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

	GENERATE_VAR(BlendOp, ::g->BlendOp.generate({ 0 }));
	GENERATE_VAR(BlendFlags, ::g->BlendFlags.generate({ 0 }));
	GENERATE_VAR(SourceConstantAlpha, ::g->SourceConstantAlpha.generate());
	GENERATE_VAR(AlphaFormat, ::g->AlphaFormat.generate({ 0, 1 }));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRALPHABLEND* EMRALPHABLEND::generate() {
	if (generated == 1) {
		EMRALPHABLEND* new_instance = new EMRALPHABLEND(instances);
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

	emrSize = 0x6c;
	bmiSize = 0x30;
	emrOffset = FTell();
	FSeek(emrOffset);
	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_ALPHABLEND }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ emrSize }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(xDest, ::g->xDest_.generate());
	GENERATE_VAR(yDest, ::g->yDest_.generate());
	GENERATE_VAR(cxDest, ::g->cxDest_.generate());
	GENERATE_VAR(cyDest, ::g->cyDest_.generate());
	GENERATE_VAR(dwRop, ::g->dwRop_.generate());
	GENERATE_VAR(xSrc, ::g->xSrc_.generate());
	GENERATE_VAR(ySrc, ::g->ySrc_.generate());
	GENERATE_VAR(xformSrc, ::g->xformSrc.generate());
	GENERATE_VAR(crBkColorSrc, ::g->crBkColorSrc.generate());
	GENERATE_VAR(iUsageSrc, DIBColors_generate());
	GENERATE_VAR(offBmiSrc, ::g->offBmiSrc.generate({ emrSize }));
	GENERATE_VAR(cbBmiSrc, ::g->cbBmiSrc.generate({ bmiSize }));
	GENERATE_VAR(offBitsSrc, ::g->offBitsSrc.generate({ (emrSize + bmiSize) }));
	GENERATE_VAR(cbBitsSrc, ::g->cbBitsSrc.generate({ 4 }));
	GENERATE_VAR(cxSrc, ::g->cxSrc.generate());
	GENERATE_VAR(cySrc, ::g->cySrc.generate());
	GENERATE_VAR(BmiSrc, ::g->BmiSrc.generate());
	GENERATE_VAR(BitsSrc, ::g->BitsSrc.generate(cbBitsSrc()));
	end = FTell();
	FSeek((emrOffset + 4));
	GENERATE_VAR(nSize, ::g->nSize.generate({ ((emrSize + bmiSize) + cbBitsSrc()) }));
	FSeek(end);

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRTRANSPARENTBLT* EMRTRANSPARENTBLT::generate() {
	if (generated == 1) {
		EMRTRANSPARENTBLT* new_instance = new EMRTRANSPARENTBLT(instances);
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

	emrSize = 0x6c;
	bmiSize = 0x30;
	emrOffset = FTell();
	FSeek(emrOffset);
	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_TRANSPARENTBLT }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ emrSize }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(xDest, ::g->xDest_.generate());
	GENERATE_VAR(yDest, ::g->yDest_.generate());
	GENERATE_VAR(cxDest, ::g->cxDest_.generate());
	GENERATE_VAR(cyDest, ::g->cyDest_.generate());
	GENERATE_VAR(dwRop, ::g->dwRop.generate());
	GENERATE_VAR(xSrc, ::g->xSrc_.generate());
	GENERATE_VAR(ySrc, ::g->ySrc_.generate());
	GENERATE_VAR(xformSrc, ::g->xformSrc.generate());
	GENERATE_VAR(crBkColorSrc, ::g->crBkColorSrc.generate());
	GENERATE_VAR(iUsageSrc, DIBColors_generate());
	GENERATE_VAR(offBmiSrc, ::g->offBmiSrc.generate({ emrSize }));
	GENERATE_VAR(cbBmiSrc, ::g->cbBmiSrc.generate({ bmiSize }));
	GENERATE_VAR(offBitsSrc, ::g->offBitsSrc.generate({ (emrSize + bmiSize) }));
	GENERATE_VAR(cbBitsSrc, ::g->cbBitsSrc.generate({ 4 }));
	GENERATE_VAR(cxSrc, ::g->cxSrc.generate());
	GENERATE_VAR(cySrc, ::g->cySrc.generate());
	GENERATE_VAR(BmiSrc, ::g->BmiSrc.generate());
	GENERATE_VAR(BitsSrc, ::g->BitsSrc.generate(cbBitsSrc()));
	end = FTell();
	FSeek((emrOffset + 4));
	GENERATE_VAR(nSize, ::g->nSize.generate({ ((emrSize + bmiSize) + cbBitsSrc()) }));
	FSeek(end);

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRRESERVED117* EMRRESERVED117::generate() {
	if (generated == 1) {
		EMRRESERVED117* new_instance = new EMRRESERVED117(instances);
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

	GENERATE_VAR(iType, ::g->iType.generate({ EMR_RESERVED_117 }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x28 }));
	GENERATE_VAR(ReservedData, ::g->ReservedData.generate(8));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


TRIVERTEX* TRIVERTEX::generate() {
	if (generated == 1) {
		TRIVERTEX* new_instance = new TRIVERTEX(instances);
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

	GENERATE_VAR(x, ::g->x.generate());
	GENERATE_VAR(y, ::g->y.generate());
	GENERATE_VAR(Red, ::g->Red__.generate());
	GENERATE_VAR(Green, ::g->Green__.generate());
	GENERATE_VAR(Blue, ::g->Blue__.generate());
	GENERATE_VAR(Alpha, ::g->Alpha.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


GRADIENT_RECT* GRADIENT_RECT::generate() {
	if (generated == 1) {
		GRADIENT_RECT* new_instance = new GRADIENT_RECT(instances);
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

	GENERATE_VAR(UpperLeft, ::g->UpperLeft.generate());
	GENERATE_VAR(LowerRight, ::g->LowerRight.generate());

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRGRADIENTFILL* EMRGRADIENTFILL::generate() {
	if (generated == 1) {
		EMRGRADIENTFILL* new_instance = new EMRGRADIENTFILL(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_GRADIENTFILL }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x40 }));
	GENERATE_VAR(rclBounds, ::g->rclBounds.generate());
	GENERATE_VAR(nVer, ::g->nVer.generate({ 1 }));
	GENERATE_VAR(nTri, ::g->nTri.generate({ 1 }));
	GENERATE_VAR(ulMode, GradientFill_generate());
	GENERATE_VAR(vObjects, ::g->vObjects.generate(nVer()));
	GENERATE_VAR(vIndexes, ::g->vIndexes.generate(nTri()));
	GENERATE_VAR(vPadding, ::g->vPadding.generate(nTri()));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRCOLORMATCHTOTARGETW* EMRCOLORMATCHTOTARGETW::generate() {
	if (generated == 1) {
		EMRCOLORMATCHTOTARGETW* new_instance = new EMRCOLORMATCHTOTARGETW(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_COLORMATCHTOTARGETW }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x1c }));
	GENERATE_VAR(dwAction, ColorSpace_generate());
	GENERATE_VAR(dwFlags, ColorMatchToTarget_generate());
	GENERATE_VAR(cbName, ::g->cbName.generate({ 2 }));
	GENERATE_VAR(cbData, ::g->cbData.generate({ 2 }));
	GENERATE_VAR(data, ::g->data_.generate((cbName() + cbData())));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


LOGCOLORSPACEW* LOGCOLORSPACEW::generate() {
	if (generated == 1) {
		LOGCOLORSPACEW* new_instance = new LOGCOLORSPACEW(instances);
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

	GENERATE_VAR(lcsSignature, ::g->lcsSignature.generate({ 0x50534F43 }));
	GENERATE_VAR(lcsVersion, ::g->lcsVersion.generate({ 0x400 }));
	GENERATE_VAR(lcsSize, ::g->lcsSize.generate({ 0x24c }));
	GENERATE_VAR(lcsCSType, LogicalColorSpace_generate());
	GENERATE_VAR(lcsIntent, GamutMappingIntent_generate());
	GENERATE_VAR(lcsEndpoints, ::g->lcsEndpoints.generate());
	GENERATE_VAR(lcsGammaRed, ::g->lcsGammaRed.generate());
	GENERATE_VAR(lcsGammaGreen, ::g->lcsGammaGreen.generate());
	GENERATE_VAR(lcsGammaBlue, ::g->lcsGammaBlue.generate());
	GENERATE_VAR(lcsFilename, ::g->lcsFilename_.generate(520));

	::g->_struct_id = _parent_id;
	_sizeof = FTell() - _startof;
	return this;
}


EMRCREATECOLORSPACEW* EMRCREATECOLORSPACEW::generate() {
	if (generated == 1) {
		EMRCREATECOLORSPACEW* new_instance = new EMRCREATECOLORSPACEW(instances);
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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_CREATECOLORSPACEW }));
	GENERATE_VAR(nSize, ::g->nSize.generate({ 0x18 }));
	GENERATE_VAR(ihCS, ::g->ihCS.generate());
	GENERATE_VAR(lcs, ::g->lcs_.generate());
	GENERATE_VAR(dwFlags, ::g->dwFlags.generate());
	GENERATE_VAR(cbData, ::g->cbData.generate({ 4 }));
	GENERATE_VAR(Data, ::g->Data.generate(cbData()));

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

	GENERATE_VAR(iType, EmfRecordType_generate({ EMR_EOF }));
	GENERATE_VAR(Size, ::g->Size.generate({ 0x18 }));
	GENERATE_VAR(nPalEntries, ::g->nPalEntries.generate({ 1 }));
	GENERATE_VAR(offPalEntries, ::g->offPalEntries.generate({ 0x12 }));
	GENERATE_VAR(paletteBuffer, ::g->paletteBuffer.generate(nPalEntries()));
	GENERATE_VAR(SizeLast, ::g->SizeLast.generate({ 0x18 }));

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
	if ((::g->EmfHeader().iType() != EMR_HEADER)) {
		Warning("File has no valid EMR_HEADER record. Template stopped.");
		exit_template(-1);
	};
	if (((::g->EmfHeader().nDescription() != 0) && ((::g->EmfHeader().nDescription() % 4) != 0))) {
		Warning("Description size is invalid. Template stopped.");
		exit_template(-1);
	};
	if ((::g->EmfHeader().nDescription() && ::g->EmfHeader().offDescription())) {
		FSeek(::g->EmfHeader().offDescription());
		GENERATE(EmfDescription, ::g->EmfDescription.generate());
	};
	FSeek(::g->EmfHeader().nSize());
	::g->recCnt = 1;
	for (::g->recCnt = 1; (::g->recCnt <= (::g->EmfHeader().nRecords() - 2)); ::g->recCnt++) {
			::g->bitmapRecords = { 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x72, 0x74 };
		::g->clippingRecords = { 0x1a, 0x1d, 0x1e, 0x43, 0x4b };
		::g->commentRecords = { 0x46 };
		::g->controlRecords = { 0x1, 0xe };
		::g->drawingRecords = { 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0xf, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x35, 0x36, 0x37, 0x38, 0x3e, 0x3f, 0x40, 0x47, 0x48, 0x4a, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5a, 0x5b, 0x5c, 0x60, 0x61, 0x6c, 0x76 };
		::g->escapeRecords = { 0x69, 0x6a, 0x6e };
		::g->objectCreationRecords = { 0x26, 0x27, 0x31, 0x52, 0x5d, 0x5e, 0x5f, 0x63, 0x7a };
		::g->objectManipulationRecords = { 0x25, 0x28, 0x30, 0x32, 0x33, 0x64, 0x65, 0x6f };
		::g->openGLRecords = { 0x66, 0x67 };
		::g->pathBracketRecords = { 0x3b, 0x3c, 0x3d, 0x41, 0x42, 0x44 };
		::g->stateRecords = { 0x9, 0xa, 0xb, 0xc, 0xd, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x1b, 0x1f, 0x20, 0x22, 0x3a, 0x39, 0x49, 0x62, 0x68, 0x6d, 0x70, 0x71, 0x73, 0x77, 0x78, 0x79 };
		::g->transformRecords = { 0x23, 0x24 };
		::g->possible = { 0x2, 0x3, 0x4, 0x5, 0x6, 0x7, 0x8, 0xf, 0x1a, 0x1d, 0x1e, 0x25, 0x26, 0x27, 0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f, 0x30, 0x31, 0x32, 0x33, 0x35, 0x36, 0x37, 0x38, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f, 0x40, 0x41, 0x42, 0x43, 0x44, 0x46, 0x47, 0x48, 0x49, 0x4a, 0x4b, 0x4c, 0x4d, 0x4e, 0x4f, 0x50, 0x51, 0x53, 0x5d, 0x5e, 0x5f, 0x60, 0x63, 0x64, 0x65, 0x66, 0x67, 0x69, 0x6a, 0x6d, 0x6e, 0x6f, 0x72, 0x74, 0x76, 0x79 };
		GENERATE(recType, ::g->recType.generate(::g->possible));
		FSkip(-1);
		switch (::g->recType()) {
		case EMR_POLYBEZIER:
			GENERATE(PolyBezier, ::g->PolyBezier.generate());
			break;
		case EMR_POLYGON:
			GENERATE(Polygon, ::g->Polygon.generate());
			break;
		case EMR_POLYLINE:
			GENERATE(Polyline, ::g->Polyline.generate());
			break;
		case EMR_POLYBEZIERTO:
			GENERATE(PolyBezierTo, ::g->PolyBezierTo.generate());
			break;
		case EMR_POLYLINETO:
			GENERATE(PolyBezierTo, ::g->PolyBezierTo_.generate());
			break;
		case EMR_POLYPOLYLINE:
			GENERATE(PolyPolyline, ::g->PolyPolyline.generate());
			break;
		case EMR_POLYPOLYGON:
			GENERATE(PolyPolygon, ::g->PolyPolygon.generate());
			break;
		case EMR_SETPIXELV:
			GENERATE(SetPixelV, ::g->SetPixelV.generate());
			break;
		case EMR_OFFSETCLIPRGN:
			GENERATE(OffsetClipRgn, ::g->OffsetClipRgn.generate());
			break;
		case EMR_EXCLUDECLIPRECT:
			GENERATE(ExcludeClipRect, ::g->ExcludeClipRect.generate());
			break;
		case EMR_INTERSECTCLIPRECT:
			GENERATE(InterSectClipRect, ::g->InterSectClipRect.generate());
			break;
		case EMR_SELECTOBJECT:
			GENERATE(SelectObject, ::g->SelectObject.generate());
			break;
		case EMR_CREATEPEN:
			GENERATE(CreatePen, ::g->CreatePen.generate());
			break;
		case EMR_CREATEBRUSHINDIRECT:
			GENERATE(CreateBrushIndirect, ::g->CreateBrushIndirect.generate());
			break;
		case EMR_DELETEOBJECT:
			GENERATE(DeleteObject, ::g->DeleteObject.generate());
			break;
		case EMR_ANGLEARC:
			GENERATE(AngleArc, ::g->AngleArc.generate());
			break;
		case EMR_ELLIPSE:
			GENERATE(Ellipse, ::g->Ellipse.generate());
			break;
		case EMR_RECTANGLE:
			GENERATE(Rectangle, ::g->Rectangle.generate());
			break;
		case EMR_ROUNDRECT:
			GENERATE(RoundRect, ::g->RoundRect.generate());
			break;
		case EMR_ARC:
			GENERATE(Arc, ::g->Arc.generate());
			break;
		case EMR_CHORD:
			GENERATE(Chord, ::g->Chord.generate());
			break;
		case EMR_PIE:
			GENERATE(Pie, ::g->Pie.generate());
			break;
		case EMR_SELECTPALETTE:
			GENERATE(SelectPalette, ::g->SelectPalette.generate());
			break;
		case EMR_CREATEPALETTE:
			GENERATE(CreatePalette, ::g->CreatePalette.generate());
			break;
		case EMR_SETPALETTEENTRIES:
			GENERATE(SetPaletteEntries, ::g->SetPaletteEntries.generate());
			break;
		case EMR_RESIZEPALETTE:
			GENERATE(ResizePalette, ::g->ResizePalette.generate());
			break;
		case EMR_EXTFLOODFILL:
			GENERATE(ExtFloodFill, ::g->ExtFloodFill.generate());
			break;
		case EMR_LINETO:
			GENERATE(LineTo, ::g->LineTo.generate());
			break;
		case EMR_ARCTO:
			GENERATE(ArcTo, ::g->ArcTo.generate());
			break;
		case EMR_POLYDRAW:
			GENERATE(PolyDraw, ::g->PolyDraw.generate());
			break;
		case EMR_BEGINPATH:
			GENERATE(BeginPath, ::g->BeginPath.generate());
			break;
		case EMR_ENDPATH:
			GENERATE(EndPath, ::g->EndPath.generate());
			break;
		case EMR_CLOSEFIGURE:
			GENERATE(CloseFigure, ::g->CloseFigure.generate());
			break;
		case EMR_FILLPATH:
			GENERATE(FillPath, ::g->FillPath.generate());
			break;
		case EMR_STROKEANDFILLPATH:
			GENERATE(FillPath, ::g->FillPath_.generate());
			break;
		case EMR_STROKEPATH:
			GENERATE(StrokePath, ::g->StrokePath.generate());
			break;
		case EMR_FLATTENPATH:
			GENERATE(FlattenPath, ::g->FlattenPath.generate());
			break;
		case EMR_WIDENPATH:
			GENERATE(WidenPath, ::g->WidenPath.generate());
			break;
		case EMR_SELECTCLIPPATH:
			GENERATE(SelectClipPath, ::g->SelectClipPath.generate());
			break;
		case EMR_ABORTPATH:
			GENERATE(AbortPath, ::g->AbortPath.generate());
			break;
		case EMR_COMMENT:
			GENERATE(Comment, ::g->Comment.generate());
			break;
		case EMR_FILLRGN:
			GENERATE(FillRgn, ::g->FillRgn.generate());
			break;
		case EMR_FRAMERGN:
			GENERATE(FrameRgn, ::g->FrameRgn.generate());
			break;
		case EMR_INVERTRGN:
			GENERATE(InvertRgn, ::g->InvertRgn.generate());
			break;
		case EMR_PAINTRGN:
			GENERATE(PaintRgn, ::g->PaintRgn.generate());
			break;
		case EMR_EXTSELECTCLIPRGN:
			GENERATE(ExtSelectClipRgn, ::g->ExtSelectClipRgn.generate());
			break;
		case EMR_BITBLT:
			GENERATE(BitBlt, ::g->BitBlt.generate());
			break;
		case EMR_STRETCHBLT:
			GENERATE(StretchBlt, ::g->StretchBlt.generate());
			break;
		case EMR_MASKBLT:
			GENERATE(MaskBlt, ::g->MaskBlt.generate());
			break;
		case EMR_PLGBLT:
			GENERATE(PlgBlt, ::g->PlgBlt.generate());
			break;
		case EMR_SETDIBITSTODEVICE:
			GENERATE(SetDiBitsToDevice, ::g->SetDiBitsToDevice.generate());
			break;
		case EMR_STRETCHDIBITS:
			GENERATE(StretchDIBits, ::g->StretchDIBits.generate());
			break;
		case EMR_EXTTEXTOUTA:
			GENERATE(ExtTextOutA, ::g->ExtTextOutA.generate());
			break;
		case EMR_CREATEMONOBRUSH:
			GENERATE(CreateMonoBrush, ::g->CreateMonoBrush.generate());
			break;
		case EMR_CREATEDIBPATTERNBRUSHPT:
			GENERATE(CreateDIBPatternBrushPt, ::g->CreateDIBPatternBrushPt.generate());
			break;
		case EMR_EXTCREATEPEN:
			GENERATE(CreatePenEx, ::g->CreatePenEx.generate());
			break;
		case EMR_POLYTEXTOUTA:
			GENERATE(PolyTextOutA, ::g->PolyTextOutA.generate());
			break;
		case EMR_CREATECOLORSPACE:
			GENERATE(CreateColorSpace, ::g->CreateColorSpace.generate());
			break;
		case EMR_SETCOLORSPACE:
			GENERATE(SetColorSpace, ::g->SetColorSpace.generate());
			break;
		case EMR_DELETECOLORSPACE:
			GENERATE(DeleteColorSpace, ::g->DeleteColorSpace.generate());
			break;
		case EMR_GLSRECORD:
			GENERATE(GlsRecord, ::g->GlsRecord.generate());
			break;
		case EMR_GLSBOUNDEDRECORD:
			GENERATE(GlsBoundedRecord, ::g->GlsBoundedRecord.generate());
			break;
		case EMR_DRAWESCAPE:
			GENERATE(DrawEscape, ::g->DrawEscape.generate());
			break;
		case EMR_EXTESCAPE:
			GENERATE(ExtEscape, ::g->ExtEscape.generate());
			break;
		case EMR_RESERVED_107:
			GENERATE(Reserved, ::g->Reserved__.generate());
			break;
		case EMR_FORCEUFIMAPPING:
			GENERATE(ForceUfiMapping, ::g->ForceUfiMapping.generate());
			break;
		case EMR_NAMEDESCAPE:
			GENERATE(NamedEscape, ::g->NamedEscape.generate());
			break;
		case EMR_COLORCORRECTPALETTE:
			GENERATE(ColorCorrectPalette, ::g->ColorCorrectPalette.generate());
			break;
		case EMR_ALPHABLEND:
			GENERATE(AlphaBlend, ::g->AlphaBlend.generate());
			break;
		case EMR_TRANSPARENTBLT:
			GENERATE(TransparentBlt, ::g->TransparentBlt.generate());
			break;
		case EMR_RESERVED_117:
			GENERATE(Reserved, ::g->Reserved___.generate());
			break;
		case EMR_GRADIENTFILL:
			GENERATE(GradientFill, ::g->GradientFill.generate());
			break;
		case EMR_COLORMATCHTOTARGETW:
			GENERATE(ColorMatchToTargetW, ::g->ColorMatchToTargetW.generate());
			break;
		case EMR_CREATECOLORSPACEW:
			GENERATE(CreateColorSpaceW, ::g->CreateColorSpaceW.generate());
			break;
		};
	;
	};
	GENERATE(EmfEndOfFile, ::g->EmfEndOfFile.generate());
	if ((::g->EmfEndOfFile().Size() != ::g->EmfEndOfFile().SizeLast())) {
		Warning("End of file is corrupt. Template stopped.");
		exit_template(-1);
	};
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

