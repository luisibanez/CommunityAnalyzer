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

#ifndef __PeopleContainer_h
#define __PeopleContainer_h

#include <string>
#include <unordered_map>

#include "Person.h"

namespace GitStatistics
{

class PeopleContainer
{
public:
  PeopleContainer();
  ~PeopleContainer();

  void AddPerson( const Person & newperson );

  void Print( std::ostream & outputStream ) const;

private:

  typedef std::unordered_map< std::string, Person >  ContainerType;

  ContainerType     container;

};

}

#endif
