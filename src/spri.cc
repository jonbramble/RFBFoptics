/*
 * spri.cc
 * Copyright (C) Jonathan Bramble 2015
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

#include "spri.h"

SPRI::SPRI(int N){
  //data = boost::numeric::ublas::vector<double>(N);
  //cores = std::thread::hardware_concurrency();
  setnpts(N);
}

void SPRI::setnpts(double _N){N = _N;}

void SPRI::setmodulator(double _M){M = _M;}
void SPRI::setpolariser(double _P){P = _P;}
void SPRI::setanalyser(double _A){A = _A;}
void SPRI::setdelta(double _D){Delta = _D;}


//boost::math::cyl_bessel_j<double, std::complex<double> > (1.0,std::complex<double>(1.0,0.0)); 


// would prefer a matrix approach here
void SPRI::DC_phia(double phia){
  double Rp = pow(abs(rpp_phia(phia)),2);
  double Rs = pow(abs(rss_phia(phia)),2);
  double rpr = real(rpp_phia(phia));
  double rpi = imag(rpp_phia(phia));
  double rsr = real(rss_phia(phia));
  double rsi = imag(rss_phia(phia));
  double Mr = rpr*rsr+rpi*rsi;
  
  dc = Rp*pow(cos(A),2)+Rs*pow(sin(A),2)+bessel_j(0,Delta)*(Rp*pow(cos(A),2)-Rs*pow(sin(A),2))+Mr*sin(2*A)*sin(2*P);
  
}

double SPRI::bessel_j(int v, double x){
  return boost::math::cyl_bessel_j<int, double> (v,x); 
}




