/**
 * @file DiffusionSolver.cpp
 * @brief Primary calling code for the thermal diffusion solver.
 * @author Kevin Briggs <kevin.briggs@3dsim.com>
 * Copyright 2017, Kevin Briggs
 * @version 1
 * @date 2017-05-03
 */

#include "ISolver.h"

namespace DIFFSOLVER
{

/******************************************************************************
* CONSTRUCTORS / DESTRUCTORS **************************************************
******************************************************************************/

DifffusionSolver::DiffusionSolver()
{
  // do nothing
}

DifffusionSolver::~DiffusionSolver()
{
  // do nothing
}

/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

DiffusionSolver::solve()
{
  // unpack inputs
  const ISolver& solver = m_config.getSolver();

  // get mesh info

  // declare persistent data structures
  std::vector<real_type> Tn;
  std::vector<real_type> Tnm1;
  std::vector<real_type> Tnp1;

  // set initial conditions

  // time loop
  for (index_type t = 0; t < m_config.getNumTimeSteps(); ++t) {

    // update mesh (if applicable)

    // reset boundary conditions

    // solve for new time step
    solver.solve();

  }
}

} // namespace DIFFSOLVER
