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

#' An S4 class to represent a SPR experiment for a single angle point.
#' 
#'
#' @slot lambda Wavelength of light
#' @slot n_entry Refractive index of the entry medium, eg a Prism
#' @slot n_exit Refractive index of the exit medium
#' @slot angle Exterior angle in degrees
#' 
SPR <- setClass("SPR", 
                representation(
                  lambda="numeric",
                  n_entry="numeric",
                  n_exit="numeric",
                  angle="numeric",
                  layers="list"
                ),
                prototype(lambda=633e-9,n_entry=1.85,n_exit=1.33,angle=55)
)

validitySPR <- function(object){
  retval <- NULL
  if(object@angle > 90) {
    retval <- c(retval,"angle is greater than 90")
  }
  if ( is.null(retval)) return (TRUE)
  else return ( retval )
}

setValidity("SPR",validitySPR)

#setters
setGeneric("points<-",function(x,value) standardGeneric("points<-"))
setGeneric("angle<-",function(x,value) standardGeneric("angle<-"))
setGeneric("n_entry<-",function(x,value) standardGeneric("n_entry<-"))
setGeneric("n_exit<-",function(x,value) standardGeneric("n_exit<-"))
setGeneric("lambda<-",function(x,value) standardGeneric("lambda<-"))

setReplaceMethod("points","SPR", function(x,value) {x@points <- value; validObject(x); x})
setReplaceMethod("angle","SPR", function(x,value) {x@angle <- value; validObject(x); x})
setReplaceMethod("n_entry","SPR", function(x,value) {x@n_entry <- value; validObject(x); x})
setReplaceMethod("n_exit","SPR", function(x,value) {x@n_exit <- value; validObject(x); x})
setReplaceMethod("lambda","SPR", function(x,value) {x@lambda <- value; validObject(x); x})

setGeneric("curve", function(object) {standardGeneric("curve")})
setGeneric("sprmin", function(object){standardGeneric("sprmin")})
setGeneric("rppval", function(e1,e2) {standardGeneric("rppval")})

setMethod("rppval",signature(e1="SPR",e2="numeric"),function(e1,e2){
  Rpp<-S4_SPRVAL(e1,e2)
  return(Rpp)
})

setMethod("sprmin",signature(object="SPR"),function(object){
  Rpp<-S4_SPRMIN(object)
  return(Rpp)
})

setMethod("initialize",signature="SPR",function(.Object){
  value <- callNextMethod()
  validObject(value) 
  value
})

setMethod("show", signature(object="IsoLayer"),function(object){
  cat(" Isotropic Layer data \n")
})

setMethod("show", signature(object="SPR"), function(object){
  cat(" SPR base data \n")   
  cat(" Wavelength:", object@lambda , "\n")
  cat(" Angle:", object@angle , "\n")
  cat(" Entry Medium Index:", object@n_entry , "\n")
  cat(" Exit Medium Index:", object@n_exit , "\n")
})

setMethod("+", signature(e1="SPR",e2="IsoLayer"), function(e1,e2){
  e1@layers <- c(e1@layers,e2)
  structure(e1,class="SPR")
})
