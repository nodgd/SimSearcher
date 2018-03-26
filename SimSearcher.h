#ifndef SIM_SEARCHER_H_
#define SIM_SEARCHER_H_

#include <vector>
#include <string>

#include "GramSet.h"

/**
 *  近似查询主类。
 */
class SimSearcher {
    
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
    int * asciiId;
    
    //ED距离的数据结构
    GramSet * edGramSet;
    
    
public:
    /*
     *  @构造函数
     */
	SimSearcher();
	
	/*
	 *  @析构函数
	 */
	~SimSearcher();

private:
    ///构建索引时用到的函数
    /*
     *  函数：openInputFile
     *  功能：打开指定的输入文件，如果找不到指定的输入文件或者没有指定输入文件就打开调试用的输入文件
     */
    bool openInputFile(const char * fileName);
    
    /*
     *  函数：readInputFile
     *  功能：把输入文件逐行读入，存到lineList里面，并统计输入文件中的字符集等基本信息
     */
    void readInputFile();
    
    /*
     *  函数：createEdIndex
     *  功能：构建编辑距离的索引
     */
    void createEdIndex();
	
public:
    ///外部调用的函数
    /*
     *  函数：createIndex
     *  功能：建立索引
     */
	int createIndex(const char * fileName, unsigned Q_);
	
	/*
     *  函数：searchJaccard
     *  功能：查询Jaccard
     */
	int searchJaccard(const char * query, double threshold, std::vector < std::pair < unsigned, double > > & result);
	
	/*
     *  函数：searchED
     *  功能：查询ED
	 */
	int searchED(const char * query, unsigned threshold, std::vector < std::pair < unsigned, unsigned > > & result);
};

#endif // SIM_SEARCHER_H_
