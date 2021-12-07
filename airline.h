#ifndef AIRLINE
#define AIRLINE

#include <iostream>
#include <string>
#include <vector>

#include "datetime.h"

using namespace std;

const int AIRPORT_NUM = 79;

typedef enum FlightType
{
    Intl,
    Dome
} FlightType;

typedef enum AirplaneType
{
    type1,
    type2,
    type3
} AirplaneType;

typedef int AirportID; // 机场（顶点）

class Flight;
class AirLine;

class Flight // 航班（弧）
{
public:
    Flight(int id, AirportID departure, AirportID arrival, FlightType ft, AirplaneType at, Datetime departure_t, Datetime arrival_time, int fare);
    Flight(Flight &other);
    ~Flight();

    int ID() const;
    AirportID get_departure_airport() const;
    AirportID get_arrival_airport() const;
    Datetime get_departure_time() const;
    Datetime get_arrival_time() const;
    FlightType get_flight_type() const;
    AirplaneType get_airplane_type() const;
    TimeDelta get_flight_time() const;
    int get_fares() const;

    Flight &operator=(const Flight &other);

    friend ostream &operator>>(const ostream &os, const Flight &self);

    friend AirLine;

private:
    int id;
    int no;
    AirportID departure_airport;
    AirportID arrival_airport;
    FlightType airline_type;
    AirplaneType airplane_type;
    Datetime departure_time;
    Datetime arrival_time;
    int fares;
};

class AirLine // 航线（路径）
{
public:
    AirLine(vector<Flight> &flights);
    ~AirLine();

    vector<int> get_ids();
    AirportID get_departure_airport();
    AirportID get_arrival_airport();
    Datetime get_departure_time();
    Datetime get_arrival_time();
    TimeDelta get_airline_time();
    int transit_times();
    int get_fares();

private:
    vector<Flight> flights;
};

#endif