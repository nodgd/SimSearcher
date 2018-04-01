#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

typedef unsigned long long uint64;

const int N = 200000;
const int MAX_N = N + 4;
const int Q = 200000;
const int MAX_Q = Q + 4;
const int MAX_LINE_LENGTH = 256;

const int W = 200000;
const int MAX_W = W + 4;
const int MAX_WORD_LENGTH = 10;
const int SIM_ED_DIFF = 4;
const int SIM_JC_DIFF = 3;
const int SIM_OP = 3;
const int BASE_RANGE = 4;
const int MOVE_EXPECTION = 10;
const char WORD_FILE_NAME[] = "data\\gen2.word.in";
const char DATA_FILE_NAME[] = "data\\gen2.data.in";
const char ED_QUERY_FILE_NAME[] = "data\\gen2.ed.in";
const char JC_QUERY_FILE_NAME[] = "data\\gen2.jc.in";
const int Z = 26;
const int ZZ = 127 - 32;
const int HASH_BASE = 29;
const uint64 HASH_MODE = 1000000000000037ull;

std::string wordList[MAX_W];
std::map < std::string, int > dict;
int sumWordLen;
std::vector < int > lineList[MAX_N];
std::map < uint64, int > lineDict;
std::pair < std::string, int > edQueryList[MAX_Q];
std::pair < std::string, double > jcQueryList[MAX_Q];

int randInt() {
    return rand() << 15 | rand();
}

void genWord(std::string & word) {
    int len = randInt() % MAX_WORD_LENGTH + 1;
    static char word_c[MAX_WORD_LENGTH + 4];
    for (int i = 0; i < len; i ++) {
        int t = randInt() % Z;
        word_c[i] = 'a' + t;
    }
    word_c[len] = 0;
    word = word_c;
}

void genSimWord(std::string & word, int I) {
    int base = I - 1 - randInt() % BASE_RANGE;
    word = wordList[base];
    int ed = randInt() % SIM_ED_DIFF + 1;
    int cnt0, cnt1, cnt2;
    do {
        cnt0 = cnt1 = cnt2 = 0;
        for (int i = 0; i < ed; i ++) {
            int op = randInt() % SIM_OP;
            cnt0 += (op == 0);
            cnt1 += (op == 1);
            cnt2 += (op == 2);
        }
    } while ((int) word.length() - cnt0 < 1 || (int) word.length() - cnt0 + cnt2 > MAX_WORD_LENGTH);
    for (int i = 0; i < cnt0; i ++) {
        int j = randInt() % word.length();
        word = word.substr(0, j) + word.substr(j + 1, word.length() - j - 1);
    }
    for (int i = 0; i < cnt1; i ++) {
        int j = randInt() % word.length();
        int t = randInt() % Z;
        word[j] = t + 'a';
    }
    for (int i = 0; i < cnt2; i ++) {
        int j = randInt()% (word.length() + 1);
        word = word.substr(0, j) + " " + word.substr(j, word.length() - j);
        int t = randInt() % Z;
        word[j] = t + 'a';
    }
}

void genWordList() {
    for (int i = 0; i < W; i ++) {
        do {
            if (i < BASE_RANGE) {
                genWord(wordList[i]);
            } else {
                genSimWord(wordList[i], i);
            }
        } while(dict.find(wordList[i]) != dict.end());
        dict[wordList[i]] = i;
    }
    sumWordLen = 0;
    for (int i = 0; i < W; i ++) {
        sumWordLen += wordList[i].length();
    }
    FILE * fout = fopen(WORD_FILE_NAME, "w");
    for (int i = 0; i < W; i ++) {
        fprintf(fout, "%s %d\n", wordList[i].c_str(), i);
    }
    fclose(fout);
}

void genLine(std::vector < int > & line) {
    int lineLen;
    do {
        int len = randInt() % (MAX_LINE_LENGTH * W) / sumWordLen + 1;
        line.clear();
        lineLen = 0;
        for (int i = 0; i < len; i ++) {
            bool isUnique;
            int t;
            do {
                t = randInt() % (W / 2) * 2;
                isUnique = true;
                for (int j = 0; j < i && isUnique; j ++) {
                    isUnique = isUnique && (t != line[j]);
                }
            } while (! isUnique);
            line.push_back(t);
            lineLen += wordList[t].length() + (i > 0);
        }
    } while (lineLen > MAX_LINE_LENGTH || lineLen < MAX_LINE_LENGTH / 2);
}

