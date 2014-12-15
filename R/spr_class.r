##
# spr_class.r
# Copyright (C) Jonathan Bramble 2011
# 
# FBF-Optics is free software: you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by the
# Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# FBF-Optics is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
# See the GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License along
# with this program.  If not, see <http://www.gnu.org/licenses/>.
#

#' An S4 class to represent a SPR experiment.
#'
#' @slot points The number of data points
#' @slot lambda Wavelength of light
#' @slot n_entry Refractive index of the entry medium, eg a Prism
#' @slot n_exit Refractive index of the exit medium
#' @slot start_angle Exterior starting angle in degrees
#' @slot end_angle Exterior ending angle in degrees
#' 
SPR <- setClass("SPR", 
         representation(
           points="numeric",
           lambda="numeric",
           n_entry="numeric",
           n_exit="numeric",
           start_angle="numeric",
           end_angle="numeric",
           layers = "list"
           ),
         prototype(points=1000,lambda=633e-9,n_entry=1.85,n_exit=1.33,start_angle=45,end_angle=60)
)

validitySPR <- function(object){
  ## add real tests here
  TRUE
}

setValidity("SPR",validitySPR)

setGeneric("run", function(object) {
  standardGeneric("run")
})

setGeneric("sprmin", function(object) {
  standardGeneric("sprmin")
})

setGeneric("rppval", function(e1,e2) {
  standardGeneric("rppval")
})

setMethod("rppval",signature(e1="SPR",e2="numeric"),function(e1,e2){
  Rpp<-S4sprval(e1,e2)
  return(Rpp)
})

setMethod("run",signature(object="SPR"),function(object){
  Rpp<-S4spr(object)
  int_angle <- seq(length=object@points,from=object@start_angle,to=object@end_angle)
  dat <- cbind(int_angle,Rpp)
  return(dat)
})

setMethod("sprmin",signature(object="SPR"),function(object){
  Rpp<-S4sprmin(object)
  return(Rpp)
})

setMethod("initialize",signature="SPR",function(.Object){
  value <- callNextMethod()
  validObject(value) 
  value
})

setMethod("show", signature(object="SPR"), function(object){
  cat(" SPR base data \n")   
  cat(" Number of data points:", object@points , "\n")
  cat(" Wavelength:", object@lambda , "\n")
  cat(" Starting Angle:", object@start_angle , "\n")
  cat(" Ending Angle:", object@end_angle , "\n")
  cat(" Entry Medium Index:", object@n_entry , "\n")
  cat(" Exit Medium Index:", object@n_exit , "\n")
})

setMethod("+", signature(e1="SPR",e2="IsoLayer"), function(e1,e2){
  e1@layers <- c(e1@layers,e2)
  structure(e1,class="SPR")
})
