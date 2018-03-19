#ifndef SIM_SEARCHER_H_
#define SIM_SEARCHER_H_

#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>
#include <string>

#include "GramSet.h"

const int SUCCESS = 0;
const int FAILURE = 1;

class SimSearcher {
    
public:
    //每一行的最大长度
    static const int MAX_LENGTH = 256;
    
private:
    //算法要求Q-grams
    int Q;
    //输入文件的文件指针
    FILE * inputFile;
    //输入数据行数
    int N;
    //输入数据的每一行
    std::vector < std::string > lineList;
    //字符集的大小
    int Z;
    //字符对应的数值编号，范围[0, Z - 1]
    int asciiId[MAX_ASCII + 4];
    
    
public:
    /*
     *  @构造函数
     */
	SimSearcher() {
	    Q = 0;
	    inputFile = NULL;
	}
	
	/*
	 *  @析构函数
	 */
	~SimSearcher() {
	}

private:
    ///构建索引时用到的函数
    /*
     *  函数：openInputFile
     *  功能：打开指定的输入文件，如果找不到指定的输入文件或者没有指定输入文件就打开调试用的输入文件
     */
    bool openInputFile(const char * fileName) {
        FILE * file = fopen(fileName, "r");
        if (file == NULL) {
            file = fopen("sample.txt", "r");
        }
        if (file == NULL) {
            return false;
        }
        inputFile = file;
        return true;
    }
    
    /*
     *  函数：readInputFile
     *  功能：把输入文件逐行读入，存到lineList里面，同时统计输入文件中的字符集等基本信息
     */
    void readInputFile() {
        static char buf[MAX_LENGTH + 4];
        while (fscanf(inputFile, "%[^\n]\n", buf) != EOF) {
            lineList.push_back(std::string(buf));
            for (int j = 0; j < MAX_LENGTH && buf[j]; j ++) {
                asciiId[buf[j]] = 1;
            }
            memset(buf, 0 ,sizeof(buf));
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
    }
    
    /*
     *  函数：createEdIndex
     *  功能：构建编辑距离的索引
     */
    void createEdIndex() {
        int n = lineList.size();
        for (int i = 0; i < n; i ++) {
            std::string line = lineList[i];
            int length = line.length();
            for (int l = 0; l + Q <= length; l ++) {
                std::string gram = line.substr(l, Q);
                
                printf("%d %d %s\n", i, l, gram.c_str());
                
            }
        }
    }
	
public:
    ///外部调用的函数
    /*
     *  函数：createIndex
     *  功能：建立索引
     */
	int createIndex(const char * fileName, unsigned Q_) {
	    if (! openInputFile(fileName)) {
            fprintf(stderr, "Can not open the input file.\n");
            return FAILURE;
	    }
	    Q = Q_;
	    readInputFile();
        createEdIndex();


	}
	
	/*
     *  函数：searchJaccard
     *  功能：查询Jaccard
     */
	int searchJaccard(const char * query, double threshold, std::vector < std::pair < unsigned, double > > & result) {
	    
	}
	
	/*
     *  函数：searchED
     *  功能：查询ED
	 */
	int searchED(const char * query, unsigned threshold, std::vector < std::pair < unsigned, unsigned > > & result) {
	    
	    
	}
};

#endif // SIM_SEARCHER_H_
