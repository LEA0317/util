#include <iostream>
#include "util.h"


int
main(int argc, char **argv) {
  /*util::Timer t(util::MODE::NANO);
  t.start();
  t.end();
  t.print();
  std::cout << t.get_diff() << std::endl;*/

  util::Perf p;
  p.start();
  sleep(10);
  p.end();
  
  return 0;
}
