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
        shouldFlush_ = true;
        time_ = getTime();
    }

    Flusher(Flusher&& f){}

    template <typename T>
    Flusher& operator<< (const T& element)
    {
        buffer_ << element;
        return *this;
    }

    ~Flusher()
    {
        if(!shouldFlush_) return;
        using namespace terminal;
        std::cout << time_ << " - [" << prefix_ <<"] "<< buffer_.str() << Color(FG_DEFAULT)<< std::endl;
    }

protected:
    Flusher()
    {
        shouldFlush_ = false;
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
    bool shouldFlush_;
};

class DisabledFlusher : public Flusher
{
public:
    DisabledFlusher() : Flusher()
    {

    }

    ~DisabledFlusher()
    {

    }

};

enum LogLevel
{
    DBG,
    INF,
    ERR,
    WRN
};

class Logger
{
public:
    Logger(std::string prefix) : prefix_{prefix}
    {

    }

    void setLevel(LogLevel level)
    {
        level_ = level;
    }

    Flusher dbg()
    {
        if (level_ != LogLevel::DBG) 
        {
            return DisabledFlusher();
        }
        return Flusher(prefix_+"/"+terminal::Color(terminal::FG_CYAN).get()+"DBG"+terminal::Color(terminal::FG_DEFAULT).get());
    }

    Flusher wrn()
    {
        if (level_ == LogLevel::ERR) 
        {
            return DisabledFlusher();
        }
        return Flusher(prefix_+"/"+terminal::Color(terminal::FG_LIGHT_BLUE).get()+"WRN"+terminal::Color(terminal::FG_DEFAULT).get());
    }

    Flusher err()
    {
        return Flusher(prefix_+"/"+terminal::Color(terminal::FG_RED).get()+"ERR"+terminal::Color(terminal::FG_DEFAULT).get());
    }

    Flusher inf()
    {
        if (level_ == LogLevel::ERR || level_ == LogLevel::WRN) 
        {
            return DisabledFlusher();
        }
        return Flusher(prefix_+"/"+terminal::Color(terminal::FG_GREEN).get()+"INF"+terminal::Color(terminal::FG_DEFAULT).get());
    }

private:
    std::string prefix_;
    static LogLevel level_;

};


#endif  // LOGGER_HPP_