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
#include <chrono>
#include <iostream>
#include <sstream>

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

  this->localTimePoint = std::chrono::system_clock::from_time_t(std::mktime(&tm));

  this->AccountForTimeZone( datestring );
}

const Date::TimePointType &
Date::GetLocalTimePoint() const
{
  return this->localTimePoint;
}

Date::TimePointType
Date::GetUniversalTimePoint() const
{
  return this->localTimePoint + this->timeZoneDifference;
}


void
Date::AccountForTimeZone( const std::string & datestring )
{
  std::string timeZoneSignString     =  datestring.substr(datestring.size()-5,1);
  std::string timeZoneHoursString    =  datestring.substr(datestring.size()-4,2);
  std::string timeZoneMinutessString =  datestring.substr(datestring.size()-2,2);

  std::chrono::hours   timeZoneHours(   atoi( timeZoneHoursString.c_str()    ) );
  std::chrono::minutes timeZoneMinutes( atoi( timeZoneMinutessString.c_str() ) );

  int timeZoneSign = timeZoneSignString == "-" ? -1 : 1;

  this->timeZoneDifference = ( timeZoneHours + timeZoneMinutes ) * timeZoneSign;
}

void
Date::Print( std::ostream & outputStream ) const
{
  std::time_t localeTime = std::chrono::system_clock::to_time_t( this->localTimePoint );
  std::string localTimeString = ctime(&localeTime);

  TimePointType universalTimePoint = this->localTimePoint + this->timeZoneDifference;

  std::time_t universalTime = std::chrono::system_clock::to_time_t( universalTimePoint );
  std::string universalTimeString = ctime( &universalTime );

  outputStream << "Local Time = " << localTimeString;
  outputStream << "UTC   Time = " << universalTimeString;
}

}
