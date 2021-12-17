#include "graph.h"
#include "airline.h"
#include "datetime.h"
#include "datautils.h"

class App
{
public:
    App() : mgraph(NULL), algraph(NULL), detail(false), diff(false), max_len(MAX_TRANSIT_TIMES), departure(-1), arrival(-1) {}

    void load_mgraph(MGraph<AirportID, Flights *> *data);
    void load_algraph(ALGraph<AirportID, Flights *> *data);

    void set_detail(bool d) { this->detail = d; }
    void set_diff(bool d) { this->diff = d; }

    void set_departure_arrival(int d = -1, int a = -1)
    {
        this->departure = d;
        this->arrival = a;
    }

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

    void sort_by_fare(vector<AirLine> &airlines);         // 按费用排序
    void sort_by_airline_time(vector<AirLine> &airlines); // 按飞行时间（含转机时间）排序

    AirLine find_min_by_fare(vector<AirLine> &airlines);
    AirLine find_min_by_airline_time(vector<AirLine> &airlines);

    void run();

private:
    MGraph<AirportID, Flights *> *mgraph;
    ALGraph<AirportID, Flights *> *algraph;

    int departure, arrival;
    int max_len;
    bool detail; //输出详细信息
    bool diff;   // 同一条路线是否输出不同时间

    vector<vector<AirportID>> get_all_routes(const AirportID d, const AirportID a);
    Flights get_flights(const AirportID d, const AirportID a);
    vector<AirLine> flights_to_airlines(const vector<Flights> &flights);

    vector<AirLine> find_baisc(AirportID departure, AirportID arrival);
    void sort_basic(vector<AirLine> &airlines, bool (*cmp)(AirLine &, AirLine &)); // std::sort()

    AirLine find_min(vector<AirLine> &airlines, bool (*cmp)(AirLine &, AirLine &));
};

void App::run()
{
    assert(mgraph != NULL);
    assert(algraph != NULL);

    std::cout << "\nHello, world!\n\n";

    cout << "Please input departure airport id and arrival airport id:" << endl;
    if (departure == -1 && arrival == -1)
        cin >> departure >> arrival;

    vector<vector<AirportID>> routes = get_all_routes(departure, arrival);
    cout << "Follow are all possible route(s) (only routes with fewer than " << max_len - 2
         << " transfers are included):" << endl;
    cout << "(" << routes.size() << " in total)" << endl;
    for (int i = 0; i < routes.size(); i++)
    {
        for (int j = 0; j < routes[i].size() - 1; j++)
            cout << routes[i][j] << " => ";
        cout << routes[i][routes[i].size() - 1] << endl;
    }
    vector<AirLine> first_results = find_baisc(departure, arrival);

    // cout << "You can give some limits:\n"
    //         "Input 0 means no limits\n"
    //         "      1 to set the range of departure times;\n"
    //         "      2 to set the range of arrival times;\n"
    //         "      3 to choose airplane type;\n"
    //         "      4 to set the range of transit times (0 means direct);\n"
    //         "      5 to set the range of the flight time (including transit time);\n"
    //         "      6 to set the range of fares;\n";

    int m = 1;

    vector<AirLine> res = first_results;
    while (m > 0 && m <= 6)
    {
        cout << "You can give some limits:\n"
            "Input 0 means no limits\n"
            "      1 to set the range of departure times;\n"
            "      2 to set the range of arrival times;\n"
            "      3 to choose airplane type;\n"
            "      4 to set the range of transit times (0 means direct);\n"
            "      5 to set the range of the flight time (including transit time);\n"
            "      6 to set the range of fares;\n";
        cin >> m;
        assert(getchar() == '\n');
        if (m == 0)
        {
            // cout << "(" << first_results.size() << " possible airlines in total)" << endl;
            // for (int i = 0; i < first_results.size(); i++)
            //     cout << "[AIRLINE " << i + 1 << "]" << endl
            //          << first_results[i];
        }
        else if (m == 1)
        {
            string datetime;
            cout << "Please input starting time(format: month/day/year hour:minute): ";
            getline(cin, datetime);
            Datetime start(datetime);
            cout << "Please input ending time: ";
            getline(cin, datetime);
            Datetime end(datetime);
            res = find_by_departure_time(res, start, end);
        }
        else if (m == 2)
        {
            string datetime;
            cout << "Please input starting time(format: month/day/year hour:minute): ";
            getline(cin, datetime);
            Datetime start(datetime);
            cout << "Please input ending time: ";
            getline(cin, datetime);
            Datetime end(datetime);
            res = find_by_arrival_time(res, start, end);
        }
        else if (m == 3)
        {
        }
        else if (m == 4)
        {
            int times = 0;
            cout << "Please input the max num of transit times (0 means direct): ";
            cin >> times;
            res = find_by_transit_times(res, times);
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
            res = find_by_airline_time(res, least, most);
        }
        else if (m == 6)
        {
            int least, most;
            cout << "Please input the min fares: ";
            cin >> least;
            cout << "Please input the max fares: ";
            cin >> most;
            res = find_by_fare(res, least, most);
        }
        else
        {
            cout << "Please input a number between 1 and 6!\n";
            return;
        }
    }

    cout << "You can sort the results by different rules: \n"
            "Input 0 means no sort; \n"
            "      1 to sort by fares;\n"
            "      2 to sort by airline time;\n";
    int s = 0;
    cin >> s;

    if (s == 1)
        sort_by_fare(res);
    else if (s == 2)
        sort_by_airline_time(res);

    int n = 10;
    cout << "Please input a number to determine the number of output routes (if not all output):";
    cin >> n;
    n = n < res.size() ? n : res.size();

    cout << "Follow are all airlines found:" << endl
         << "(" << n << " in total)\n";
    for (int i = 0; i < n; i++)
        cout << "[AIRLINE " << i + 1 << "]" << endl
             << res[i];
}

void App::load_mgraph(MGraph<AirportID, Flights *> *data)
{
    this->mgraph = data;
}

void App::load_algraph(ALGraph<AirportID, Flights *> *data)
{
    this->algraph = data;
}

vector<vector<AirportID>> App::get_all_routes(const AirportID d, const AirportID a)
{
    return mgraph->find_all_paths(d, a, max_len);
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
    for (int j = 0; j < flights[i].size(); j++)
    {
        if (i > 0 && flights[i][j].get_departure_time() < stack[i - 1].get_arrival_time())
            continue;
        stack.push_back(flights[i][j]);
        choose1flight(flights, res, stack, i + 1);
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
    vector<vector<AirportID>> all_path = get_all_routes(departure, arrival);
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

void App::sort_basic(vector<AirLine> &airlines, bool (*cmp)(AirLine &, AirLine &))
{
    std::sort(airlines.begin(), airlines.end(), cmp);
}

static bool cmp_by_fare(AirLine &a1, AirLine &a2)
{
    return a1.get_fares() < a2.get_fares();
}

static bool cmp_by_airline_time(AirLine &a1, AirLine &a2)
{
    return a1.get_airline_time() < a2.get_airline_time();
}

void App::sort_by_fare(vector<AirLine> &airlines)
{
    sort_basic(airlines, cmp_by_fare);
}

void App::sort_by_airline_time(vector<AirLine> &airlines)
{
    sort_basic(airlines, cmp_by_airline_time);
}
