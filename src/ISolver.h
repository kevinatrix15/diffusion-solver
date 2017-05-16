/**
 * @file ISolver.h
 * @brief Interface class for solvers.
 * @author Kevin Briggs <kevin.briggs@3dsim.com>
 * Copyright 2017, Kevin Briggs
 * @version 1
 * @date 2017-05-03
 */

#pragma once

#include "Types.h"


namespace DIFFSOLVER
{
class ISolver
{
  public:
  virtual ~ISolver()
  {
    // do nothing
  }

  virtual void solve(const std::vector<real_type>& volSource,
    const std::vector<real_type>& faceSource,
    const std::vector<real_type>& Tn,
    const std::vector<real_type>& Tnm1,
    std::vector<real_type>& Tnp1Ref) = 0;

  virtual void setICs(std::vector<real_type>& TnRef) = 0;

  virtual void setBCs(std::vector<real_type>& TnRef) = 0;

  virtual real_type getSolveTime() = 0;
  // TODO: change this to return a timer object

  private:
}
} // namespace DIFFSOLVER
