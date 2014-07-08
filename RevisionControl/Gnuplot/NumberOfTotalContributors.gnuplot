set output "NumberOfTotalContributors.pdf"
set term pdf
set title "Number of Total Contributors"
col = 3
plot \
"/tmp/LinuxKernelGitAnalysis.txt" using 1:col with lines title "Linux Kernel", \
"/tmp/FirefoxGitAnalysis.txt" using 1:col with lines title "Firefox", \
"/tmp/VTKGitAnalysis.txt" using 1:col with lines title "VTK", \
"/tmp/ITKGitAnalysis.txt" using 1:col with lines title "ITK"
