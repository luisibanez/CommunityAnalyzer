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

#ifndef __GitNetwork_h
#define __GitNetwork_h

#include <string>
#include <vector>

#include "CommitsContainer.h"
#include "PeopleContainer.h"
#include "FilesContainer.h"
#include "AuthorChanges.h"

namespace GitStatistics
{

class GitNetwork
{
public:
  GitNetwork();
  ~GitNetwork();

  void AddCommit( const Commit & commit );

  void ParseInputFile(const char * inputFileName);

  void ListPeople() const;

  void ListFiles() const;

  void ListCommits() const;

  void ComputeTotalActivityPerAuthor() const;

  void ReportActivityPerAuthorSortedByCommits() const;
  void ReportActivityPerAuthorSortedByLinesAdded() const;
  void ReportActivityPerAuthorSortedByLinesRemoved() const;
  void ReportActivityPerAuthorSortedByLinesTouched() const;

  void ComputeMonthlyActivy() const;

  typedef Commit::NumberOfLinesType  NumberOfLinesType;

private:

  // Member variables

  CommitsContainer   commits;
  PeopleContainer    people;
  FilesContainer     files;

private:

  // Cached structures, therefore use mutable as modifier

  typedef std::vector< AuthorChanges >  ChangesVectorType;

  mutable ChangesVectorType       sortedChangesPerAuthor;

};

}

#endif
