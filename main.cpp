/**
    Aritmética Computacional
    main.cpp
    Purpose: Calculates M ^ e (mod n) with the quaternary method.

    @author Zelzin Márquez
    @version 1.0 27/11/17
*/
#include <iostream> //std::cout, std::cerr
#include <cstdlib> //std::atol

/**
    Returns an array of preprocessed exponenciations.

    @param M The radix.
    @param calculatedExp Base address to the array which store the preprossed
    exponenciations from M^0 to M^3.
*/
void preprocessing(unsigned long M, unsigned long* calculatedExp);
/**
    Returns the index values to access the preproceesed array.
    Access by pairs the F array in which are stored the bits of exponent e.
    @param e The exponent.
    @param index The index to be acessed in the preprocessed array.
*/
unsigned long get_Fi(unsigned long e, unsigned index);
/**
    Returns M^e (mod n).
    @param M The radix.
    @param e The exponent.
    @param n The divisor.
*/
unsigned long quaternaryExp(unsigned long M, unsigned long e, unsigned long n);

int main(int argc, char const* argv[]) {
    if (argc != 4) {
        std::cerr << "Args: M, e, n" << std::endl;
        return 1;
    }
    unsigned long M = std::atol(argv[1]);
    unsigned long e = std::atol(argv[2]);
    unsigned long n = std::atol(argv[3]);
    std::cout<< quaternaryExp(M, e, n) << std::endl;
	return 0;
}

unsigned long quaternaryExp(unsigned long M, unsigned long e, unsigned long n) {
    unsigned long preprocessed[4], C;
    preprocessing(M, preprocessed);
    C = preprocessed[get_Fi(e, 15)];
    for (int i = 14; i >= 0; i--) {
        C = C * C * C * C % n;
        if (get_Fi(e, i) != 0)
            C = C * preprocessed[get_Fi(e, i)] % n;
    }
    return C;
}

void preprocessing(unsigned long M, unsigned long* calculatedExp) {
    calculatedExp[0] = 1;
    calculatedExp[1] = M;
    calculatedExp[2] = M * M;
    calculatedExp[3] = calculatedExp[2] * M;
}

unsigned long get_Fi(unsigned long e, unsigned index) {
    return ((3 << (index << 1)) & e) >> (index << 1);
}
