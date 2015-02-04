/*
 * fbfoptics.cc
 * Copyright (C) Jonathan Bramble 2011
 * 
 * FBF-Optics is free software: you can redistribute it and/or modify it
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

#include "fbfoptics.h"


Fbfoptics::Fbfoptics(){
}

Fbfoptics::~Fbfoptics(){
}

// Construct the entrance matrix
// na refractive index of the ambient
// cphia cosine of the entrance angle
// ILa the reference to the entrance matrix
void Fbfoptics::incmat(const double na, const double cphia, MatrixZ& ILa){
	ILa(0,0) = complex<double>(0,0);
	ILa(0,1) = complex<double>(0,0);
	ILa(0,2) = complex<double>(0.5,0);
	ILa(0,3) = complex<double>(1/(2*na*cphia),0);

	ILa(1,0) = complex<double>(0,0);
	ILa(1,1) = complex<double>(0,0);
	ILa(1,2) = complex<double>(0.5,0);
	ILa(1,3) = complex<double>(-1/(2*na*cphia),0);

	ILa(2,0) = complex<double>(1/(2*cphia),0);
	ILa(2,1) = complex<double>(1/(2*na),0);
	ILa(2,2) = complex<double>(0,0);
	ILa(2,3) = complex<double>(0,0);

	ILa(3,0) = complex<double>(-1/(2*cphia),0);
	ILa(3,1) = complex<double>(1/(2*na),0);	
	ILa(3,2) = complex<double>(0,0);
	ILa(3,3) = complex<double>(0,0);
}

// Construct the exit matrix
// na refractive index of the exit media, must be real
// cphia cosine of the exit angle
// Lf the reference to the exit matrix
void Fbfoptics::extmat(const double nf, const complex<double> cphif, MatrixZ& Lf)
{
	complex<double> znf= complex<double>(nf,0.0);
	complex<double> zk = znf*cphif;
	
	Lf(0,0) = complex<double>(0,0);
	Lf(0,1) = complex<double>(0,0);
	Lf(0,2) = cphif;
	Lf(0,3) = complex<double>(0,0);

	Lf(1,0) = complex<double>(0,0);
	Lf(1,1) = complex<double>(0,0);
	Lf(1,2) = znf;
	Lf(1,3) = complex<double>(0,0);

	Lf(2,0) = complex<double>(1.0,0.0);
	Lf(2,1) = complex<double>(0,0);
	Lf(2,2) = complex<double>(0,0);
	Lf(2,3) = complex<double>(0,0);

	Lf(3,0) = zk;
	Lf(3,1) = complex<double>(0,0);
	Lf(3,2) = complex<double>(0,0);
	Lf(3,3) = complex<double>(0,0);
}

//Calculate the dielectric tensor representation for the layer
//eav 

void Fbfoptics::dietens(double eav, double dem, double S, double stheta, double ctheta, double sphi, double cphi, MatrixD& ep)
{
	MatrixD A (3,3), ea(3,3), Ap(3,3), inverse(3,3);
	MatrixD epsilon (3,3);
	
	A(0,0) = cphi*ctheta;
	A(0,1) = sphi;
	A(0,2) = -cphi*stheta;
	A(1,0) = -sphi*ctheta;
	A(1,1) = cphi;
	A(1,2) = sphi*stheta;
	A(2,0) = stheta;
	A(2,1) = 0;
	A(2,2) = ctheta;

	epsilon(0,0)=eav-(1/3)*S*dem;
	epsilon(1,1)=eav-(1/3)*S*dem;
	epsilon(2,2)=eav+(2/3)*S*dem;

	ea = prod(A,epsilon);

	// move to external implementation for clarity
  using namespace boost::numeric::ublas;
	//inverse http://www.crystalclearsoftware.com/cgi-bin/boost_wiki/wiki.pl?LU_Matrix_Inversion
	typedef permutation_matrix<std::size_t> pmatrix;
 	MatrixD wc(A); // create a working copy of the input
 	pmatrix pm(wc.size1()); // create a permutation matrix for the LU-factorization
 	int res = lu_factorize(wc,pm); // perform LU-factorization
        //if( res != 0 ) return false;
 	inverse.assign(identity_matrix<double>(wc.size1())); // create identity matrix of "inverse"
 	lu_substitute(wc, pm, inverse); // backsubstitute to get the inverse

	ep = prod(ea,inverse);
}

//Calculate the general transfer matrix for isotropic materials
void Fbfoptics::gtmiso(const complex<double> eiso, const double k0, const double eta, const double diso, MatrixZ& Tiso)
{
	double eta2 = pow(eta,2);
	complex<double> rb, za, qiso, zb, zc, zd, carg, sarg;

	rb = complex<double>(eta2,0);

	za = eiso-eta2;
	//za = complex_sub_real(eiso,eta2);
	qiso = sqrt(za);
	zb = qiso*k0;
	zc = zb*diso;
	zd= rb/eiso;

	carg = cos(zc);
	sarg = sin(zc);

	static const complex<double> zero = complex<double>(0.0,0.0);
	static const complex<double> i = complex<double>(0.0,1.0);
	static const complex<double> one = complex<double>(1.0,0.0);
	
  MatrixZ T(4,4);

	T(0,2) = zero;
	T(0,3) = zero;
	T(1,2) = zero;
	T(1,3) = zero;
	T(2,0) = zero;
	T(2,1) = zero;	
	T(3,0) = zero;
	T(3,1) = zero;
	
	T(0,0) = carg; 
	T(1,1) = carg; 
	T(2,2) = carg; 
	T(3,3) = carg; 

	T(0,1) = ((i*(one-zd))/qiso)*sarg; 
	T(1,0) = ((i*eiso)/qiso)*sarg; 
	T(2,3) = ((i*one)/qiso)*sarg; 
	T(3,2) = ((i*(eiso-eta2))/qiso)*sarg; 

	Tiso = T;
}

//Calculate the differential propagation matrix
void Fbfoptics::diffpropmat(const MatrixD ep, const double eta, MatrixD& Delta)
{
	double zb[10];
	double eta2 = pow(eta,2);

	double ep31,ep33,ep32,ep13,ep22,ep11,ep12,ep21,ep23;

	ep11 = ep(0,0);
	ep12 = ep(0,1);
	ep13 = ep(0,2);
	ep21 = ep(1,0);
	ep22 = ep(1,1);
	ep23 = ep(1,2);
	ep31 = ep(2,0);
	ep32 = ep(3,1);
	ep33 = ep(3,2);

	Delta(0,0)=-eta*ep31/ep33;
	Delta(0,1)=1-eta2/ep33;
	Delta(0,2)=-eta*ep32/ep33;
	Delta(0,3)=0;
	Delta(1,0)=ep11-(ep13*ep31)/ep33;
	Delta(1,1)=-eta*ep13/ep33;
	Delta(1,2)=ep11-(ep12*ep32)/ep33;
	Delta(1,3)=0;
	Delta(2,0)=0;
	Delta(2,1)=0;
	Delta(2,2)=0;
	Delta(2,3)=1.0;
	Delta(3,0)=ep21-(ep31*ep23)/ep33;
	Delta(3,1)=-eta*ep23/ep33;
	Delta(3,2)=ep11-(ep13*ep31)/ep33-eta2;
	Delta(3,3)=0;
}

//Calculate the p-polarised reflectivity
complex<double> Fbfoptics::rpp(const MatrixZ& M)
{
	complex<double> zr;
	zr = ((M(0,0)*M(3,2))-(M(3,0)*M(0,2)))/((M(0,0)*M(2,2))-(M(0,2)*M(2,0)));
	return zr;
}

complex<double> Fbfoptics::rps(const MatrixZ& M)
{
  complex<double> zr;
  zr = ((M(1,2)*M(0,0))-(M(1,0)*M(0,2)))/((M(0,0)*M(2,2))-(M(0,2)*M(2,0)));
  return zr;
}

complex<double> Fbfoptics::rsp(const MatrixZ& M)
{
  complex<double> zr;
  zr = ((M(3,2)*M(2,1))-(M(2,2)*M(3,0)))/((M(0,2)*M(2,0))-(M(0,0)*M(2,2)));
  return zr;
}

complex<double> Fbfoptics::rss(const MatrixZ& M)
{
  complex<double> zr;
  zr = ((M(1,0)*M(2,2))-(M(1,2)*M(2,0)))/((M(0,0)*M(2,2))-(M(0,2)*M(2,0)));
  return zr;
}

double Fbfoptics::Rpp(const MatrixZ& M)
{
  complex<double> y,z;
  y = rpp(M);
  z = rss(M);
  return abs(y/z);
}

MatrixZ Fbfoptics::jones(const MatrixZ& M)
{
  MatrixZ J(2,2);
  
  J(0,0) = rpp(M);
  J(0,1) = rps(M);
  J(1,0) = rsp(M);
  J(1,1) = rss(M);
  
  return J;
}

//TODO: Add all the other reflectivities and transmissions
//TODO: FOR phase modified configuration this might be more complex

//Calculate the general transfer matrix
void Fbfoptics::gtm(const MatrixD& Delta, const double k0, const double h, MatrixZ& T)
{
	MatrixZ Tw = Delta;
	for (unsigned i = 0; i < 4; ++ i)
        	for (unsigned j = 0; j < 4; ++ j)
            		Tw(i,j)=complex<double>(0,-h*k0*Delta(i,j));
	T = expm_pad(Tw); 
  
}

//Calculate the general transfer matrix
void Fbfoptics::gtm_eig(const MatrixD& Delta, const double k0, const double h, MatrixZ& T){
  //here we need an eigenvalue solution for the matrix exponential becuase this contains physically relavent information
  MatrixZ Tw = Delta;
  for (unsigned i = 0; i < 4; ++ i)
        	for (unsigned j = 0; j < 4; ++ j)
            		Tw(i,j)=complex<double>(0,-h*k0*Delta(i,j));
                
  T = expm_eigen(Tw); // change this to eigs method
}

//Calculate the total transfer matrix
void Fbfoptics::total_trans(std::vector<MatrixZ> prod_seq, MatrixZ& T)
{
	std::vector<MatrixZ>::reverse_iterator mat_it;
	MatrixZ Temp(4,4);
	boost::numeric::ublas::identity_matrix<complex<double> > Id(4,4); 

	Temp = Id; // resets temp

	for ( mat_it=prod_seq.rbegin() ; mat_it<prod_seq.rend(); mat_it++ ){  //iterate over elements
			T = prod(*mat_it,Temp);
			Temp = T;
	}

}


