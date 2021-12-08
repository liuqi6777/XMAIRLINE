#ifndef DATA_UTILS_
#define DATA_UTILS_

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <assert.h>

#include "airline.h"

using namespace std;

void split(const string &s, vector<string> &tokens, const string &delimiters = " ")
{
    string::size_type lastPos = s.find_first_not_of(delimiters, 0);
    string::size_type pos = s.find_first_of(delimiters, lastPos);
    while (string::npos != pos || string::npos != lastPos)
    {
        tokens.push_back(s.substr(lastPos, pos - lastPos));
        lastPos = s.find_first_not_of(delimiters, pos);
        pos = s.find_first_of(delimiters, lastPos);
    }
}

Flight &get_flight(ifstream &ifs)
{
    string str;
    getline(ifs, str);
    stringstream ss(str);

    // str format:
    // Flight ID, Departure date, Intl/Dome, Flight NO., Departure airport, Arrival airport,
    // Departure Time, Arrival Time, Airplane ID, Airplane Model, Air fares

    vector<string> infos;
    split(str, infos, ",");
    assert(infos.size() == 11);

    int id = stoi(infos[0]);
    AirportID dairport = stoi(infos[4]);
    AirportID aairport = stoi(infos[5]);
    FlightType ftype = infos[2] == "Dome" ? Dome : Intl;
    AirplaneType atype = stoi(infos[9]) == 1 ? type1 : (stoi(infos[9]) == 2) ? type2
                                                                             : type3;
    Datetime dtime(infos[6]);
    Datetime atime(infos[7]);
    int fares(stoi(infos[10]));

    return Flight(id, dairport, aairport, ftype, atype, dtime, atime, fares);
}

vector<Flight> &get_flights(ifstream &ifs)
{
    string head;
    getline(ifs, head);

    vector<Flight> flights;
    while (!ifs.eof())
        flights.push_back(get_flight(ifs));

    flights.shrink_to_fit();
    return flights;
}

void read_data(string path, vector<Flight> &flights)
{
    ifstream ifs(path, fstream::in);
    if (!ifs.is_open())
        cout << "failed to open " << path << '\n';
    else
    {
        flights = get_flights(ifs);
        ifs.close();
    }
}

#endif