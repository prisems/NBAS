// Metadata
// Author == earthrulerr
// Name == NBAS
// NBAS = "Notepad Basic"
// Description == A programming language created by earthrulerr meant to be
// Basic and short worded, like Basic.
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <string>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif
using namespace std;

string getOsName() {
#ifdef _WIN32
  return "Windows 32-bit";
#elif _WIN64
  return "Windows 64-bit";
#elif __APPLE__ || __MACH__
  return "Mac OSX";
#elif __linux__
  return "Linux";
#elif __FreeBSD__
  return "FreeBSD";
#elif __unix || __unix__
  return "Unix";
#else
  return "Other";
#endif
}
void pkghelp() {
  cout << "\033[93m"
       << "PACKAGES:"
       << "\033[33m" << endl
       << "'(pkg.custom)' - Allows console customization." << endl
       << "\033[93m"
       << "CUSTOM PKG TAGS:"
       << "\033[33m" << endl
       << "'COLOR: COLOR' - Changes font color of console text. Colors "
          "include: BLUE, RED, MAGENTA, CYAN, GREEN, YELLOW, WHITE."
       << "\033[0m" << endl;
}
void help() {
  cout << "\033[93m"
       << "GUIDE:"
       << "\033[33m" << endl
       << "'#' - Represents a number." << endl
       << "\033[93m"
       << "TAGS:"
       << "\033[33m" << endl
       << "'GET INPUT' - The next word is recorded as INPUTVAL." << endl
       << "'MGET INPUT' - Multiline." << endl
       << "'INPUTVAL' - Reports INPUTVAL." << endl
       << "'PRNT text ;' - Print to console." << endl
       << "'GUIDES' - Opens all guides." << endl
       << "'ADD # , #' - Addition." << endl
       << "'SUB # , #' - Subtraction." << endl
       << "'MUL # , #' - Multiplication." << endl
       << "'DIV # , #' - Division." << endl
       << "'POW # , #' - Raised to the power." << endl
       << "'WAIT #' - Wait # seconds until proceeding." << endl
       << "\033[93m"
       << "OTHER:"
       << "\033[33m" << endl
       << "'CMT' - Comment." << endl
       << "'%20' - Prints a space to console." << endl
       << "'CLR' - Clears program." << endl
       << "'ENT' - Prints a new line to console." << endl
       << "'$SYST' - Reports data." << endl
       << "'$LINE' - Reports current line." << endl
       << "'$USER' - Prints the host name." << endl
       << "'$OS' - Prints the OS name." << endl
       << "'$IP' Prints the IP address." << endl
       << "'$LOC' - Prints location." << endl
       << "'$TIME' - Prints time (of server)." << endl
       << "'$CPU $CPUS $CPUM $CPU_ARCH $CPU_SPD $CPU_FREW' all print "
          "information on CPU."
       << endl
       << "'PKGHELP' - Help for packages." << endl
       << "\033[93m"
       << "ERRORS:"
       << "\033[33m" << endl
       << "'ERROR 409' - UKNOWN TAG, improper or non existent tag." << endl
       << "\033[93m"
       << "PACKAGES:"
       << "\033[33m" << endl
       << "'(pkg.reset)' - Resets program to default, deletes all packages."
       << endl
       << "'(pkg.custom)' - Installs the custom package, allows for "
          "console customization."
       << endl
       << "\033[0m" << endl;
}

