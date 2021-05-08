#ifndef IP_UTILS_HPP
#define IP_UTILS_HPP

#include <cstdint>
#include <valarray>
#include <iostream>
#include <sstream>
#include <string>

/**
 * @brief Represent a IPv4 address.
 */
struct IP
{
    /**
     * @brief Default constructor.
     */
    IP():
        bytes(4)
    {}
    /**
     * @brief Constructor.
     */
    IP(uint8_t a, uint8_t b, uint8_t c, uint8_t d):
        bytes(4)
    {
        bytes[0]=a;
        bytes[1]=b;
        bytes[2]=c;
        bytes[3]=d;
    }

    /**
     * @brief Is b ip address b equal to this?.
     */
    bool operator == (IP const& b) const
    {
        bool equals = bytes[0] == b.bytes[0];
        for (size_t i= 1; i<4 && equals; ++i )
        {
            equals = bytes[i]==b.bytes[i];
        }
        return equals;
    }

    /**
     * @brief Is b ip address b less than this?
     * A lexicographical order is check.
     */
    bool operator < (IP const& b) const
    {
        bool less = bytes[0] < b.bytes[0];
        bool equal = bytes[0] == b.bytes[0];
        for (size_t i=1 ;i<4 && equal; ++i )
        {
            less = bytes[i] < b.bytes[i];
            equal = bytes[i] == b.bytes[i];
        }
        return less;
    }

    /**
     * The ip bytes so 150.214.110.3 are
     * bytes[0]=150, bytes[1]=214, bytes[2]=110, bytes[3]=4
     */
    std::valarray<uint8_t> bytes;
};


/**
 * @brief Functional class to convert a ipaddress into a uint64_t.
 */
class IpToInt
{
public:
    /**
     * @brief Transform IPv4 addresses into uint64_t.
     * i.e. 150.214.117.3 -> 150*2^24+214*2^16+2^8*117+3
     * @return The corresponding uint64_t.
     */
    uint64_t operator() (const IP& ip) const
    {
        return (static_cast<uint64_t>(ip.bytes[0])<<24) +
                (static_cast<uint64_t>(ip.bytes[1])<<16) +
                (static_cast<uint64_t>(ip.bytes[2])<<8) +
                (static_cast<uint64_t>(ip.bytes[3]));
    }
};

/**
 * @brief output a ip in text format.
 */
inline std::ostream&
operator<< (std::ostream& out, const IP& ip)
{
    out << static_cast<int>(ip.bytes[0]) << '.' <<
           static_cast<int>(ip.bytes[1]) << '.' <<
           static_cast<int>(ip.bytes[2]) << '.' <<
           static_cast<int>(ip.bytes[3]);
    return out;
}

/**
 * @brief load an IPv4 address from a text input stream.
 */
inline std::istream&
operator>>(std::istream& in, IP& ip)
{
    std::string text_ip;
    in >> text_ip;
    if (in)
    {
        for(size_t i=0;i<text_ip.size();++i)
            if (text_ip[i]=='.')
                text_ip[i]=' ';
        std::istringstream in_(text_ip);
        int v[4];
        in_ >> v[0] >> v[1] >> v[2] >> v[3];
        if (in_)
        {
            ip.bytes[0] = static_cast<uint8_t>(v[0]);
            ip.bytes[1] = static_cast<uint8_t>(v[1]);
            ip.bytes[2] = static_cast<uint8_t>(v[2]);
            ip.bytes[3] = static_cast<uint8_t>(v[3]);
        }
    }
    return in;
}

#endif // IP_UTILS_HPP
