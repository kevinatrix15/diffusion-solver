/**
 * @file ISolver.h
 * @brief Interface class for solvers.
 * @author Kevin Briggs <kevin.briggs@3dsim.com>
 * @version 1
 * @date 2017-05-03
 */

#pragma once


namespace DIFFSOLVER
{
class ISolver
{
  public:
  virtual ~ISolver()
  {
    // do nothing
  }

  virtual void solve(const std::vector<real_type>& Tn,
      const std::vector<real_type>& Tnm1,
      std::vector<real_type>& Tnp1Ref) = 0;

  virtual void setICs() = 0;

  virtual void setBCs() = 0;

  virtual real_type getSolveTime() = 0;
  // TODO: change this to return a timer object

  private:
}
} // namespace DIFFSOLVER
