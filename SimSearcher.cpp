#include <cstdio>
#include <cstring>
#include <algorithm>

#include "Const.h"
#include "SimSearcher.h"
#include "MergeHelper.h"

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
    MergeHelper::init(N);
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
    return SUCCESS;
}

int SimSearcher::searchJaccard(const char * query, double threshold, std::vector < std::pair < unsigned, double > > & result) {
    return FAILURE;
}

void SimSearcher::getEdLineSetList(const std::string & query, std::vector < std::vector < int > * > & lineSetList) {
    for (int l = 0; l + Q <= (int) query.length(); l ++) {
        std::string gram = query.substr(l, Q);
        std::vector < int > * lineSet = edGramSet -> getLineSet(gram);
        if (lineSet != NULL) {
            lineSetList.push_back(lineSet);
        }
    }
    std::sort(lineSetList.begin(), lineSetList.end(), cmpVectorIntPointer);
}

void SimSearcher::mergeEdLineSet(const std::vector < std::vector < int > * > & lineSetList, int minOccur, std::vector < int > & mergeResult) {
//    int setCnt = lineSetList.size();
//    std::vector < std::pair < int, int > > mergeProc;
//    std::vector < std::pair < int, int > > mergeTemp;
//    std::vector < int > * curSet;
//    //先把第0个集合拿出来
//    curSet = lineSetList[0];
//    mergeProc.clear();
//    for (int j = 0, sz = curSet -> size(); j < sz; j ++) {
//        mergeProc.push_back(std::make_pair(curSet -> operator [] (j), 1));
//    }
//    //然后开始逐个合并
//    for (int i = 1; i < setCnt; i ++) {
//        curSet = lineSetList[i];
//        int curMinOccur = minOccur + i + 1 - setCnt;
//        if (curMinOccur <= 1) {
//            //归并合并
//            mergeTemp.clear();
//            for (int j0 = 0, j1 = 0, sz0 = mergeProc.size(), sz1 = curSet -> size(); j0 < sz0 || j1 < sz1;) {
//                if (j0 < sz0 && (j1 == sz1 || mergeProc[j0].first < curSet -> operator [] (j1))) {
//                    if (mergeProc[j0].second >= curMinOccur) {
//                        mergeTemp.push_back(mergeProc[j0]);
//                    }
//                    j0 ++;
//                } else if (j1 < sz1 && (j0 == sz0 || mergeProc[j0].first > curSet -> operator [] (j1))) {
//                    if (1 >= curMinOccur) {
//                        mergeTemp.push_back(std::make_pair(curSet -> operator [] (j1), 1));
//                    }
//                    j1 ++;
//                } else {
//                    mergeProc[j0].second ++;;
//                    mergeTemp.push_back(mergeProc[j0]);
//                    j0 ++;
//                    j1 ++;
//                }
//            }
//            mergeProc.clear();
//            mergeProc.swap(mergeTemp);
//        } else {
//            //查找合并
//            for (int j = 0, sz = curSet -> size(); j < sz; j ++) {
//                int tmp = curSet -> operator [] (j);
//                std::vector < int, int > * ite = std::lower_bound(mergeTemp.begin(), mergeTemp.end(), std::make_pair(tmp, 0));
//                if (ite -> first == tmp) {
//                    ite -> second ++;
//                }
//            }
//        }
//    }
//    //得到最终的结果
//    mergeResult.clear();
//    for (int j = 0, sz = mergeProc.size(); j < sz; j ++) {
//        if (mergeProc[j].second >= minOccur) {
//            mergeResult.push_back(mergeProc[j].first);
//        }
//    }
    int setCnt = lineSetList.size();
    std::vector < int > upperList;
    for (int i = 0; i < setCnt; i ++) {
        std::vector < int > * curSet = lineSetList[i];
        int curSize = curSet -> size();
        int curMinOccur = minOccur + i - setCnt;
        int upperCnt = MergeHelper::getInstance() -> getUpperCnt(curMinOccur);
        if (curMinOccur <= 0 || upperCnt * MERGE_METHOD_CHANGE > curSize) {
            //用枚举curSet的方法
            for (int j = 0; j < curSize; j ++) {
                MergeHelper::getInstance() -> increase(curSet -> operator [] (j));
            }
        } else {
            //用枚举MergeHelper的方法
            MergeHelper::getInstance() -> getUpperList(curMinOccur, upperList);
            for (int j = 0; j < upperCnt; j ++) {
                std::vector < int > :: iterator ite = std::lower_bound(curSet -> begin(), curSet -> end(), upperList[j]);
                if (ite == curSet -> end()) {
                    upperList[j] = upperList.back();
                    upperList.pop_back();
                    upperCnt --;
                }
            }
            for (int j = 0; j < upperCnt; j ++) {
                MergeHelper::getInstance() -> increase(upperList[j]);
            }
        }
    }
    MergeHelper::getInstance() -> getUpperList(minOccur, mergeResult);
    std::sort(mergeResult.begin(), mergeResult.end());
}

