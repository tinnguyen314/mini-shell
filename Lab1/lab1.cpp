#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sstream>
#include <set>
//#include <algorithm> 
//#include <cctype>
//#include <locale>



std::vector<std::string> split(const std::string& , const std::string& regex);
inline void ltrim(std::string &s);
inline void rtrim(std::string &s);
inline void trim(std::string &s);
std::string change_prompt(const std::vector<std::string>&, std::string&);
void info (const std::vector<std::string>& inputSplit, std::string& info);
std::string info_var = "info";
std::string shell = "Myshell";


int main(){
    using namespace std;

    bool running = true;
    int exit_code;
    while (running) 
    {
        cout << shell << ">> ";
        string input = "";
        getline(cin, input);
        trim(input);

        if (input.empty())
        {
            cout << "Invalid command (Empty)." << endl;
            continue;
        }
        vector<string> inputSplit = split(input, " ");
        
        // type exit to quit the prompt
        if (inputSplit[0] == "exit" or inputSplit[0] == "quit") 
        {
            if (inputSplit.size() < 2)
            {
                exit(0);
            }
            else if (inputSplit.size() == 2)
            {
                int exit_code;
                try
                {
                    exit_code = stoi(inputSplit[1]);
                    exit(exit_code);
                }
                catch (invalid_argument e){
                    cout << "Invalid exit error code. Error code has to be a number!!!" << endl;
                }
            }
            else{
                cout << "####################################### \n";
                cout << "INVALID COMMAND \n\n";
                cout << "HELP on quit- Sample cmd below:\t" << endl;
                cout << "\t quit: quit the shell";
                cout << "\t quit + error_code: quit the shell with error_code";
                cout << "####################################### \n";
            }



        }
        // type change_prompt to change root
        else if (inputSplit[0] == "change_prompt")
        {
           change_prompt(inputSplit,shell);
           continue;
        }
        // type distro to get all the distro info
        else if (inputSplit[0] == "distro")
        {   
            ifstream ifs ("/etc/os-release", ifstream::in);
            string distro_key = "";
            if (inputSplit.size() < 2){
                    cout << "####################################### \n";
                    cout << "HELP on distro - Sample cmd below:\t" << endl;
                    cout << "\t distro -v: distro's version";
                    cout << "\t distro -n: distro's name";
                    cout << "\t distro -c: distro's code name" << endl;
                    cout << "####################################### \n";
                }
            else if (ifs.is_open()){    
                if (inputSplit[1] == "-v"){
                    while(getline(ifs, distro_key)){
                        if (distro_key.find("VERSION_ID") != string::npos) {
                            distro_key = distro_key.erase(0,12);
                            distro_key.erase(distro_key.size()-1,1);
                            cout << distro_key << endl;
                            break;
                        }
                    }
                }
                else if (inputSplit[1] == "-n"){
                    while(getline(ifs, distro_key)){
                        if (distro_key.find("NAME") != string::npos){
                            distro_key = distro_key.erase(0,6);
                            distro_key = distro_key.erase(distro_key.size()-1,1);
                            cout << distro_key << endl;
                            break;
                        }
                    }
                }  
                else if (inputSplit[1] == "-c"){
                    while(getline(ifs, distro_key)){
                        if (distro_key.find("VERSION_CODENAME") != string::npos){
                            distro_key = distro_key.erase(0,17);
                            cout << distro_key << endl;
                            break;
                        }
                    }
                }
                else if (inputSplit[1] == "-h" or inputSplit[1] == "--help")
                {
                cout << "####################################### \n";
                cout << "HELP on distro - Sample cmd below:\t" << endl;
                cout << "\t distro -v: distro's version";
                cout << "\t distro -n: distro's name";
                cout << "\t distro -c: distro's code name" << endl;
                cout << "####################################### \n";  
                }                
                else {
                    cout << "####################################### \n";
                    cout << "INVALID COMMAND \n" << endl;
                    cout << "HELP on distro - Sample cmd below:\t" << endl;
                    cout << "\t distro -v: distro's version";
                    cout << "\t distro -n: distro's name";
                    cout << "\t distro -c: distro's code name" << endl;
                    cout << "####################################### \n";

                }     
            }

            else{
                cout << "OS-Release file doesn't exit" << endl;
                continue;
            }
            
        }
        // type info to get info about the CPU and Memory
        else if (inputSplit[0] == "info"){
            info(inputSplit,info_var);
        }
        
        else {
            system(input.c_str());
        }
/*
        else 
        {
            cout << "Unknown command" << endl;
            cout << "Example commands are: change_prompt, distro, info" << endl;
        }*/
        
    }
}

