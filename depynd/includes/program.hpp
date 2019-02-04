#ifndef __MODULE_PROGRAM__
#define __MODULE_PROGRAM__

#include <vector>
#include <processor.hpp>
#include <instructions.hpp>

////////////////////////////////////////
//
// Class for maintaining a (very simple)
// program, with its own state. It is not
// as general as might be; just enough
// for what we need
//
class program
 {
  private:

  public:

      processor cpu;
      std::vector<instruction *> instructions;

      // also, not as general as it should be
      // Input is in register 0
      // Output in register 1
      processor::register_type run(const std::string & key)
       {
        cpu.reset();
        for (char k:key)
         {
          cpu.registers[0]=k;
          for (const instruction * i:instructions) (*i)(&cpu);
         }

        return cpu.registers[1];
       }


  program() {}
  program(const program & other)
   : instructions(other.instructions)
  {}
  
  ~program()=default;
 };

#endif
     // __MODULE_PROGRAM__
