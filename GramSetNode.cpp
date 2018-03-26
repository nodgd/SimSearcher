#include <cstdio>
#include <cstring>

#include "Const.h"
#include "GramSetNode.h"

int GramSetNode::Z = 0;
int * GramSetNode::asciiId = NULL;

GramSetNode::GramSetNode() {
    son = new GramSetNode * [Z];
    memset(son, 0 ,sizeof(GramSetNode *) * Z);
    lineSet = NULL;
}

GramSetNode::~GramSetNode(){
    delete [] son;
    if (lineSet != NULL) {
        delete lineSet;
    }
}

GramSetNode * GramSetNode::getSonById(int i) {
    return son[i];
}

GramSetNode * GramSetNode::getSonByAscii(char ch) {
    if (asciiId[(int) ch] == -1) {
        return NULL;
    } else {
        return son[asciiId[(int) ch]];
    }
}

GramSetNode * GramSetNode::getOrCreateSonByAscii(char ch) {
    if (son[asciiId[(int) ch]] == NULL) {
        son[asciiId[(int) ch]] = new GramSetNode();
    }
    return son[asciiId[(int) ch]];
}

std::vector < int > * GramSetNode::getLineSet() {
    return lineSet;
}

std::vector < int > * GramSetNode::getOrCreateLineSet() {
    if (lineSet == NULL) {
        lineSet = new std::vector < int > ();
    }
    return lineSet;
}

void GramSetNode::init(int Z_, int * asciiId_) {
    Z = Z_;
    asciiId = asciiId_;
}
