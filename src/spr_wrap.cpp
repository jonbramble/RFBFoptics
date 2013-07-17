#include <Rcpp.h>
#include "spr.hpp"
//using namespace Rcpp;

void convert_layer(std::vector<Layer>&vlayers, Rcpp::List layers, int layer_count){
  Layer a_layer;
  double layer_d;
  //complex<double> layer_eps;
  //convert to layers    //could I use std::transform need iterators
  for(int i=0;i<layer_count;i++)// loop over layers to push into vlayer
  {
    Rcpp::S4 S4layer((SEXP)layers[i]);// get the layer S4 object from the list
       
    layer_d = S4layer.slot("d");//get the data from the slots
    complex<double> layer_eps = S4layer.slot("eps"); 
       
    a_layer.seteps(layer_eps);
    a_layer.setd(layer_d);
    
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