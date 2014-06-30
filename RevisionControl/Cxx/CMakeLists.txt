PROJECT(GitStatistics)

ADD_EXECUTABLE(GitStatisticsAnalyzer
  GitNetwork.cxx
  Commit.cxx
  CommitsContainer.cxx
  GitStatisticsParser.cxx
  )
