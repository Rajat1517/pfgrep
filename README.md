# pfgrep - Parallel File Grep

A high-performance, multi-threaded file search utility written in C++. `pfgrep` (parallel file grep) recursively searches for a keyword within all files in a directory and its subdirectories, using multiple worker threads for efficient parallel processing.

## Features

- **Multi-threaded Search**: Uses 10 worker threads by default for parallel file processing
- **Recursive Directory Scanning**: Automatically traverses subdirectories to find all files
- **Thread-Safe Operations**: Implements safe queues and synchronization mechanisms
- **Fast Pattern Matching**: Uses the KMP (Knuth-Morris-Pratt) algorithm for efficient string searching
- **C++17 Standard**: Modern C++ implementation with proper threading support

## Project Structure

```
pfgrep/
├── Makefile                     # Build configuration
├── README.md                    # This file
├── src/
│   ├── main.cpp                # Entry point
│   ├── FileScanner.cpp         # Directory scanning logic
│   ├── FileSearcher.cpp        # Keyword search implementation
│   ├── WorkerManager.cpp       # Thread pool management
│   ├── SafeQueue.cpp           # Thread-safe queue implementation
│   └── include/
│       ├── FileScanner.hpp
│       ├── FileSearcher.hpp
│       ├── WorkerManager.hpp
│       └── SafeQueue.hpp
└── obj/                         # Build artifacts (generated)
```

## Prerequisites

- **C++ Compiler**: GCC/Clang with C++17 support (or newer)
- **Build Tool**: GNU Make
- **POSIX Threading**: pthread library support
- **Git**: For cloning the repository

### System Requirements

- Linux/Unix-based system (macOS, Linux, WSL, etc.)
- 1 GB disk space (for source and build artifacts)
- Multi-core processor recommended for best performance

## Installation & Setup

### 1. Clone the Repository

```bash
git clone https://github.com/Rajat1517/pfgrep.git
cd pfgrep
```

### 2. Build the Project

```bash
make
```

This will:
- Create an `obj/` directory for object files
- Compile all source files with `-std=c++17` and threading support
- Generate the `pfgrep` executable in the project root

### 3. Clean Build (Optional)

To remove all build artifacts and start fresh:

```bash
make clean
```

## Usage

### Basic Syntax

```bash
./pfgrep <directory> <keyword>
```

### Parameters

- **directory**: Path to the directory to search (can be absolute or relative)
- **keyword**: The keyword/pattern to search for in files

### Examples

**Search for "TODO" in the current directory:**

```bash
./pfgrep . TODO
```

**Search for "error" in /var/log:**

```bash
./pfgrep /var/log error
```

**Search for "function" in a specific project:**

```bash
./pfgrep ~/my_project function
```

## How It Works

1. **Main Thread**: The main thread spawns a producer thread to scan the directory tree
2. **File Scanner**: Recursively scans directories and queues file paths into a safe queue
3. **Worker Threads**: 10 worker threads process files from the queue in parallel
4. **Keyword Search**: Each worker uses the KMP algorithm to efficiently search for the keyword
5. **Results**: Matching files are reported to standard output

The architecture uses:
- **SafeQueue**: Thread-safe queue with mutex protection
- **Producer-Consumer Pattern**: File scanner produces file paths, workers consume them
- **Thread Pool**: Fixed number of worker threads for consistent performance


## Performance Considerations

- **Optimal for Large Directories**: The multi-threaded approach provides significant speed improvements when searching large directory trees
- **Thread Count**: Configured with 10 worker threads (adjustable in `src/main.cpp`)
- **I/O Bound**: Performance scales well with SSD storage and multi-core processors

## Contributing

Feel free to submit issues or pull requests to improve this project.

## License

This project is provided as-is for educational and practical use.

## Author

Rajat1517

## Troubleshooting

### Issue: "Allowed usage: ./pfgrep <directory> <keyword>"

**Solution**: Make sure to provide exactly 2 arguments - a directory path and a keyword:

```bash
./pfgrep /path/to/search keyword
```

### Issue: "No files found" or no output

**Possible causes**:
- The directory doesn't exist (provide a valid path)
- The keyword doesn't exist in any files
- Permission issues preventing file access

**Solution**: Verify the directory path and keyword, and ensure you have read permissions:

```bash
ls -l /path/to/directory
./pfgrep /path/to/directory keyword
```

### Issue: Compilation errors

**Solution**: Ensure you have g++ with C++17 support installed:

```bash
g++ --version
```

If needed, install/update your compiler:

```bash
# Ubuntu/Debian
sudo apt-get install build-essential

# macOS with Homebrew
brew install gcc
```