//info method
void info (const std::vector<std::string>& inputSplit, std::string& info){
    using namespace std;
    if (inputSplit[0] == info) {
        if (inputSplit.size() < 2){
            cout << "####################################### \n";
            cout << "HELP on info - Sample cmd below:\t" << endl;
            cout << "\t info -s: current memory page size";
            cout << "\t info -n: current available page number";
            cout << "\t info -p: current number available processor" << endl;
            cout << "####################################### \n";
        }
        else if (inputSplit[1] == "-s"){
            cout << "Current memory page size: " << getpagesize() <<" KB" << endl;
        }
        else if (inputSplit[1] == "-p"){
            cout << "Current available processors: " << get_nprocs() << endl;
        }
        else if (inputSplit[1] == "-h" or inputSplit[1] == "--help")
        {
            cout << "####################################### \n";
            cout << "HELP on info - Sample cmd below:\t" << endl;
            cout << "\t info -s: current memory page size";
            cout << "\t info -n: current available page number";
            cout << "\t info -p: current number available processor" << endl;
            cout << "####################################### \n";
        }
        else if (inputSplit[1] == "-n"){
            ifstream ifs ("/proc/meminfo", ifstream::in);
            string mem_avail = "";
            if (ifs.is_open())
            {
                while (getline(ifs,mem_avail)){
                    if (mem_avail.find("MemAvailable") != string::npos){
                        mem_avail = mem_avail.erase(0,17);
                        mem_avail = mem_avail.erase((mem_avail.length()-3),3);
                        int mem_avail_number = stoi(mem_avail);
                        cout << "Current available page numbers: "<<(mem_avail_number/getpagesize()) << endl;
                        break;
                    } 
                }
            }
            else {
                cout << "Memory info page is not available. Please try again later" << endl;
            }
        }
        else{
            cout << "####################################### \n";
            cout << "INVALID COMMAND \n" << endl;
            cout << "HELP on info - Sample cmd below:\t" << endl;
            cout << "\t info -s: current memory page size";
            cout << "\t info -n: current available page number";
            cout << "\t info -p: current number available processor" << endl;
            cout << "####################################### \n";
        }
        
    
    }
}
       
// change prompt
std::string change_prompt(const std::vector<std::string>& inputSplit, std::string& de){
    
    using namespace std;
    if (inputSplit.size() < 2){
        de = "Myshell";
        return de;
    }
    else if (inputSplit[1] == "--h" or inputSplit[1] == "--help")
    {
        cout << "####################################### \n";
        cout << "HELP on change_prompt:" << endl;
        cout << "\t SYNTAX: change_prompt + ROOT_NAME \n";
        cout << "\t change_prompt: by itself will change back to root directory \n";
        cout << "####################################### \n";
    }
    else {
        de = "";
        for (int i = 1; i < inputSplit.size(); i++){
            de = de + inputSplit[i];
            if (i < (inputSplit.size()-1)){
                de = de + " ";
            }
        }   
        return de;
    }
    
}

// split string or tokenizer  method 
std::vector<std::string> split(const std::string& input, const std::string& regex)
{

    std::regex re(regex);
    std::sregex_token_iterator
        first{input.begin(), input.end(),re, -1},
        last;
    return {first, last};
}

// trim from start (in place)
inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}
