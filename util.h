#ifndef __HEADER_UTIL__
#define __HEADER_UTIL__

#include <chrono>
#include <iostream>
#include <string>
#include <cstdlib>
#include <sys/types.h>
#include <unistd.h>

namespace util {

  enum class MODE {
    NANO,
    MILLI,
    DEFAULT  
  };
  
  class Timer {
  private:
    MODE Mode;
    std::chrono::system_clock::time_point Start, End;

  public:
  Timer(MODE _mode)
    : Mode(_mode) {}

    void start(void) {
      Start = std::chrono::system_clock::now();
    }

    void end(void) {
      End = std::chrono::system_clock::now();
    }
    
    void print(void) {
      double elapsed = get_diff();
      switch(Mode) {
      case MODE::NANO:
	{
	  std::cout << "nano sec" << std::endl;
	  break;
	}
      case MODE::MILLI:
	{
	  std::cout << "milli sec" << std::endl;
	  break;
	}
      default:
	{
	  std::cout << "sec" << std::endl;
	  break;
	}
      }
      std::cout << "    " << elapsed << std::endl;
    }

    double get_diff(void) {
      auto diff = End - Start;
      double elapsed;
      switch(Mode) {
      case MODE::NANO:
	{
	  elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(diff).count();
	  break;
	}
      case MODE::MILLI:
	{
	  elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(diff).count();
	  break;
	}
      default:
	{
	  elapsed = std::chrono::duration_cast<std::chrono::seconds>(diff).count();
	  break;
	}
      }
      return elapsed;
    }
  };

  class Perf {
  public:
    Perf() {}

    void start(void) {
      pid_t pid = getpid();
      std::string perf_stat = "perf stat -p " + std::to_string(pid) + " &";
      std::system(perf_stat.c_str());
      sleep(3);
    }

    void end(void) {
      std::system("pkill --signal 2 perf");
    }
  };
}

#endif
