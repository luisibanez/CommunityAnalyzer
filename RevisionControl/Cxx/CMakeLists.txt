PROJECT(GitStatistics)

SET(
  CMAKE_CXX_FLAGS "-std=c++11"
  )

ADD_EXECUTABLE(GitStatisticsAnalyzer
  AuthorChanges.cxx
  GitNetwork.cxx
  Commit.cxx
  CommitsContainer.cxx
  Date.cxx
  File.cxx
  FileChange.cxx
  FilesContainer.cxx
  GitStatisticsParser.cxx
  Person.cxx
  PeopleContainer.cxx
  )
