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

#ifndef __Date_h
#define __Date_h

#include <string>
#include <chrono>


namespace GitStatistics
{

class Date
{
public:
  Date();
  ~Date();

  void Set( const std::string & datestring );

  void Print( std::ostream & os ) const;

private:

  void AccountForTimeZone( const std::string & datestring );

  typedef std::chrono::time_point< std::chrono::system_clock > TimePointType;

  // time interval in minutes.
  typedef std::chrono::duration< int, std::ratio<60> >         TimeDurationType;

  TimePointType     localTimePoint;

  TimeDurationType  timeZoneDifference;

};

}

#endif
