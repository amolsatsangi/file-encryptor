# file-encryptor

A simple command-line tool to **encrypt and decrypt files** securely.

---

## 🚀 Features

- Encrypt any file with a **key** 
- Decrypt encrypted files using the correct credentials  
- Lightweight and platform-agnostic (written in C++)  
- Ideal for securing sensitive data on disk or before sharing  
- MIT-licensed — free and open source

---

## 🧰 Prerequisites

- A C++ compiler (e.g. `g++`, `clang`) supporting C++11 or later  

---

## 💻 Installation

Clone the repository:

```bash
git clone https://github.com/amolsatsangi/file-encryptor.git
cd file-encryptor
```
Build the project (example with g++):
```
g++ -std=c++11 -o file-encryptor main.cpp
```
🎯 Usage

# Encrypt a file
./file-encryptor encrypt <input-file> <output-file> <password-or-key>

# Decrypt a file
./file-encryptor decrypt <encrypted-file> <decrypted-output-file> <password-or-key>
