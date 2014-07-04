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

#include "GitNetwork.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

namespace GitStatistics
{

GitNetwork::GitNetwork()
{
}

GitNetwork::~GitNetwork()
{
}

void GitNetwork::AddCommit( const Commit & commit )
{
  this->commits.Add( commit );
}

void GitNetwork::ParseInputFile( const char * inputFileName )
{
  std::ifstream inputFile;

  inputFile.open(inputFileName);

  std::string inputLine;

  while( !inputFile.eof() )
    {
    std::getline( inputFile, inputLine );

    //
    // This parsing approach presumes a specific order of the tags.
    // It makes the parsing more efficient, but also more vulnerable.
    //
    if( inputLine.find("Commit:") != std::string::npos )
      {
      Commit commit;
      std::string hash = inputLine.substr(8,std::string::npos);
      commit.SetHash( hash );

      std::getline( inputFile, inputLine );
      if( inputLine.find("Author:") != std::string::npos )
        {
        std::string authorName = inputLine.substr(8,std::string::npos);
        commit.SetAuthor( authorName );
        Person author;
        author.SetName( authorName );
        this->people.AddPerson( author );

        std::getline( inputFile, inputLine );
        if( inputLine.find("Date:") != std::string::npos )
          {
          std::string dateString = inputLine.substr(6,std::string::npos);
          commit.SetDate( dateString );

          std::getline( inputFile, inputLine );
          if( inputLine.find("Committer:") != std::string::npos )
            {
            std::string committerName = inputLine.substr(11,std::string::npos);
            commit.SetCommitter( committerName );

            // Now attempt to parse the changed files

            // get an empty line out of the way
            std::getline( inputFile, inputLine);
            if( !inputLine.empty() )
              {
              std::cerr << "Were expecting an empty line after Committer:" << std::endl;
              }

            while(1)
              {

              std::getline( inputFile, inputLine);

              if( inputLine.empty() )
                {
                // This must be the end of the list of files
                break;
                }
              else
                {

                if( inputLine.substr(0,7) == "Commit:" )
                  {
                  // No files were changed, and we are starting the next commit.
                  // Therefore, add the commit so far, and then break the cicle.
                  this->AddCommit( commit );
                  break;
                  }

                // This must be one of the changed files
                std::string linesAddedString;
                std::string linesRemovedString;
                std::string fileName;

                std::istringstream(inputLine) >> linesAddedString >> linesRemovedString >> fileName;

                Commit::NumberOfLinesType linesAdded = 0;
                Commit::NumberOfLinesType linesRemoved = 0;

                if( linesAddedString != "-" )
                  {
                  std::istringstream(linesAddedString) >> linesAdded;
                  }

                if( linesRemovedString != "-" )
                  {
                  std::istringstream(linesRemovedString) >> linesRemoved;
                  }

                commit.AddFileChange( linesAdded, linesRemoved, fileName );

                File newFile;

                newFile.SetName( fileName );

                this->files.AddFile( newFile );
                }

              }

            }

          }

        }
      this->AddCommit( commit );
      }

    }
}

void GitNetwork::ListPeople() const
{
  this->people.Print( std::cout );
}

void GitNetwork::ListFiles() const
{
  this->files.Print( std::cout );
}

void GitNetwork::ListCommits() const
{
  this->commits.Print( std::cout );
}

void GitNetwork::ComputeTotalActivityPerAuthor() const
{
  typedef std::unordered_map< std::string, AuthorChanges >  ChangesContainerType;

  CommitsContainer::ConstIterator citr = this->commits.Begin();
  CommitsContainer::ConstIterator cend = this->commits.End();

  ChangesContainerType changesPerAuthor;

  while( citr != cend )
    {
    const Commit & commit = citr->second;

    const std::string authorName = commit.GetAuthor().GetName();

    if( changesPerAuthor.count(authorName) == 0 )
      {
      AuthorChanges newchange;
      newchange.SetAuthorName( authorName );
      changesPerAuthor[authorName] = newchange;
      }

    AuthorChanges & change = changesPerAuthor[authorName];

    change.SetNumberOfLinesAdded( change.GetNumberOfLinesAdded() + commit.GetNumberOfLinesAdded() );
    change.SetNumberOfLinesRemoved( change.GetNumberOfLinesRemoved() + commit.GetNumberOfLinesRemoved() );
    change.SetNumberOfCommits( change.GetNumberOfCommits() + 1 );

    ++citr;
    }

  for( const auto & change : changesPerAuthor )
    {
    this->sortedChangesPerAuthor.push_back( change.second );
    }

}

void GitNetwork::ReportActivityPerAuthorSortedByCommits() const
{

  struct changesOrderedByCommit {
    bool operator() (const AuthorChanges & a,const AuthorChanges & b)
      {
      return (a.GetNumberOfCommits()>b.GetNumberOfCommits());
      }
  } orderByNumberOfCommits;

  std::sort(this->sortedChangesPerAuthor.begin(),this->sortedChangesPerAuthor.end(),orderByNumberOfCommits);

  std::cout << std::endl;
  std::cout << "Authors sorted by number of commits" << std::endl;
  std::cout << std::endl;

  for( const auto & change : this->sortedChangesPerAuthor )
    {
    change.Print( std::cout );
    }

}

void GitNetwork::ReportActivityPerAuthorSortedByLinesAdded() const
{

  struct changesOrderedByLinesAdded {
    bool operator() (const AuthorChanges & a,const AuthorChanges & b)
      {
      return (a.GetNumberOfLinesAdded()>b.GetNumberOfLinesAdded());
      }
  } orderByNumberOfLinesAdded;

  std::sort(this->sortedChangesPerAuthor.begin(),this->sortedChangesPerAuthor.end(),orderByNumberOfLinesAdded);

  std::cout << std::endl;
  std::cout << "Authors sorted by number of lines added" << std::endl;
  std::cout << std::endl;

  for( const auto & change : this->sortedChangesPerAuthor )
    {
    change.Print( std::cout );
    }

}

void GitNetwork::ReportActivityPerAuthorSortedByLinesRemoved() const
{

  struct changesOrderedByLinesRemoved {
    bool operator() (const AuthorChanges & a,const AuthorChanges & b)
      {
      return (a.GetNumberOfLinesRemoved()>b.GetNumberOfLinesRemoved());
      }
  } orderByNumberOfLinesRemoved;

  std::sort(this->sortedChangesPerAuthor.begin(),this->sortedChangesPerAuthor.end(),orderByNumberOfLinesRemoved);

  std::cout << std::endl;
  std::cout << "Authors sorted by number of lines removed" << std::endl;
  std::cout << std::endl;

  for( const auto & change : this->sortedChangesPerAuthor )
    {
    change.Print( std::cout );
    }

}

void GitNetwork::ReportActivityPerAuthorSortedByLinesTouched() const
{

  struct changesOrderedByLinesTouched {
    bool operator() (const AuthorChanges & a,const AuthorChanges & b)
      {
      return ( ( a.GetNumberOfLinesAdded() + a.GetNumberOfLinesRemoved() ) >
               ( b.GetNumberOfLinesAdded() + b.GetNumberOfLinesRemoved() )    );
      }
  } orderByNumberOfCommits;

  std::sort(this->sortedChangesPerAuthor.begin(),this->sortedChangesPerAuthor.end(),orderByNumberOfCommits);

  std::cout << std::endl;
  std::cout << "Authors sorted by number of lines touched" << std::endl;
  std::cout << std::endl;

  for( const auto & change : this->sortedChangesPerAuthor )
    {
    change.Print( std::cout );
    }

}

}
