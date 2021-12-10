#include "graph.h"
#include "airline.h"
#include "datetime.h"
#include "datautils.h"

class App
{
public:
    App() : mgraph(NULL), algraph(NULL) {}

    void load_mgraph(MGraph<AirportID, Flights *> *data);
    void load_algraph(ALGraph<AirportID, Flights *> *data);

    vector<AirLine> find(AirportID departure, AirportID arrival);

    vector<AirLine> find_by_departure_time(AirportID departure, AirportID arrival, Datetime start, Datetime end);
    vector<AirLine> find_by_departure_time(vector<AirLine> airlines, Datetime start, Datetime end);

    vector<AirLine> find_by_arrival_time(AirportID departure, AirportID arrival, Datetime start, Datetime end);
    vector<AirLine> find_by_arrival_time(vector<AirLine> airlines, Datetime start, Datetime end);

    vector<AirLine> find_by_flight_type(AirportID departure, AirportID arrival, AirplaneType type);
    vector<AirLine> find_by_flight_type(vector<AirLine> airlines, AirplaneType type);

    vector<AirLine> find_by_transit_times(AirportID departure, AirportID arrival, int times);
    vector<AirLine> find_by_transit_times(vector<AirLine> airlines, int times);

    vector<AirLine> find_by_direct(AirportID departure, AirportID arrival);
    vector<AirLine> find_by_direct(vector<AirLine> airlines);

    vector<AirLine> find_by_airline_time(AirportID departure, AirportID arrival, TimeDelta least, TimeDelta most);
    vector<AirLine> find_by_airline_time(vector<AirLine> airlines, TimeDelta least, TimeDelta most);

    vector<AirLine> find_by_fare(AirportID departure, AirportID arrival, int least, int most);
    vector<AirLine> find_by_fare(vector<AirLine> airlines, int least, int most);

    void run();

private:
    MGraph<AirportID, Flights *> *mgraph;
    ALGraph<AirportID, Flights *> *algraph;

    Flights get_flights(const AirportID d, const AirportID a);
    vector<AirLine> flights_to_airlines(const vector<Flights> &flights);

    vector<AirLine> find_baisc(AirportID departure, AirportID arrival);
    void sort_basic(int (*cmp)(const AirLine &, const AirLine &)); // std::sort()
};

void App::run()
{
    assert(mgraph != NULL);
    assert(algraph != NULL);

    std::cout << "\nHello, world!\n\n";

    cout << "Please input departure airport id and arrival airport id:" << endl;
    int d, a;
    cin >> d >> a;
    vector<AirLine> first_results = find_baisc(d, a);

    cout << "Follow are all airline(s) (only routes with fewer than 3 transfers are included):" << endl;
    cout << "(" << first_results.size() << " in total)\n"; 
    for (int i = 0; i < first_results.size(); i ++)
        cout << "[AIRLINE " << i+1 << "]" << endl << first_results[i];

    cout << "You can give some limits:\n"
         << "Input 1 to set the range of departure times;\n"
         << "      2 to set the range of arrival times;\n"
         << "      3 to choose airplane type;\n"
         << "      4 to set the range of transit times (0 means direct);\n"
         << "      5 to set the range of the flight time (including transit time);\n"
         << "      6 to set the range of fares;\n";

    int m = 0;
    cin >> m;
    
    vector<AirLine> res;
    if (m == 1)
    {
        int year, month, day, hour, min;
        cout << "Please input starting time(format: y m d h min): ";
        cin >> year >> month >> day >> hour >> min;
        Datetime start(year, month, day, hour, min);
        cout << "Please input ending time: ";
        cin >> year >> month >> day >> hour >> min;
        Datetime end(year, month, day, hour, min);
        res = find_by_departure_time(first_results, start, end);

        cout << "Follow are all airlines found by departure time:" << endl;
        cout << "(" << res.size() << " in total)\n"; 
        for (int i = 0; i < res.size(); i ++)
            cout << res[i];
    }
    else if (m == 2)
    {
        int year, month, day, hour, min;
        cout << "Please input starting time(format: y m d h min): ";
        cin >> year >> month >> day >> hour >> min;
        Datetime start(year, month, day, hour, min);
        cout << "Please input ending time: ";
        cin >> year >> month >> day >> hour >> min;
        Datetime end(year, month, day, hour, min);
        res = find_by_arrival_time(first_results, start, end);

        cout << "Follow are all airlines found by arrival time:" << endl;
        cout << "(" << res.size() << " in total)\n"; 
        for (int i = 0; i < res.size(); i ++)
            cout << res[i];
    }
    else if (m == 3)
    {

    }
    else if (m == 4)
    {
        int times = 0;
        cout << "Please input the max num of transit times (0 means direct): ";
        cin >> times;
        res = find_by_transit_times(first_results, times);

        cout << "Follow are all airlines found by transit times:" << endl;
        cout << "(" << res.size() << " in total)\n"; 
        for (int i = 0; i < res.size(); i ++)
            cout << res[i];
    }
    else if (m == 5)
    {
        int day, hour, minute;
        cout << "Please input the min flight time for your flight (format: day hour min): ";
        cin >> day >> hour >> minute;
        TimeDelta least(day, hour, minute);
        cout << "Please input the max flight time for your flight: ";
        cin >> day >> hour >> minute;
        TimeDelta most(day, hour, minute);
        res = find_by_airline_time(first_results, least, most);

        cout << "Follow are all airlines found by airline time:" << endl;
        cout << "(" << res.size() << " in total)\n"; 
        for (int i = 0; i < res.size(); i ++)
            cout << res[i];
    }
    else if (m == 6)
    {
        int least, most;
        cout << "Please input the min fares: ";
        cin >> least;
        cout << "Please input the max fares: ";
        cin >> most;
        res = find_by_fare(first_results, least, most);

        cout << "Follow are all airlines found by fares:" << endl;
        cout << "(" << res.size() << " in total)\n"; 
        for (int i = 0; i < res.size(); i ++)
            cout << res[i];
    }
    else
    {
        cout << "Please input a number between 1 and 6!\n";
    }
}

