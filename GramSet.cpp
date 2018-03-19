#include <assert.h>
#include <cstring>

#include "GramSet.h"

int GramSet::Z = 0;
int * GramSet::asciiId = NULL;

GramSet::GramSet() {
    root = new GramSetNode();
}

GramSet::~GramSet() {
    //TODO 清理所有节点
}



void GramSet::init(int Z_, int * asciiId_) {
    Z = Z_;
    asciiId = asciiId_;
    GramSetNode::init(Z_, asciiId_);
}
