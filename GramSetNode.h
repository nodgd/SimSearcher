#ifndef GRAM_SET_NODE_H_
#define GRAM_SET_NODE_H_

#include <vector>

/**
 *  Gram字典树的每个节点，需要先调用init函数。
 *  一开始它的lineSet是NULL，等到用的时候才去创建。
 */
class GramSetNode {
    
private:
    //字符集大小
    static int Z;
    //字符对应的数值编号，范围[0, Z - 1]，这个数组不清理
    static int * asciiId;
    
private:
    //子节点列表
    GramSetNode ** son;
    //包含当前节点表示的gram的行集合
    std::vector < int > * lineSet;
    
public:
    /*
     *  构造函数
     */
    GramSetNode();
    
    /*
     *  析构函数
     */
    virtual ~GramSetNode();
    
public:
    /*
     *  函数：getSonByAscii
     *  功能：获取子节点
     */
    GramSetNode * getSonById(int i);
    
    /*
     *  函数：getSonByAscii
     *  功能：获取子节点
     */
    GramSetNode * getSonByAscii(char ch);
    
    /*
     *  函数：getOrCreateSonByAscii
     *  功能：获取子节点，如果不存在就创建一个
     */
    GramSetNode * getOrCreateSonByAscii(char ch);
    
    /*
     *  函数：getLineSet
     *  功能：获取行集合
     */
    std::vector < int > * getLineSet();
    
    /*
     *  函数：getOrCreateLineSet
     *  功能：获取或创建行集合
     */
    std::vector < int > * getOrCreateLineSet();
    
public:
    /*
     *  函数：init
     *  功能：设置Z和asciiId
     */
    static void init(int Z_, int * asciiId_);
};

#endif // GRAM_SET_NODE_H_
