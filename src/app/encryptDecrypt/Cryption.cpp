#include "../crypto/SodiumCryptoEngine.hpp"
#include "../processes/Task.hpp"

#include <vector>
#include <iterator>
#include <fstream>

int executeCrypto(Task& task) {
    SodiumCryptoEngine crypto;

    std::istreambuf_iterator<char> begin(task.f_stream);
    std::istreambuf_iterator<char> end;
    std::vector<uint8_t> buffer(begin, end);

    if (buffer.empty()) {
        task.f_stream.close();
        return 0;
    }

    std::vector<uint8_t> result =(task.action == Action::ENCRYPT)? crypto.encrypt(buffer): crypto.decrypt(buffer);

    
    std::string tmpPath = task.filePath + ".tmp";

    // write to temp file
    std::ofstream out(tmpPath, std::ios::binary | std::ios::trunc);
    out.write(reinterpret_cast<const char*>(result.data()), result.size());
    out.close();

    // replace original atomically
    std::rename(tmpPath.c_str(), task.filePath.c_str());

    return 0;
}
