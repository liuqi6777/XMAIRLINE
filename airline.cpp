#include "airline.h"
#include <assert.h>

Flight::Flight(const Flight &other)
{
    *this = other;
}

int Flight::ID() const
{
    return this->id;
}

AirportID Flight::get_departure_airport() const
{
    return this->departure_airport;
}

AirportID Flight::get_arrival_airport() const
{
    return this->arrival_airport;
}

Datetime Flight::get_departure_time() const
{
    return this->departure_time;
}

Datetime Flight::get_arrival_time() const
{
    return this->arrival_time;
}

FlightType Flight::get_flight_type() const
{
    return this->flight_type;
}

AirplaneType Flight::get_airplane_type() const
{
    return this->airplane_type;
}

TimeDelta Flight::get_flight_time()
{
    return arrival_time - departure_time;
}

int Flight::get_fares() const
{
    return this->fares;
}

Flight &Flight::operator=(const Flight &other)
{
    id = other.id;
    departure_airport = other.departure_airport;
    arrival_airport = other.arrival_airport;
    flight_type = other.flight_type;
    airplane_type = other.airplane_type;
    departure_time = other.departure_time;
    arrival_time = other.arrival_time;
    fares = other.fares;
    return *this;
}

ostream &operator<<(ostream &os, const Flight &flight)
{
    os << "----------------------------------------" << endl
       << "|             Flight's INFO             " << endl
       << "|---------------------------------------" << endl
       << "|                ID : " << flight.id<< endl
       << "| Departure Airport : " << flight.departure_airport  << endl
       << "| Arrival   Airport : " << flight.arrival_airport << endl
       << "| Departure    Time : " << flight.departure_time << endl
       << "| Arrival      Time : " << flight.arrival_time << endl
       << "|             Fares : " << flight.fares << endl
       << "----------------------------------------" << endl;
    return os;
}


AirLine::AirLine(vector<Flight> &flights)
{
    this->flights = flights;
    if (flights.size())
        this->airport_num = flights.size() + 1;
    else
        this->airport_num = 0;
}

AirLine::~AirLine()
{
}

vector<int> AirLine::get_ids()
{
    int flights_num = flights.size();
    vector<int> ids(flights_num);
    for (int i = 0; i != flights_num; ++i)
        ids[i] = flights[i].ID();
    return ids;
}

AirportID AirLine::get_departure_airport()
{
    return flights.begin()->get_departure_airport();
}

AirportID AirLine::get_arrival_airport()
{
    return (flights.end() - 1)->get_arrival_airport();
}

Datetime AirLine::get_departure_time()
{
    return flights.begin()->get_departure_time();
}

Datetime AirLine::get_arrival_time()
{
    return (flights.end() - 1)->get_arrival_time();
}

TimeDelta AirLine::get_airline_time()
{
    return get_arrival_time() - get_departure_time();
}

int AirLine::transit_times()
{
    return flights.size() - 1;
}

int AirLine::get_fares()
{
    int sum = 0;
    for (vector<Flight>::iterator iter = flights.begin(); iter != flights.end(); ++iter)
        sum += iter->get_fares();
    return sum;
}

ostream &operator<<(ostream &os, AirLine &airline)
{
    os << "----------------------------------------" << endl
       << "|             Airline's INFO            " << endl
       << "|---------------------------------------" << endl;
    os << "| " << airline.get_departure_airport();
    for (int i = 0; i < airline.flights.size(); i++)
        os << " => " << airline.flights[i].get_arrival_airport();
    os << endl << "|";
    for (int i = 0; i < airline.flights.size(); i++)
        os << "    " << airline.flights[i].ID();
    os << endl;
    os << "|---------------------------------------" << endl
       << "| Departure Airport : " << airline.get_departure_airport()  << endl
       << "| Arrival   Airport : " << airline.get_arrival_airport() << endl
       << "| Departure    Time : " << airline.get_departure_time() << endl
       << "| Arrival      Time : " << airline.get_arrival_time() << endl
       << "| Airline      Time : " << airline.get_airline_time() << endl
       << "|             Fares : " << airline.get_fares() << endl
       << "----------------------------------------" << endl;
    return os;
}
