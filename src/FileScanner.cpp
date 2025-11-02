#include <dirent.h>
#include <vector>
#include <string>
#include <cstring>
#include <sys/stat.h>


class FileScanner{

    std::string base;
    std::vector<std::string> allFiles;

    void parseDirectory(const std::string &src){

        DIR *directory= opendir(src.c_str());
        if(directory == nullptr){
            std::string err= "Could not open directory "+ src;
            perror(err.c_str());
            return;
        }
        struct dirent *entry;
        while((entry= readdir(directory))!= nullptr){
            if(strcmp(entry->d_name, ".")==0 || strcmp(entry->d_name,"..")==0)continue;

            std::string fullPath= src + "/"+ entry->d_name;
            struct stat info;
            if(stat(fullPath.c_str(), &info)==0){
                if(S_ISREG(info.st_mode)){
                    allFiles.push_back(fullPath);
                }
                else if (S_ISDIR(info.st_mode)) {
                    parseDirectory(fullPath);
                }
            }
            else{
                std::string err=  "stat failed for" + fullPath;
                perror(err.c_str());
                continue;
            }
        }

        closedir(directory);

    }

    public:

    FileScanner(const std::string &path): base(path){}


    std::vector<std::string> getFiles(){
        allFiles.clear();
        parseDirectory(base);
        return allFiles;
    }

};