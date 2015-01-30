/*
 * spr.cc
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

#include "spr.h"

SPR::SPR(){
  s_pi = boost::math::constants::pi<double>();
}

void SPR::setna(double _na){na = _na;}
void SPR::setnf(double _nf){nf = _nf;}
void SPR::setangle(double _angle){angle = _angle;}
double SPR::getangle(){return angle;}
void SPR::setlambda(double _lambda){lambda = _lambda;}
void SPR::setnlayers(double _size){size = _size;}
void SPR::setlayers(std::vector<IsoLayer> _layers){ vlayers = _layers; } // must check these have been called

void SPR::getval(double& ret_val){ret_val=val;}
void SPR::getmin(double& ret_min){ret_min=min;}

void SPR::sprval(){
  double phia;
  phia = angle*(s_pi/180);
  val = Rpp_phia(phia);
}

//this should find the spr minimum in a small number of steps
void SPR::sprmin(){
  
  double result, result_old, phia, crangle, step;
  int limit = 1000;
  int k = 0;
  double eps = 0.0001;
  double precision = 0.00001;  
  double one_deg_rad = s_pi/180;
  double offset = 5.0;    // a guess at a suitable offset
  
  phia = angle*(s_pi/180);       //starting angle 
  crangle = asin(nf/na);          // calc the critical angle in radians
  
  if(phia < crangle + offset*one_deg_rad ) {    // offsets the starting point past the critical angle
    phia += offset*one_deg_rad;
  }
  
  result =  Rpp_phia(phia);        // starting value of rpp
  
  do{
    result_old = result;
    step = eps*rpp_p1(phia);    // the step is proportional to the gradient - gradient descent
    result =  Rpp_phia(phia-step);
    phia -= step;               // update phia value
    k++;    
  }while((abs(result - result_old) > precision) && k < limit);   // limit the number of steps

  min = phia*(180/s_pi);  // return the angle of the min in degrees in min var
  
}

// first derivative of the rpp values
double SPR::rpp_p1(double phia){
 
 double h,xm1,xp1,rpp_xm1,rpp_xp1, m, eps;
 h = 0.001;
 xm1 = phia - h;
 xp1 = phia + h;
 rpp_xm1 = Rpp_phia(xm1);
 rpp_xp1 = Rpp_phia(xp1);

 m = (-0.5*rpp_xm1 + 0.5*rpp_xp1)/h;  

 return m; 
}

// second derivative of the rpp values
double SPR::rpp_p2(double phia){
 
 double h,xm2,xp2,rpp_xm2,rpp_xp2, rpp_val, m, eps;
 h = 0.001;
 xm2 = phia - h;
 xp2 = phia + h;
 rpp_xm2 = Rpp_phia(xm2);
 rpp_val = Rpp_phia(phia);
 rpp_xp2 = Rpp_phia(xp2);

 m = (-1*rpp_xm2 + 2*rpp_val + rpp_xp2)/pow(h,2);  

 return m;  
}

MatrixZ SPR::transfer_matrix(double phia){
  
  MatrixZ T(4,4), ILa(4,4), Lf(4,4), Tli(4,4);
  MatrixD ep(4,4), Delta(4,4);
  boost::numeric::ublas::identity_matrix<complex<double> > Id(4,4);
  std::vector<MatrixZ> prod_seq;
  
	complex<double>	result, zcphif2, phif, cphif, eps;

	double cphia, eta, d;
	double k0 = (2*s_pi)/lambda; // laser wavevector
	
	cphia = cos(phia); 
	eta = na*sin(phia); // x comp of wavevector
	zcphif2 = complex<double>(1-pow((na/nf)*sin(phia),2),0);  // this always picks the correct sector
	cphif = sqrt(zcphif2);
		
	incmat(na,cphia,ILa);
	extmat(nf,cphif,Lf);
		
	prod_seq.push_back(ILa); 
  
  //iterate over physical layers
	for(IsoLayer& v : vlayers){
      eps = v.geteps();
  		d = v.getd();
      gtmiso(eps,k0,eta,-1*d,Tli);
			prod_seq.push_back(Tli);
	}
  
	prod_seq.push_back(Lf);           //add exit matrix at end
	total_trans(prod_seq, T);
	prod_seq.clear();
  
  return T;
}

// value of rpp at a fixed value of phia for the stack
complex<double> SPR::rpp_phia(double phia){
	return rpp(transfer_matrix(phia)); // need to choose data rpp rps etc              
}

// value of rps at a fixed value of phia for the stack
complex<double>  SPR::rps_phia(double phia){
  return rps(transfer_matrix(phia));          
}

// value of rsp at a fixed value of phia for the stack
complex<double>  SPR::rsp_phia(double phia){
  return rsp(transfer_matrix(phia));         
}

// value of rss at a fixed value of phia for the stack
complex<double>  SPR::rss_phia(double phia){
  return rss(transfer_matrix(phia));            
}

// value of rpp at a fixed value of phia for the stack
double SPR::Rpp_phia(double phia){
  //return Rpp(transfer_matrix(phia)); // need to choose data rpp rps rss etc   
  return pow(Rpp(transfer_matrix(phia)),2);
}

// value of rpp at a fixed value of phia for the stack with a value for a fitable layer
// could be improved by precalcuating the variables that are fixed with angle  
// could extract the main part out again for other calcs
double SPR::rpp_phia(double phia, double d){
  
  MatrixZ T(4,4), ILa(4,4), Lf(4,4), Tli(4,4);
  MatrixD ep(4,4), Delta(4,4);
  boost::numeric::ublas::identity_matrix<complex<double> > Id(4,4);
  std::vector<MatrixZ> prod_seq;
  
	complex<double>	result, zcphif2, phif, cphif, eps;

	double cphia, eta, dval;
	double k0 = (2*s_pi)/lambda; // laser wavevector

	cphia = cos(phia); 
	eta = na*sin(phia); // x comp of wavevector
	zcphif2 = complex<double>(1-pow((na/nf)*sin(phia),2),0);  // this always picks the correct sector
	cphif = sqrt(zcphif2);
		
	incmat(na,cphia,ILa);
	extmat(nf,cphif,Lf);
		
	prod_seq.push_back(ILa); 
  
  //iterate over physical layers
	for(IsoLayer& v : vlayers){
      eps = v.geteps();
      if(v.getfitd())
      {
        dval = d;
      }
      else
      {
        dval = v.getd();
      }  	
      gtmiso(eps,k0,eta,-1*dval,Tli);
			prod_seq.push_back(Tli);
	}
  
	prod_seq.push_back(Lf);           //add exit matrix at end
	total_trans(prod_seq, T);
	prod_seq.clear();

	return Rpp(T);                    // need to choose data rpp rps etc
}