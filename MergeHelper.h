#ifndef MERGE_HELPER_H_
#define MERGE_HELPER_H_

#include <vector>

/**
 *  在合并lineSet时使用的数据结构。
 *  第一次调用getInstance前必须先调用init函数，否则是NULL
 *  可以O(1)给某个行编号增加一次计数；
 *  可以O(1)查询至少出现t次的行编号个数；
 *  可以O(数量)导出至少出现t此的行编号vector；
 *  可以均摊O(1)清空以便下次使用。
 */
class MergeHelper {
    
private:
    //数据的总行数
    static int N;
    //单例
    static MergeHelper * instance;
    
private:
    //每个行编号出现的次数数组
    int * lCnt;
    //每个次数的行编号数量后缀和数组
    int * cSum;
    //每个数量的双向链表的头节点编号
    int * headNode;
    //每个节点的上个节点编号和下个节点编号，初始为-1
    int * nodePrev;
    int * nodeNext;
    
private:
    /*
     *  构造函数
     */
    MergeHelper();
    
    /*
     *  析构函数
     */
    virtual ~MergeHelper();
    
public:
    /*
     *  函数：increase
     *  功能：给一个行编号的计数器+1
     */
    void increase(int l);
    
    /*
     *  函数：getUpperCnt
     *  功能：查询至少出现t次的行编号
     */
    int getUpperCnt(int t);
    
    /*
     *  函数：exportOutUpper
     *  功能：导出至少出现t此的行编号到vector，无序状态
     */
    void getUpperList(int t0, std::vector < int > & upperList);
    
    /*
     *  函数：clear
     *  功能：清理现场以便下次使用
     */
    void clear();
    
    /*
     *  函数：print
     *  功能：把整个链表都打印出来
     */
    void print();
    
public:
    /*
     *  函数：init
     *  功能：设置N的值
     */
    static void init(int N_);
    
    /*
     *  函数：getInstance
     *  功能：获取单例
     */
    static MergeHelper * getInstance();
};

#endif // MERGE_HELPER_H_
