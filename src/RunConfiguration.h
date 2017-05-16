/**
 * @file RunConfiguration.h
 * @brief Class contianing necessary inputs and objects to run the thermal
 * diffusion solver.
 * @author Kevin Briggs <kevin.briggs@3dsim.com>
 * Copyright 2017, Kevin Briggs
 * @version 1
 * @date 2017-05-15
 */

#pragma once

#include "ISolver.h"
#include "Uniform3DMesh.h"

namespace DIFFSOLVER
{
  public:

  RunConfiguration();

  ~RunConfiguration();

  ISolver& getSolver() const noexcept;

  Uniform3DMesh& getMesh() const noexcept;

  // TODO: eventually replace this with scan pattern generator which
  // pre-determines number of time steps necessary??
  size_t getNumTimeSteps() const noexcept;

  // TODO: add setters for parsing and passing in inputs

  private:

  std::unique_ptr<ISolver> m_solverPtr;
  std::unique_ptr<Uniform3DMesh> m_mesh;
  const size_t m_numTimeSteps;
  
} // namespace DIFFSOLVER
