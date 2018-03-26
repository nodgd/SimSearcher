#include <cstdio>
#include <cstring>

#include "Const.h"
#include "SimSearcher.h"

SimSearcher::SimSearcher() {
    Q = 0;
    inputFile = NULL;
    N = 0;
    Z = 0;
    asciiId = NULL;
    edGramSet = NULL;
}

SimSearcher::~SimSearcher() {
    if (inputFile != NULL) {
        fclose(inputFile);
    }
    if (asciiId != NULL) {
        delete asciiId;
    }
    if (edGramSet != NULL) {
        delete edGramSet;
    }
}

bool SimSearcher::openInputFile(const char * fileName) {
    FILE * file = fopen(fileName, "r");
    if (file == NULL) {
        file = fopen("data\\sample.txt", "r");
    }
    if (file == NULL) {
        return false;
    }
    inputFile = file;
    return true;
}

void SimSearcher::readInputFile() {
    static char buf[MAX_LINE_LENGTH + 4];
    asciiId = new int [MAX_ASCII];
    memset(asciiId, 0, sizeof(int) * MAX_ASCII);
    while (fscanf(inputFile, "%[^\n]\n", buf) != EOF) {
        lineList.push_back(std::string(buf));
        for (int j = 0; j < MAX_LINE_LENGTH && buf[j]; j ++) {
            asciiId[(int) buf[j]] = 1;
        }
        memset(buf, 0,sizeof(buf));
    }
    N = lineList.size();
    Z = 0;
    for (int c = 0; c < MAX_ASCII; c ++) {
        if (asciiId[c]) {
            asciiId[c] = Z;
            Z ++;
        } else {
            asciiId[c] = -1;
        }
    }
    GramSet::init(Z, asciiId);
}

void SimSearcher::createEdIndex() {
    edGramSet = new GramSet();
    for (int i = 0; i < N; i ++) {
        std::string line = lineList[i];
        int length = line.length();
        for (int l = 0; l + Q <= length; l ++) {
            std::string gram = line.substr(l, Q);
            edGramSet -> insertGram(gram, i);
        }
    }
    edGramSet -> print();
}

int SimSearcher::createIndex(const char * fileName, unsigned Q_) {
    if (! openInputFile(fileName)) {
        fprintf(stderr, "Can not open the input file.\n");
        return FAILURE;
    }
    Q = Q_;
    readInputFile();
    createEdIndex();
    return FAILURE;
}

int SimSearcher::searchJaccard(const char * query, double threshold, std::vector < std::pair < unsigned, double > > & result) {
    return FAILURE;
}

int SimSearcher::searchED(const char * query, unsigned threshold, std::vector < std::pair < unsigned, unsigned > > & result) {
    return FAILURE;
}
