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

// would prefer a matrix approach here

// construct the intensity for all inputs and find frequency components

SPRI::SPRI(int N){
  //data = boost::numeric::ublas::vector<double>(N);
  //cores = std::thread::hardware_concurrency();
  //setnpts(N);
}

void SPRI::setmodulator(double _M){M = _M;}
void SPRI::setpolariser(double _P){P = _P;}
void SPRI::setanalyser(double _A){A = _A;}
void SPRI::setdelta(double _D){Delta = _D;}

double SPRI::get_dc(){return dc;}
double SPRI::get_Rw(){return Rw;}
double SPRI::get_R2w(){return R2w;}

void SPRI::run(){ 
  phia = angle*(s_pi/180);
  setreflectivities();
  DC_phia(); // do those calculations
  Rw_phia();
  R2w_phia();
}

void SPRI::setreflectivities(){
  double Rp = pow(abs(rpp_phia(phia)),2);
  double Rs = pow(abs(rss_phia(phia)),2);
  double rpr = real(rpp_phia(phia));
  double rpi = imag(rpp_phia(phia));
  double rsr = real(rss_phia(phia));
  double rsi = imag(rss_phia(phia));
  double Mr = rpr*rsr+rpi*rsi;
  
  double Rpc2 = Rp*pow(cos(A),2);
  double Rss2 = Rs*pow(sin(A),2); 
}
// naming schemes and calling styles need a clean up

void SPRI::DC_phia(){
  dc = Rpc2+Rss2+bessel_j(0,Delta)*(Rpc2-Rss2)+Mr*sin(2*A)*sin(2*P); 
}

void SPRI::Rw_phia(){
  Rw = 2*bessel_j(1,Delta)*(sin(2*P)*(Rss2-Rpc2)+Mr*sin(2*A)*cos(2*P));
}

void SPRI::R2w_phia(){
  R2w = 2*bessel_j(2,Delta)*(cos(2*P)*(Rpc2-Rss2)+Mr*sin(2*A)*cos(2*P));
}

double SPRI::bessel_j(int v, double x){
  return boost::math::cyl_bessel_j<int, double> (v,x); 
}