int SimSearcher::calculateEd(const std::string & a, const std::string & b, int th) {
    int lenA = a.length();
    int lenB = b.length();
    static int f[2][MAX_LINE_LENGTH + 4];
    if (lenA < lenB - th || lenA > lenB + th) {
        return th + 1;
    }
    for (int i = 0; i < lenA; i ++) {
        char ai = a[i];
        int minF = INF_INT;
        int jd0 = 0;
        int jd1 = i - th;
        int jd2 = lenB - lenA + i - th;
        int jd = jd0 <= jd1 ? jd0 <= jd2 ? jd0 : jd2 : jd1 <= jd2 ? jd1 : jd2;
        int ju0 = lenB - 1;
        int ju1 = i + th;
        int ju2 = lenB - lenA + i + th;
        int ju = ju0 >= ju1 ? ju0 >= ju2 ? ju0 : ju2 : ju1 >= ju2 ? ju1 : ju2;
        for (int j = jd; j <= ju; j ++) {
            int tmpF = INF_INT;
            if (ai == b[j]) {
                if (i == 0) {
                    tmpF = j;
                } else if (j == 0) {
                    tmpF = i;
                } else {
                    tmpF = f[(i & 1) ^ 1][j - 1];
                }
            } else {
                int tmp;
                if (j - 1 >= jd && tmpF > (tmp = f[i][j - 1] + 1)) {
                    tmpF = tmp;
                } else if (j == 0 && tmpF > (tmp = i + 1)) {
                    tmpF = i + 1;
                }
                if (j < ju1 && j < ju2) {
                    if (i > 0 && tmpF > (tmp = f[(i & 1) ^ 1][j] + 1)) {
                        tmpF = tmp;
                    } else if (tmpF > (tmp = j + 1)) {
                        tmpF = tmp;
                    }
                }
            }
            f[i & 1][j] = tmpF;
            minF = minF > tmpF ? tmpF : minF;
        }
        if (minF > th) {
            return th + 1;
        }
    }
    return f[lenA & 1 ^ 1][lenB - 1];
}

void SimSearcher::testEdAllInput(const std::string & query, int th, std::vector < std::pair < unsigned, unsigned > > & result) {
    result.clear();
    for (int i = 0; i < N; i ++) {
        int ed = calculateEd(query, lineList[i], th);
        if (ed <= th) {
            result.push_back(std::make_pair((unsigned) i, (unsigned) ed));
        }
    }
}

void SimSearcher::testEdMergeResult(const std::string & query, int th, const std::vector < int > & mergeResult, std::vector < std::pair < unsigned, unsigned > > & result) {
    result.clear();
    for (int j = 0, sz = mergeResult.size(); j < sz; j ++) {
        int i = mergeResult[j];
        int ed = calculateEd(query, lineList[i], th);
        if (ed <= th) {
            result.push_back(std::make_pair((unsigned) i, (unsigned) ed));
        }
    }
}

int SimSearcher::searchED(const char * query_, unsigned threshold, std::vector < std::pair < unsigned, unsigned > > & result) {
    printf("SimSearcher::searchED()\n");
    //抓取所有非空的lineSet
    std::string query(query_);
    std::vector < std::vector < int > * > lineSetList;
    getEdLineSetList(query, lineSetList);
    int minOccur = query.length() - Q + 1 - threshold * Q;
    int setCnt = lineSetList.size();
    result.clear();
    std::vector < int > mergeResult;
    
    printf("query = %s, queryLength = %d, threshold = %d\n", query.c_str(), query.length(), threshold);
    printf("minOccur = %d, setCnt = %d\n", minOccur, setCnt);
    for (int i = 0; i < setCnt; i ++) {
        printf("lineSetList[%d] = {", i);
        for (int j = 0; j < (int) lineSetList[i] -> size(); j ++) {
            printf("%d, ", lineSetList[i] -> operator [] (j));
        }
        printf("}\n");
    }
    
    //按照PPT的方法剪枝
    if (minOccur > setCnt) {
        //查不到结果
        return SUCCESS;
    } else if (minOccur <= 0) {
        //这个剪枝不能实现，改用暴力算法
        testEdAllInput(query, threshold, result);
    } else {
        //用这个算法剪枝
        mergeEdLineSet(lineSetList, minOccur, mergeResult);
        
        printf("mergeResult = {");
        for (int j = 0; j < (int) mergeResult.size(); j ++) {
            printf("%d, ", mergeResult[j]);
        }
        printf("}\n");
        
        testEdMergeResult(query, threshold, mergeResult, result);
    }
    
    printf("result = {");
    for (int j = 0, sz = result.size(); j < sz; j ++) {
        printf("(%d, %d), ", (int) result[j].first, (int) result[j].second);
    }
    printf("}\n");
    
    return SUCCESS;
}

bool cmpVectorIntPointer(const std::vector < int > * a, const std::vector < int > * b) {
    return a -> size() < b -> size();
}
