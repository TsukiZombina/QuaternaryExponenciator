#include <iostream>
#include <cstdlib>
//#include <cstdint>
//#include <bitset>

//unsigned long binaryExp(unsigned long M, unsigned long e, unsigned long n);
void preprocessing(unsigned long M, unsigned long* calculatedExp);
//void d2b_le(unsigned long e, int* bit); 
//void d2b_be(unsigned long e, std::bitset<32>& bits);
unsigned long get_Fi(unsigned long e, unsigned index);
unsigned long quaternaryExp(unsigned long M, unsigned long e, unsigned long n);

int main(int argc, char const* argv[]) {
    if (argc != 4) {
        std::cerr << "Args: M, e, n" << std::endl;
        return 1;
    }
    unsigned long M = std::atol(argv[1]);
    unsigned long e = std::atol(argv[2]);
    unsigned long n = std::atol(argv[3]);
    //std::cout<< binaryExp(4294967295, 7, 32) << std::endl;
    std::cout<< quaternaryExp(M, e, n) << std::endl;
	return 0;
}

unsigned long quaternaryExp(unsigned long M, unsigned long e, unsigned long n) {
    unsigned long preprocessed[4], C;
    preprocessing(M, preprocessed); //1
    C = preprocessed[get_Fi(e, 15)];
    for (int i = 14; i >= 0; i--) {
        C = C * C * C * C % n;
        if (get_Fi(e, i) != 0)
            C = C * preprocessed[get_Fi(e, i)] % n;
    }
    return C;
}

/*unsigned long binaryExp(unsigned long M, unsigned long e, unsigned long n) {
    unsigned long C;
    std::bitset<32> binary(e);
    if (binary[31])
        C = M;
    else
        C = 1;
    for (int i = 30; i >= 0; i--) {
        C = (C * C) % n;
        if(binary[i])
            C = (C * M) % n;
    }
    return C;
}*/

/*unsigned long binaryStringExp(unsigned long M, unsigned long e, unsigned long n) {
    unsigned long C;
    std::string binary = std::bitset<32>(e).to_string();
    int m = binary.length();
    if (binary[0] == '1')
        C = M;
    else
        C = 1;
    for (int i = 1; i < 32; i++) {
        C = (C * C) % n;
        if(binary[i] == '1')
            C = (C * M) % n;
    }
    unsigned long decimal = std::bitset<32>(C).to_ulong();
    return decimal;
}*/

void preprocessing(unsigned long M, unsigned long* calculatedExp) {
    calculatedExp[0] = 1;
    calculatedExp[1] = M;
    calculatedExp[2] = M * M;
    calculatedExp[3] = calculatedExp[2] * M;
}

/*void d2b_le(unsigned long e, int* bits) {
    for (unsigned i = 0; i < 32; i++)
        *(bits++) = (e >> i) & 0x1;
}

void d2b_be(unsigned long e, int* bits) {
    for(unsigned i = 0; i < 32; i++)
        *bits = (((0x80000000 >> i) & e) == 0) ? 0 : 1;
}

void decompose(unsigned long e, int* indices) {
    for(unsigned i = 0; i < 16; i++)
        *indices = ((0xC0000000 >> i * 2) & e) >> 30 - 2 * i;
}*/

unsigned long get_Fi(unsigned long e, unsigned index) {
    return ((3 << (index << 1)) & e) >> (index << 1);
}
