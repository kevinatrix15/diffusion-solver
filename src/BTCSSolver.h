/**
 * @file BTCSSolver.h
 * @brief A class for solving the diffusion solver using a backward in time,
 * centered in space explicit solution scheme.
 * @author Kevin Briggs <kevin.briggs@3dsim.com>
 * Copyright 2017, Kevin Briggs
 * @version 1
 * @date 2017-05-10
 */

#pragma once

#include "Types.h"

namespace DIFFSOLVER
{
class BTCSSolver : public ISolver
{
  public:

  BTCSSolver(const Uniform3DMesh& mesh, const real_type dt);

  virtual ~BTCSSolver();

  void solve(const std::vector<real_type>& volSource,
    const std::vector<real_type>& faceSource,
    const std::vector<real_type>& Tn,
    const std::vector<real_type>& Tnm1,
    std::vector<real_type>& Tnp1Ref) override;

  void setICs(std::vector<real_type>& TnRef) override;

  void setBCs(std::vector<real_type>& TnRef) override;

  real_type getSolveTime() override;

  private:

  Uniform3DMesh m_mesh;
  const real_type m_dt;
  const real_type m_heaterTemp;

};
} // namespace DIFFSOLVER
