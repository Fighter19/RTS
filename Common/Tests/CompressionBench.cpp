#include <benchmark/benchmark.h>
#include "Compression.h"

enum
{
	NUM_TIMES = 10
};

struct CompData
{
  public:
	Int origSize;
	Int compressedSize[COMPRESSION_MAX + 1];
};

// void DoCompressTest(void)
// {

// 	Int i;

// 	PerfGather *s_compressGathers[COMPRESSION_MAX + 1];
// 	PerfGather *s_decompressGathers[COMPRESSION_MAX + 1];
// 	for (i = 0; i < COMPRESSION_MAX + 1; ++i)
// 	{
// 		s_compressGathers[i] = new PerfGather(CompressionManager::getCompressionNameByType((CompressionType)i));
// 		s_decompressGathers[i] = new PerfGather(CompressionManager::getDecompressionNameByType((CompressionType)i));
// 	}

// 	std::map<AsciiString, CompData> s_sizes;

// 	std::map<AsciiString, MapMetaData>::const_iterator it = TheMapCache->begin();
// 	while (it != TheMapCache->end())
// 	{
// 		// if (it->second.m_isOfficial)
// 		//{
// 		//++it;
// 		// continue;
// 		//}
// 		// static Int count = 0;
// 		// if (count++ > 2)
// 		// break;
// 		File *f = TheFileSystem->openFile(it->first.str());
// 		if (f)
// 		{
// 			DEBUG_LOG(("***************************\nTesting '%s'\n\n", it->first.str()));
// 			Int origSize = f->size();
// 			UnsignedByte *buf = (UnsignedByte *)f->readEntireAndClose();
// 			UnsignedByte *uncompressedBuf = NEW UnsignedByte[origSize];

// 			CompData d = s_sizes[it->first];
// 			d.origSize = origSize;
// 			d.compressedSize[COMPRESSION_NONE] = origSize;

// 			for (i = COMPRESSION_MIN; i <= COMPRESSION_MAX; ++i)
// 			{
// 				DEBUG_LOG(("=================================================\n"));
// 				DEBUG_LOG(("Compression Test %d\n", i));

// 				Int maxCompressedSize = CompressionManager::getMaxCompressedSize(origSize, (CompressionType)i);
// 				DEBUG_LOG(("Orig size is %d, max compressed size is %d bytes\n", origSize, maxCompressedSize));

// 				UnsignedByte *compressedBuf = NEW UnsignedByte[maxCompressedSize];
// 				memset(compressedBuf, 0, maxCompressedSize);
// 				memset(uncompressedBuf, 0, origSize);

// 				Int compressedLen, decompressedLen;

// 				for (Int j = 0; j < NUM_TIMES; ++j)
// 				{
// 					s_compressGathers[i]->startTimer();
// 					compressedLen = CompressionManager::compressData((CompressionType)i, buf, origSize, compressedBuf,
// 																	 maxCompressedSize);
// 					s_compressGathers[i]->stopTimer();
// 					s_decompressGathers[i]->startTimer();
// 					decompressedLen =
// 						CompressionManager::decompressData(compressedBuf, compressedLen, uncompressedBuf, origSize);
// 					s_decompressGathers[i]->stopTimer();
// 				}
// 				d.compressedSize[i] = compressedLen;
// 				DEBUG_LOG(("Compressed len is %d (%g%% of original size)\n", compressedLen,
// 						   (double)compressedLen / (double)origSize * 100.0));
// 				DEBUG_ASSERTCRASH(compressedLen, ("Failed to compress\n"));
// 				DEBUG_LOG(("Decompressed len is %d (%g%% of original size)\n", decompressedLen,
// 						   (double)decompressedLen / (double)origSize * 100.0));

// 				DEBUG_ASSERTCRASH(decompressedLen == origSize,
// 								  ("orig size does not match compressed+uncompressed output\n"));
// 				if (decompressedLen == origSize)
// 				{
// 					Int ret = memcmp(buf, uncompressedBuf, origSize);
// 					if (ret != 0)
// 					{
// 						DEBUG_CRASH(("orig buffer does not match compressed+uncompressed output - ret was %d\n", ret));
// 					}
// 				}

// 				delete compressedBuf;
// 				compressedBuf = NULL;
// 			}

// 			DEBUG_LOG(("d = %d -> %d\n", d.origSize, d.compressedSize[i]));
// 			s_sizes[it->first] = d;
// 			DEBUG_LOG(("s_sizes[%s] = %d -> %d\n", it->first.str(), s_sizes[it->first].origSize,
// 					   s_sizes[it->first].compressedSize[i]));

// 			delete[] buf;
// 			buf = NULL;

// 			delete[] uncompressedBuf;
// 			uncompressedBuf = NULL;
// 		}

// 		++it;
// 	}

// 	for (i = COMPRESSION_MIN; i <= COMPRESSION_MAX; ++i)
// 	{
// 		Real maxCompression = 1000.0f;
// 		Real minCompression = 0.0f;
// 		Int totalUncompressedBytes = 0;
// 		Int totalCompressedBytes = 0;
// 		for (std::map<AsciiString, CompData>::iterator cd = s_sizes.begin(); cd != s_sizes.end(); ++cd)
// 		{
// 			CompData d = cd->second;

// 			Real ratio = d.compressedSize[i] / (Real)d.origSize;
// 			maxCompression = min(maxCompression, ratio);
// 			minCompression = max(minCompression, ratio);

// 			totalUncompressedBytes += d.origSize;
// 			totalCompressedBytes += d.compressedSize[i];
// 		}
// 		DEBUG_LOG(("***************************************************\n"));
// 		DEBUG_LOG(("Compression method %s:\n", CompressionManager::getCompressionNameByType((CompressionType)i)));
// 		DEBUG_LOG(("%d bytes compressed to %d (%g%%)\n", totalUncompressedBytes, totalCompressedBytes,
// 				   totalCompressedBytes / (Real)totalUncompressedBytes * 100.0f));
// 		DEBUG_LOG(("Min ratio: %g%%, Max ratio: %g%%\n", minCompression * 100.0f, maxCompression * 100.0f));
// 		DEBUG_LOG(("\n"));
// 	}

// 	PerfGather::dumpAll(10000);
// 	// PerfGather::displayGraph(TheGameLogic->getFrame());
// 	PerfGather::resetAll();
// 	CopyFile("AAAPerfStats.csv", "AAACompressPerfStats.csv", FALSE);

// 	for (i = 0; i < COMPRESSION_MAX + 1; ++i)
// 	{
// 		delete s_compressGathers[i];
// 		s_compressGathers[i] = NULL;

// 		delete s_decompressGathers[i];
// 		s_decompressGathers[i] = NULL;
// 	}
// }