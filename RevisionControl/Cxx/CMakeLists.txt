PROJECT(GitStatistics)

ADD_EXECUTABLE(GitStatisticsAnalyzer
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
