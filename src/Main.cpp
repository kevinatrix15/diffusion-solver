/**
 * @file Main.cpp
 * @brief File containing the main function for calling the diffusion solver.
 * @author Kevin Briggs <kevin.briggs@3dsim.com>
 * Copyright 2017, Kevin Briggs
 * @version 1
 * @date 2017-05-03
 */

#include <iostream>

using namespace DIFFSOLVER;

/******************************************************************************
* MAIN ************************************************************************
******************************************************************************/

int main(int argc, char **argv)
{
  // unpack command line args
  const std::string fileA = argv[1];
  const std::string fileX = argv[2];
  const std::string fileY = argv[3];
  // const MatrixMode mode = static_cast<MatrixMode>(std::atoi(argv[4]));

  // display command line args
  std::cout << "\nCommand Line Arguments:\n";
  for (int arg = 0; arg < argc; ++arg) {
    std::cout << "  argv[" << arg << "]   " << argv[arg] << "\n";
  }

  // preprocessing
  // * read and store inputs
  // * perform meshing (if applicable)

  // run solver

  // post processing

  return 0;
}
