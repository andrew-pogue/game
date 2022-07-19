#pragma once
#include <string>

const char* get_filename(const char *path) {
    std::string file = path, name = "", ext = "";
    auto i = file.size() - 1;
    
    for (; i > 0; i--) {
        ext.insert(0, 1, file[i]);
        if (file[i] == '.') break;
    }
    
    if (i>0) i--;
    for (; i > 0; i--) {
        if (file[i] == '/' || file[i] == '\\') break;
        name.insert(0, 1, file[i]);
    }

    return name.c_str();
}