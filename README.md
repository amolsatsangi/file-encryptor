# Multi-threaded File Encryption Tool

A high-performance, concurrent file encryption/decryption utility written in Modern C++17. Uses libsodium for authenticated encryption and implements a thread-safe producer-consumer pattern to process entire directory trees efficiently.

## Features

* **Authenticated Encryption** - Uses libsodium's `crypto_secretbox` (XSalsa20 + Poly1305)
* **Multi-threaded Processing** - Concurrent encryption/decryption using worker threads
* **Recursive Directory Support** - Processes entire directory trees automatically
* **Thread-Safe Operations** - Mutex-protected task queue with condition variables
* **Atomic File Updates** - Uses temporary files to prevent data corruption
* **Persistent Key Storage** - Automatically generates and stores encryption key

## Architecture Overview

<img width="1536" height="1024" alt="ChatGPT Image May 12, 2026, 11_28_44 PM" src="https://github.com/user-attachments/assets/01a07425-22d4-46fd-aff4-5a0691f79b43" />

## Prerequisites

* **Compiler**: GCC 9+ or Clang 10+ (C++17 support required)
* **Operating System**: Linux, macOS, or Windows (with MSVC 2019+)
* **Dependencies**:

  * libsodium (>= 1.0.18)
  * pthread (usually included with compiler)

## Installation

### Ubuntu/Debian

```bash
# Install dependencies
sudo apt update
sudo apt install build-essential libsodium-dev

# Clone repository
git clone https://github.com/amolsatsangi/file-encryptor.git
cd file-encryptor

# Build
g++ -std=c++17 -pthread \
    main.cpp \
    src/app/processes/ProcessManagement.cpp \
    src/app/fileHandling/IO.cpp \
    src/app/encryptDecrypt/Cryption.cpp \
    src/app/crypto/SodiumCryptoEngine.cpp \
    -lsodium \
    -o encrypt_tool
```
## Run
```bash
./encrypt_tool
```
## Usage Example

```text
Enter the directory path:
test

Enter the action (encrypt/decrypt)
encrypt

Thread 1 Executing task: test/test1.txt
Thread 2 Executing task: test/test2.txt
Thread 3 Executing task: test/test3.txt
```

## License

This project is licensed under the MIT License - see the LICENSE file for details.

## Author
Amol Satsangi
