#include <iostream>
#include "FileScanner.cpp"


int main(){
    
    FileScanner fs("..");

    auto files= fs.getFiles();

    for(auto &file:files){
        std::cout<<file<<std::endl;
    }

    return 0;
}