/***********************************************************
 * 中国人民大学，2021年秋季学期，数据结构，大作业，航班路线查询系统
 *
 * Author: Liu Qi
 * Time:   2021.12
 * *********************************************************/

#include "App.h"
#include <getopt.h>

void print_usage()
{
    printf(
        "Usage:\n"

    );
    exit(0);
}

int main(int argc, char *argv[])
{
    // 0. 命令行解析
    int opt = 0;
    int departure = -1, arrival = -1;
    while ((opt = getopt(argc, argv, "h::d:a:")) != -1)
    {
        switch (opt)
        {
        case 'h':
            print_usage();
            break;
        case 'd':
            departure = atoi(optarg);
            break;
        case 'a':
            arrival = atoi(optarg);
            break;
        default:
            print_usage();
        }
    }

    // 1. 读取数据，将字符串转换成航班数据并存储在一个 vector 中
    //    - 机场 ID 最小为 1，最大为 79
    string data_path = "..\\data\\airline.csv";
    vector<Flight> flights;
    read_data(data_path, flights);

    // 2. 建立储存图的结构
    int airport_num = 79;            // 机场数量，即顶点数量
    int flight_num = flights.size(); // 航班数量

    int vexnum = airport_num + 1;
    int arcnum = 0;

    cout << "airport_num : " << airport_num << endl;
    cout << "flight_num  : " << flight_num << endl;

    // - 2.1 建立邻接矩阵
    vector<AirportID> vertexs(MAX_VERTEX_NUM);
    for (int i = 1; i <= airport_num; i++)
        vertexs[i] = i;

    vector<vector<Flights *>> arcs(MAX_VERTEX_NUM);
    for (int i = 0; i < MAX_VERTEX_NUM; i++)
        arcs[i] = vector<Flights *>(MAX_VERTEX_NUM, NULL);
    for (vector<Flight>::iterator iter = flights.begin(); iter != flights.end(); iter++)
    {
        int i = iter->get_departure_airport(), j = iter->get_arrival_airport();
        if (arcs[i][j] == NULL)
        {
            arcnum++;
            arcs[i][j] = new Flights;
        }
        arcs[i][j]->push_back(*iter);
    }
    MGraph<AirportID, Flights *> mgraph(vertexs, arcs, vexnum, arcnum);

    cout << "vexnum : " << vexnum << endl;
    cout << "arcnum : " << arcnum << endl;

    // - 2.2 建立邻接表
    vector<VNode<AirportID, Flights *>> vexs(vexnum);
    for (int i = 1; i < vexnum; i++)
        vexs[i].data = i;
    for (int i = 1; i < vexnum; i++)
        for (int j = 1; j < vexnum; j++)
            if (arcs[i][j])
            {
                ArcNode<Flights *> node = {j, arcs[i][j]};
                vexs[i].arc_list.push_back(node);
            }
    ALGraph<AirportID, Flights *> algraph(vexs, vexnum, arcnum);

    // 3. 启动应用
    App app;
    app.load_mgraph(&mgraph);
    app.load_algraph(&algraph);
    if (departure != -1 && arrival != -1)
        app.set_departure_arrival(departure, arrival);
    app.run();

    // 4. 释放内存
    for (int i = 0; i < MAX_VERTEX_NUM; i++)
    {
        for (int j = 0; j < MAX_VERTEX_NUM; j++)
        {
            if (arcs[i][j])
                delete arcs[i][j];
        }
    }

    return 0;
}
