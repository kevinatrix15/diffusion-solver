/**
 * @file BTCSSolver.cpp
 * @brief Implementation of the BTCSSolver.
 * @author Kevin Briggs <kevin.briggs@3dsim.com>
 * @version 1
 * @date 2017-05-10
 */

#include "BTCSSolver.h"

namespace DIFFSOLVER
{

/******************************************************************************
* CONSTRUCTORS / DESTRUCTORS **************************************************
******************************************************************************/

BTCSSolver::BTCSSolver(const Uniform3DMesh& mesh, const real_type dt, const
    real_type heaterTemp)
  : m_mesh(mesh),
    m_dt(dt),
    m_heaterTemp(heaterTemp)

{
  // ensure inputs are valid
  assert(m_dt > 0.0);
}

BTCSSolver::~BTCSSolver()
{
  // do nothing
}

/******************************************************************************
* PRIVATE METHODS *************************************************************
******************************************************************************/


/******************************************************************************
* PUBLIC METHODS **************************************************************
******************************************************************************/

void solve(const std::vector<real_type>& volSource,
    const std::vector<real_type>& faceSource,
    const std::vector<real_type>& Tn,
    const std::vector<real_type>& Tnm1,
    std::vector<real_type>& Tnp1Ref) override
{
  // TODO: check inputs for correctness

  // loop over domain in row-major order
  const size_t nx = m_mesh.getNumNodesX();
  const size_t ny = m_mesh.getNumNodesY();
  const size_t nz = m_mesh.getNumNodesZ();

  // set neighbor offsets
  const size_t EW_OFFSET = 1;
  const size_t NS_OFFSET = nx;
  const size_t UD_OFFSET = nx*ny;

  // TODO: decide whether to keep this generic for full domain, or handle
  // boundary faces separately...
  for (size_t k = 0; k < nz; ++k) {
    for (size_t j = 0; j < ny; ++j) {
      for (size_t i = 0; i < nx; ++i) {
        const size_t idx = i + (j*nx) + (k*nx*ny);

        // store neighbor temperatures in each direction
        // TODO: experiment with SOR here
        const real_type TE = (i<nx-1) ? Tn[idx + EW_OFFSET] : Tn[idx];
        const real_type TW = (i>0) ? Tn[idx - EW_OFFSET] : Tn[idx];
        const real_type TN = (j<ny-1) ? Tn[idx + NS_OFFSET] : Tn[idx];
        const real_type TS = (j>0) ? Tn[idx - NS_OFFSET] : Tn[idx];
        const real_type TU = (k<nz-1) ? Tn[idx + UD_OFFSET] : Tn[idx];
        const real_type TD = (k>0) ? Tn[idx - UD_OFFSET] : Tn[idx];

        // get diffusivities for each face of current volume
        const real_type alphP = m_materialProps.getDiffusivity(Tn[idx]);
        const real_type alphE = m_materialProps.getFaceDiffusivity(Tn[idx], TE);
        const real_type alphW = m_materialProps.getFaceDiffusivity(Tn[idx], TW);
        const real_type alphN = m_materialProps.getFaceDiffusivity(Tn[idx], TN);
        const real_type alphS = m_materialProps.getFaceDiffusivity(Tn[idx], TS);
        const real_type alphU = m_materialProps.getFaceDiffusivity(Tn[idx], TU);
        const real_type alphD = m_materialProps.getFaceDiffusivity(Tn[idx], TD);

        // determine neighbor transfer coefficients
        const real_type aE = (alphE*m_mesh.getAreaEW()) / m_mesh.getXSpacing();
        const real_type aW = (alphW*m_mesh.getAreaEW()) / m_mesh.getXSpacing();
        const real_type aN = (alphN*m_mesh.getAreaNS()) / m_mesh.getYSpacing();
        const real_type aS = (alphS*m_mesh.getAreaNS()) / m_mesh.getYSpacing();
        const real_type aU = (alphU*m_mesh.getAreaUD()) / m_mesh.getZSpacing();
        const real_type aD = (alphD*m_mesh.getAreaUD()) / m_mesh.getZSpacing();
        // TODO: add integration of face source terms
        const real_type aP = aE + aW + aN + aS + aU + aD - volSource[idx];
      
        const real_type vol = m_mesh.getCellVolume();
        Tnp1[idx] = 1 / (1+m_dt/vol*aP)*(
          (1.0 -  aP*(m_dt / vol)) * Tnm1[idx] +
          (aE*TE + aW*TW + aU*TU + aD*TD + aN*TN + aS*TS) *
          ((2.0*m_dt) / vol));
      }
    }
  }
}


void BTCSSolver::setICs(std::vector<real_type>& TnRef) override
{
  // TODO
}

void BTCSSolver::setBCs(std::vector<real_type>& TnRef) override
{
  // for now, loop over each domain face cell, setting its value to the
  // constant heater temperature
  // TODO: build in flexibility to experiment with different boundary
  // conditions
  
  const size_t nx = m_mesh.getNumNodesX();
  const size_t ny = m_mesh.getNumNodesY();
  const size_t nz = m_mesh.getNumNodesZ();

  // north boundary
  size_t j = ny-1;
  for (size_t k = 0; k < nz; ++k) {
    for (size_t i = 0; i < nx; ++i) {
      const size_t idx = i + (j*nx) + (k*nx*ny);
      TnRef[idx] = m_heaterTemp;
    }
  }

  // east boundary
  size_t i = nx-1;
  for (size_t k = 0; k < nz; ++k) {
    for (size_t j = 0; j < ny; ++j) {
      const size_t idx = i + (j*nx) + (k*nx*ny);
      TnRef[idx] = m_heaterTemp;
    }
  }

  // south boundary
  j = 0;
  for (size_t k = 0; k < nz; ++k) {
    for (size_t i = 0; i < nx; ++i) {
      const size_t idx = i + (j*nx) + (k*nx*ny);
      TnRef[idx] = m_heaterTemp;
    }
  }

  // west boundary
  i = 0;
  for (size_t k = 0; k < nz; ++k) {
    for (size_t j = 0; j < ny; ++j) {
      const size_t idx = i + (j*nx) + (k*nx*ny);
      TnRef[idx] = m_heaterTemp;
    }
  }

  // bottom boundary
  k = 0;
  for (size_t j = 0; j < ny; ++j) {
    for (size_t i = 0; i < ny; ++i) {
      const size_t idx = i + (j*nx) + (k*nx*ny);
      TnRef[idx] = m_heaterTemp;
    }
  }
}

real_type BTCSSolver::getSolveTime() override
{
  // TODO: build in timer functionality
  return 0.0;
}
} // namespace DIFFSOLVER
