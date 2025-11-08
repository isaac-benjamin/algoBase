# Start from a clean, stable Linux environment
FROM ubuntu:22.04

# Install necessary tools: build-essential includes GCC/G++
RUN apt-get update && \
    apt-get install -y build-essential git && \
    rm -rf /var/lib/apt/lists/*

# Set the working directory for your project
WORKDIR /usr/src/app

# Copy your source code into the container
COPY . .

# Compile your code with AddressSanitizer and LeakSanitizer enabled
# -g for debug symbols, -O1 for reasonable performance
RUN g++ -o SubSeq.exe LongestIncreasingSubseqDP.cpp -fsanitize=address -fsanitize=undefined -g -O1

# Set the default command to run when the container starts
# The ASAN_OPTIONS environment variable ensures leak checking is active
CMD ["/bin/bash", "-c", "cat ./timeTests/100.txt | ASAN_OPTIONS=detect_leaks=1 ./SubSeq.exe"]