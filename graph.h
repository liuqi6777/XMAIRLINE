#ifndef GRAGH_
#define GRAPH_

#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

#include <assert.h>

using namespace std;

const int MAX_VERTEX_NUM = 80;

// 邻接矩阵  （行为出，列为入）
template <typename VertexType, typename InfoType>
class MGraph
{
public:
    MGraph(vector<VertexType> &vexs, vector<vector<InfoType>> &arcs, int vexnum, int arcnum);
    ~MGraph();
    // void set_vertex(VertexType vertex, int idx);
    // void set_arc(InfoType *arc, int vex_a_idx, int vex_b_idx);

    void dfs_traverse(int vertex_idx); // 从某个顶点开始深度优先遍历
    void bfs_traverse(int vertex_idx); // 从某个顶点开始广度优先遍历

    vector<vector<VertexType>> find_all_paths(int v1_idx, int v2_idx, int max_len = -1);
    vector<VertexType> find_shortest_path(int v1_idx, int v2_idx, bool (*cmp)(const InfoType &, const InfoType &)); // 寻找最短路径

    VertexType get_vertex(const int idx);
    InfoType get_arc_info(const int v1_idx, const int v2_idx);

private:
    // typedef InfoType AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

    vector<VertexType> vexs;       // 顶点向量
    vector<vector<InfoType>> arcs; // 邻接矩阵，是否连通，或权值
    int vexnum, arcnum;

    void dfs(int vertex_idx, bool *visited);
    void find_path(int v1_idx, int v2_idx, vector<VertexType> &current_path, vector<vector<VertexType>> &all_paths, int max_len);
    void visit(int vertex_idx);
};

template <typename InfoType>
struct ArcNode
{
    int adjvex; // 该弧所指向的顶点的位置
    // ArcNode *nextarc; // 指向下一条弧的指针
    InfoType info; // 该弧相关信息的指针
};

template <typename VertexType, typename InfoType>
struct VNode
{
    VertexType data; // 顶点信息
    // ArcNode<InfoType> *firstarc; // 指向第一条依附该顶点的弧
    vector<ArcNode<InfoType>> arc_list; // 指向弧的链表（使用数组替代简化）
};


// 邻接表
template <typename VertexType, typename InfoType>
class ALGraph
{
public:
    ALGraph(vector<VNode<VertexType, InfoType>> vexs, int vexnum, int arcnum);
    ~ALGraph();

    void dfs_traverse(int vertex_idx); // 从某个顶点开始深度优先遍历
    void bfs_traverse(int vertex_idx); // 从某个顶点开始广度优先遍历

    vector<vector<VertexType>> find_all_paths(int v1_idx, int v2_idx, int max_len = -1);
    vector<VertexType> find_shortest_path(int v1_idx, int v2_idx, bool (*cmp)(const InfoType &, const InfoType &)); // 寻找最短路径

private:
    vector<VNode<VertexType, InfoType>> vertices;
    int vexnum, arcnum;
};

#endif

template <typename VertexType, typename InfoType>
MGraph<VertexType, InfoType>::MGraph(vector<VertexType> &vexs, vector<vector<InfoType>> &arcs, int vexnum, int arcnum)
{
    this->vexs = vexs;
    this->arcs = arcs;
    this->vexnum = vexnum;
    this->arcnum = arcnum;
}

template <typename VertexType, typename InfoType>
MGraph<VertexType, InfoType>::~MGraph()
{
    for (int i = 0; i < arcs.size(); i++)
        for (int j = 0; j < arcs.size(); j++)
            if (arcs[i][j])
                delete arcs[i][j];
}

template <typename VertexType, typename InfoType>
VertexType MGraph<VertexType, InfoType>::get_vertex(const int idx)
{
    assert(idx >= 0 && idx < vexnum);
    return vexs[idx];
}

template <typename VertexType, typename InfoType>
InfoType MGraph<VertexType, InfoType>::get_arc_info(const int v1_idx, const int v2_idx)
{
    assert(v1_idx >= 0 && v1_idx < vexnum);
    assert(v2_idx >= 0 && v2_idx < vexnum);
    return arcs[v1_idx][v2_idx];
}

