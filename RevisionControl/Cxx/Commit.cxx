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

#include "Commit.h"

#include <sstream>

namespace GitStatistics
{

Commit::Commit()
{
}

Commit::~Commit()
{
}

Commit::Commit( const Commit & other )
{
  this->hash = other.hash;
  this->date = other.date;
  this->author = other.author;
  this->committer = other.committer;
  this->fileChanges = other.fileChanges;
}

const std::string & Commit::GetHash() const
{
  return this->hash;
}

void Commit::SetHash( const std::string & hashvalue )
{
  this->hash = hashvalue;
}

void Commit::SetAuthor( const std::string & authorname )
{
  this->author.SetName( authorname );
}

void Commit::SetCommitter( const std::string & committername )
{
  this->committer.SetName( committername );
}

void Commit::SetDate( const std::string & datestring )
{
  this->date.Set( datestring );
}

void Commit::AddFileChange( const std::string & filechangestring )
{
  FileChange change;

  std::istringstream inputStream( filechangestring );

  unsigned int numberOfLinesAdded;
  unsigned int numberOfLinesRemoved;
  std::string fileName;

  inputStream >> numberOfLinesAdded;
  inputStream >> numberOfLinesRemoved;
  inputStream >> fileName;

  change.SetNumberOfLinesAdded(numberOfLinesAdded);
  change.SetNumberOfLinesRemoved(numberOfLinesRemoved);
  change.SetFileName(fileName);

  this->fileChanges[fileName] = change;
}

void
Commit::Print( std::ostream & outputStream ) const
{
  outputStream << "Commit: " << this->hash << std::endl;
  this->date.Print( outputStream );
  outputStream << "Author:   ";
  this->author.Print( outputStream );
  outputStream << "Commiter: ";
  this->committer.Print( outputStream );

  for( const auto & filechange : this->fileChanges )
    {
    filechange.second.Print( outputStream );
    }
}

}
