#include <cstring>

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

void LineSet::getAll(std::vector < int > & lineList_) {
    lineList_ = lineList;
}

bool LineSet::cmpPointer(const LineSet * a, const LineSet * b) {
    int aSize = a == NULL ? 0 : a -> lineList.size();
    int bSize = b == NULL ? 0 : b -> lineList.size();
    return aSize < bSize;
}
