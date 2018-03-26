#include <cstdio>
#include <cstring>

#include "Const.h"
#include "MergeHelper.h"

int MergeHelper::N = 0;
MergeHelper * MergeHelper::instance = NULL;

MergeHelper::MergeHelper() {
    lCnt = new int [N + 4];
    memset(lCnt, 0, sizeof(int) * (N + 4));
    cSum = new int [MAX_LINE_LENGTH];
    memset(cSum, 0, sizeof(int) * MAX_LINE_LENGTH);
    cSum[0] = N;
    headNode = new int [MAX_LINE_LENGTH];
    memset(headNode, -1, sizeof(int) * MAX_LINE_LENGTH);
    nodePrev = new int [N + 4];
    memset(nodePrev, -1, sizeof(int) * (N + 4));
    nodeNext = new int [N + 4];
    memset(nodeNext, -1, sizeof(int) * (N + 4));
}

MergeHelper::~MergeHelper() {
    delete [] lCnt;
    delete [] cSum;
    delete [] headNode;
    delete [] nodePrev;
    delete [] nodeNext;
}

void MergeHelper::increase(int l) {
    int c = lCnt[l];
    if (c >= 1) {
        if (nodePrev[l] != -1) {
            nodeNext[nodePrev[l]] = nodeNext[l];
        } else {
            headNode[c] = nodeNext[l];
        }
        if (nodeNext[l] != -1) {
            nodePrev[nodeNext[l]] = nodePrev[l];
        }
    }
    lCnt[l] ++;
    c = lCnt[l];
    cSum[c] ++;
    nodePrev[l] = -1;
    nodeNext[l] = headNode[c];
    headNode[c] = l;
    if (nodeNext[l] != -1) {
        nodePrev[nodeNext[l]] = l;
    }
}

int MergeHelper::getUpperCnt(int t) {
    if (t <= 0) {
        return N;
    } else {
        return cSum[t];
    }
}

void MergeHelper::getUpperList(int t0, std::vector < int > & upperList) {
    upperList.clear();
    for (int t = t0 < 0 ? 0 : t0; t < MAX_LINE_LENGTH && cSum[t] > 0; t ++) {
        for (int l = headNode[t]; l != -1; l = nodeNext[l]) {
            upperList.push_back(l);
        }
    }
}

void MergeHelper::clear() {
    for (int t = 1; t < MAX_LINE_LENGTH && cSum[t] > 0; t ++) {
        for (int l = headNode[t]; l != -1; l = nodeNext[l]) {
            lCnt[l] = 0;
            nodePrev[l] = -1;
            nodeNext[l] = -1;
        }
        cSum[t] = 0;
        headNode[t] = -1;
    }
    cSum[0] = N;
}

void MergeHelper::print() {
    printf("MergeHelper {\n");
    printf("    lCnt = {");
    for (int j = 0; j < N; j ++) {
        printf("%d, ", lCnt[j]);
    }
    printf("}\n");
    printf("    nodePrev = {");
    for (int j = 0; j < N; j ++) {
        printf("%d, ", nodePrev[j]);
    }
    printf("}\n");
    printf("    nodeNext = {");
    for (int j = 0; j < N; j ++) {
        printf("%d, ", nodeNext[j]);
    }
    printf("}\n");
    printf("    cSum = {");
    for (int j = 0; j < MAX_LINE_LENGTH && cSum[j] > 0; j ++) {
        printf("%d, ", cSum[j]);
    }
    printf("}\n");
    printf("    headNode = {");
    for (int j = 0; j < MAX_LINE_LENGTH && cSum[j] > 0; j ++) {
        printf("%d, ", headNode[j]);
    }
    printf("}\n");
}

void MergeHelper::init(int N_) {
    N = N_;
    instance = new MergeHelper();
}

MergeHelper * MergeHelper::getInstance() {
    return instance;
}
