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

// FILE: SDL3GameEngine.h ////////////////////////////////////////////////////////////////////////
// Author: Stephan Vedder, January 2026
// Description: 
//   Device implementation of the game engine ... this is, of course, the 
//   highest level of the game that creates the necessary interfaces to the 
//   devices we need
///////////////////////////////////////////////////////////////////////////////////////////////////

#pragma once

#include "Common/GameEngine.h"
#include "GameLogic/GameLogic.h"
#include "GameNetwork/NetworkInterface.h"
#if defined(RTS_USE_OPENAL)
#include "AudioDevice/OpenAL/OpenALAudioManager.h"
#elif defined(RTS_USE_MILES)
#include "AudioDevice/OpenAL/MilesAudioManager.h"
#else
//#error "No audio device defined"
#endif
#ifdef RTS_USE_STDFS
#include "StdDevice/Common/StdBIGFileSystem.h"
#include "StdDevice/Common/StdLocalFileSystem.h"
#elif _WIN32
#include "Win32Device/Common/Win32BIGFileSystem.h"
#include "Win32Device/Common/Win32LocalFileSystem.h"
#else
#error "No file system defined"
#endif
#include "W3DDevice/Common/W3DModuleFactory.h"
#include "W3DDevice/GameLogic/W3DGameLogic.h"
#include "W3DDevice/GameClient/W3DGameClient.h"
#include "W3DDevice/GameClient/W3DWebBrowser.h"
#include "W3DDevice/Common/W3DFunctionLexicon.h"
#include "W3DDevice/Common/W3DRadar.h"
#include "W3DDevice/Common/W3DFunctionLexicon.h"
#include "W3DDevice/Common/W3DThingFactory.h"


#include <functional>

//-------------------------------------------------------------------------------------------------
/** Class declaration for the SDL3 game engine */
//-------------------------------------------------------------------------------------------------
class SDL3GameEngine : public GameEngine
{

public:

  SDL3GameEngine();
  virtual ~SDL3GameEngine();

  virtual void init( void );
  virtual void init( int argc, char** argv );
  virtual void reset( void );
  virtual void update( void );
  virtual void serviceWindowsOS( void );

  void setPostInitCallback(std::function<void()> callback) { m_postInitCallback = callback; }
  // Factories
protected:
  virtual GameLogic *createGameLogic( void );
  virtual GameClient *createGameClient( void );
  virtual ModuleFactory *createModuleFactory( void );
  virtual ThingFactory *createThingFactory( void );
  virtual FunctionLexicon *createFunctionLexicon( void );
  virtual LocalFileSystem *createLocalFileSystem( void );
  virtual ArchiveFileSystem *createArchiveFileSystem( void );
  virtual NetworkInterface *createNetwork(void); // <-- Seems to be unused
  virtual Radar *createRadar(void);
  virtual WebBrowser *createWebBrowser(void) { return NULL; }
  virtual AudioManager *createAudioManager(void);
  virtual ParticleSystemManager *createParticleSystemManager(void);

  std::function<void()> m_postInitCallback;
};

// INLINE -----------------------------------------------------------------------------------------
inline GameLogic *SDL3GameEngine::createGameLogic( void ) { return NEW W3DGameLogic; }
inline GameClient *SDL3GameEngine::createGameClient( void ) { return NEW W3DGameClient; }
inline ModuleFactory *SDL3GameEngine::createModuleFactory( void ) { return NEW W3DModuleFactory; }
inline ThingFactory *SDL3GameEngine::createThingFactory( void ) { return NEW W3DThingFactory; }
inline FunctionLexicon *SDL3GameEngine::createFunctionLexicon( void ) { return NEW W3DFunctionLexicon; }
#ifdef RTS_USE_STDFS
inline LocalFileSystem *SDL3GameEngine::createLocalFileSystem( void ) { return NEW StdLocalFileSystem; }
inline ArchiveFileSystem *SDL3GameEngine::createArchiveFileSystem( void ) { return NEW StdBIGFileSystem; }
#elif _WIN32
inline LocalFileSystem *SDL3GameEngine::createLocalFileSystem( void ) { return NEW Win32LocalFileSystem; }
inline ArchiveFileSystem *SDL3GameEngine::createArchiveFileSystem( void ) { return NEW Win32BIGFileSystem; }
#else
#error "No file system defined"
#endif
inline ParticleSystemManager* SDL3GameEngine::createParticleSystemManager( void ) { return NEW W3DParticleSystemManager; }

inline NetworkInterface *SDL3GameEngine::createNetwork( void ) { return NetworkInterface::createNetwork(); }
inline Radar *SDL3GameEngine::createRadar( void ) { return NEW W3DRadar; }
#if defined(RTS_USE_OPENAL)
inline AudioManager *SDL3GameEngine::createAudioManager( void ) { return NEW OpenALAudioManager; }
#elif defined(RTS_USE_MILES)
inline AudioManager* SDL3GameEngine::createAudioManager(void) { return NEW MilesAudioManager; }
#else 
inline AudioManager* SDL3GameEngine::createAudioManager(void) { return NULL; }
#endif