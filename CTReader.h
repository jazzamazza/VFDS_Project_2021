// Header file for the CTReader class

#ifndef CTREADER_H
#define CTREADER_H

#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include <regex>

namespace imgread {
    class CTReader {
        private:
        public:
            CTReader(void);
            ~CTReader();

            unsigned char *** readPGMStack(std::string& dir, int& dim);
    };
}

#endif