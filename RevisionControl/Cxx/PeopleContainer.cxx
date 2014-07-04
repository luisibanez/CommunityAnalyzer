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

#include "PeopleContainer.h"

#include <iostream>

namespace GitStatistics
{

PeopleContainer::PeopleContainer()
{
}

PeopleContainer::~PeopleContainer()
{
}

void
PeopleContainer::AddPerson( const Person & newperson )
{
  this->container[newperson.GetName()]=newperson;
}

void
PeopleContainer::Print( std::ostream & outputStream ) const
{
  outputStream << "List of People" << std::endl;
  outputStream << this->container.size() << " entries" << std::endl;

  for(const auto & person : this->container )
    {
    outputStream << person.second.GetName() << std::endl;
    }

  outputStream << std::endl;
}

}