void App::load_mgraph(MGraph<AirportID, Flights *> *data)
{
    this->mgraph = data;
}

void App::load_algraph(ALGraph<AirportID, Flights *> *data)
{
    this->algraph = data;
}

Flights App::get_flights(const AirportID d, const AirportID a)
{
    return *(mgraph->get_arc_info(d, a));
}

static void choose1flight(const vector<Flights> &flights, vector<AirLine> &res, vector<Flight> &stack, int i)
{
    if (i == flights.size())
    {
        res.push_back(AirLine(stack));
        return;
    }
    for (int j = 0; j < flights[i].size(); j ++)
    {
        if (i > 0 && flights[i][j].get_departure_time() < stack[i-1].get_arrival_time())
            continue;
        stack.push_back(flights[i][j]);
        choose1flight(flights, res, stack, i+1);
        stack.pop_back();
    }
}

vector<AirLine> App::flights_to_airlines(const vector<Flights> &flights)
{
    // 求在一条路径（顶点确定，或中转机场确定），所有可能的航线（乘法原理 + 条件判断）
    vector<AirLine> res;
    vector<Flight> stack; // 模拟栈
    choose1flight(flights, res, stack, 0);
    return res;
}

vector<AirLine> App::find_baisc(AirportID departure, AirportID arrival)
{
    // 求两个顶点之间所有符合条件的航线
    vector<vector<AirportID>> all_path = mgraph->find_all_paths(departure, arrival, 3);
    vector<vector<Flights>> all_arcs(all_path.size());
    for (int i = 0; i < all_path.size(); i++)
    {
        for (int j = 0; j < all_path[i].size() - 1; j++)
            all_arcs[i].push_back(get_flights(all_path[i][j], all_path[i][j + 1]));
        all_arcs[i].shrink_to_fit();
    }
    vector<AirLine> res;
    for (int i = 0; i < all_arcs.size(); i++)
    {
        vector<AirLine> tmp = flights_to_airlines(all_arcs[i]);
        for (int j = 0; j < tmp.size(); j++)
            res.push_back(tmp[j]);
    }
    res.shrink_to_fit();

    return res;
}

vector<AirLine> App::find_by_departure_time(vector<AirLine> airlines, Datetime start, Datetime end)
{
    vector<AirLine> res;
    for (int i = 0; i < airlines.size(); i++)
        if (airlines[i].get_departure_time() >= start && airlines[i].get_departure_time() <= end)
            res.push_back(airlines[i]);
    return res;
}

vector<AirLine> App::find_by_departure_time(AirportID departure, AirportID arrival, Datetime start, Datetime end)
{
    return find_by_departure_time(find_baisc(departure, arrival), start, end);
}

vector<AirLine> App::find_by_arrival_time(vector<AirLine> airlines, Datetime start, Datetime end)
{
    vector<AirLine> res;
    for (int i = 0; i < airlines.size(); i++)
        if (airlines[i].get_arrival_time() >= start && airlines[i].get_arrival_time() <= end)
            res.push_back(airlines[i]);
    return res;
}

vector<AirLine> App::find_by_arrival_time(AirportID departure, AirportID arrival, Datetime start, Datetime end)
{
    return find_by_arrival_time(find_baisc(departure, arrival), start, end);
}

vector<AirLine> App::find_by_flight_type(vector<AirLine> airlines, AirplaneType type)
{
    // TODO: 按机型查找
    vector<AirLine> res;
    return res;
}

vector<AirLine> App::find_by_flight_type(AirportID departure, AirportID arrival, AirplaneType type)
{
    return find_by_flight_type(find_baisc(departure, arrival), type);
}

vector<AirLine> App::find_by_transit_times(vector<AirLine> airlines, int times)
{
    vector<AirLine> res;
    for (int i = 0; i < airlines.size(); i++)
        if (airlines[i].transit_times() <= times)
            res.push_back(airlines[i]);
    return res;
}

vector<AirLine> App::find_by_transit_times(AirportID departure, AirportID arrival, int times)
{
    return find_by_transit_times(find_baisc(departure, arrival), times);
}

vector<AirLine> App::find_by_direct(vector<AirLine> airlines)
{
    return find_by_transit_times(airlines, 0);
}

vector<AirLine> App::find_by_direct(AirportID departure, AirportID arrival)
{
    return find_by_transit_times(find_baisc(departure, arrival), 0);
}

vector<AirLine> App::find_by_airline_time(vector<AirLine> airlines, TimeDelta least, TimeDelta most)
{
    vector<AirLine> res;
    for (int i = 0; i < airlines.size(); i++)
        if (airlines[i].get_airline_time() >= least && airlines[i].get_airline_time() <= most)
            res.push_back(airlines[i]);
    return res;
}

vector<AirLine> App::find_by_airline_time(AirportID departure, AirportID arrival, TimeDelta least, TimeDelta most)
{
    return find_by_airline_time(find_baisc(departure, arrival), least, most);
}

vector<AirLine> App::find_by_fare(vector<AirLine> airlines, int least, int most)
{
    vector<AirLine> res;
    for (int i = 0; i < airlines.size(); i++)
        if (airlines[i].get_fares() >= least && airlines[i].get_fares() <= most)
            res.push_back(airlines[i]);
    return res;
}

vector<AirLine> App::find_by_fare(AirportID departure, AirportID arrival, int least, int most)
{
    return find_by_fare(find_baisc(departure, arrival), least, most);
}
