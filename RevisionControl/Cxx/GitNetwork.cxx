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
      std::cout << "hash = " << hash << std::endl;
      commit.SetHash( hash );

      std::getline( inputFile, inputLine );
      if( inputLine.find("Author:") != std::string::npos )
        {
        std::string authorName = inputLine.substr(8,std::string::npos);
        std::cout << "author = " << authorName << std::endl;
        commit.SetAuthor( authorName );

        std::getline( inputFile, inputLine );
        if( inputLine.find("Date:") != std::string::npos )
          {
          std::string dateString = inputLine.substr(6,std::string::npos);
          std::cout << "date = " << dateString << std::endl;
          commit.SetDate( dateString );

          std::getline( inputFile, inputLine );
          if( inputLine.find("Committer:") != std::string::npos )
            {
            std::string committerName = inputLine.substr(11,std::string::npos);
            std::cout << "committer = " << committerName << std::endl;
            commit.SetCommitter( committerName );
            }
          }
        }

      }

    }
}

}
