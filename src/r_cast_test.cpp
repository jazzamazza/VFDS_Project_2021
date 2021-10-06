// testing for ray_casting
# include "CTReader.h"
# include "VolumeVisualizer.h"
# include "RaySampler.h"

int main(void) {
    raycst::VolumeVisualizer vv(256);
    //vv.getAxis_1().printVec3();
    //vv.getAxis_2().printVec3();
    
    imgread::CTReader ctr;
    std::string hdr = "home/noahdenicola/Desktop/Capstone/core/vfds/images/cross256_14/test-D256-V3086-F14-.hdr";
    int dim = 256;
std::cout << "here" << std::endl; 
    unsigned char *** data = ctr.imgread::CTReader::readPGMStack(hdr);
    raycst::RaySampler rs(dim, 2);

    //write out
    for (int i = 0; i < 10; ++i) {
        unsigned char ** ip = rs.sample(data, vv);
        vv.moveCOP(0);
        std::string sz = std::to_string(i);
        std::ofstream out("castup"+sz+".pgm", std::ofstream::binary);
        out << "P5" <<"\n";
        out << dim << " ";
        out << dim << "\n";
        out << "255" << "\n";
            
        char* wbuf = new char[dim];
        for(int x=0; x<dim; x++)
        {
            wbuf = reinterpret_cast<char *>(ip[x]);
            out.write(wbuf, dim);
        }

        out.close();
    }
    return 0;
}
