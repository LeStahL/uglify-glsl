#include "license.h"

#include "intermediate.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include <vector>

void printLicense() {
    std::cout << licenseString << std::endl;
}

void printHelp() {
    std::cout << "uglify-glsl  Copyright (C) 2020  Alexander Kraus <nr4@z10.info>" << std::endl
        << "This program comes with ABSOLUTELY NO WARRANTY; for details type `uglify-glsl -l' or `uglify-glsl --license'." << std::endl
        << "This is free software, and you are welcome to redistribute it" << std::endl
        << "under certain conditions; type `uglify-glsl -l' or `uglify-glsl --license' for details." << std::endl
        << std::endl
        << "Usage:" << std::endl
        << "uglify-glsl [FILES]: uglify input files." << std::endl
        << "-h, --help: Display this information and exit" << std::endl
        << "-I[PATH-OR-COMMA-SEPARATED-PATH-LIST], --include-dir [PATH-OR-COMMA-SEPARATED-PATH-LIST], --include-dir=[PATH-OR-COMMA-SEPARATED-PATH-LIST]: Add path or path list to list of search paths for shader files" << std::endl
        << "-o [FILE], --output [FILE], --output=[FILE]: Output the result to this specific file." << std::endl
        << "--glsl: Output result to shader source file" << std::endl
        << "--header: Output result to C header file" << std::endl
        << "--header-constant [IDENTIFIER]: Change the identifier of the exported source constant" << std::endl
        << "-g [FILE] --generate-context-model [FILE]: Creates the context model of all input files and saves it in FILE." << std::endl
        << "-c [FILE] --context-model [FILE]: Use context model from FILE for minification" << std::endl
        << "-l, --license: Print the license and exit" << std::endl;
}

void checkArgumentPresent(int i, int argc, std::string dependentArgument) {
    if(i >= argc) {
        std::cout << "Error: Option " << dependentArgument 
            << " is missing a positional argument." << std::endl;
        printHelp();
        exit(0);
    }
}

std::vector<std::string> split(std::string str) {
    std::vector<std::string> splittedString;
    std::istringstream f(str);

    while(std::getline(f, str, ','))
        splittedString.push_back(str);
    return splittedString;
}

std::string fileContent(std::string fileName) {
    std::ifstream t(fileName);
    std::string str;

    if(!t.is_open()) {
        std::cout << "Error: Could not open file " << fileName
            << "." << std::endl;
        exit(0);
    }

    t.seekg(0, std::ios::end);   
    str.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    str.assign((std::istreambuf_iterator<char>(t)),
        std::istreambuf_iterator<char>());
    
    return str;
}

int main(int argc, char **args) {
    std::string executableName = args[0],
        contextModelFilename;
    std::vector<std::string> includeDirectories,
        shaderFileNames,
        shaderSources;
    bool saveContextModel = false;

    for(int i = 1; i < argc; ++i) {
        std::string argument = std::string(args[i]);

        if(argument == "-I" || argument == "--include-dir") {
            ++i;
            checkArgumentPresent(i, argc, argument);
            
            std::vector splittedString = split(std::string(args[i]));
            includeDirectories.insert(includeDirectories.end(), splittedString.begin(), splittedString.end());
        }
        else if(argument.starts_with("-I")) {
            std::vector splittedString = split(std::string(argument.substr(2)));
            includeDirectories.insert(includeDirectories.end(), splittedString.begin(), splittedString.end());
        }
        else if(argument == "-h" || argument == "--help") {
            printHelp();
            exit(0);
        }
        else if(argument == "-l" || argument == "--license") {
            printLicense();
            exit(0);
        }
        else if(argument == "-g" || argument == "--generate-context-model") {
            saveContextModel = true;

            ++i;
            checkArgumentPresent(i, argc, argument);

            contextModelFilename = std::string(args[i]);
        }
        else
            shaderFileNames.push_back(std::string(args[i]));
    }

    // Load all shader files and create their intermediate representation.
    // Remove comments and unneeded spaces and CRLFs. Then proceed with 
    // any analysis specified.
    for(int i = 0; i < shaderFileNames.size(); ++i) {
        shaderSources.push_back(fileContent(shaderFileNames[i]));
    }

    return 0;
}
