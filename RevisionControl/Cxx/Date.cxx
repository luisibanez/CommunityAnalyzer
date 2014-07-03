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

#include "Date.h"

#include <ctime>
#include <iostream>

namespace GitStatistics
{

Date::Date()
{
}

Date::~Date()
{
}

void
Date::Set( const std::string & datestring )
{
  std::tm tm;
  strptime( datestring.c_str(),"%a, %d %b %Y %H:%M:%S %Z", &tm);
  this->timePoint = std::chrono::system_clock::from_time_t(std::mktime(&tm));

  // quick verification
  std::time_t tt = std::chrono::system_clock::to_time_t( this->timePoint );
  std::string timeString = ctime(&tt);

  std::cout << "Input Time = " << datestring << std::endl;
  std::cout << "Parse Time = " << timeString << std::endl;

  // Note: Time zone is note being taken into account correctly.
  // Must investigate this further.
}

}