int main() {
  system("clear");
  string input, comment, print, comma, color, get, inputVAL, if1, if2, ifc, do1,
      file, store, do2, doc, ifcheck, ifdo;
  int add1, add2, sub1, sub2, mult1, mult2, div1, div2, wait, pow1,
      pow2;
  string custom = "false";
  string version = "8.1.53";
  string customCOLOR = "WHITE '0m'";
  int loop = 1;
  int prnt = 0;
  int cmnt = 0;
  int line = 0;
  int mathL = 0;
  int errors = 0;
  cout << "\033[90m"
       << "NBAS v:" << version << " main:" << endl
       << "\033[0m";
  while (loop == 1) {
    ofstream MyFile("code.txt");
    line = line + 1;
    cin >> input;
    if (input == "CMT") {
      getline(cin, comment);
    } else if (input == "WAIT") {
      cin >> wait;
      sleep(wait);
    } else if (input == "(pkg.custom)") {
      custom = "true";
    } else if (input == "(pkg.reset)") {
      custom = "false";
      customCOLOR = "WHITE '0m'";
      cout << "\033[0m";
    } else if (input == "%20") {
      cout << " ";
    } else if (input == "ENT") {
      cout << endl;
    } else if (input == "$SYST") {
      cout << "\033[33m"
           << "version: " << version << endl
           << "author: earthrulerr" << endl
           << "errors: " << errors << endl
           << "PACKAGES:" << endl
           << "pkg.custom: " << custom << endl
           << "custom.colorSET: " << customCOLOR << "\033[0m";
    } else if (input == "REPEAT") {
      // format: REPEAT #
      // would loop following tags # of times
    } else if (input == "$LINE") {
      cout << line;
    } else if (input == "PRNT") {
      prnt = 1;
      while (prnt == 1) {
        cin >> print;
        if (print != ";") {
          cout << " " << print;
        } else if (print == ";") {
          prnt = 0;
        }
      }
    } else if (input == "$USER") {
      char hostname[HOST_NAME_MAX];
      gethostname(hostname, HOST_NAME_MAX);
      cout << hostname;
    } else if (input == "$OS") {
      cout << getOsName();
    } else if (input == "$CPU") {
      string cpu_name;
      char buffer[1024];
      FILE *pipe = popen(
          "cat /proc/cpuinfo | grep 'model name' | head -1 | cut -d: -f2-",
          "r");
      if (pipe) {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
          cpu_name += buffer;
        }
        pclose(pipe);
      }
      cout << cpu_name;
    } else if (input == "$CPUM") {
      string cpu_memory;
      char buffer[1024];
      FILE *pipe = popen("cat /proc/meminfo | grep 'MemTotal'", "r");
      if (pipe) {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
          cpu_memory += buffer;
        }
        pclose(pipe);
      }
      cout << cpu_memory;
    } else if (input == "$IP") {
      string ip_address;
      char buffer[1024];
      FILE *pipe = popen("curl -s checkip.dyndns.org | sed -e 's/.*Current IP "
                         "Address: //' -e 's/<.*$//'",
                         "r");
      if (pipe) {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
          ip_address += buffer;
        }
        pclose(pipe);
      }
      cout << ip_address;
    } else if (input == "$CPUS") {
      string num_cpus;
      char buffer[1024];
      FILE *pipe = popen("nproc", "r");
      if (pipe) {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
          num_cpus += buffer;
        }
        pclose(pipe);
      }
      cout << num_cpus;
    } else if (input == "$CPU_ARCH") {
      string cpu_architecture;
      char buffer[1024];
      FILE *pipe = popen("uname -p", "r");
      if (pipe) {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
          cpu_architecture += buffer;
        }
        pclose(pipe);
      }
      cout << cpu_architecture;
    } else if (input == "$CPU_FREQ") {
      string cpu_frequency;
      char buffer[1024];
      FILE *pipe = popen("cat /proc/cpuinfo | grep 'cpu MHz'", "r");
      if (pipe) {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
          cpu_frequency += buffer;
        }
        pclose(pipe);
      }
      cout << cpu_frequency;
    } else if (input == "$CPU_SPD") {
      string processor_usage;
      char buffer[1024];
      FILE *pipe = popen("top -bn1 | grep 'Cpu(s)'", "r");
      if (pipe) {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
          processor_usage += buffer;
        }
        pclose(pipe);
      }
      cout << processor_usage;
    } else if (input == "$LOC") {
      string location;
      char buffer[1024];
      FILE *pipe = popen("curl -s https://ipapi.co/country_name/", "r");
      if (pipe) {
        while (fgets(buffer, sizeof buffer, pipe) != NULL) {
          location += buffer;
        }
        pclose(pipe);
      }
      cout << location;
    } else if (input == "$TIME") {
      time_t rawtime;
      struct tm *timeinfo;
      char time_buffer[80];
      time(&rawtime);
      timeinfo = localtime(&rawtime);
      strftime(time_buffer, sizeof(time_buffer), "%I:%M %p", timeinfo);
      string time(time_buffer);
      cout << time;
    } else if (input == "GET") {
      cin >> get;
      if (get == "INPUT") {
        cin >> get;
        inputVAL = get;
      } else {
        cout << "\033[31m"
             << "\033[101m";
        cout << "ERROR 206 'partial:missing-string'" << endl;
        cout << "\033[0m";
        errors = errors + 1;
      }
    } else if (input == "MGET") {
      cin >> get;
      if (get == "INPUT") {
        getline(cin, get);
        inputVAL = get;
      } else {
        cout << "\033[31m"
             << "\033[101m";
        cout << "ERROR 206 'partial:missing-string'" << endl;
        cout << "\033[0m";
        errors = errors + 1;
      }
    } else if (input == "INPUTVAL") {
      cout << inputVAL;
    } else if (input == "DOES") {
      cin >> do1;
      cin >> doc;
      cin >> do1;
      if (doc == "=") {
        if (do1 == do2) {
          cout << "'true'";
        } else if (do1 != do2) {
          cout << "'false'";
        }
      } else if (doc == "!=") {
        if (do1 != do2) {
          cout << "'true'";
        } else if (do1 == do2) {
          cout << "'false'";
        } else {
          cout << "\033[31m"
               << "\033[101m";
          cout << "ERROR 'UNKNOWN'" << endl;
          cout << "\033[0m";
          errors = errors + 1;
        }
      }
    } else if (input == "IF") {
      // ifc if1 if2 ifcheck ifdo
      cin >> if1;
      cin >> ifc;
      cin >> if2;
      cin >> ifdo;
      if (ifdo == "DO") {
        cin >> ifdo;
      }
      if (ifc == "=") {
        if (if1 == if2) {
          input = ifdo;
        } else {
        }
      } else if (ifc == "!=") {
        if (if1 != if2) {

        } else if (if1 == if2) {
        } else {
          cout << "\033[31m"
               << "\033[101m";
          cout << "ERROR 409, TRY: '=' '!='" << endl;
          cout << "\033[0m";
          errors = errors + 1;
        }
      }
    } else if (input == "ADD") {
      cin >> add1;
      cin >> comma;
      if (comma == ",") {
      } else {
        cout << "\033[31m"
             << "\033[101m";
        cout << "ERROR 206 'partial:missing-comma'" << endl;
        cout << "\033[0m";
        errors = errors + 1;
      }
      cin >> add2;
      cout << add1 + add2;
    } else if (input == "SUB") {
      cin >> sub1;
      cin >> comma;
      if (comma == ",") {
      } else {
        cout << "\033[31m"
             << "\033[101m";
        cout << "ERROR 206 'Partial:missing-comma'" << endl;
        cout << "\033[0m";
        errors = errors + 1;
      }
      cin >> sub2;
      cout << sub1 - sub2;
    } else if (input == "MUL") {
      cin >> mult1;
      cin >> comma;
      if (comma == ",") {
      } else {
        cout << "\033[31m"
             << "\033[101m";
        cout << "ERROR 206 'Partial:missing-comma'" << endl;
        cout << "\033[0m";
        errors = errors + 1;
      }
      cin >> mult2;
      cout << mult1 * mult2;
    } else if (input == "DIV") {
      cin >> div1;
      cin >> comma;
      if (comma == ",") {
      } else {
        cout << "\033[31m"
             << "\033[101m";
        cout << "ERROR 206 'Partial:missing-comma'" << endl;
        cout << "\033[0m";
        errors = errors + 1;
      }
      cin >> div2;
      cout << div1 / div2;
    } else if (input == "POW") {
      cin >> pow1;
      cin >> comma;
      if (comma == ",") {
      } else {
        cout << "\033[31m"
             << "\033[101m";
        cout << "ERROR 206 'Partial:missing-comma'" << endl;
        cout << "\033[0m";
        errors = errors + 1;
      }
      cin >> pow2;
      cout << pow(pow1, pow2);
    } else if (input == "CLR") {
      system("clear");
      cout << "\033[90m"
           << "NBAS v:" << version << endl
           << "> "
           << "\033[0m";
      errors = 0;
      custom = "false";
      line = 0;
    } else if (input == "COLOR:") {
      if (custom == "true") {
        cin >> color;
        if (color == "RED") {
          cout << "\033[31m";
          customCOLOR = "RED '31m'";
        } else if (color == "CYAN") {
          cout << "\033[36m";
          customCOLOR = "CYAN '36m'";
        } else if (color == "YELLOW") {
          cout << "\033[33m";
          customCOLOR = "YELLOW '33m'";
        } else if (color == "BLUE") {
          cout << "\033[34m";
          customCOLOR = "BLUE '34m'";
        } else if (color == "GREEN") {
          cout << "\033[32m";
          customCOLOR = "GREEN '32m'";
        } else if (color == "MAGENTA") {
          cout << "\033[35m";
          customCOLOR = "MAGENTA '35m'";
        } else if (color == "WHITE") {
          cout << "\033[0m";
          customCOLOR = "WHITE '0m'";
        } else {
          cout << "\033[31m"
               << "\033[101m"
               << "ERROR custom.color:non existent"
               << "\033[0m" << endl;
          errors = errors + 1;
        }
      }
    } else if (input == "PKGHELP") {
      pkghelp();
    } else if (input == "HELP") {
      help();
    } else if (input == "GUIDES") {
      help();
      pkghelp();
    }

    else {
      cout << "\033[31m"
           << "\033[101m";
      if (input == "help") {
        cout << "ERROR 'UNKNOWN TAG (TRY: HELP)'" << endl;
        errors = errors + 1;
      } else if (input == "clr") {
        cout << "ERROR 'UNKNOWN TAG (TRY: CLR)'" << endl;
        errors = errors + 1;
      } else if (input == "ent") {
        cout << "ERROR 'UNKNOWN TAG (TRY: ENT)'" << endl;
        errors = errors + 1;
      } else if (input == "add") {
        cout << "ERROR 'UNKNOWN TAG (TRY: ADD)'" << endl;
        errors = errors + 1;
      } else if (input == "sub") {
        cout << "ERROR 'UNKNOWN TAG (TRY: SUB)'" << endl;
        errors = errors + 1;
      } else if (input == "mul") {
        cout << "ERROR 'UNKNOWN TAG (TRY: MULT)'" << endl;
        errors = errors + 1;
      } else if (input == "div") {
        cout << "ERROR 'UNKNOWN TAG (TRY: DIV)'" << endl;
        errors = errors + 1;
      } else if (input == "pow") {
        cout << "ERROR 'UNKNOWN TAG (TRY: POW)'" << endl;
        errors = errors + 1;
      } else if (input == "prnt") {
        cout << "ERROR 'UNKNOWN TAG (TRY: PRNT)'" << endl;
        errors = errors + 1;
      } else if (input == "line") {
        cout << "ERROR 'UNKNOWN TAG (TRY: LINE)'" << endl;
        errors = errors + 1;
      } else if (input == "inputval") {
        cout << "ERROR 'UNKNOWN TAG (TRY: INPUTVAL)'" << endl;
        errors = errors + 1;
      } else if (input == "get") {
        cout << "ERROR 'UNKNOWN TAG (TRY: GET)'" << endl;
        errors = errors + 1;
      } else if (input == "mget") {
        cout << "ERROR 'UNKNOWN TAG (TRY: MGET)'" << endl;
        errors = errors + 1;
      } else if (input == "wait") {
        cout << "ERROR 'UNKNOWN TAG (TRY: WAIT)'" << endl;
        errors = errors + 1;
      } else if (input == "cmt") {
        cout << "ERROR 'UNKNOWN TAG (TRY: CMT)'" << endl;
        errors = errors + 1;
      } else if (input == "syst") {
        cout << "ERROR 'UNKNOWN TAG (TRY: SYST)'" << endl;
        errors = errors + 1;
      } else if (input == "system") {
        cout << "ERROR 'UNKNOWN TAG (TRY: SYST)'" << endl;
        errors = errors + 1;
      } else if (input == "SYSTEM") {
        cout << "ERROR 'UNKNOWN TAG (TRY: SYST)'" << endl;
        errors = errors + 1;
      } else if (input == "clear") {
        cout << "ERROR 'UNKNOWN TAG (TRY: CLR)'" << endl;
        errors = errors + 1;
      } else if (input == "CLEAR") {
        cout << "ERROR 'UNKNOWN TAG (TRY: CLR)'" << endl;
        errors = errors + 1;
      } else if (input == "PRMT") {
        cout << "ERROR 'UNKNOWN TAG (TRY: PRNT)'" << endl;
        errors = errors + 1;
      } else {
        cout << "ERROR 409 'UNKNOWN TAG' LINE: " << line << endl;
        input = "409";
        errors = errors + 1;
      }
      cout << "\033[0m";
    }
  }
}
