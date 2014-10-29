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
	data = boost::numeric::ublas::vector<double>(100);
	setnpts(100);// set defaults
}

Spr::Spr(int N){
	data = boost::numeric::ublas::vector<double>(N);
	setnpts(N);
}

void Spr::setnpts(double _N){N = _N;}
void Spr::setna(double _na){na = _na;}
void Spr::setstartangle(double _sangle){sangle = _sangle;}
void Spr::setendangle (double _endangle){endangle = _endangle;}
void Spr::setnf(double _nf){nf = _nf;}
void Spr::setnlayers(double _size){size = _size;}
void Spr::setlayers(std::vector<Layer> _layers){   // must check these have been called
	vlayers = _layers;
}		
	
void Spr::setlambda(double _lambda){lambda = _lambda;}

void Spr::getdata(boost::numeric::ublas::vector<double>& ret_data){
	ret_data=data;
}

//this should find the spr minimum
void Spr::sprmin(){
  // calculate the critical angle and see if we are beyond it
  // is there an algorithm for this
}

void Spr::rpp_array(){ 
  static const double s_pi = static_cast<double>(3.141592653589793238462643383279502884197L);
  
  end_angle_rad = endangle*(s_pi/180);
  start_angle_rad = sangle*(s_pi/180);
	range_rad = end_angle_rad-start_angle_rad;
  
  int cores = std::thread::hardware_concurrency();
  //int cores = 1;
  std::vector<std::thread> threads;
  
  int parts = N / cores;
  int extra = N % cores;
  int start, end;

  //std::cout << "cores " << cores << std::endl;
  //std::cout << "parts " << parts << std::endl;
  //std::cout << "extra " << extra << std::endl;

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
    mu.lock();
    data(k) = result;
    mu.unlock();
  }
}

double Spr::rpp_phia(double phia){
  
  static const double s_pi = static_cast<double>(3.141592653589793238462643383279502884197L);

	matrix<complex<double> > T(4,4), ILa(4,4), Lf(4,4), Tli(4,4);
	identity_matrix<complex<double> > Id(4,4);

	complex<double>	result, zcphif2, phif, cphif;

	double cphia, eta;
	double k0 = (2*s_pi)/lambda; // laser wavevector
		
	cphia = cos(phia); 
	eta = na*sin(phia); // x comp of wavevector
	zcphif2 = complex<double>(1-pow((na/nf)*sin(phia),2),0);  // this always picks the correct sector
	cphif = sqrt(zcphif2);
		
	incmat(na,cphia,ILa);
	extmat(nf,cphif,Lf);
		
	prod_seq.push_back(ILa); 
  
  //iterate over elements
	for ( iso_it=vlayers.begin() ; iso_it<vlayers.end(); iso_it++ ){
			eps = iso_it->geteps();
			d = iso_it->getd();
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


/*void Spr::old_run()
{
  //make tests
	static const double s_pi = static_cast<double>(3.141592653589793238462643383279502884197L);

	matrix<complex<double> > T(4,4), ILa(4,4), Lf(4,4), Tli(4,4);
	identity_matrix<complex<double> > Id(4,4);

	complex<double>	result, zcphif2, phif, cphif;

	double end_angle_rad = endangle*(s_pi/180);
	double start_angle_rad = sangle*(s_pi/180);
	double range_rad = end_angle_rad-start_angle_rad;

	double phia, cphia, eta;
	double k0 = (2*s_pi)/lambda; // laser wavevector
	int k;
	
	// need some kind of generalised loop - will always have N points
	for(k=0;k<N;k++)
	{	
		phia = start_angle_rad+k*(range_rad/N); //input angle

		cphia = cos(phia); 
		eta = na*sin(phia); // x comp of wavevector
		zcphif2 = complex<double>(1-pow((na/nf)*sin(phia),2),0);  // this always picks the correct sector
		cphif = sqrt(zcphif2);
		
		incmat(na,cphia,ILa);
		extmat(nf,cphif,Lf);
		
		prod_seq.push_back(ILa); 
		for ( iso_it=vlayers.begin() ; iso_it<vlayers.end(); iso_it++ ){//iterate over elements
			eps = iso_it->geteps();
			d = iso_it->getd();
			gtmiso(eps,k0,eta,-1*d,Tli);
			prod_seq.push_back(Tli);
		}
		prod_seq.push_back(Lf); //add at end

		total_trans(prod_seq, T);
	
		prod_seq.clear();

		data(k) = rpp(T);    // need to choose data rpp rps etc
	}
}*/
