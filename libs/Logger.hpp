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
    Flusher(const std::string prefix);
    Flusher(Flusher&& f);

    template <typename T>
    Flusher& operator<< (const T& element)
    {
        buffer_ << element;
        return *this;
    }

    ~Flusher();

protected:
    Flusher();

private:
    std::string getTime() const;

    const std::string prefix_;
    const std::string time_;
    std::stringstream buffer_;
    bool shouldFlush_;
};

class DisabledFlusher : public Flusher
{
public:
    DisabledFlusher() : Flusher()
    {}

    ~DisabledFlusher() = default;
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
    Logger(const std::string prefix) : prefix_{prefix}
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
    const std::string prefix_;
    static LogLevel level_;

};


#endif  // LOGGER_HPP_