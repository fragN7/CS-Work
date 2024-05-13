//
// Created by Alen on 24/04/2024.
//

#include <fstream>
#include "Document.h"

std::string Document::loadFile() {

    std::ifstream file(this->filename);
    std::string content;

    if(file.is_open()){
        std::string line;
        while(std::getline(file, line)){
            content += line + '\n';
        }

        file.close();
    }

    return content;
}
