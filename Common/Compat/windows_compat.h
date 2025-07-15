#pragma once
#include <cstdint>
#include <unistd.h>

typedef void *HANDLE;
typedef HANDLE HWND;
typedef HANDLE HINSTANCE;
typedef HANDLE HKEY;
typedef HANDLE HDC;
typedef int32_t HRESULT;
typedef unsigned int UINT;

#define S_OK 0

#define HKEY_LOCAL_MACHINE NULL
#define HKEY_CURRENT_USER NULL

#define MAX_PATH 260
#define MAX_COMPUTERNAME_LENGTH 25
#define UNLEN 256
#define GetUserName(a,b) false
#define GetComputerName(a,b) false

#define _access access
#define TRUE true
#define FALSE false

class CComModule
{
  public:
    void Init(void*, HINSTANCE hInstance)
    {
      m_hInstance = hInstance;
    }
    void Term() {}

  private:
    HINSTANCE m_hInstance;
};

bool GetModuleFileName(HINSTANCE hInstance, char* buffer, int size);

typedef uintptr_t (*FARPROC)();
typedef HANDLE HMODULE;

HMODULE LoadLibrary(const char* lpFileName);
FARPROC GetProcAddress(HMODULE hModule, const char* lpProcName);
void FreeLibrary(HMODULE hModule);

/// MessageBox function for displaying messages
typedef enum eMessageBoxType
{
  MB_OK = 0x00000000L,
  MB_OKCANCEL = 0x00000001L,
  MB_ABORTRETRYIGNORE = 0x00000002L,
  MB_YESNOCANCEL = 0x00000003L,
  MB_YESNO = 0x00000004L,
  MB_RETRYCANCEL = 0x00000005L,
  MB_CANCELTRYCONTINUE = 0x00000006L,
  MB_ICONHAND = 0x00000010L,
  MB_ICONERROR = 0x00000010L,
  MB_ICONWARNING = 0x00000030L,
  MB_TASKMODAL = 0x00002000L,
  MB_SYSTEMMODAL = 0x00001000L,
} eMessageBoxType;

typedef enum eMessageBoxResult
{
  IDABORT = 3,
  IDRETRY = 4,
  IDIGNORE = 5,
  IDYES = 6,
  IDNO = 7,
} eMessageBoxResult;

#include <stdio.h>

inline int MessageBoxA(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, unsigned int uType)
{
  // Simulate a message box by printing the message to the console
  printf("MessageBox: %s\nCaption: %s\n", lpText, lpCaption);
  return 0; // Simulate a "Yes" response
}

inline int MessageBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, unsigned int uType)
{
  // Simulate a message box by printing the message to the console
  wprintf(L"MessageBox: %s\nCaption: %s\n", lpText, lpCaption);
  return 0; // Simulate a "Yes" response
}

#define MessageBox MessageBoxA