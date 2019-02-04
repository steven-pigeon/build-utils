#ifndef __MODULE_OPTIONS__
#define __MODULE_OPTIONS__

#include <string>
#include <vector>
#include <list>
#include <boost/program_options.hpp> // exceptions also

#include "zig/machin.hpp"

class options
 {
  public:

      bool verbose;
      bool help;
      bool version;

      std::string input;
      std::string output;

      // population parameters
      struct
       {
        size_t size;
       } population;

      // algorithm parameters
      struct
       {
        size_t max_generations;
       } evolution;

      static void show_help();
      static void show_version();

  options()
   : verbose(false),
     help(false),
     version(false),
     population{10000}, // alas,  designators are c++20.
     evolution{100}
  {}

  options(int, const char * const[]);

  ~options()=default;
 };

size_t first_of(const std::list<bool> & l);

#endif
// __MODULE_OPTIONS__
