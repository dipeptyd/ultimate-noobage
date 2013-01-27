#include <iostream>
#include <cstdio>
#include <cstdlib>


int main()
{
    char a[] = "ff f0 ff ff";

    long foo;

    char *aEnd;
    std::cout << &(*aEnd)  << " : " << &aEnd << std::endl;
    std::cout << std::strtol(a,&aEnd, 16) << std::endl;
    std::cout << &(*aEnd)  << " : " << &aEnd << std::endl;
    std::cout << std::strtol(aEnd,&aEnd, 16) << std::endl;
    std::cout << &(*aEnd)  << " : " << &aEnd << std::endl;
    std::cout << std::strtol(aEnd,&aEnd, 16) << std::endl;
    std::cout << &(*aEnd)  << " : " << &aEnd << std::endl;
    std::cout << std::strtol(aEnd,&aEnd, 16) << std::endl;
    std::cout << &(*aEnd)  << " : " << &aEnd << std::endl;
    //std::cout << &aEnd << aEnd << std::endl;
    //std::cout << foo;



    //std::cout << "derpderpderp " + std::to_string(a) << std::endl;
    





    return 0;
}
