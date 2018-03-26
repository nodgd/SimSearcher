#include "LineSet.h"

LineSet::LineSet(){
}

LineSet::~LineSet(){
}

void LineSet::insertLine(int line) {
    lineList.push_back(line);
}

int LineSet::getSize() {
    return (int) lineList.size();
}

int LineSet::getLineById(int i) {
    return lineList[i];
}
