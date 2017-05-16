/**
 * @file RunConfiguration.cpp
 * @brief Implementation of the RunConfiguration class.
 * @author Kevin Briggs <kevin.briggs@3dsim.com>
 * @version 1
 * @date 2017-05-15
 */

#include "RunConfiguration.h"

namespace DIFFSOLVER
{
/******************************************************************************
* CONSTANTS / DEFAULTS ********************************************************
******************************************************************************/
namespace
{
// defaults
const size_t DEFAULT_NUM_STEPS = 1000;
}


/******************************************************************************
* CONSTRUCTORS / DESTRUCTORS **************************************************
******************************************************************************/
RunConfiguration::RunConfiguration()
  : m_solverPtr(nullptr),
  m_mesh(nullptr),
  m_numTimeSteps(DEFAULT_NUM_STEPS)
{
  // do nothing
}

RunConfiguration::~RunConfiguration()
{
  // do nothing
}


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

ISolver& RunConfiguration::getSolver() const noexcept
{
  // TODO: add checking to ensure all inputs have been finalized
  return *m_solverPtr;
}

Uniform3DMesh& RunConfiguration::getMesh() const noexcept
{
  // TODO: add checking to ensure all inputs have been finalized
  return *m_mesh;
}

// TODO: eventually replace this with scan pattern generator which
// pre-determines number of time steps necessary??
size_t RunConfiguration::getNumTimeSteps() const noexcept
{
  return m_numTimeSteps;
}

} // DIFFSOLVER