void genSimLine(std::vector < int > & line, int I) {
    int base = I, T;
    do {
        base --;
        T = randInt() % MOVE_EXPECTION;
    } while (base > 0 && T != 0);
    int lineLen;
    int jc;
    do {
        line = lineList[base];
        jc = randInt() % SIM_JC_DIFF + 1;
        int cnt0, cnt1, cnt2;
        do {
            cnt0 = cnt1 = cnt2 = 0;
            for (int i = 0; i < jc; i ++) {
                int op = randInt() % SIM_OP;
                cnt0 += (op == 0);
                cnt1 += (op == 1);
                cnt2 += (op == 2);
            }
        } while ((int) line.size() - cnt0 < 1);
        for (int i = 0; i < cnt0; i ++) {
            int k = randInt() % line.size();
            for (int j = k; j + 1 < (int) line.size(); j ++) {
                line[j] = line[j + 1];
            }
            line.pop_back();
        }
        for (int i = 0; i < cnt1; i ++) {
            int k;
            int t;
            bool isUnique;
            do {
                k = randInt() % line.size();
                int dt = randInt() % BASE_RANGE - randInt() % BASE_RANGE;
                t = line[k] + dt;
                isUnique = true;
                for (int j = 0; j < (int) line.size() && isUnique; j ++) {
                    isUnique = isUnique && (line[j] != t);
                }
            } while (t < 0 || t >= W || t % 2 != 0 || ! isUnique);
            line[k] = t;
        }
        for (int i = 0; i < cnt2; i ++) {
            int k;
            int t;
            bool isUnique;
            do {
                k = randInt() % (line.size() + 1);
                t = randInt() % (W / 2) * 2;
                isUnique = true;
                for (int j = 0; j < (int) line.size() && isUnique; j ++) {
                    isUnique = isUnique && (line[j] != t);
                }
            } while (! isUnique);
            line.resize(line.size() + 1);
            for (int j = line.size() - 1; j > k; j --) {
                line[j] = line[j - 1];
            }
            line[k] = t;
        }
        lineLen = 0;
        for (int j = 0; j < (int) line.size(); j ++) {
            lineLen += wordList[line[j]].length() + (j > 0);
        }
    } while (lineLen > MAX_LINE_LENGTH || lineLen < MAX_LINE_LENGTH / 2);
}

uint64 getLineHashValue(std::vector < int > & line) {
    uint64 hv = 0;
    for (int i = 0; i < line.size(); i ++) {
        hv = (hv * HASH_BASE + line[i]) % HASH_MODE;
    }
    return hv;
}

void genLineList() {
    for (int i = 0; i < N; i ++) {
        if (i % (N / 100) == 0) {
            printf("genLineList:  %d / %d\n", i, N);
        }
        uint64 hv;
        do {
            if (i < BASE_RANGE) {
                genLine(lineList[i]);
            } else {
                genSimLine(lineList[i], i);
            }
            hv = getLineHashValue(lineList[i]);
        } while(lineDict.find(hv) != lineDict.end());
        lineDict[hv] = i;
    }
    FILE * fout = fopen(DATA_FILE_NAME, "w");
    for (int i = 0; i < N; i ++) {
        for (int j = 0, sz = lineList[i].size(); j < sz; j ++) {
            int t = lineList[i][j];
            if (t % 2 != 0) {
                printf("!!!\n");
            }
            fprintf(fout, "%s%s", j > 0 ? " " : "", wordList[t].c_str());
        }
        fprintf(fout, "\n");
    }
    fclose(fout);
}

void genEdQuery(std::pair < std::string, int > & edQuery) {
    int base = randInt() % N;
    int ed = randInt() % (MAX_LINE_LENGTH / 8);
    std::string line = "";
    for (int i = 0, sz = lineList[base].size(); i < sz; i ++) {
        int t = lineList[base][i];
        line = line + wordList[t];
        if (i + 1 < sz) {
            line = line + " ";
        }
    }
    int cnt0, cnt1, cnt2;
    do {
        cnt0 = cnt1 = cnt2 = 0;
        for (int i = 0; i < ed; i ++) {
            int op = randInt() % SIM_OP;
            cnt0 += (op == 0);
            cnt1 += (op == 1);
            cnt2 += (op == 2);
        }
    } while ((int) line.length() - cnt0 < 1 || (int) line.length() - cnt0 + cnt2 > MAX_LINE_LENGTH);
    for (int i = 0; i < cnt0; i ++) {
        int j = randInt() % line.length();
        line = line.substr(0, j) + line.substr(j + 1, line.length() - j - 1);
    }
    for (int i = 0; i < cnt1; i ++) {
        int j = randInt() % line.length();
        int t = randInt() % ZZ;
        line[j] = t + ' ';
    }
    for (int i = 0; i < cnt2; i ++) {
        int j = randInt()% (line.length() + 1);
        line = line.substr(0, j) + " " + line.substr(j, line.length() - j);
        int t = randInt() % ZZ;
        line[j] = t + ' ';
    }
    edQuery.first = line;
    edQuery.second = ed - 1 + randInt() % (MAX_WORD_LENGTH * SIM_JC_DIFF);
}

