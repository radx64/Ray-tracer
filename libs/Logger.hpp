#ifndef LOGGER_HPP_
#define LOGGER_HPP_

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

#include <libs/Color.hpp>

class Flusher
{
public:
    Flusher(std::string prefix) : prefix_{prefix}
    {
        time_ = getTime();
    }

    Flusher(Flusher&& f)
    {

    }

    ~Flusher()
    {
        using namespace terminal;
        std::cout << time_ << " - [" << prefix_ <<"] "<< buffer_.str() << Color(FG_DEFAULT)<< std::endl;
    }

    template <typename T>
    Flusher& operator<< (const T& element)
    {

        buffer_ << element;
        return *this;
    }

private:
    std::string getTime()
    {
        using namespace terminal;
        std::stringstream ss;
        std::time_t t = time(0);
        std::tm* localtime = std::localtime(&t);

        ss  << std::setw(2) << std::setfill('0') << localtime->tm_hour 
            << ":" << std::setw(2) << std::setfill('0') << localtime->tm_min 
            << ":" << std::setw(2) << std::setfill('0') << localtime->tm_sec;

        return ss.str();
    }

    std::string prefix_;
    std::string time_;
    std::stringstream buffer_;

};


class Logger
{
public:
    Logger(std::string prefix) : prefix_{prefix}
    {

    }

    Flusher dbg()
    {
        return Flusher(prefix_+"/"+terminal::Color(terminal::FG_CYAN).get()+"DBG"+terminal::Color(terminal::FG_DEFAULT).get());
    }

    Flusher wrn()
    {
        return Flusher(prefix_+"/"+terminal::Color(terminal::FG_LIGHT_BLUE).get()+"WRN"+terminal::Color(terminal::FG_DEFAULT).get());
    }

    Flusher err()
    {
        return Flusher(prefix_+"/"+terminal::Color(terminal::FG_LIGHT_RED).get()+"ERR"+terminal::Color(terminal::FG_DEFAULT).get());
    }

    Flusher inf()
    {
        return Flusher(prefix_+"/"+terminal::Color(terminal::FG_LIGHT_GREEN).get()+"INF"+terminal::Color(terminal::FG_DEFAULT).get());
    }


private:
    std::string prefix_;

};


#endif  // LOGGER_HPP_