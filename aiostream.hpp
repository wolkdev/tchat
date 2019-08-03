#ifndef AIOSTREAM__HPP
#define AIOSTREAM__HPP

#include <mutex>
#include <atomic>
#include <string>

class aiostream
{
    private:
    std::string ibuffer;
    std::string obuffer;
    std::mutex mutex;
    std::atomic<bool> reading;
    bool shouldQuit = false;

    public:
    void operator<<(const std::string& _string);
    void operator>>(std::string& _string);
    bool should_quit() const;
};

#endif // !AIOSTREAM__HPP