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

////////////////////////////////////////////////////////////////////////////////
//																																						//
//  (c) 2001-2003 Electronic Arts Inc.																				//
//																																						//
////////////////////////////////////////////////////////////////////////////////

//----------------------------------------------------------------------------
//                                                                          
//                       Westwood Studios Pacific.                          
//                                                                          
//                       Confidential Information                           
//                Copyright (C) 2001 - All Rights Reserved                  
//                                                                          
//----------------------------------------------------------------------------
//
// Project:   Generals
//
// Module:    Game Engine Device Win32 Common
//
// File name: Win32CDManager.cpp
//
// Created:   01/07/26 Stephan Vedder
//
//----------------------------------------------------------------------------

//----------------------------------------------------------------------------
//         Includes                                                      
//----------------------------------------------------------------------------
#include "SDL3Device/Common/SDL3CDManager.h"
#include <fcntl.h>

CDManagerInterface* CreateCDManager( void )
{
  return NEW SDL3CDManager;
}


SDL3CDDrive::SDL3CDDrive()
{
}

SDL3CDDrive::~SDL3CDDrive()
{
}

void SDL3CDDrive::refreshInfo(void)
{
  // For the given drive path, determine the disk name and ID
  m_disk = CD::NO_DISK;
  // int fd = open(m_drivePath.str(), O_RDONLY | O_NONBLOCK);
  // if (fd != -1)
  // {
  //   struct cdrom_tochdr tocHeader;
  //   if (ioctl(fd, CDROMREADTOCHDR, &tocHeader) == 0)
  //   {
  //     m_disk = CD::UNKNOWN_DISK;
  //   }
  //   close(fd);
  // }
}


SDL3CDManager::SDL3CDManager()
{
}
SDL3CDManager::~SDL3CDManager()
{
}

void SDL3CDManager::init(void)
{
  CDManager::init();
  destroyAllDrives();

  // Detect CD Drives
  for (Char driveLetter = '0'; driveLetter <= '0'; driveLetter++)
  {
    AsciiString drivePath;
    drivePath.format("/dev/sr", driveLetter);

    // if (access(drivePath.str(), F_OK) == 0)
    // {
    //   newDrive(drivePath.str());
    // }
  }

  refreshDrives();
}

void SDL3CDManager::update(void)
{
  CDManager::update();
}

void SDL3CDManager::reset(void)
{
  CDManager::reset();
}

void SDL3CDManager::refreshDrives(void)
{
  CDManager::refreshDrives();
}

CDDriveInterface* SDL3CDManager::createDrive(void)
{
  return NEW SDL3CDDrive;
}