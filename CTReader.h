// Header file for the CTReader class

#ifndef CTREADER_H
#define CTREADER_H

#include <fstream>
#include <iostream>
#include <string>
#include <memory>
#include "Voxel.h"

namespace imgread {
    class CTReader {
        private:
        public:
            CTReader(void);
            ~CTReader();

            unsigned char *** readPGMStack(const std::string& header, const int& dim);
    };
}

#endif