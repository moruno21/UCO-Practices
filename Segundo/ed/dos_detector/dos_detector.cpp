#include "dos_detector.hpp"
#include "hash_table.hpp"

/** @brief return a reference to the abstracted operating system to use into the code.*/
OS& System()
{
    static std::shared_ptr<OS> system_;
    if (!system_)
        system_=std::make_shared<OS>();
    return *system_;
}

void OS::check_banned_ips(size_t now)
{
    //For each valid entry of banned ips table,
    //check if the banned time is met now and then the entry must be removed.
    banned_ips_.goto_begin();
    while(banned_ips_.is_valid())
    {
        if (banned_ips_.get_value()<now)
            banned_ips_.remove(); //remove and advance the cursor.
        else
            banned_ips_.goto_next();
    }
}

/** @brief Each second, this algorithm scan log to see if some address must be banned.
 * @arg log is the system's log.
 * @arg i is the first not processed line in log.
 * @arg j is the last old line out of the temporal processing windown.
 * @pre j<=i<log.size()
*/
static void
update_counters(Log& log, size_t &i, size_t& j,
                HashTable<IP,int, IpToInt>& counters,
                int max_acc)
{
//    Algorithm updateCounters(
//      log:Log,
//      Var i:Integer,
//      Var j:Integer,
//      Var c:?,
//      maxAcc:Integer)
//    Begin
//      //update new accesses.
//      while log[i].time < system::now() do
//        increment(log[i].ip, c)
//        if nAcc(log[i].ip, c) >= maxAcc then
//          system::banIP(log[i].ip], 60) //ban ip during 60 seconds.
//        end-if
//        i ← i + 1
//      end-while
//      //remove old accesses.
//      while log[j].time+60 < system::now() do //we use 60 seconds window time.
//        decrement(log[j].ip, c)– 1
//        j ← j + 1
//      end-while
//    end.


    // You can use System() to do the os operations.
    // i.e.: System().time() to get the current time.
    //       System().is_banned() to know if a ip is banned at current time.
    //       System().ban_ip() to ban an ip.
    // Remeber that in this simulated case var 'i' can achieves log.size() value.
    while(i < log.size() && (log[i].time < System().time()) )
    {
        if (!System().is_banned(log[i].ip))
        {
          //TODO
          //Process this ip according to the algorithm.



        }
        else
        {
            // This is necessary because this is a simulated system.
            // In an actual system, a banned ip will be blocked by the firewall so
            // this banned ip shouldn't appear in the log at this time.
            // We reset the log entry's ip to 0.0.0.0 to mark this situation for the next step.
            log[i].ip = IP(0,0,0,0);
        }
        ++i;
    }

    //remove old accesses. We use a 60 seconds window time.
    while(j < log.size()  &&  ((log[j].time + 60) < System().time()))
    {
        if (! (log[j].ip == IP(0,0,0,0)) )
        {
            //TODO
            //This ip is not marked as banned at this moment
            //so we update its counter according to the algorithm.
            //To things must be true here.
            // - We can find the ip in the table and
            // - its counter must be >=0 after decrementing.
            //You should check these things to make sure you are doing well the work.
        }
        ++j;
    }
}


void dos_detector(Log& log, int max_acc, size_t m)
{
    size_t i=0;
    size_t j=0;
    HashTable<IP, int, IpToInt> counters(m);

    while(!System().sleep(1))
    {
        update_counters(log, i, j, counters, max_acc);

        if (j==log.size()) //The log is ended.
            System().kill();
    }
}
