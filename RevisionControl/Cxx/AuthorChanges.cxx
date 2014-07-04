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

#include "AuthorChanges.h"

#include <iomanip>

namespace GitStatistics
{

AuthorChanges::AuthorChanges()
{
  this->numberOfLinesAdded = 0;
  this->numberOfLinesRemoved = 0;
  this->numberOfCommits = 0;
}

AuthorChanges::~AuthorChanges()
{
}

AuthorChanges::AuthorChanges( const AuthorChanges & other )
{
  this->numberOfLinesAdded = other.numberOfLinesAdded;
  this->numberOfLinesRemoved = other.numberOfLinesRemoved;
  this->numberOfCommits = other.numberOfCommits;
  this->authorName = other.authorName;
}

const AuthorChanges &
AuthorChanges::operator=( const AuthorChanges & other )
{
  this->numberOfLinesAdded = other.numberOfLinesAdded;
  this->numberOfLinesRemoved = other.numberOfLinesRemoved;
  this->numberOfCommits = other.numberOfCommits;
  this->authorName = other.authorName;

  return *this;
}


void
AuthorChanges::SetNumberOfLinesAdded(NumberOfLinesType numberOfLines)
{
  this->numberOfLinesAdded = numberOfLines;

}

void
AuthorChanges::SetNumberOfLinesRemoved(NumberOfLinesType numberOfLines)
{
  this->numberOfLinesRemoved = numberOfLines;
}

void
AuthorChanges::SetNumberOfCommits(size_t commits)
{
  this->numberOfCommits = commits;
}

void
AuthorChanges::SetAuthorName(const std::string & authorname)
{
  this->authorName = authorname;
}

AuthorChanges::NumberOfLinesType
AuthorChanges::GetNumberOfLinesAdded() const
{
  return this->numberOfLinesAdded;
}

AuthorChanges::NumberOfLinesType
AuthorChanges::GetNumberOfLinesRemoved() const
{
  return this->numberOfLinesRemoved;
}

size_t
AuthorChanges::GetNumberOfCommits() const
{
  return this->numberOfCommits;
}

const std::string &
AuthorChanges::GetAuthorName() const
{
  return this->authorName;
}

void
AuthorChanges::Print( std::ostream & outputStream ) const
{
  outputStream << std::setw(5) << this->numberOfLinesAdded << " ";
  outputStream << std::setw(5) << this->numberOfLinesRemoved << " ";
  outputStream << std::setw(5) << this->numberOfCommits << " ";
  outputStream << this->authorName << std::endl;
}

}
