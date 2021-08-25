// Header file for the CTReader class

#include <iostream>
#include <string>
#include <memory>

namespace imgread {
    class CTReader {
        private:
        public:
            CTReader(void);
            ~CTReader();

            std::vector< std::vector < std::vector<unsigned char[]>[]>[]> readPGMStack(const std::string header, const int dim);

    };
}