#include <iostream>
#include <algorithm>
#include <string>
#include <filesystem>
#include <fstream>
#include "Global.h"
using namespace std;
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
		exit(0);
	}
	if (response == 'n')
	{
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
	projectname.erase(remove(projectname.begin(), projectname.end(), '\n'), projectname.end());
	name.erase(remove(name.begin(), name.end(), '\n'), name.end());
	auto path = std::filesystem::current_path();
	filesystem::create_directory(projectname);
	ofstream mainfile;
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
	hglobal << "//" << projectname << " Global file\n";
	hglobal << "// - Only put variables for build and other scripts \n";
	hglobal << "// - Do not put varible names that contain names from other headers or scripts\n";
	hglobal << "#ifndef GLOBALS\n";
	hglobal << "#define GLOBALS\n";
	hglobal << "#include <iostream>\n";
	hglobal << "#include <fstream>\n";
	hglobal << "#include <string>\n";
	hglobal << "#include <stdlib.h>\n";
	hglobal << "extern std::string ver;\n";
	hglobal << "extern std::string build_type;\n";
	hglobal << "#endif	\n";
	hglobal.close();
	cout << "Done making project " << projectname << "\n";
}