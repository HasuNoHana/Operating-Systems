/*
	Author: Tomasz Jordan Kruk
	http://www.ia.pw.edu.pl/~tkruk/
*/

#ifndef __monitor_h
#define __monitor_h

#include <stdio.h> 
#include <stdlib.h> 

#ifdef _WIN32
#include <windows.h>
#else
#include <sys/types.h> 
#include <sys/stat.h> 
#include <string.h> 
#include <errno.h> 
#include <fcntl.h> 
#include <pthread.h> 
#include <unistd.h>
#include <semaphore.h>

#endif

// semaphore wrapped into class
class Semaphore
{
public:

  Semaphore( int value )
  {
#ifdef _WIN32
	sem = CreateSemaphore( NULL, value, 1, NULL );
#else
	// check if semaphore was initalized sucessfuly
     if( sem_init( & sem, 0, value ) != 0 )
       throw "sem_init: failed";
#endif
  }
  ~Semaphore()
  { 
#ifdef _WIN32
	CloseHandle( sem );
#else
	  sem_destroy( & sem ); 
#endif
  }

  void p()
  {
#ifdef _WIN32
	  WaitForSingleObject( sem, INFINITE );
#else
	// check if sem_wait was execetued sucessfuly
     if( sem_wait( & sem ) != 0 )
       throw "sem_wait: failed";
#endif
  }

  void v()
  {
#ifdef _WIN32
	  ReleaseSemaphore( sem, 1, NULL );
#else
	// check if sem_post was execetued sucessfuly
     if( sem_post( & sem ) != 0 )
       throw "sem_post: failed";
#endif
  }
  

private:

#ifdef _WIN32
	HANDLE sem;
#else
	sem_t sem;
#endif
};

// conditon class for suspending process on certain conditon
class Condition
{
  friend class Monitor;

public:
	Condition() : w( 0 )
	{
		waitingCount = 0;
	}

	// suspend on certain condtion
	void wait()
	{
		w.p();
	}

	// resuming suspended processes
	bool signal()
	{
		if( waitingCount )
		{
			-- waitingCount;
			w.v();
			return true;
		}//if
		else
			return false;
	}

private:
	Semaphore w;
	int waitingCount; //liczba oczekujacych watkow
};


class Monitor
{
public:
	Monitor() : s( 1 ) {}
	// called at the beginning of each monitor's method
	void enter()
	{
		s.p();
	}
	// called at the end of each monitor's method
	void leave()
	{
		s.v();
	}
	// suspension on condition cond
	void wait( Condition & cond )
	{
		++ cond.waitingCount;
		leave();
		cond.wait();
	}
	// resuming suspended processes
	void signal( Condition & cond )
	{
		if( cond.signal() )
			enter();
	}


private:
	Semaphore s;
};

#endif

