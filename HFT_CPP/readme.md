Build command : g++ ./Benchmarking_Read.cxx -std=c++11 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o mybenchmark
Out File    : mybenchmark
Run command : ./mybenchmark --bechmark_out_format=<json|csv|console> --benchmark_out_file="filename" 
