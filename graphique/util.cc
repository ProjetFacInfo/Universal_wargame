#include "util.hh"

long long getTempsMilliSecondre() {
    using namespace std::chrono;
    steady_clock::time_point now = steady_clock::now();
    return duration_cast<milliseconds>(now.time_since_epoch()).count();
}

bool lireFichier(const char* pFileName, std::string& outFile) {
    std::ifstream f(pFileName);

    printf("pfilename : %s\n", pFileName);
    if (f.is_open()) {
        printf("LireFichier OK\n");
        std::string line;
        while (getline(f, line)) {
            outFile.append(line);
            outFile.append("\n");
        }

        f.close();

        return true;
    } else {
        printf("LireFichier KO \n");
    }

    return false;
}

std::string cheminDuFic(const std::string & fic) {
    std::string::size_type slashPos = fic.find_last_of("/");

    std::string dir;

    if (slashPos == std::string::npos) {
        dir = ".";
    } else if (slashPos == 0) {
        dir = "/";
    } else {
        dir = fic.substr(0, slashPos);
    }

    return dir;
}
