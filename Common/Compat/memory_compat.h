#pragma once
#include <cstdint>

struct MEMORYSTATUS
{
    uint32_t dwLength;
    uint32_t dwMemoryLoad;
    uint32_t dwTotalPhys;
    uint32_t dwAvailPhys;
    uint32_t dwTotalPageFile;
    uint32_t dwAvailPageFile;
    uint32_t dwTotalVirtual;
    uint32_t dwAvailVirtual;
};

inline void GlobalMemoryStatus(MEMORYSTATUS *lpBuffer)
{
    // This is a stub implementation for compatibility.
    lpBuffer->dwLength = sizeof(MEMORYSTATUS);
    lpBuffer->dwMemoryLoad = 0; // Assume no memory load
    lpBuffer->dwTotalPhys = 0; // Total physical memory
    lpBuffer->dwAvailPhys = 0; // Available physical memory
    lpBuffer->dwTotalPageFile = 0; // Total page file size
    lpBuffer->dwAvailPageFile = 0; // Available page file size
    lpBuffer->dwTotalVirtual = 0; // Total virtual memory
    lpBuffer->dwAvailVirtual = 0; // Available virtual memory
}