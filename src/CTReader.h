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
            int dim;
            std::string dir="";

        public:
            CTReader(void);
            ~CTReader();

            void setDim(std::string& hdrPath);
            int getDim(std::string& hdrPath);
            int getDim();

            void setDir(std::string& hdrPath);
            std::string getDir(std::string& hdrPath);
            std::string getDir();

            unsigned char *** readPGMStack(std::string& hdrPath);
            unsigned char *** readPGMStack(std::string& dir, int& dim);

            std::string getPGM(std::string& hdrPath, const int& layer);
    };
}

#endif
