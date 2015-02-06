##
# spri_class.r
# Copyright (C) Jonathan Bramble 2015
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

#' An S4 class to represent a SPR experiment over a range of thicknesses for one layer.
#' 
#'
#' @slot lambda Wavelength of light
#' @slot n_entry Refractive index of the entry medium, eg a Prism
#' @slot angle Exterior angle in degrees
#' @slot n_exit Refractive index of the exit medium
#' 
SPRI <- setClass("SPRI", 
                 representation(
                   points="numeric",
                   lambda="numeric",
                   n_entry="numeric",
                   n_exit="numeric",
                   angle="numeric",
                   polariser="numeric",
                   modulator="numeric",
                   analyser="numeric",
                   mod_amplitude="numeric",
                   layers="list"
                 ),
                 prototype(lambda=633e-9,n_entry=1.85,n_exit=1.33,angle=50,polariser=0,modulator=0,analyser=0,mod_amplitude=0)
)

validitySPRI <- function(object){
  ## add real tests here - what can we check? n_entry > n_exit? end_angle > start_angle, end angle < 90
  retval <- NULL
  if(object@angle > 90) {
    retval <- c(retval,"end angle is greater than 90")
  }
  if ( is.null(retval)) return (TRUE)
  else return ( retval )
}

setValidity("SPRI",validitySPRI)

#setters
setGeneric("points<-",function(x,value) standardGeneric("points<-"))
setGeneric("angle<-",function(x,value) standardGeneric("angle<-"))
setGeneric("n_entry<-",function(x,value) standardGeneric("n_entry<-"))
setGeneric("n_exit<-",function(x,value) standardGeneric("n_exit<-"))
setGeneric("lambda<-",function(x,value) standardGeneric("lambda<-"))
setGeneric("polariser<-",function(x,value) standardGeneric("polariser<-"))
setGeneric("analyser<-",function(x,value) standardGeneric("analyser<-"))
setGeneric("mod_amplitude<-",function(x,value) standardGeneric("mod_amplitude<-"))
setGeneric("modulator<-",function(x,value) standardGeneric("modulator<-"))
setGeneric("run", function(object) {standardGeneric("run")})

setReplaceMethod("points","SPRI", function(x,value) {x@points <- value; validObject(x); x})
setReplaceMethod("angle","SPRI", function(x,value) {x@angle <- value; validObject(x); x})
setReplaceMethod("n_entry","SPRI", function(x,value) {x@n_entry <- value; validObject(x); x})
setReplaceMethod("n_exit","SPRI", function(x,value) {x@n_exit <- value; validObject(x); x})
setReplaceMethod("lambda","SPRI", function(x,value) {x@lambda <- value; validObject(x); x})
setReplaceMethod("polariser","SPRI", function(x,value) {x@polariser <- value; validObject(x); x})
setReplaceMethod("analyser","SPRI", function(x,value) {x@analyser <- value; validObject(x); x})
setReplaceMethod("mod_amplitude","SPRI", function(x,value) {x@mod_amplitude <- value; validObject(x); x})
setReplaceMethod("modulator","SPRI", function(x,value) {x@modulator <- value; validObject(x); x})

setMethod("run",signature(object="SPRI"),function(object){
  Rpp<-S4_SPRI(object)
  return(Rpp)
})

setMethod("initialize",signature="SPRI",function(.Object){
  value <- callNextMethod()
  validObject(value) 
  value
})

setMethod("show", signature(object="SPRI"), function(object){
  cat(" SPR base data \n")   
  cat(" Number of data points:", object@points , "\n")
  cat(" Wavelength:", object@lambda , "\n")
  cat(" Angle:", object@angle , "\n")
  cat(" Entry Medium Index:", object@n_entry , "\n")
  cat(" Exit Medium Index:", object@n_exit , "\n")
})

setMethod("+", signature(e1="SPRI",e2="IsoLayer"), function(e1,e2){
  e1@layers <- c(e1@layers,e2)
  structure(e1,class="SPRI")
})