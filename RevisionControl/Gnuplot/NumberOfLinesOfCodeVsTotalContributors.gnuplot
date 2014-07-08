set output "NumberOfLinesOfCodeVsTotalContributors.pdf"
set term pdf
set title "Lines of Code vs Number of Contributors"
row = 2
col = 3
plot \
"/tmp/LinuxKernelGitAnalysis.txt" using row:col with lines title "Linux Kernel", \
"/tmp/FirefoxGitAnalysis.txt" using row:col with lines title "Firefox", \
"/tmp/VTKGitAnalysis.txt" using row:col with lines title "VTK", \
"/tmp/ITKGitAnalysis.txt" using row:col with lines title "ITK"
