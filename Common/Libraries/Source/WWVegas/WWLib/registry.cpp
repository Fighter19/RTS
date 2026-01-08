/*
**	Command & Conquer Generals(tm)
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

/***********************************************************************************************
 ***              C O N F I D E N T I A L  ---  W E S T W O O D  S T U D I O S               ***
 ***********************************************************************************************
 *                                                                                             *
 *                 Project Name : Westwood Library                                             *
 *                                                                                             *
 *                     $Archive:: /Commando/Code/wwlib/registry.cpp                           $*
 *                                                                                             *
 *                      $Author:: Patrick                                                     $*
 *                                                                                             *
 *                     $Modtime:: 8/16/01 11:40a                                              $*
 *                                                                                             *
 *                    $Revision:: 10                                                          $*
 *                                                                                             *
 *---------------------------------------------------------------------------------------------*
 * - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - */

#include "registry.h"
#include <assert.h>

#ifdef _WIN32
#include <windows.h>
#endif 
// #include "wwdebug.h"

/*
**
*/
RegistryClass::RegistryClass(const char *sub_key) : IsValid(false) {
#ifdef _WIN32
	DWORD disposition;
	HKEY key;
	assert(sizeof(HKEY) == sizeof(int));
	if (::RegCreateKeyEx(HKEY_LOCAL_MACHINE, sub_key, 0, NULL, 0, KEY_ALL_ACCESS, NULL, &key, &disposition) ==
		ERROR_SUCCESS) {
		IsValid = true;
		Key = (int)key;
	}
#else
	// Non-Win32 platform, registry not supported
	Key = 0;
	IsValid = false;
#endif
}

RegistryClass::~RegistryClass(void) {
#ifdef _WIN32
	if (IsValid) {
		if (::RegCloseKey((HKEY)Key) != ERROR_SUCCESS) { // Close the reg key
		}
		IsValid = false;
	}
#endif
}

int RegistryClass::Get_Int(const char *name, int def_value) {
#ifdef _WIN32
	assert(IsValid);
	DWORD type, data = 0, data_len = sizeof(data);
	if ((::RegQueryValueEx((HKEY)Key, name, NULL, &type, (LPBYTE)&data, &data_len) == ERROR_SUCCESS) &&
		(type == REG_DWORD)) {
	} else {
		data = def_value;
	}
	return data;
#else
	// Non-Win32 platform, registry not supported
	return def_value;
#endif
}

void RegistryClass::Set_Int(const char *name, int value) {
#ifdef _WIN32
	assert(IsValid);
	if (::RegSetValueEx((HKEY)Key, name, 0, REG_DWORD, (LPBYTE)&value, sizeof(DWORD)) != ERROR_SUCCESS) {
	}
#endif
}

bool RegistryClass::Get_Bool(const char *name, bool def_value) { return (Get_Int(name, def_value) != 0); }

void RegistryClass::Set_Bool(const char *name, bool value) { Set_Int(name, value ? 1 : 0); }

float RegistryClass::Get_Float(const char *name, float def_value) {
#ifdef _WIN32
	assert(IsValid);
	float data = 0;
	DWORD type, data_len = sizeof(data);
	if ((::RegQueryValueEx((HKEY)Key, name, NULL, &type, (LPBYTE)&data, &data_len) == ERROR_SUCCESS) &&
		(type == REG_DWORD)) {
	} else {
		data = def_value;
	}
#else
	// Non-Win32 platform, registry not supported
	float data = def_value;
#endif
	return data;
}

void RegistryClass::Set_Float(const char *name, float value) {
#ifdef _WIN32
	assert(IsValid);
	if (::RegSetValueEx((HKEY)Key, name, 0, REG_DWORD, (LPBYTE)&value, sizeof(DWORD)) != ERROR_SUCCESS) {
	}
#endif
}

int RegistryClass::Get_Bin_Size(const char *name) {
#ifdef _WIN32
	assert(IsValid);

	unsigned long size = 0;
	::RegQueryValueEx((HKEY)Key, name, NULL, NULL, NULL, &size);
	return size;
#else
	// Non-Win32 platform, registry not supported
	return 0;
#endif
}

void RegistryClass::Get_Bin(const char *name, void *buffer, int buffer_size) {
#ifdef _WIN32
	assert(IsValid);
	assert(buffer != NULL);
	assert(buffer_size > 0);

	unsigned long size = buffer_size;
	::RegQueryValueEx((HKEY)Key, name, NULL, NULL, (LPBYTE)buffer, &size);
#endif
	return;
}

