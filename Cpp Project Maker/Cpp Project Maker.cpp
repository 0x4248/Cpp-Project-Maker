// Cpp Project Maker
// By:0x4248
#include "Global.h"
#include <algorithm>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>

using namespace std;

int dirExists(const char *const path) {
    //>0 if dir exists AND is a dir,
    // 0 if dir does not exist OR exists but not a dir,
    //<0 if an error occurred (errno is also set)

    struct stat info;

    int statRC = stat(path, &info);
    if (statRC != 0) {
        if (errno == ENOENT) {
            return 0;
        } // something along the path does not exist
        if (errno == ENOTDIR) {
            return 0;
        } // something in path prefix is not a dir
        return -1;
    }

    return (info.st_mode & S_IFDIR) ? 1 : 0;
}

int main() {
    cout << "Welcome to the C++ Project Maker " << ver << " " << build_type
         << "\n";
    char response;
    cout << "--------------------\n";
    cout << "Do you want to continue (Y/N):";
    cin >> response;
    cout << "--------------------\n";
    if (response == 'N') {
        cout << "[ \033[0;32mOK \033[0;37m] N received closing app\n";
        exit(0);
    }
    if (response == 'n') {
        cout << "[ \033[0;32mOK \033[0;37m] n received closing app\n";
        exit(0);
    }
    string projectname;
    cout << "Enter a project name:";
    cin >> projectname;
    string name;
    cout << "--------------------\n";
    cout << "Enter your name or the author:";
    cin >> name;
    cout << "--------------------\n";
    cout << "[ \033[0;32mOK \033[0;37m] Formatting strings\n";
    projectname.erase(remove(projectname.begin(), projectname.end(), '\n'),
                      projectname.end());
    cout << "[ \033[0;32mOK \033[0;37m] Formatted projectname\n";
    name.erase(remove(name.begin(), name.end(), '\n'), name.end());
    cout << "[ \033[0;32mOK \033[0;37m] Formatted name\n";
    if (dirExists(projectname.c_str()) > 0) {
        cout << "[ \033[0;33mWARN \033[0;37m] Project exists\n";
        char response;
        cout << "--------------------\n";
        cout << "The folder exists do you want to contintue (Y/N):";
        cin >> response;
        cout << "--------------------\n";
        if (response == 'N') {
            cout << "[ \033[0;32mOK \033[0;37m] N received closing app\n";
            exit(0);
        }
        if (response == 'n') {
            cout << "[ \033[0;32mOK \033[0;37m] n received closing app\n";
            exit(0);
        }
    }

    auto path = filesystem::current_path();
    cout << "[ \033[0;32mOK \033[0;37m] Creating project directory\n";
    filesystem::create_directory(projectname);
    cout << "[ \033[0;32mOK \033[0;37m] Creating modules directory\n";
    filesystem::create_directory(projectname + "/modules");
    cout << "[ \033[0;32mOK \033[0;37m] Creating bin directory\n";
    filesystem::create_directory(projectname + "/bin");
    ofstream mainfile;
    cout << "[ \033[0;32mOK \033[0;37m] Creating main.cpp\n";
    mainfile.open(projectname + "/main.cpp");
    mainfile << "//Project:" + projectname + "\n";
    mainfile << "//Author:" + name + "\n";
    mainfile << "#include <iostream>\n";
    mainfile << "#include " << '"' << "Global.h" << '"' << "\n";
    mainfile << "using namespace std;";
    mainfile << "int main(int argc, char** argv) {\n";
    mainfile << "	cout << " << '"' << "Hello World!" << '"' << ";\n";
    mainfile << "}\n";
    mainfile.close();
    ofstream cppglobal;
    cout << "[ \033[0;32mOK \033[0;37m] Creating Global.cpp\n";
    cppglobal.open(projectname + "/Global.cpp");
    cppglobal << "//" << projectname << " Global file\n";
    cppglobal << "// - Only put variables for build and other scripts \n";
    cppglobal << "// - Do not put variable names that contain names from other "
                 "headers or scripts\n";
    cppglobal << "#include " << '"' << "Global.h" << '"' << "\n";
    cppglobal << "#include <fstream>\n";
    cppglobal << "#include <string>\n";
    cppglobal << "#include <stdlib.h>\n";
    cppglobal << "std::string ver =" << '"' << "0.0.0.0" << '"' << ";\n";
    cppglobal << "std::string build_type = " << '"' << "BETA" << '"' << ";\n";
    cppglobal.close();
    ofstream hglobal;
    hglobal.open(projectname + "/Global.h");
    cout << "[ \033[0;32mOK \033[0;37m] Creating Global.h\n";
    hglobal << "//" << projectname << " Global file\n";
    hglobal << "// - Only put variables for build and other scripts \n";
    hglobal << "// - Do not put variable names that contain names from other "
               "headers or scripts\n";
    hglobal << "#ifndef GLOBALS\n";
    hglobal << "#define GLOBALS\n";
    hglobal << "#include <iostream>\n";
    hglobal << "#include <fstream>\n";
    hglobal << "#include <string>\n";
    hglobal << "#include <stdlib.h>\n";
    hglobal << "extern std::string version;\n";
    hglobal << "extern std::string build_type;\n";
    hglobal << "#endif	\n";
    hglobal.close();
    cout << "[ \033[0;32mOK \033[0;37m] Creating read me\n";
    ofstream readme;
    readme.open(projectname + "/README.md");
    readme << "#" << projectname << "\n";
    readme << "By:" << name << "\n";
    cout << "{\n      project_name:" << projectname
         << ",\n      author:" << name << "\n}\n";
    cout << "Done making project go have a look and good luck with "
         << projectname << "\n";
}