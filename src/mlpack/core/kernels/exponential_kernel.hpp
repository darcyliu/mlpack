/**
 * @file exponential_kernel.hpp
 * @author Ajinkya Kale <kaleajinkya@gmail.com>
 *
 * Implementation of the Exponential kernel (ExponentialKernel).
 */
#ifndef __MLPACK_CORE_KERNELS_EXPONENTIAL_KERNEL_HPP
#define __MLPACK_CORE_KERNELS_EXPONENTIAL_KERNEL_HPP

#include <mlpack/core.hpp>

namespace mlpack {
namespace kernel {

/**
 * The standard Exponential kernel.  Given two vectors @f$ x @f$, @f$ y @f$, and a
 * bandwidth @f$ \mu @f$ (set in the constructor),
 *
 * @f[
 * K(x, y) = \exp(-\frac{|| x - y ||}{2 \mu^2}).
 * @f]
 *
 * The implementation is all in the header file because it is so simple.
 */
class ExponentialKernel
{
 public:
  /**
   * Default constructor; sets bandwidth to 1.0.
   */
  ExponentialKernel() : bandwidth(1.0), gamma(-0.5)
  { }

  /**
   * Construct the Exponential kernel with a custom bandwidth.
   *
   * @param bandwidth The bandwidth of the kernel (@f$\mu@f$).
   */
  ExponentialKernel(double bandwidth) :
    bandwidth(bandwidth),
    gamma(-0.5 * pow(bandwidth, -2.0))
  { }

  /**
   * Evaluation of the Exponential kernel.  This could be generalized to use any
   * distance metric, not the Euclidean distance, but for now, the Euclidean
   * distance is used.
   *
   * @tparam VecType Type of vector (likely arma::vec or arma::spvec).
   * @param a First vector.
   * @param b Second vector.
   * @return K(a, b) using the bandwidth (@f$\mu@f$) specified in the
   *   constructor.
   */
  template<typename VecType>
  double Evaluate(const VecType& a, const VecType& b) const
  {
    // The precalculation of gamma saves us a little computation time.
    return exp(gamma * sqrt(metric::SquaredEuclideanDistance::Evaluate(a, b)));
  }

  /**
   * Evaluation of the Exponential kernel using a double precision argument.
   *
   * @param t double value.
   * @return K(t) using the bandwidth (@f$\mu@f$) specified in the
   *     constructor.
   */
  double Evaluate(double t) const
  {
    // The precalculation of gamma saves us a little computation time.
    return exp(gamma * t);
  }

  //! Get the bandwidth.
  const double& Bandwidth() const { return bandwidth; }
  //! Get the precalculated constant.
  const double& Gamma() const { return gamma; }

 private:
  //! Kernel bandwidth.
  double bandwidth;

  //! Precalculated constant depending on the bandwidth;
  //! @f$ \gamma = -\frac{1}{2 \mu^2} @f$.
  double gamma;
};

}; // namespace kernel
}; // namespace mlpack

#endif