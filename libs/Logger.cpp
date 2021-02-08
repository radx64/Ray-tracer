#include "Logger.hpp"

Flusher::Flusher(const std::string prefix) 
: prefix_{prefix}, time_(getTime())
{
    shouldFlush_ = true;
}

Flusher::Flusher(Flusher&& f){}

Flusher::Flusher()
{
    shouldFlush_ = false;
}

Flusher::~Flusher()
{
    if(!shouldFlush_) return;
    std::cout << time_ << " - [" << prefix_ <<"] "<< buffer_.str() << terminal::Color(terminal::FG_DEFAULT)<< std::endl;
}

std::string Flusher::getTime() const
{
    std::stringstream ss;
    std::time_t t = time(0);
    std::tm* localtime = std::localtime(&t);

    ss  << std::setw(2) << std::setfill('0') << localtime->tm_hour 
        << ":" << std::setw(2) << std::setfill('0') << localtime->tm_min 
        << ":" << std::setw(2) << std::setfill('0') << localtime->tm_sec;

    return ss.str();
}

LogLevel Logger::level_;