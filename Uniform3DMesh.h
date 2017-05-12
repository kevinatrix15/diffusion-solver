/**
 * @file Uniform3DMesh.h
 * @brief A class used for storing 3D cartesian mesh information on with
 * uniform spacing in each given direction.
 * @author Kevin Briggs <kevin.briggs@3dsim.com>
 * @version 1
 * @date 2017-05-10
 */

#pragma once

#include <cassert>
#include <climits>

#include "Types.h"

namespace DIFFSOLVER
{

class Uniform3DMesh
{
  public:
  Uniform3DMesh(const size_t numPtsX, numPtsY, numPtsZ, const real_type lenX,
      const real_type lenY, const real_type lenZ)
    : m_numPtsX(numPtsX),
    m_numPtsY(numPtsY),
    m_numPtsZ(numPtsZ),
    m_lenX(lenX),
    m_lenY(lenY),
    m_lenZ(lenZ),
    m_spacingX(m_lenX / static_cast<real_type>(m_numPtsX)),
    m_spacingY(m_lenY / static_cast<real_type>(m_numPtsY)),
    m_spacingZ(m_lenZ / static_cast<real_type>(m_numPtsZ))
  {
    // verify inputs
    if (m_numPtsX == 0 || m_numPtsY == 0 || m_numPtsZ == 0 ||
        m_numPtsX == NULL_NODE || m_numPtsY == NULL_NODE || m_numPtsZ ==
        NULL_NODE)
    {
      throw runtime_error("Invalid numbber of points in the mesh.");
    }

    if (m_lenX <= 0.0 || m_lenY <= 0.0 || m_lenZ <= 0.0)
    {
      throw runtime_error("Invalid domain size.");
    }

    if (m_spacingX <= 0.0 || m_spacingY <= 0.0 || m_spacingZ <= 0.0)
    {
      throw runtime_error("Invalid mesh spacing.");
    }

  }

  /**
   * @brief Get the number of nodes in the x-direction.
   *
   * @return The number of nodes in the x-direction
   */
  size_t getNumNodesX() const noexcept
  {
    return m_numNodexX;
  }

  /**
   * @brief Get the number of nodes in the y-direction.
   *
   * @return The number of nodes in the y-direction
   */
  size_t getNumNodesY() const noexcept
  {
    return m_numNodexY;
  }

  /**
   * @brief Get the number of nodes in the z-direction.
   *
   * @return The number of nodes in the z-direction
   */
  size_t getNumNodesZ() const noexcept
  {
    return m_numNodexZ;
  }

  /**
   * @brief Get the spacing in the x-direction.
   *
   * @return The spacing in the x-direction.
   */
  real_type getXSpacing() const noexcept
  {
    return m_spacingX;
  }

  /**
   * @brief Get the spacing in the y-direction.
   *
   * @return The spacing in the y-direction.
   */
  real_type getYSpacing() const noexcept
  {
    return m_spacingY;
  }

  /**
   * @brief Get the spacing in the z-direction.
   *
   * @return The spacing in the z-direction.
   */
  real_type getZSpacing() const noexcept
  {
    return m_spacingZ;
  }

  /**
   * @brief Get the length of the domain in x.
   *
   * @return The length in x.
   */
  real_type getLengthX() const noexcept
  {
    return m_lenX;
  }

  /**
   * @brief Get the length of the domain in y.
   *
   * @return The length in y.
   */
  real_type getLengthY() const noexcept
  {
    return m_lenY;
  }

  /**
   * @brief Get the length of the domain in z.
   *
   * @return The length in z.
   */
  real_type getLengthZ() const noexcept
  {
    return m_lenZ;
  }

  real_type getAreaEW() const noexcept
  {
    return m_spacingX * m_spacingZ;
  }

  real_type getAreaNS() const noexcept
  {
    return m_spacingY * m_spacingZ;
  }

  real_type getAreaUD() const noexcept
  {
    return m_spacingX * m_spacingY;
  }

  real_type getCellVolume() const noexcept
  {
    return m_spacingX * m_spacingY * m_spacingZ;
  }

  private:
  const size_t m_numPtsX;
  const size_t m_numPtsY;
  const size_t m_numPtsZ;
  const real_type m_lenX;
  const real_type m_lenX;
  const real_type m_lenX;
  const real_type m_spacingX;
  const real_type m_spacingX;
  const real_type m_spacingX;
};
} // namespace DIFFSOLVER
