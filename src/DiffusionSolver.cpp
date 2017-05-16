/**
 * @file DiffusionSolver.cpp
 * @brief Primary calling code for the thermal diffusion solver.
 * @author Kevin Briggs <kevin.briggs@3dsim.com>
 * Copyright 2017, Kevin Briggs
 * @version 1
 * @date 2017-05-03
 */

#include "ISolver.h"
#include "RunConfiguration.h"
#include "Uniform3DMesh.h"

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
  const ISolver& solver = config.getSolver();
  // TODO: ensure solver has been set

  // get mesh info
  const Uniform3DMesh mesh = config.getMesh();

  // allocate persistent data structures
  std::vector<real_type> Tn(mesh.getNumNodes());
  std::vector<real_type> Tnp1(mesh.getNumNodes());

  std::vector<real_type> volSource(mesh.getNumNodes());
  std::vector<real_type> faceSource((mesh.getNumNodesX()+1) *
      (mesh.getNumNodesY()+1) *
      (mesh.getNumNodesZ()+1));

  // set initial / boundary conditions
  solver.setBCs(Tn);
  std::vector<real_type> Tnm1(Tn);

  // time loop
  const size_t numSteps = config.getNumTimeSteps();
  for (size_t t = 0; t < numSteps; ++t) {

    // update mesh (if applicable)

    // update input flux

    // solve for new time step
    solver.solve(volSource, faceSource, Tn, Tnm1, Tnp1);

    // reset boundary conditions
    solver.setBCs(Tnp1);

    // copy for next time step
    Tnm1 = Tn;
    Tn = Tnp1;

  }
}

} // namespace DIFFSOLVER
