#ifndef GRAGH_
#define GRAPH_

#include <string>
#include <vector>

using namespace std;

const int MAX_VERTEX_NUM = 2400;

// 邻接矩阵
template <typename VertexType, typename InfoType>
class MGragh
{
public:
    MGragh(VertexType (*ptr2vexs)[], InfoType *(*ptr2arcs)[MAX_VERTEX_NUM][MAX_VERTEX_NUM], int vexnum, int arcnum);
    ~MGragh();
    // void set_vertex(VertexType vertex, int idx);
    // void set_arc(InfoType *arc, int vex_a_idx, int vex_b_idx);

    void dfs_traverse(int vertex_idx); // 从某个顶点开始深度优先遍历
    void bfs_traverse(int vertex_idx); // 从某个顶点开始广度优先遍历

    VertexType get_vertex(int idx);
    InfoType *get_arc_info(int v1_idx, int v2_idx);

private:
    typedef InfoType *AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM]; // 是否连通，或权值

    VertexType (*ptr2vexs)[MAX_VERTEX_NUM]; // 顶点向量
    AdjMatrix *ptr2arcs;                    // 邻接矩阵
    int vexnum, arcnum;
};


template<typename InfoType>
struct ArcNode
{
    int adjvex;       // 该弧所指向的顶点的位置
    ArcNode *nextarc; // 指向下一条弧的指针
    InfoType *info;   // 该弧相关信息的指针
};


template<typename VertexType, typename InfoType>
struct VNode
{
    VertexType data;   //顶点信息
    ArcNode<InfoType> *firstarc; // 指向第一条依附该顶点的弧
};


// 邻接表
template <typename VertexType, typename InfoType>
class ALGraph
{
public:
    ALGraph(VNode<VertexType, InfoType> (*ptr2vexs)[MAX_VERTEX_NUM], int vexnum, int arcnum);
    ~ALGraph();

    vector<vector<VertexType>> find_all_paths(int v1_idx, int v2_idx);
    vector<VertexType> find_shortest_path(int v1_idx, int v2_idx, int (*cmp)(const InfoType*, const InfoType*)); // 寻找最短路径

private:

    VNode<VertexType, InfoType> (*ptr2vertices)[MAX_VERTEX_NUM];
    int vexnum, arcnum;
};

#endif