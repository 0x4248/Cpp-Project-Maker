#include <iostream>
#include <algorithm>
#include <string>
#include <filesystem> 
#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>
#include "Global.h"


using namespace std;

int dirExists(const char* const path)
{
	//Checks to see if a directory exists. Note: This method only checks the
	//existence of the full path AND if path leaf is a dir.
	//
	//@return  >0 if dir exists AND is a dir,
	//          0 if dir does not exist OR exists but not a dir,
	//          <0 if an error occurred (errno is also set)

	struct stat info;

	int statRC = stat(path, &info);
	if (statRC != 0)
	{
		if (errno == ENOENT) { return 0; } // something along the path does not exist
		if (errno == ENOTDIR) { return 0; } // something in path prefix is not a dir
		return -1;
	}

	return (info.st_mode & S_IFDIR) ? 1 : 0;
}

int main()
{
	cout << "Welcome to the C++ Project Maker " << ver <<" " << build_type<<"\n";
	char response;
	cout << "--------------------\n";
	cout << "Do you want to continue (Y/N):";
	cin >> response;
	cout << "--------------------\n";
	if (response == 'N')
	{
		cout << "[ \033[0;32mOK \033[0;37m] N received closing app\n";
		exit(0);
	}
	if (response == 'n')
	{
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
	projectname.erase(remove(projectname.begin(), projectname.end(), '\n'), projectname.end());
	cout << "[ \033[0;32mOK \033[0;37m] Formatted projectname\n";
	name.erase(remove(name.begin(), name.end(), '\n'), name.end());
	cout << "[ \033[0;32mOK \033[0;37m] Formatted name\n";
	if (dirExists(projectname.c_str()) > 0){
		cout << "[ \033[0;33mWARN \033[0;37m] Project exists\n";
		char response;
		cout << "--------------------\n";
		cout << "The folder exists do you want to contintue (Y/N):";
		cin >> response;
		cout << "--------------------\n";
		if (response == 'N')
		{
			cout << "[ \033[0;32mOK \033[0;37m] N received closing app\n";
			exit(0);
		}
		if (response == 'n')
		{
			cout << "[ \033[0;32mOK \033[0;37m] n received closing app\n";
			exit(0);
		}
	}

	auto path = filesystem::current_path();
	cout << "[ \033[0;32mOK \033[0;37m] Creating project directory\n";
	filesystem::create_directory(projectname);
	cout << "[ \033[0;32mOK \033[0;37m] Creating modules directory\n";
	filesystem::create_directory(projectname+"/modules");
		cout << "[ \033[0;32mOK \033[0;37m] Creating bin directory\n";
	filesystem::create_directory(projectname+"/bin");
	ofstream mainfile;
	cout << "[ \033[0;32mOK \033[0;37m] Creating mainfile\n";
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
	cout << "[ \033[0;32mOK \033[0;37m] Creating cpp global file\n";
	cppglobal.open(projectname + "/Global.cpp");
	cppglobal << "//" << projectname << " Global file\n";
	cppglobal << "// - Only put variables for build and other scripts \n";
	cppglobal << "// - Do not put varible names that contain names from other headers or scripts\n";
	cppglobal << "#include " << '"' << "Global.h" << '"' << "\n";
	cppglobal << "#include <fstream>\n";
	cppglobal << "#include <string>\n";
	cppglobal << "#include <stdlib.h>\n";
	cppglobal << "std::string ver =" << '"' << "0.0.0.0" << '"' << ";\n";
	cppglobal << "std::string build_type = " << '"' << "BETA" << '"' << ";\n";
	cppglobal.close();
	ofstream hglobal;
	hglobal.open(projectname + "/Global.h");
	cout << "[ \033[0;32mOK \033[0;37m] Creating cpp header file\n";
	hglobal << "//" << projectname << " Global file\n";
	hglobal << "// - Only put variables for build and other scripts \n";
	hglobal << "// - Do not put varible names that contain names from other headers or scripts\n";
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
	cout << "[ \033[0;32mOK \033[0;37m] Creating readme\n";
	ofstream readme;
	readme.open(projectname + "/README.md");
	readme << "#" << projectname << "\n";
	readme << "By:" << name << "\n";
	cout << "{\n      projectname:" << projectname << ",\n      author:" << name << "\n}\n";
	cout << "Done making project " << projectname << "\n";
}