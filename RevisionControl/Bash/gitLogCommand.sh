#!/bin/bash
#
# This script is intended to generate the raw data from the Git log, that can
# then be analyzed to produce statistics of committers activity.
#
# The script must be run from the top directory of the git repository that is
# being analyzed.
#
# Options for the --pretty format are available at
#
#     https://www.kernel.org/pub/software/scm/git/docs/git-log.html
#
#

git log \
  --numstat \
  --no-merges \
  --pretty="%nCommit: %H%nAuthor: %aN%nDate: %aD%nCommitter: %cN%n" \
  >  /tmp/CommunityAnalyzerGitLog.txt


