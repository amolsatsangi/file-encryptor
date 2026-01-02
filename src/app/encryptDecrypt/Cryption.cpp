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

    task.f_stream.clear();
    task.f_stream.seekp(0);
    task.f_stream.write(reinterpret_cast<const char*>(result.data()),result.size());

    task.f_stream.close();
    return 0;
}
