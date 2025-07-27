/*
**	Command & Conquer Generals(tm)
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// FILE: Compression.cpp /////////////////////////////////////////////////////
// Author: Matthew D. Campbell
// LZH wrapper taken from Nox, originally from Jeff Brown
//////////////////////////////////////////////////////////////////////////////

#include "Compression.h"
#ifdef RTS_USE_LZHL
#include "LZHCompress/NoxCompress.h"
#endif // RTS_USE_LZHL
#ifdef RTS_USE_ZLIB
extern "C"
{
#define __MACTYPES__
#include <zlib.h>
}
#endif // RTS_USE_ZLIB
#include "EAC/codex.h"
#include "EAC/btreecodex.h"
#include "EAC/huffcodex.h"
#include "EAC/refcodex.h"

#ifdef _INTERNAL
// for occasional debugging...
// #pragma optimize("", off)
// #pragma message("************************************** WARNING, optimization disabled for debugging purposes")
#endif

#define DEBUG_LOG(x)                                                                                                   \
	{                                                                                                                  \
	}

const char *CompressionManager::getCompressionNameByType(CompressionType compType)
{
	// clang-format off
	static const char *s_compressionNames[COMPRESSION_MAX + 1] = {
		"No compression", "RefPack",
#ifdef RTS_USE_LZHL
		"LZHL",
#endif // RTS_USE_LZHL
#ifdef RTS_USE_ZLIB
		"ZLib 1 (fast)",
		"ZLib 2",
		"ZLib 3",
		"ZLib 4",
		"ZLib 5 (default)",
		"ZLib 6",
		"ZLib 7",
		"ZLib 8",
		"ZLib 9 (slow)",
#endif // RTS_USE_ZLIB
		"BTree",
		"Huff",
	};
	// clang-format on
	return s_compressionNames[compType];
}

// For perf timers, so we can have separate ones for compression/decompression
const char *CompressionManager::getDecompressionNameByType(CompressionType compType)
{
	// clang-format off
	static const char *s_decompressionNames[COMPRESSION_MAX + 1] = {
		"d_None", "d_RefPack",
#ifdef RTS_USE_LZHL
		"d_NoxLZW",
#endif // RTS_USE_LZHL
#ifdef RTS_USE_ZLIB
		"d_ZLib1",
		"d_ZLib2",
		"d_ZLib3",
		"d_ZLib4",
		"d_ZLib5",
		"d_ZLib6",
		"d_ZLib7",
		"d_ZLib8",
		"d_ZLib9",
#endif // RTS_USE_ZLIB
		"d_BTree",
		"d_Huff",
	};
	// clang-format on
	return s_decompressionNames[compType];
}

// ---------------------------------------------------------------------------------------

Bool CompressionManager::isDataCompressed(const void *mem, Int len)
{
	CompressionType t = getCompressionType(mem, len);
	return t != COMPRESSION_NONE;
}

CompressionType CompressionManager::getPreferredCompression(void)
{
	return COMPRESSION_REFPACK;
}

CompressionType CompressionManager::getCompressionType(const void *mem, Int len)
{
	if (len < 8)
		return COMPRESSION_NONE;
#ifdef RTS_USE_LZHL
	if (memcmp(mem, "NOX\0", 4) == 0)
		return COMPRESSION_NOXLZH;
#endif // RTS_USE_LZHL
#ifdef RTS_USE_ZLIB
	if (memcmp(mem, "ZL1\0", 4) == 0)
		return COMPRESSION_ZLIB1;
	if (memcmp(mem, "ZL2\0", 4) == 0)
		return COMPRESSION_ZLIB2;
	if (memcmp(mem, "ZL3\0", 4) == 0)
		return COMPRESSION_ZLIB3;
	if (memcmp(mem, "ZL4\0", 4) == 0)
		return COMPRESSION_ZLIB4;
	if (memcmp(mem, "ZL5\0", 4) == 0)
		return COMPRESSION_ZLIB5;
	if (memcmp(mem, "ZL6\0", 4) == 0)
		return COMPRESSION_ZLIB6;
	if (memcmp(mem, "ZL7\0", 4) == 0)
		return COMPRESSION_ZLIB7;
	if (memcmp(mem, "ZL8\0", 4) == 0)
		return COMPRESSION_ZLIB8;
	if (memcmp(mem, "ZL9\0", 4) == 0)
		return COMPRESSION_ZLIB9;
#endif // RTS_USE_ZLIB
	if (memcmp(mem, "EAB\0", 4) == 0)
		return COMPRESSION_BTREE;
	if (memcmp(mem, "EAH\0", 4) == 0)
		return COMPRESSION_HUFF;
	if (memcmp(mem, "EAR\0", 4) == 0)
		return COMPRESSION_REFPACK;

	return COMPRESSION_NONE;
}

Int CompressionManager::getMaxCompressedSize(Int uncompressedLen, CompressionType compType)
{
	switch (compType)
	{
#ifdef RTS_USE_LZHL
	case COMPRESSION_NOXLZH:
		return CalcNewSize(uncompressedLen) + 8;
#endif						  // RTS_USE_LZHL
	case COMPRESSION_BTREE:	  // guessing here
	case COMPRESSION_HUFF:	  // guessing here
	case COMPRESSION_REFPACK: // guessing here
		return uncompressedLen + 8;
#ifdef RTS_USE_ZLIB
	case COMPRESSION_ZLIB1:
	case COMPRESSION_ZLIB2:
	case COMPRESSION_ZLIB3:
	case COMPRESSION_ZLIB4:
	case COMPRESSION_ZLIB5:
	case COMPRESSION_ZLIB6:
	case COMPRESSION_ZLIB7:
	case COMPRESSION_ZLIB8:
	case COMPRESSION_ZLIB9:
		return compressBound(uncompressedLen) + 8;
	default:
		break; // no compression
#endif		   // RTS_USE_ZLIB
	}

	return 0;
}

Int CompressionManager::getUncompressedSize(const void *mem, Int len)
{
	if (len < 8)
		return len;

	CompressionType compType = getCompressionType(mem, len);
	switch (compType)
	{
#ifdef RTS_USE_LZHL
	case COMPRESSION_NOXLZH:
#endif // RTS_USE_LZHL
#ifdef RTS_USE_ZLIB
	case COMPRESSION_ZLIB1:
	case COMPRESSION_ZLIB2:
	case COMPRESSION_ZLIB3:
	case COMPRESSION_ZLIB4:
	case COMPRESSION_ZLIB5:
	case COMPRESSION_ZLIB6:
	case COMPRESSION_ZLIB7:
	case COMPRESSION_ZLIB8:
	case COMPRESSION_ZLIB9:
#endif // RTS_USE_ZLIB
	case COMPRESSION_BTREE:
	case COMPRESSION_HUFF:
	case COMPRESSION_REFPACK:
		return *(Int *)(((UnsignedByte *)mem) + 4);
	default:
		break; // no compression
	}

	return len;
}

Int CompressionManager::compressData(CompressionType compType, void *srcVoid, Int srcLen, void *destVoid, Int destLen)
{
	if (destLen < 8)
		return 0;

	destLen -= 8;

	UnsignedByte *src = (UnsignedByte *)srcVoid;
	UnsignedByte *dest = (UnsignedByte *)destVoid;

	if (compType == COMPRESSION_BTREE)
	{
		memcpy(dest, "EAB\0", 4);
		*(Int *)(dest + 4) = 0;
		Int ret = BTREE_encode(dest + 8, src, srcLen);
		if (ret)
		{
			*(Int *)(dest + 4) = srcLen;
			return ret + 8;
		}
		else
			return 0;
	}
	if (compType == COMPRESSION_HUFF)
	{
		memcpy(dest, "EAH\0", 4);
		*(Int *)(dest + 4) = 0;
		Int ret = HUFF_encode(dest + 8, src, srcLen);
		if (ret)
		{
			*(Int *)(dest + 4) = srcLen;
			return ret + 8;
		}
		else
			return 0;
	}
	if (compType == COMPRESSION_REFPACK)
	{
		memcpy(dest, "EAR\0", 4);
		*(Int *)(dest + 4) = 0;
		Int ret = REF_encode(dest + 8, src, srcLen);
		if (ret)
		{
			*(Int *)(dest + 4) = srcLen;
			return ret + 8;
		}
		else
			return 0;
	}
#ifdef RTS_USE_LZHL
	if (compType == COMPRESSION_NOXLZH)
	{
		memcpy(dest, "NOX\0", 4);
		*(Int *)(dest + 4) = 0;
		Bool ret = CompressMemory(src, srcLen, dest + 8, destLen);
		if (ret)
		{
			*(Int *)(dest + 4) = srcLen;
			return destLen + 8;
		}
		else
			return 0;
	}
#endif // RTS_USE_LZHL
#ifdef RTS_USE_ZLIB
	if (compType >= COMPRESSION_ZLIB1 && compType <= COMPRESSION_ZLIB9)
	{
		Int level = compType - COMPRESSION_ZLIB1 + 1; // 1-9
		memcpy(dest, "ZL0\0", 4);
		dest[2] = '0' + level;
		*(Int *)(dest + 4) = 0;

		unsigned long outLen = destLen;
		Int err = compress2((Bytef *)dest + 8, &outLen, (const Bytef *)src, srcLen, level);

		if (err == Z_OK || err == Z_STREAM_END)
		{
			*(Int *)(dest + 4) = srcLen;
			return outLen + 8;
		}
		else
		{
			DEBUG_LOG(("ZLib compression error (level is %d, src len is %d) %d\n", level, srcLen, err));
			return 0;
		}
	}
#endif // RTS_USE_ZLIB

	return 0;
}

Int CompressionManager::decompressData(void *srcVoid, Int srcLen, void *destVoid, Int destLen)
{
	if (srcLen < 8)
		return 0;

	UnsignedByte *src = (UnsignedByte *)srcVoid;
	UnsignedByte *dest = (UnsignedByte *)destVoid;

	CompressionType compType = getCompressionType(src, srcLen);

	if (compType == COMPRESSION_BTREE)
	{
		Int slen = srcLen - 8;
		Int ret = BTREE_decode(dest, src + 8, &slen);
		if (ret)
			return ret;
		else
			return 0;
	}
	if (compType == COMPRESSION_HUFF)
	{
		Int slen = srcLen - 8;
		Int ret = HUFF_decode(dest, src + 8, &slen);
		if (ret)
			return ret;
		else
			return 0;
	}
	if (compType == COMPRESSION_REFPACK)
	{
		Int slen = srcLen - 8;
		Int ret = REF_decode(dest, src + 8, &slen);
		if (ret)
			return ret;
		else
			return 0;
	}

#ifdef RTS_USE_LZHL
	if (compType == COMPRESSION_NOXLZH)
	{
		Bool ret = DecompressMemory(src + 8, srcLen - 8, dest, destLen);
		if (ret)
			return destLen;
		else
			return 0;
	}
#endif // RTS_USE_LZHL

#ifdef RTS_USE_ZLIB
	if (compType >= COMPRESSION_ZLIB1 && compType <= COMPRESSION_ZLIB9)
	{
#ifdef DEBUG_LOGGING
		Int level = compType - COMPRESSION_ZLIB1 + 1; // 1-9
#endif

		unsigned long outLen = destLen;
		Int err = uncompress((Bytef *)dest, &outLen, (const Bytef *)src + 8, srcLen - 8);
		if (err == Z_OK || err == Z_STREAM_END)
		{
			return outLen;
		}
		else
		{
			DEBUG_LOG(("ZLib decompression error (src is level %d, %d bytes long) %d\n", level, srcLen, err));
			return 0;
		}
	}
#endif // RTS_USE_ZLIB
	return 0;
}