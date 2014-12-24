
#ifndef EXPM_EIGEN_
#define EXPM_EIGEN_
#include <complex>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/lu.hpp>

template<typename MATRIX> MATRIX expm_eigen(const MATRIX &H) {
  //TODO implement eigen version with values and vectors
  return expm_pad(H);
}


#endif