template <typename VertexType, typename InfoType>
void MGraph<VertexType, InfoType>::dfs_traverse(int v)
{
    bool visited[vexnum] = {0};
    dfs(v, visited);
    for (int i = 0; i < vexnum; i++)
        if (!visited[i])
            dfs(i, visited);
}

template <typename VertexType, typename InfoType>
void MGraph<VertexType, InfoType>::dfs(int v, bool *visited)
{
    if (visited[v])
        return;
    visit(v);
    visited[v] = true;
    for (int i = 0; i < vexnum; i++)
        if (arcs[v][i] && !visited[i])
            dfs(i, visited);
}

template <typename VertexType, typename InfoType>
void MGraph<VertexType, InfoType>::bfs_traverse(int v)
{
    bool visited[vexnum] = {0};
    queue<int> q;
    visit(v);
    visited[v] = true;
    q.push(v);

    while (!q.empty())
    {
        int i = q.front();
        q.pop();

        for (int j = 0; j < vexnum; j++)
        {
            if (arcs[i][j] && !visited[j])
            {
                visit(j);
                visited[j] = true;
                q.push(j);
            }
        }
    }
}

template <typename VertexType, typename InfoType>
void MGraph<VertexType, InfoType>::visit(int v)
{
    std::cout << vexs[v] << std::endl;
}

template <typename VertexType, typename InfoType>
void MGraph<VertexType, InfoType>::
find_path(int v1_idx, int v2_idx, vector<VertexType> &current_path, vector<vector<VertexType>> &all_paths, int max_len)
{
    if (current_path.size() == max_len)
        return;
    if (v1_idx == v2_idx)
    {
        all_paths.push_back(current_path);
        return;
    }
    for (int i = 0; i < vexnum; i ++)
    {
        if (arcs[v1_idx][i] != NULL)
        {
            current_path.push_back(i);
            find_path(i, v2_idx, current_path, all_paths, max_len);
            current_path.pop_back();
        }
    }
}

template <typename VertexType, typename InfoType>
vector<vector<VertexType>> MGraph<VertexType, InfoType>::find_all_paths(int v1_idx, int v2_idx, int max_len)
{
    // 邻接矩阵所有路径
    vector<VertexType> s; // 模拟栈的作用
    s.push_back(v1_idx);
    vector<vector<VertexType>> res;
    find_path(v1_idx, v2_idx, s, res, max_len);
    return res;
}

template <typename VertexType, typename InfoType>
vector<VertexType> MGraph<VertexType, InfoType>::find_shortest_path(int v1_idx, int v2_idx, bool (*cmp)(const InfoType &, const InfoType &))
{
    // TODO: 邻接矩阵最短路径
    vector<VertexType> res;
    return res;
}


template <typename VertexType, typename InfoType>
ALGraph<VertexType, InfoType>::ALGraph(vector<VNode<VertexType, InfoType>> vexs, int vexnum, int arcnum)
{
    this->vertices = vexs;
    this->vexnum = vexnum;
    this->arcnum = arcnum;
}

template <typename VertexType, typename InfoType>
ALGraph<VertexType, InfoType>::~ALGraph()
{
    for (int i = 0; i < vertices.size(); i++)
    {
        for (int j = 0; j < this->vertices[i].arc_list.size(); j++)
            if (vertices[i].arc_list[j].info)
                delete vertices[i].arc_list[j].info;
    }
}

template <typename VertexType, typename InfoType>
vector<vector<VertexType>> ALGraph<VertexType, InfoType>::find_all_paths(int v1_idx, int v2_idx, int max_len)
{
    // TODO: 邻接表所有路径
    vector<vector<VertexType>> res;
    return res;
}

template <typename VertexType, typename InfoType>
vector<VertexType> ALGraph<VertexType, InfoType>::find_shortest_path(int v1_idx, int v2_idx, bool (*cmp)(const InfoType &, const InfoType &))
{
    // TODO: 邻接表最短路径
    vector<VertexType> res;
    return res;
}

template <typename VertexType, typename InfoType>
void ALGraph<VertexType, InfoType>::dfs_traverse(int v)
{
    // TODO: 邻接表dfs
}

template <typename VertexType, typename InfoType>
void ALGraph<VertexType, InfoType>::bfs_traverse(int v)
{
    // TODO: 邻接表bfs
}
