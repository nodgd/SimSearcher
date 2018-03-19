#include <assert.h>
#include <cstring>

#include "Const.h"
#include "GramSetNode.h"

int GramSetNode::Z = 0;
int * GramSetNode::asciiId = NULL;

GramSetNode::GramSetNode() {
    son = new GramSetNode * [Z];
    memset(son, 0 ,sizeof(GramSetNode) * Z);
}

GramSetNode::~GramSetNode(){
    delete [] son;
}

GramSetNode * GramSetNode::getSonByAscii(char ch) {
    assert(0 <= ch && ch < MAX_ASCII);
    assert(asciiId[ch] != -1);
    return son[asciiId[ch]];
}

void GramSetNode::setSonByAscii(char ch, GramSetNode * ns) {
    assert(0 <= ch && ch < MAX_ASCII);
    assert(asciiId[ch] != -1);
    assert(son[asciiId[ch]] == NULL);
    assert(ns != NULL);
    son[asciiId[ch]] = ns;
}

void GramSetNode::init(int Z_, int * asciiId_) {
    Z = Z_;
    asciiId = asciiId_;
}
