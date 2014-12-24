/*
 * sprd.h
 * Copyright (C) Jonathan Bramble 2014
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
 
#ifndef SPRD_H
#define SPRD_H

// vector calculations over thickness of a layer

#include "spr.h"
#include <thread>
#include <mutex>

class SPRD : public SPR {
  
  public:
  
    SPRD(int N);
  
    int N, cores;
    std::mutex mu;
    double dstart, dend, drange;   // get this from the single fitted layer
  
    void run();
    void getdata(boost::numeric::ublas::vector<double>& ret_data);
  
    boost::numeric::ublas::vector<double> data;
  
    void setdstart(double _dstart);
    void setdend(double _dend);
  
  private:

    void setnpts(double _N);
    void rpp_array();
    void rpp_segments(int start, int end);

  
};


#endif