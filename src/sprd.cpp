/*
 * sprd.cc
 * Copyright (C) Jonathan Bramble 2014
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

#include "sprd.hpp"

SPRD::SPRD(int N){
  data = boost::numeric::ublas::vector<double>(N);
  cores = std::thread::hardware_concurrency();
  setnpts(N);
}

void SPRD::setdstart(double _dstart){dstart = _dstart;}
void SPRD::setdend (double _dend){dend = _dend;}
void SPRD::setnpts(double _N){N = _N;}

void SPRD::getdata(boost::numeric::ublas::vector<double>& ret_data){ret_data=data;}

void SPRD::run(){
  rpp_array(); 
}

void SPRD::rpp_array(){ 
  std::vector<std::thread> threads;  //parallel processing part
  
  int parts = N / cores;
  int extra = N % cores;
  int start, end;
  
  // create ranges for the calcuations here
  drange = dend - dstart;
  
  for (int i=0; i<cores; ++i) // 1 per core:
  {
    start = i*parts;
    end = (i+1)*parts;
    if(i==cores-1)
      end += extra;
    threads.push_back( std::thread(&SPRD::rpp_segments, this, start, end) );
  }

  for (std::thread& t : threads) // new range-based for:
   t.join(); // runs those threads
}

void SPRD::rpp_segments(int start, int end){
  int k;
  double phia, result, d;
  phia = angle*(s_pi/180); 
  for(k=start;k<end;k++){
    d = dstart+k*(drange/N);
    result = rpp_phia(phia,d);  // need to feed in the layer information here
    mu.lock(); // lock here for writing to data
     data(k) = result;
    mu.unlock();
  }
}