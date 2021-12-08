#include <iostream>

#include "graph.h"
#include "airline.h"
#include "datetime.h"
#include "datautils.h"

class App
{
public:
    App() {};

    void load_data(ALGraph<AirportID, Flight> *data);

    vector<AirLine> find(AirportID departure, AirportID arrival);
    vector<AirLine> find_by_departure_time(AirportID departure, AirportID arrival, Datetime start, Datetime end);
    vector<AirLine> find_by_arrival_time(AirportID departure, AirportID arrival, Datetime start, Datetime end);
    vector<AirLine> find_by_airplane_type(AirportID departure, AirportID arrival, AirplaneType type);
    vector<AirLine> find_by_transit_times(AirportID departure, AirportID arrival, TimeDelta times);
    vector<AirLine> find_by_direct(AirportID departure, AirportID arrival);
    vector<AirLine> find_by_filght_time(AirportID departure, AirportID arrival, int lowest, int highest, int topk = -1, bool sorted = false);
    vector<AirLine> find_by_fare(AirportID departure, AirportID arrival, int lowest, int highest, int topk = -1, bool sorted = false);

    void sort();

    void run();

private:
    ALGraph<AirportID, Flight> *data;

    void find_baisc(AirportID departure, AirportID arrival, int (*condition)(const AirLine &));
    void sort_basic(int (*cmp)(const AirLine&, const AirLine &)); // std::sort()
};

int main()
{
    // 1. 读取数据，将字符串转换成航班数据并存储在一个 vector 中
    string data_path = "..\\data\\airline.csv";
    vector<Flight> flights;
    read_data(data_path, flights);

    // 2. 建立储存图的结构

    // 3. 启动应用
    App app;
    app.run();
}

void App::run()
{
    std::cout << "Hello, world!\n";
}
