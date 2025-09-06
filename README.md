# Z++ (Zig Plus Plus)

[![Build Status](https://github.com/pooriayousefi/zpp/actions/workflows/ci.yml/badge.svg)](https://github.com/pooriayousefi/zpp/actions/workflows/ci.yml)
[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++20](https://img.shields.io/badge/C%2B%2B-20-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B20)
[![CMake](https://img.shields.io/badge/CMake-3.20%2B-green.svg)](https://cmake.org/)

A modern C++20 cross-compilation build system generator that leverages Zig's cross-compilation capabilities to build C++ projects for multiple target architectures and platforms.

## 🚀 Features

- **Multi-Target Support**: Build for 8+ different target architectures
- **Zig-Powered**: Leverages Zig's excellent cross-compilation toolchain
- **Interactive CLI**: User-friendly command-line interface for target selection
- **Modern C++20**: Built with contemporary C++ standards
- **Cross-Platform**: Works on Linux, macOS, and Windows

## 🎯 Supported Targets

| Target | Architecture | Platform | ABI |
|--------|--------------|----------|-----|
| `x86_64-unknown-linux-gnu` | x86_64 | Linux | GNU |
| `armv7-unknown-linux-gnueabihf` | ARM v7 | Linux | GNU HF |
| `x86_64-unknown-linux-musl` | x86_64 | Linux | musl |
| `arm64-unknown-linux-gnu` | ARM64 | Linux | GNU |
| `aarch64-apple-darwin` | ARM64 | macOS | Darwin |
| `x86_64-apple-darwin` | x86_64 | macOS | Darwin |
| `i686-pc-windows-msvc` | x86 | Windows | MSVC |
| `x86_64-pc-windows-msvc` | x86_64 | Windows | MSVC |

## 🎯 Quick Start

```bash
# Run Z++ interactively
./z++

# Follow the prompts:
# 1. Enter your project root path
# 2. Select target architecture(s)
# 3. Z++ generates build configurations
```

## 🏗️ Building from Source

```bash
# Clone repository
git clone https://github.com/pooriayousefi/zpp.git
cd zpp

# Build with default settings
cmake --preset=default
cmake --build build/default
```

## 📄 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

**Author**: [Pooria Yousefi](https://github.com/pooriayousefi)  
**Repository**: [https://github.com/pooriayousefi/zpp](https://github.com/pooriayousefi/zpp)