void RegistryClass::Set_Bin(const char *name, const void *buffer, int buffer_size) {
#ifdef _WIN32
	assert(IsValid);
	assert(buffer != NULL);
	assert(buffer_size > 0);

	::RegSetValueEx((HKEY)Key, name, 0, REG_BINARY, (LPBYTE)buffer, buffer_size);
#endif
	return;
}

void RegistryClass::Get_String(const char *name, StringClass &string, const char *default_string) {
#ifdef _WIN32
	assert(IsValid);
	string = (default_string == NULL) ? "" : default_string;

	//
	//	Get the size of the entry
	//
	DWORD data_size = 0;
	DWORD type = 0;
	LONG result = ::RegQueryValueEx((HKEY)Key, name, NULL, &type, NULL, &data_size);
	if (result == ERROR_SUCCESS && type == REG_SZ) {

		//
		//	Read the entry from the registry
		//
		::RegQueryValueEx((HKEY)Key, name, NULL, &type, (LPBYTE)string.Get_Buffer(data_size), &data_size);
	}
#else
	// Non-Win32 platform, registry not supported
	string = (default_string == NULL) ? "" : default_string;
#endif

	return;
}

char *RegistryClass::Get_String(const char *name, char *value, int value_size, const char *default_string) {
#ifdef _WIN32
	assert(IsValid);
	DWORD type = 0;
	if ((::RegQueryValueEx((HKEY)Key, name, NULL, &type, (LPBYTE)value, (DWORD *)&value_size) == ERROR_SUCCESS) &&
		(type == REG_SZ)) {
	} else {
		//*value = 0;
		// value = (char *) default_string;
		if (default_string == NULL) {
			*value = 0;
		} else {
			assert(strlen(default_string) < (unsigned int)value_size);
			strcpy(value, default_string);
		}
	}
#else
	// Non-Win32 platform, registry not supported
	if (default_string == NULL) {
		*value = 0;
	} else {
		assert(strlen(default_string) < (unsigned int)value_size);
		strcpy(value, default_string);
	}
#endif
	return value;
}

void RegistryClass::Set_String(const char *name, const char *value) {
#ifdef _WIN32
	assert(IsValid);
	int size = strlen(value) + 1; // must include NULL
	if (::RegSetValueEx((HKEY)Key, name, 0, REG_SZ, (LPBYTE)value, size) != ERROR_SUCCESS) {
	}
#endif
}

void RegistryClass::Get_Value_List(DynamicVectorClass<StringClass> &list) {
	char value_name[128];

	//
	//	Simply enumerate all the values in this key
	//
	int index = 0;
	unsigned long sizeof_name = sizeof(value_name);
#ifdef _WIN32
	while (::RegEnumValue((HKEY)Key, index++, value_name, &sizeof_name, 0, NULL, NULL, NULL) == ERROR_SUCCESS) {
		sizeof_name = sizeof(value_name);

		//
		//	Add this value name to the list
		//
		list.Add(value_name);
	}
#endif

	return;
}

void RegistryClass::Delete_Value(const char *name) {
#ifdef _WIN32
	::RegDeleteValue((HKEY)Key, name);
#endif
	return;
}

void RegistryClass::Deleta_All_Values(void) {
	//
	//	Build a list of the values in this key
	//
	DynamicVectorClass<StringClass> value_list;
	Get_Value_List(value_list);

	//
	//	Loop over and delete each value
	//
	for (int index = 0; index < value_list.Count(); index++) {
		Delete_Value(value_list[index]);
	}

	return;
}

void RegistryClass::Get_String(const WCHAR *name, WideStringClass &string, const WCHAR *default_string) {
#ifdef _WIN32
	assert(IsValid);
	string = (default_string == NULL) ? L"" : default_string;

	//
	//	Get the size of the entry
	//
	DWORD data_size = 0;
	DWORD type = 0;
	LONG result = ::RegQueryValueExW((HKEY)Key, name, NULL, &type, NULL, &data_size);
	if (result == ERROR_SUCCESS && type == REG_SZ) {

		//
		//	Read the entry from the registry
		//
		::RegQueryValueExW((HKEY)Key, name, NULL, &type, (LPBYTE)string.Get_Buffer((data_size / 2) + 1), &data_size);
	}
#else
	string = (default_string == NULL) ? L"" : default_string;
#endif

	return;
}

void RegistryClass::Set_String(const WCHAR *name, const WCHAR *value) {
#ifdef _WIN32
	assert(IsValid);

	//
	//	Determine the size
	//
	int size = wcslen(value) + 1;
	size = size * 2;

	//
	//	Set the registry key
	//
	::RegSetValueExW((HKEY)Key, name, 0, REG_SZ, (LPBYTE)value, size);
#endif
	return;
}
