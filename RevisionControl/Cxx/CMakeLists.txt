PROJECT(GitStatistics)

ADD_EXECUTABLE(GitStatisticsAnalyzer
  GitNetwork.cxx
  Commit.cxx
  CommitsContainer.cxx
  Date.cxx
  GitStatisticsParser.cxx
  Person.cxx
  )
