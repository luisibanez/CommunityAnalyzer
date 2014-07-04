/*=========================================================================
 *
 *  Copyright Kitware
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *         http://www.apache.org/licenses/LICENSE-2.0.txt
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 *=========================================================================*/

#include "FileChange.h"

#include <iomanip>

namespace GitStatistics
{

FileChange::FileChange()
{
  this->numberOfLinesAdded = 0;
  this->numberOfLinesRemoved = 0;
}

FileChange::~FileChange()
{
}

FileChange::FileChange( const FileChange & other )
{
  this->numberOfLinesAdded = other.numberOfLinesAdded;
  this->numberOfLinesRemoved = other.numberOfLinesRemoved;
  this->fileName = other.fileName;
}

void
FileChange::SetNumberOfLinesAdded(NumberOfLinesType numberOfLines)
{
  this->numberOfLinesAdded = numberOfLines;

}

void
FileChange::SetNumberOfLinesRemoved(NumberOfLinesType numberOfLines)
{
  this->numberOfLinesRemoved = numberOfLines;
}

void
FileChange::SetFileName(const std::string & filename)
{
  this->fileName = filename;
}

FileChange::NumberOfLinesType
FileChange::GetNumberOfLinesAdded() const
{
  return this->numberOfLinesAdded;
}

FileChange::NumberOfLinesType
FileChange::GetNumberOfLinesRemoved() const
{
  return this->numberOfLinesRemoved;
}

const std::string &
FileChange::GetFileName() const
{
  return this->fileName;
}

void
FileChange::Print( std::ostream & outputStream ) const
{
  outputStream << std::setw(5) << this->numberOfLinesAdded << " ";
  outputStream << std::setw(5) << this->numberOfLinesRemoved << " ";
  outputStream << this->fileName << std::endl;
}

}