void genEdQuery() {
    for (int i = 0; i < Q; i ++) {
        if (i % (Q / 100) == 0) {
            printf("genEdQuery:  %d / %d\n", i, Q);
        }
        genEdQuery(edQueryList[i]);
    }
    FILE * fout = fopen(ED_QUERY_FILE_NAME, "w");
    for (int i = 0; i < Q; i ++) {
        fprintf(fout, "%s\n", edQueryList[i].first.c_str());
        fprintf(fout, "%d\n", edQueryList[i].second);
    }
    fclose(fout);
}

void genJcQuery(std::pair < std::string, double > & jcQuery) {
    int base = randInt() % N;
    int jc = randInt() % (MAX_LINE_LENGTH * W) / (sumWordLen * 8) + 1;
    double jc_d;
    std::vector < int > line;
    int lineLen;
    do {
        line = lineList[base];
        int cnt0, cnt1, cnt2;
        do {
            cnt0 = cnt1 = cnt2 = 0;
            for (int i = 0; i < jc; i ++) {
                int op = randInt() % SIM_OP;
                cnt0 += (op == 0);
                cnt1 += (op == 1);
                cnt2 += (op == 2);
            }
        } while ((int) line.size() - cnt0 < 1);
        jc_d = ((double) line.size() - cnt0 - cnt1) / ((double) line.size() + cnt1 + cnt2);
        for (int i = 0; i < cnt0; i ++) {
            int k = randInt() % line.size();
            for (int j = k; j + 1 < (int) line.size(); j ++) {
                line[j] = line[j + 1];
            }
            line.pop_back();
        }
        for (int i = 0; i < cnt1; i ++) {
            int k;
            int t;
            bool isUnique;
            do {
                k = randInt() % line.size();
                t = randInt() % W;
                isUnique = true;
                for (int j = 0; j < (int) line.size() && isUnique; j ++) {
                    isUnique = isUnique && (line[j] != t);
                }
            } while (! isUnique);
            line[k] = t;
        }
        for (int i = 0; i < cnt2; i ++) {
            int k;
            int t;
            bool isUnique;
            do {
                k = randInt() % (line.size() + 1);
                t = randInt() % W;
                isUnique = true;
                for (int j = 0; j < (int) line.size() && isUnique; j ++) {
                    isUnique = isUnique && (line[j] != t);
                }
            } while (! isUnique);
            line.resize(line.size() + 1);
            for (int j = line.size() - 1; j > k; j --) {
                line[j] = line[j - 1];
            }
            line[k] = t;
        }
        lineLen = 0;
        for (int j = 0; j < (int) line.size(); j ++) {
            lineLen += wordList[line[j]].length() + (j > 0);
        }
    } while (lineLen > MAX_LINE_LENGTH || lineLen < MAX_LINE_LENGTH / 2);
    double jc_q;
    do {
        jc_q = jc_d - (double) (randInt() % 10000) * 0.0001 * 0.4;
    } while (jc_q <= 1e-4 || jc_q >= jc_d - 1e-4);
    jcQuery.first = "";
    for (int i = 0; i < (int) line.size(); i ++) {
        jcQuery.first = jcQuery.first + wordList[line[i]];
        if (i + 1 < (int) line.size()) {
            jcQuery.first = jcQuery.first + " ";
        }
    }
    jcQuery.second = jc_q;
}

void genJcQuery() {
    for (int i = 0; i < Q; i ++) {
        if (i % (Q / 100) == 0) {
            printf("genJcQuery:  %d / %d\n", i, Q);
        }
        genJcQuery(jcQueryList[i]);
    }
    FILE * fout = fopen(JC_QUERY_FILE_NAME, "w");
    for (int i = 0; i < Q; i ++) {
        fprintf(fout, "%s\n", jcQueryList[i].first.c_str());
        fprintf(fout, "%.8lf\n", jcQueryList[i].second);
    }
    fclose(fout);
}

int main() {
    //srand(time(0));
    srand(12345);
    genWordList();
    genLineList();
    genEdQuery();
    genJcQuery();
    return 0;
}
