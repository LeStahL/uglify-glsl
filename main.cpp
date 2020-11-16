#include "license.h"

#include "intermediate.h"

#include <iostream>
#include <string>
#include <list>

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
        << "-g [FILE] --generate-context-model" << std::endl
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

int main(int argc, char **args) {
    std::string executableName = args[0];
    std::list<std::string> includeDirectories;

    for(int i = 1; i < argc; ++i) {
        std::string argument = std::string(args[i]);

        if(argument == "-I") {
            ++i;
            
        }
        else if(argument.starts_with("-I"))
            includeDirectories.push_back(argument.substr(2));
        else if(argument == "-h" || argument == "--help") {
            printHelp();
            exit(0);
        }
        else if(argument == "-l" || argument == "--license") {
            printLicense();
            exit(0);
        }
    }

    return 0;
}
