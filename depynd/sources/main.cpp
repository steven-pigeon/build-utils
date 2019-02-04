#include <iostream>
#include <algorithm>
#include <options.hpp>

#include <processor.hpp>
#include <instructions.hpp>
#include <program.hpp>

////////////////////////////////////////
int main(int argc, char * argv[])
 {
  try
   {
    options opt(argc,argv);

    switch (first_of({ opt.help,
                       opt.version
                      }))
     {
      case 0: options::show_help(); break;
      case 1: options::show_version(); break;

      default:
       // machin

       std::cout
        << "processor::nb_registers=" << processor::nb_registers << std::endl
        << "bits=" << processor::register_bits << std::endl
        << sizeof (processor) << std::endl
        ;
       break;
     }

   }

  catch (boost::program_options::error & this_exception)
   {
    std::cerr << this_exception.what() << std::endl;
    return 1;
   }
  return 0;
 }
