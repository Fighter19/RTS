#pragma once
#include <cstdint>
#include <unistd.h>

#include <tchar_compat.h>
#include <wchar_compat.h>

typedef void *HANDLE;
typedef HANDLE HWND;
typedef HANDLE HINSTANCE;
typedef HANDLE HKEY;
typedef HANDLE HDC;
typedef int32_t HRESULT;
typedef unsigned int UINT;

#define S_OK					0

#define HKEY_LOCAL_MACHINE		NULL
#define HKEY_CURRENT_USER		NULL

#define MAX_PATH				260
#define MAX_COMPUTERNAME_LENGTH 25
#define UNLEN					256
#define GetUserName(a, b)		false
#define GetComputerName(a, b)	false

#define _access					access
#define TRUE					true
#define FALSE					false

class CComModule {
  public:
	void Init(void *, HINSTANCE hInstance) { m_hInstance = hInstance; }
	void Term() {}

  private:
	HINSTANCE m_hInstance;
};

inline bool GetModuleFileName(HINSTANCE hInstance, char *buffer, int size) { return false; }

typedef uintptr_t (*FARPROC)();
typedef HANDLE HMODULE;

inline HMODULE LoadLibrary(const char *lpFileName) { return NULL; }
inline FARPROC GetProcAddress(HMODULE hModule, const char *lpProcName) { return NULL; }
inline void FreeLibrary(HMODULE hModule) {}

/// MessageBox function for displaying messages
typedef enum eMessageBoxType {
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

typedef enum eMessageBoxResult {
	IDABORT = 3,
	IDRETRY = 4,
	IDIGNORE = 5,
	IDYES = 6,
	IDNO = 7,
} eMessageBoxResult;

#include <stdio.h>

inline int MessageBoxA(HWND hWnd, LPCTSTR lpText, LPCTSTR lpCaption, unsigned int uType) {
	// Simulate a message box by printing the message to the console
	printf("MessageBox: %s\nCaption: %s\n", lpText, lpCaption);
	return 0; // Simulate a "Yes" response
}

inline int MessageBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, unsigned int uType) {
	// Simulate a message box by printing the message to the console
	wprintf(L"MessageBox: %s\nCaption: %s\n", lpText, lpCaption);
	return 0; // Simulate a "Yes" response
}

#define MessageBox	  MessageBoxA

#define HIWORD(value) ((((uint32_t)(value) >> 16) & 0xFFFF))
#define LOWORD(value) (((uint32_t)(value) & 0xFFFF))

typedef uint32_t DWORD;
typedef int32_t BOOL;
inline DWORD GetWindowLong(HWND hWnd, int nIndex) { return 0; }

struct RECT;
inline void AdjustWindowRect(RECT *pRect, DWORD dwStyle, BOOL bMenu) {}
inline void GetWindowRect(HWND hWnd, RECT *pRect) {}

typedef enum eSetWindowPosFlags {
	SWP_NOSIZE = 0x0001,
	SWP_NOMOVE = 0x0002,
	SWP_NOZORDER = 0x0004,
} eSetWindowPosFlags;

#define HWND_TOPMOST   ((HWND) - 1)
#define HWND_NOTOPMOST ((HWND) - 2)

inline void SetWindowPos(HWND hWnd, HWND hWndInsertAfter, int X, int Y, int cx, int cy, UINT uFlags) {}

inline void GetClientRect(HWND hWnd, RECT *pRect) {}

inline HWND GetDesktopWindow() { return NULL; }

inline HDC GetDC(HWND hWnd) { return NULL; }

inline int ReleaseDC(HWND hWnd, HDC hDC) { return 0; }

#define GWL_STYLE 1
typedef void *LPVOID;
inline void SetDeviceGammaRamp(HDC hDC, LPVOID lpRamp) {}

typedef int32_t *LPARAM;
typedef size_t WPARAM;

inline void ScreenToClient(HWND hWnd, struct POINT *ptCursor) {}
inline void ClientToScreen(HWND hWnd, struct POINT *ptCursor) {}

inline short GetAsyncKeyState(int vKey) { return 0; }
inline bool GetCursorPos(struct POINT *lpPoint) { return false; }

#define VK_INSERT 0x2D
#define VK_DELETE 0x2E

#define VK_F5	  0x74
#define VK_F6	  0x75
#define VK_F7	  0x76
#define VK_F8	  0x77

#define MAKE_HRESULT(sev,fac,code) \
    ((HRESULT) (((unsigned long)(sev)<<31) | ((unsigned long)(fac)<<16) | ((unsigned long)(code))) )

#define SEVERITY_SUCCESS    0
#define SEVERITY_ERROR      1
#define FACILITY_ITF 4
#define E_FAIL MAKE_HRESULT(SEVERITY_ERROR, FACILITY_ITF, 0xFFFF)

#define MulDiv(num, denom, div) (((denom) == 0) ? 0 : (((num) * (div)) / (denom)))

inline void SetCursor(void* hCursor) {}
#define D3DCURSOR_IMMEDIATE_UPDATE 0x00000001