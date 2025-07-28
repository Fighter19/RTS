/*
**	Copyright 2025 Stephan Vedder
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
#pragma once
#include "chunk_d.h"

#include <string>
#include <fstream>

class WDumpDoc {
public:
  WDumpDoc(const std::string &filename) : m_filename(filename) {
    m_chunkData.Load(filename.c_str());
  }

  ~WDumpDoc() {
    m_chunkData.Release_Data();
  }

  inline const std::string &GetFilename() const {
    return m_filename;
  }

  inline bool Render() {
    return m_chunkData.Render();
  }

protected:
  std::string m_filename; // Name of the file to dump
  ChunkData m_chunkData; // Chunk data to be processed
};