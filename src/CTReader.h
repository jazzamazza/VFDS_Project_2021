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
            int getDim(std::string& hdrPath);
            std::string getDir(std::string& hdrPath);
            unsigned char *** readPGMStack(std::string& dir, int& dim);
            unsigned char *** readPGMStack(std::string& hdrPath);
    };
}

#endif
