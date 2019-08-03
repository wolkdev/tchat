
#include <iostream>
#include <string>
#include <thread>
#include <vector>

void server()
{

}

void client(std::string _ip)
{
    
}

int main(int argc, char const* argv[])
{
    if (argc >= 2)
    {
        std::string arg = std::string(argv[1]);

        if (argc >= 3 && arg == "client")
        {
            std::string ip = std::string(argv[2]);
            client(ip);
        }
        else if (arg == "server")
        {
            server();
        }
    }

    return 0;
}