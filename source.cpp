#include <cryptopp/sha.h>
#include <cryptopp/filters.h>
#include <cryptopp/hex.h>
#include <iostream>
#include <string>
#include <getopt.h>

int main(int argc, char* argv[]) {
    CryptoPP::SHA256 hash;
    std::string digest;
    std::string line;

    bool useUppercase = false;

    struct option long_options[] = {
        {"string", required_argument, 0, 's'},
        {"letter_case", required_argument, 0, 'l'},
        {0, 0, 0, 0}
    };

    int opt;
    int option_index = 0;
    while ((opt = getopt_long(argc, argv, "s:l:", long_options, &option_index)) != -1) {
        switch (opt) {
            case 's':
                line = optarg;
                break;
            case 'l':
                if (std::string(optarg) == "upper") {
                    useUppercase = true;
                } else if (std::string(optarg) == "lower") {
                    useUppercase = false;
                } else {
                    std::cerr << "Invalid argument for --letter_case: " << optarg << std::endl;
                    return 1;
                }
                break;
            default:
                std::cerr << "Usage: " << argv[0] << " --string <string to hash> [--letter_case upper|lower]" << std::endl;
                return 1;
        }
    }

    if (line.empty()) {
        std::cerr << "No string provided to hash. Use --string option." << std::endl;
        return 1;
    }

    CryptoPP::StringSource s(line, true, 
        new CryptoPP::HashFilter(hash, 
            new CryptoPP::HexEncoder(
                new CryptoPP::StringSink(digest), useUppercase)));

    std::cout << digest << std::endl;

    return 0;
}