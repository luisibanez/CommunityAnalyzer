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

#ifndef __AuthorChanges_h
#define __AuthorChanges_h

#include <string>
#include <iostream>

#include "FileChange.h"

namespace GitStatistics
{

class AuthorChanges
{
public:

  AuthorChanges();
  ~AuthorChanges();

  AuthorChanges(const AuthorChanges & other);
  const AuthorChanges & operator=( const AuthorChanges & other );

  typedef FileChange::NumberOfLinesType NumberOfLinesType;

  void SetNumberOfLinesAdded(NumberOfLinesType);
  void SetNumberOfLinesRemoved(NumberOfLinesType);

  void SetNumberOfCommits(size_t);
  void SetAuthorName(const std::string & filename);

  NumberOfLinesType GetNumberOfLinesAdded() const;
  NumberOfLinesType GetNumberOfLinesRemoved() const;

  size_t GetNumberOfCommits() const;

  const std::string & GetAuthorName() const;

  void Print( std::ostream & outputStream ) const;

private:

  NumberOfLinesType     numberOfLinesAdded;
  NumberOfLinesType     numberOfLinesRemoved;

  size_t                numberOfCommits;

  std::string           authorName;

};

}

#endif
