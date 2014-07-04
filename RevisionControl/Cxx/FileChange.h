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

#ifndef __FileChange_h
#define __FileChange_h

#include <string>
#include <iostream>

namespace GitStatistics
{

class FileChange
{
public:
  FileChange();
  ~FileChange();
  FileChange(const FileChange & other);

  void SetNumberOfLinesAdded(size_t);
  void SetNumberOfLinesRemoved(size_t);
  void SetFileName(const std::string & filename);

  size_t GetNumberOfLinesAdded() const;
  size_t GetNumberOfLinesRemoved() const;

  const std::string & GetFileName() const;

  void Print( std::ostream & outputStream ) const;

private:

  unsigned int    numberOfLinesAdded;
  unsigned int    numberOfLinesRemoved;
  std::string     fileName;

};

}

#endif
