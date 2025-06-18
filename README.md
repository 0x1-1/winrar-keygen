# WinRAR Key Generator

A tool for generating WinRAR registration keys.

## Project Structure

```
winrar-keygen/
├── include/              # Header files
│   ├── core/            # Core functionality
│   │   ├── WinRarKeygen.hpp
│   │   └── WinRarConfig.hpp
│   ├── crypto/          # Cryptographic implementations
│   │   ├── BigInteger.hpp
│   │   ├── EllipticCurveGF2m.hpp
│   │   └── GaloisField.hpp
│   └── utils/           # Utility functions
│       ├── Hasher.hpp
│       ├── HasherCrc32Traits.hpp
│       └── HasherSha1Traits.hpp
├── src/                 # Source files
│   └── main.cpp         # Main application entry point
└── README.md           # Project overview

```

## Directory Purpose

- `include/core/`: Contains the main key generation logic and configuration
- `include/crypto/`: Contains cryptographic implementations like elliptic curve and finite field arithmetic
- `include/utils/`: Contains utility functions for hashing and other operations
- `src/`: Contains the main application source code

## Building

This project uses C++17 and requires:
- Windows SDK
- Visual Studio 2019 or later
- C++17 compliant compiler

## Usage

```bash
winrar-keygen.exe <Username> <License Type>
```

For example:
```bash
winrar-keygen.exe "John Doe" "Single PC usage license"
```
