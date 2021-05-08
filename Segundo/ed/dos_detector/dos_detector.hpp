#ifndef DOS_DETECTOR_HPP
#define DOS_DETECTOR_HPP

#include <cstdlib>
#include <utility>
#include <vector>
#include "ip_utils.hpp"
#include "hash_table.hpp"

/**
 * @brief A log's entry.
 */
struct LogEntry
{
    /** @brief constructor */
    LogEntry(size_t time_=0, const IP& ip_=IP())
        : time(time_), ip(ip_)
    {}
    size_t time; /** arrival time*/
    IP ip; /** ip address from the access is.*/
};

/** @brief The system's log. */
typedef std::vector<LogEntry> Log;

/**
 * @brief Run the DOS dectection algorithm.
 * @arg log is the system's log.
 * @arg max_acc is the number max of accesses per hour allowed.
 * @arg m is the initial size of the hash table.
*/
void dos_detector(Log &log, int max_acc, size_t m);

/** @brief This class abstracts several OS's operations.*/
class OS
{
public:

    /** @brief constructor. */
    OS():
        time_(0), kill_(false), banned_ips_(1000)
    {}

    /** @brief Abstracts the time() os call.
     * @see man 3 time
     */
    size_t time ()
    {
        return time_;
    }

    /** @brief Abstracts the sleep() os call.
     * @see man 3 sleep
     */
    size_t sleep (size_t seconds)
    {
        time_ += seconds;
        check_banned_ips(time_);
        if (kill_)
            return seconds;
        else
            return 0;
    }

    /**
     * @brief Add an ip address to the banned ips list.
     */
    void ban_ip(IP const& ip, size_t ban_time)
    {
        std::cout << "Ban ip: " << ip << " at " << time_ << std::endl;
        banned_ips_.insert(ip, time_+ban_time);
    }

    /**
     * @brief Is banned this ip address?
     */
    bool is_banned(IP const& ip)
    {
        return banned_ips_.has(ip);
    }

    /**
     * @brief return a vector with the banned ips.
     */
    std::vector<LogEntry> banned_ips()
    {
        std::vector<LogEntry> ips;
        banned_ips_.goto_begin();
        while(banned_ips_.is_valid())
        {
            ips.push_back(LogEntry(banned_ips_.get_value(),
                                   banned_ips_.get_key()));
            banned_ips_.goto_next();
        }
        return ips;
    }

    /** @brief abstract the kill of the process. */
    void kill()
    {
        kill_=true;
    }

    /**
     * @brief Check if the banned time is met for the banned ips
     * @arg now is the current system time.
     */
    void check_banned_ips(size_t now);

protected:
    size_t time_;
    bool kill_;
    HashTable <IP, size_t, IpToInt> banned_ips_;
};

/** @brief Return a reference to a singleton that references the abstracted operating system to use into the code.*/
OS& System();

#endif // DOS_DETECTOR_HPP
