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

#ifndef __CommitsContainer_h
#define __CommitsContainer_h

#include <string>

#include "Commit.h"

namespace GitStatistics
{

class CommitsContainer
{
public:
  CommitsContainer();
  ~CommitsContainer();

  void Add( const Commit & commit );

  void Print( std::ostream & outputStream ) const;

private:

  typedef std::unordered_map< std::string, Commit >  ContainerType;

  ContainerType     container;

public:

  typedef ContainerType::iterator         Iterator;
  typedef ContainerType::const_iterator   ConstIterator;

  Iterator Begin();
  ConstIterator Begin() const;

  Iterator End();
  ConstIterator End() const;

  size_t Size() const;

};

}

#endif
