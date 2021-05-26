#ifndef CITY_HPP
#define CITY_HPP

#include <exception>
#include <iostream>
#include <string>

#include "graph_utils.hpp"

/**
 * @brief Define a City.
 */
struct City
{
    std::string name;
    float latitude;
    float longitude;

    City(const std::string& name_="", float latitude_=0.0f, float longitude_=0.0f)
        : name(name_), latitude(latitude_), longitude(longitude_)
    {}
    bool operator<(const City& o) const
    {
        return name < o.name;
    }
    bool operator==(const City& o) const
    {
        return name == o.name;
    }
};



/**
 * @brief Compute the the distance between two cities given their locations.
 */
double distance(const City& s, const City& d);

/**
 * @brief unfold a city from an input stream.
 */
std::istream& operator>>(std::istream& in, City& c);

/**
 * @brief fold a City to an output stream.
 */
std::ostream& operator<<(std::ostream& out, City const& c);

/**
 * @brief Create a City graph from txt representation.
 * Template specialization to save space.
 * For the edges only the name of the City is used.
 *
 * Input Format:
 *
 * [DIRECTED|NON_DIRECTED]
 * <NUM-CITIES>
 * CITY_1.NAME CITY_1.LATITUDE CITY_1.LONGITUDE
 * ... 
 * <NUM-EDGES>
 * <CITI_U.NAME> <CITY_V.NAME> <DISTANCE>
 * ...
 * @arg[in,out] in is the input stream.
 * @return a reference to the graph or nullptr if input error.
 * @warning std::runtime_error("Wrong graph") is throw if bad input format.
 */
template<>
std::shared_ptr<WGraph<City>> create_wgraph(std::istream &in) noexcept(false);


#endif // CITY_HPP
