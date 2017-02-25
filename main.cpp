#include <iostream>
#include "Note.h"

int main(){
    std::cout << "Test\n";
    Note a{ 5 };
    std::cout << a.name() << std::endl;
    Note b{ 9 };
    std::cout << a.higherInterval(b) << std::endl;
    std::cout << b.lowerInterval(a) << std::endl;
    exit(0);
}