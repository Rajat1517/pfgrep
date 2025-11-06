#include "FileScanner.hpp"
#include <dirent.h>
#include <sys/stat.h>
#include <cstring>
#include <iostream>

void* FileScanner::parseDirectory(void* args) {
    auto* arguments = static_cast<ScanArgs*>(args);

    DIR* directory = opendir(arguments->path.c_str());
    if (directory == nullptr) {
        std::cerr << "Could not open directory " << arguments->path << std::endl;
        return nullptr;
    }

    struct dirent* entry;
    while ((entry = readdir(directory)) != nullptr) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        std::string fullPath = arguments->path + "/" + entry->d_name;
        struct stat info;
        if (stat(fullPath.c_str(), &info) == 0) {
            if (S_ISREG(info.st_mode)) {
                arguments->safequeue->push(fullPath);
            } else if (S_ISDIR(info.st_mode)) {
                ScanArgs subArgs{ arguments->safequeue, fullPath };
                parseDirectory(&subArgs);
            }
        } else {
            std::cerr << "stat failed for " << fullPath << std::endl;
            continue;
        }
    }

    closedir(directory);

    // if (pthread_self() == main_producer_thread_id)
    //     arguments->safequeue->setDone();

    return nullptr;
}
