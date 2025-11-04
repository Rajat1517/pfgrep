#include <iostream>
#include <string>
#include "FileScanner.cpp"
#include "FileSearcher.cpp"


int main(int argc, char** argv){

    if(argc!=3){
        std::cerr<<"Allowed usage: "<<argv[0]<<" <directory> <keyword>"<<std::endl;
        return 1;
    }

    std::string directory= argv[1];
    std::string keyword= argv[2];

    
    FileScanner fs(directory);

    auto files= fs.getFiles();

    if(files.empty()){
        std::cout<<"No file found in the directory "<<directory<<std::endl;
        return 0;
    }

    for(auto &file:files){
        if(FileSearcher::containsKeyword(file,keyword)){
            std::cout<<file<<" contains "<<keyword<<std::endl;
        }
    }

    return 0;
}