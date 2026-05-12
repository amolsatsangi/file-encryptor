# file-encryptor

A lightweight C++ application for securely encrypting and decrypting files in bulk.  
It scans a directory recursively, creates tasks for each file, queues them, and processes them through a clean, modular pipeline.

---

## 🚀 Features
- Recursive directory scanning and batch file processing  
- Queue-based task management system (`std::queue<std::unique_ptr<Task>>`)  
- Clean separation of concerns: IO, Task, Process Management, and Encryption  
- In-place file encryption/decryption using environment-based key  
- RAII and smart-pointer ownership for safe file handling  
- Simple CLI interface, no Makefile required  

---

## 📦 Build Instructions

Clone the repository:
```bash
git clone https://github.com/amolsatsangi/file-encryptor.git
cd file-encryptor
```
Compile using any C++11+ compiler:
```
g++ main.cpp \
src/app/processes/ProcessManagement.cpp \
src/app/encryptDecrypt/Cryption.cpp \
src/app/fileHandling/IO.cpp \
src/app/crypto/SodiumCryptoEngine.cpp \
-o file_encryptor \
-std=c++17 \
-lsodium
```
## 📖 Usage

### Set your Environment Key:
The application requires an encryption key (integer). Ensure your environment or .env loader (via ReadEnv.cpp) is configured correctly.

Example (if using standard env vars in terminal):
```
export ENV_KEY=12345  # Linux/Mac
set ENV_KEY=12345     # Windows CMD
```
### Run the executable
```
./file_encryptor
```
Follow the prompts:

Directory: Enter the full path to the folder you want to process.
Action: Type encrypt to lock files or decrypt to unlock them.

Example:
```
Enter the directory path:
/home/user/documents/secret_folder
Enter the action (encrypt/decrypt)
encrypt
```

Output:
```
Executing task: /home/user/documents/secret_folder/file1.txt,ENCRYPT
Executing task: /home/user/documents/secret_folder/image.png,ENCRYPT
```
## 📂 Project Structure

```
file-encryptor/
├── main.cpp                       # Entry point, handles user input and directory recursion
└── src/
    └── app/
        ├── encryptDecrypt/
        │   ├── Cryption.cpp       # Encryption/Decryption logic
        │   └── Cryption.hpp
        ├── fileHandling/
        │   ├── IO.cpp             # File stream management
        │   ├── IO.hpp
        │   └── ReadEnv.cpp        # Environment variable loader
        └── processes/
            ├── ProcessManagement.cpp # Task queue manager
            ├── ProcessManagement.hpp
            └── Task.hpp           # Task structure definition
```

## 📜 License

This project is open-source under the MIT License.
