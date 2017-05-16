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
  // TODO: implement configuration class
  const ISolver& solver = m_config.getSolver();

  // get mesh info
  const Uniform3DMesh mesh = m_config.getMesh();

  // allocate persistent data structures
  std::vector<real_type> Tn(mesh.getNumNodes());
  std::vector<real_type> Tnm1(mesh.getNumNodes());
  std::vector<real_type> Tnp1(mesh.getNumNodes());
  std::vector<real_type> volSource(mesh.getNumNodes());
  std::vector<real_type> faceSource((mesh.getNumNodesX()+1) *
      (mesh.getNumNodesY()+1) *
      (mesh.getNumNodesZ()+1));

  // set initial conditions

  // time loop
  for (index_type t = 0; t < m_config.getNumTimeSteps(); ++t) {

    // update mesh (if applicable)

    // update input flux

    // reset boundary conditions

    // solve for new time step
    solver.solve(volSource, faceSource, Tn, Tnm1, Tnp1);

  }
}

} // namespace DIFFSOLVER
