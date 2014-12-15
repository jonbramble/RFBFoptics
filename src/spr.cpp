/*
 * spr.cc
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

#include "spr.hpp"

Spr::Spr(){
	Spr(100);
}

Spr::Spr(int N){
	data = boost::numeric::ublas::vector<double>(N);
  s_pi = boost::math::constants::pi<double>();
  cores = std::thread::hardware_concurrency();
	setnpts(N);
}

void Spr::setnpts(double _N){N = _N;}
void Spr::setna(double _na){na = _na;}
void Spr::setstartangle(double _sangle){sangle = _sangle;}
void Spr::setendangle (double _endangle){endangle = _endangle;}
void Spr::setnf(double _nf){nf = _nf;}
void Spr::setnlayers(double _size){size = _size;}
void Spr::setlayers(std::vector<IsoLayer> _layers){ vlayers = _layers; } // must check these have been called
	
void Spr::setlambda(double _lambda){lambda = _lambda;}

void Spr::getdata(boost::numeric::ublas::vector<double>& ret_data){
	ret_data=data;
}

void Spr::getmin(double& ret_min){
  ret_min=min;
}

//this should find the spr minimum
void Spr::sprmin(){
  // calculate the critical angle and see if we are beyond it
  // is there an algorithm for this kind of progressing min?
  
  // calculate rpp for an angle
  // if it is falling continue
  // when value increases, check local 2nd derivative, should be above zero for minimum
  // return min value
  
  // could make it do - min searching with forward a back angle iterations with finer steps
  
  // hard to parallelize 
  
  double result, result_old, phia, crangle, step;
  int k = 0;
  double eps = 0.0001;
  double precision = 0.00001;  
  double one_deg_rad = s_pi/180;
  double offset = 5.0;    // a guess at a suitable offset
  
  phia = sangle*(s_pi/180);       //starting angle 
  crangle = asin(nf/na);           // calc the critical angle in radians
  
  if(phia < crangle + offset*one_deg_rad ) {    // offsets the starting point past the critical angle
    phia += offset*one_deg_rad;
  }
  
  result =  Spr::rpp_phia(phia);        // starting value of rpp
  
  do{
    result_old = result;
    step = eps*rpp_p1(phia);    // the step is proportional to the gradient - gradient descent
    result =  Spr::rpp_phia(phia-step);
    phia -= step;               // update phia value
    k++;    
  }while((abs(result - result_old) > precision) && k < 10000);

  min = phia*(180/s_pi);  // return the angle of the min in degrees in min var
  
}

double Spr::rpp_p1(double phia){
 
 double h,xm1,xp1,rpp_xm1,rpp_xp1, slope, eps;
 
 //eps = std::numeric_limits<double>::epsilon();
 
 //h = sqrt(eps)*phia;
 h = 0.001;
 xm1 = phia - h;
 xp1 = phia + h;
 rpp_xm1 = Spr::rpp_phia(xm1);
 rpp_xp1 = Spr::rpp_phia(xp1);

 slope = (-0.5*rpp_xm1 + 0.5*rpp_xp1)/h;  

 return slope;
  
}

double Spr::rpp_p2(double phia){
 
 double h,xm2,xp2,rpp_xm2,rpp_xp2, rpp_val, slope, eps;
 
 //eps = std::numeric_limits<double>::epsilon();
 
 //h = sqrt(eps)*phia;
 h = 0.001;
 xm2 = phia - h;
 xp2 = phia + h;
 rpp_xm2 = Spr::rpp_phia(xm2);
 rpp_val = Spr::rpp_phia(phia);
 rpp_xp2 = Spr::rpp_phia(xp2);

 slope = (-1*rpp_xm2 + 2*rpp_val + rpp_xp2)/pow(h,2);  

 return slope;
  
}


void Spr::rpp_array(){ 
  std::vector<std::thread> threads;  //parallel processing part
  
  int parts = N / cores;
  int extra = N % cores;
  int start, end;
  
  end_angle_rad = endangle*(s_pi/180);
  start_angle_rad = sangle*(s_pi/180);
  range_rad = end_angle_rad-start_angle_rad;

  for (int i=0; i<cores; ++i) // 1 per core:
  {
    start = i*parts;
    end = (i+1)*parts;
    if(i==cores-1)
    	end += extra;
    threads.push_back( std::thread(&Spr::rpp_segments, this, start, end) );
  }

  for (std::thread& t : threads) // new range-based for:
   t.join(); // runs those threads
}

void Spr::rpp_segments(int start, int end){
  int k; 
  double phia, result;
  for(k=start;k<end;k++){
    phia = start_angle_rad+k*(range_rad/N); //input angle
    result = Spr::rpp_phia(phia);
    mu.lock(); // lock here for writing to data
     data(k) = result;
    mu.unlock();
  }
}

double Spr::rpp_phia(double phia){
  
  static const double s_pi = static_cast<double>(3.141592653589793238462643383279502884197L);

	matrix<complex<double> > T(4,4), ILa(4,4), Lf(4,4), Tli(4,4);
  matrix<double> ep(4,4), Delta(4,4);
	identity_matrix<complex<double> > Id(4,4);
  std::vector<boost::numeric::ublas::matrix<complex<double> > > prod_seq;
  
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
  
	prod_seq.push_back(Lf); //add exit matrix at end
	total_trans(prod_seq, T);
	prod_seq.clear();

	return rpp(T);    // need to choose data rpp rps etc
}

void Spr::run(){
  rpp_array();
}