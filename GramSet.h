#ifndef GRAM_SET_H_
#define GRAM_SET_H_

#include <string>

#include "GramSetNode.h"

/**
 *  所有Gram的字典树，需要先调用init函数。
 *  每个Gram的末尾节点有一个LineSet，存带有这个Gram的所有行的编号。
 */
class GramSet {
    
private:
    //字符集大小
    static int Z;
    //字符对应的数值编号，范围[0, Z - 1]，这个数组不清理
    static int * asciiId;
    
private:
    //根节点
    GramSetNode * root;
    
public:
    /*
     *  构造函数
     */
    GramSet();
    
    /*
     *  析构函数
     */
    virtual ~GramSet();

private:
    /*
     *  函数：clear
     *  功能：清理cur子树下的所有节点
     */
    void clear(GramSetNode * cur);
    
    /*
     *  函数：printVisitor
     *  功能：打印到屏幕时的递归访问
     */
    void printVisitor(GramSetNode * cur, char * gram, int gramLen);
    
public:
    /*
     *  函数：insertGram
     *  功能：插入一个gram
     */
    void insertGram(const std::string & gram, int lineId);
    
    /*
     *  函数：getLineSet
     *  功能：查询一个gram的行编号集合，如果没有就返回NULL
     */
    std::vector < int > * getLineSet(const std::string & gram);
    
    /*
     *  函数：print
     *  功能：打印到屏幕，方便Debug
     */
    void print();
    
public:
    /*
     *  函数：init
     *  功能：设置Z和asciiId
     */
    static void init(int Z_, int * asciiId_);
};

#endif // GRAM_SET_H_
