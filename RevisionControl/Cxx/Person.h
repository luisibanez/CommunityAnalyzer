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

#ifndef __Person_h
#define __Person_h

#include <string>
#include <iostream>

namespace GitStatistics
{

class Person
{
public:
  Person();
  ~Person();

  void SetName( const std::string & namevalue );

  const std::string & GetName() const;

  void Print( std::ostream & outuptStream ) const;

private:

  std::string     name;

};

}

#endif
