/*
 * spr_wrap.ccp
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

#include <Rcpp.h>
#include "spr.hpp"

using namespace Rcpp;

void convert_layer(std::vector<IsoLayer>&vlayers, List layers, int layer_count){
  IsoLayer a_layer;
  double layer_d;
  //convert to layers    //could I use std::transform need iterators
  for(int i=0;i<layer_count;i++)// loop over layers to push into vlayer
  {
    S4 S4layer((SEXP)layers[i]);// get the layer S4 object from the list
       
    layer_d = S4layer.slot("d");//get the data from the slots
    complex<double> layer_eps = S4layer.slot("eps"); 

    a_layer.seteps(layer_eps);
    a_layer.setd(layer_d);
 
    vlayers[i]=a_layer;
  }
}

void setsim(S4 fullstack, Spr *spr_simulation){
  
  int N, layer_count;
  double lambda, n_entry, n_exit, start_angle, end_angle;
  Rcpp::List layers;
  
  N = fullstack.slot("points");
  lambda = fullstack.slot("lambda");
  n_entry = fullstack.slot("n_entry");
  n_exit = fullstack.slot("n_exit");
  start_angle = fullstack.slot("start_angle");
  end_angle = fullstack.slot("end_angle");
  layers = fullstack.slot("layers");
  
  layer_count = layers.size();
  std::vector<IsoLayer> vlayers(layer_count);   // vector of layers
  convert_layer(vlayers,layers,layer_count);    // r to layer conversion
  
  spr_simulation->setnlayers(layer_count);
  spr_simulation->setlayers(vlayers);

  spr_simulation->setstartangle(start_angle); 
	spr_simulation->setendangle(end_angle);
	spr_simulation->setna(n_entry);
	spr_simulation->setnf(n_exit);
	spr_simulation->setlambda(lambda);
  
  return;
}

// return the value of rpp only at a chosen angle for the layers specified
// [[Rcpp::export]]
NumericVector S4sprval(S4 fullstack, NumericVector angle){
  int N = 1;
  Spr *spr_simulation = new Spr(N);
  setsim(fullstack, spr_simulation);
  
  double d_angle = (double)angle[0];
  spr_simulation->setstartangle(d_angle); 
  
  Rcpp::NumericVector y(N);             // create rcpp numeric vector for result
  boost::numeric::ublas::vector<double> result(N); // allocation boost vector for result
  
  spr_simulation->run();                //more error handling required probabily
	spr_simulation->getdata(result);      // this could be more efficient with less unness code execution
  
  delete spr_simulation;  
  y = result;
  return y;
}

// return the full set of data
// [[Rcpp::export]]
NumericVector S4spr(S4 fullstack){
  int N = fullstack.slot("points"); 
  Spr *spr_simulation = new Spr(N);     // create simulation with N points
  
  setsim(fullstack, spr_simulation);    // set parameters
  
  Rcpp::NumericVector y(N);             // create rcpp numeric vector for result
  boost::numeric::ublas::vector<double> result(N); // allocation boost vector for result

	spr_simulation->run();  //more error handling required probabily
	spr_simulation->getdata(result);
    
  delete spr_simulation;  
  y = result;
  return y;
}

// return the min angle
// [[Rcpp::export]]
NumericVector S4sprmin(S4 fullstack){
  int N;
  NumericVector y(1);  
  double result;
  
  Spr *spr_simulation = new Spr(1);     // create simulation with N points
  setsim(fullstack, spr_simulation);    // set parameters
  
  spr_simulation->sprmin();  //more error handling required probabily
  spr_simulation->getmin(result);
  
  delete spr_simulation;  
  y = result;
  return y;
}