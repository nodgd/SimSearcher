#include <cstdio>
#include <cstring>

#include "Const.h"
#include "GramSet.h"

int GramSet::Z = 0;
int * GramSet::asciiId = NULL;

GramSet::GramSet() {
    root = new GramSetNode();
}

GramSet::~GramSet() {
    clear(root);
}

void GramSet::clear(GramSetNode * cur) {
    if (cur == NULL) {
        return;
    }
    for (int i = 0; i < Z; i ++) {
        GramSetNode * son = cur -> getSonById(i);
        if (son != NULL) {
            clear(son);
        }
    }
    delete cur;
}

void GramSet::printVisitor(GramSetNode * cur, char * gram, int gramLen) {
    std::vector < int > * lineSet = cur -> getLineSet();
    if (lineSet != NULL) {
        int n = lineSet -> size();
        printf("%s:{", gram);
        for (int i = 0; i < n; i ++) {
            printf("%d,", lineSet -> operator [] (i));
        }
        printf("}\n");
    }
    for (int ch = 0; ch < MAX_ASCII; ch ++) {
        int i = asciiId[ch];
        if (i != -1) {
            GramSetNode * son = cur -> getSonById(i);
            if (son != NULL) {
                gram[gramLen] = ch;
                printVisitor(son, gram, gramLen + 1);
            }
        }
    }
    gram[gramLen] = 0;
}

void GramSet::insertGram(const std::string & gram, int lineId) {
    GramSetNode * cur = root;
    for (int i = 0; i < (int) gram.length(); i ++) {
        cur = cur -> getOrCreateSonByAscii(gram[i]);
    }
    std::vector < int > * lineSet = cur -> getOrCreateLineSet();
    if (lineSet -> size() == 0 || lineSet -> back() != lineId) {
        lineSet -> push_back(lineId);
    }
}

std::vector < int > * GramSet::getLineSet(const std::string & gram) {
    GramSetNode * cur = root;
    for (int i = 0; i < (int) gram.length(); i ++) {
        cur = cur -> getSonByAscii(gram[i]);
        if (cur == NULL) {
            return NULL;
        }
    }
    return cur -> getLineSet();
}

void GramSet::print() {
    static char gram[MAX_LINE_LENGTH];
    memset(gram, 0, sizeof(gram));
    printVisitor(root, gram, 0);
    
}

void GramSet::init(int Z_, int * asciiId_) {
    Z = Z_;
    asciiId = asciiId_;
    GramSetNode::init(Z_, asciiId_);
}
