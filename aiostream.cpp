
#include "aiostream.hpp"
#include <iostream>

#define FIRST_PRINTABLE_CHAR (char)32
#define LAST_PRINTABLE_CHAR (char)126
#define NL_CHAR (char)10
#define ENTER_CHAR (char)13
#define DEL_CHAR (char)127
#define BS_CHAR (char)8
#define QUIT_CHAR (char)3

#ifdef OS_UNIX

#include <termios.h>
#include <unistd.h>

int getch()
{
	int c = 0;

	struct termios old_sett, getch_sett;
	int error = 0;

	  //----- store old settings -----------
	error = tcgetattr(STDIN_FILENO, &old_sett);
	assert(error == 0);

	  //---- set getch terminal parms --------
	getch_sett = old_sett;
	getch_sett.c_lflag &= ~ICANON; // disable buffered io
	getch_sett.c_lflag &= ~ECHO; // disable echo
	error = tcsetattr(STDIN_FILENO, TCSANOW, &getch_sett);
	assert(error == 0);

	c = std::cin.get();

	  //------  restore old settings ---------
	error = tcsetattr(STDIN_FILENO, TCSANOW, &old_sett);
	assert(error == 0);

	return c;
}

#else

#include <conio.h>

int getch()
{
    return _getch();
}

#endif

void erase(unsigned int _n)
{
    unsigned int i;
    for (i = 0; i < _n; i++)
        std::cout << BS_CHAR << " " << BS_CHAR;
}

void aiostream::operator<<(const std::string& _string)
{
    mutex.lock();

    if (reading)
        erase(ibuffer.length());

    std::cout << _string << std::endl;

    if (reading)
        std::cout << ibuffer;

    std::cout.flush();

    mutex.unlock();
}

void aiostream::operator>>(std::string& _string)
{
    char c;

    ibuffer.clear();
    reading = true;

	while(reading)
	{
        c = getch();

        mutex.lock();

        if (c >= FIRST_PRINTABLE_CHAR && c <= LAST_PRINTABLE_CHAR)
		{
			std::cout << c;
			ibuffer.push_back(c);
		}
        else if ((c == BS_CHAR || c == DEL_CHAR) && ibuffer.length() >= 1)
		{
			erase(1);
			ibuffer.erase(ibuffer.length() - 1, 1);
		}
		else if (c == NL_CHAR || c == ENTER_CHAR)
		{
            std::cout << std::endl;
            _string = ibuffer;
            reading = false;
		}
		else if (c == QUIT_CHAR)
		{
			std::cout << std::endl;
			shouldQuit = true;
			reading = false;
		}

        mutex.unlock();
	}
}

bool aiostream::should_quit() const
{
	return shouldQuit;
}