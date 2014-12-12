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
//using namespace Rcpp;

void convert_layer(std::vector<Layer>&vlayers, Rcpp::List layers, int layer_count){
  Layer a_layer;
  double layer_d;
  Rcpp::CharacterVector is_iso;
  //Rcpp::CharacterVector iso("isotropic");
  //complex<double> layer_eps;
  //convert to layers    //could I use std::transform need iterators
  for(int i=0;i<layer_count;i++)// loop over layers to push into vlayer
  {
    Rcpp::S4 S4layer((SEXP)layers[i]);// get the layer S4 object from the list
       
    layer_d = S4layer.slot("d");//get the data from the slots
    complex<double> layer_eps = S4layer.slot("eps"); 
    //is_iso = S4layer.slot("type");

    a_layer.seteps(layer_eps);
    a_layer.setd(layer_d);
    
    //if(is_iso==iso){
      a_layer.setiso(true);
    //}
  
    vlayers[i]=a_layer;
  }
}

// [[Rcpp::export]]
Rcpp::NumericVector S4spr(Rcpp::S4 fullstack){
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
    
  Spr *spr_simulation = new Spr(N);  // create simulation
  Rcpp::NumericVector y(N); // create rcpp numeric vector
  boost::numeric::ublas::vector<double> result(N); // allocation boost vector for result
  
  layer_count = layers.size();
  std::vector<Layer> vlayers(layer_count);  // vector of layers

  convert_layer(vlayers,layers,layer_count); // r to layer conversion
  
  spr_simulation->setnlayers(layer_count);
  spr_simulation->setlayers(vlayers);

	spr_simulation->setstartangle(start_angle); 
	spr_simulation->setendangle(end_angle);
	spr_simulation->setna(n_entry);
	spr_simulation->setnf(n_exit);
	spr_simulation->setlambda(lambda);

	spr_simulation->run();  //more error handling required probabily
	spr_simulation->getdata(result);
    
  delete spr_simulation;  
    
  for(int k=0;k<N;k++){
    y[k]=result[k];
  }
  return y;
}