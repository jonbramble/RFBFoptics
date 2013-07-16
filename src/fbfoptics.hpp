/*
 * fbfoptics.hpp
 * Copyright (C) Jonathan Bramble 2011
 * 
FBF-Optics is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * FBF-Optics is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef FBFOPTICS_H_
#define FBFOPTICS_H_

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/numeric/ublas/io.hpp>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/vector_proxy.hpp>
#include <boost/numeric/ublas/triangular.hpp>
#include <boost/numeric/ublas/lu.hpp>

#include <complex>
#include "complex_methods.hpp"
#include "expm.hpp"

using namespace boost::numeric::ublas;
using namespace std;
/*
 * @file fbfoptics.hpp
 * @brief All the code required to do 4x4 optics on stratified media. Following the methods of Berreman. Can be used for both isotropic and aniostropic layers, but entry and exit media must be isotropic. isotropic layers tested, but aniostropic not yet tested
 * 
 * 
 * @author Jonathan Bramble
 * @date 25/06/2009
 */
class Fbfoptics {

public:
	Fbfoptics();
	~Fbfoptics();

protected:
	/// The entrance matrix
	void incmat(const double, const double, matrix<complex<double> >&);
	/// The exit matrix
	void extmat(const double, const complex<double>, matrix<complex<double> >&);
	/// The dielectric tensor
	void dietens(const double,const double,const double,const double,const double,const double, const double, matrix<double>&);
	/// The general transfer matrix for isotropic layers
	void gtmiso(const complex<double>,const double,const double,const double, matrix<complex<double> >&);
	/// The general transfer matrix for anisotropic layers
	void gtm(const matrix<double>& Delta, const double k0, const double h, matrix<complex<double> >& T);
	/// The differential propagation matrix Delta
	void diffpropmat(const matrix<double> ep, const double eta, matrix<double>& Delta);
	/// Calculates from the total transfer matrix the rpp reflectivity co-efficient
	double rpp(const matrix<complex<double> >& M);
	/// Returns the product of the sequence of transfer matricies
	void total_trans(std::vector<boost::numeric::ublas::matrix<complex<double> > > prod_seq, matrix<complex<double> >& T);
};

#endif /* FBFOPTICS_H_ */




