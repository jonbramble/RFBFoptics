##
# sprd_class.r
# Copyright (C) Jonathan Bramble 2014
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
SPRD <- setClass("SPRD", 
                 representation(
                   points="numeric",
                   lambda="numeric",
                   n_entry="numeric",
                   n_exit="numeric",
                   angle="numeric",
                   layers="list"
                 ),
                 prototype(lambda=633e-9,n_entry=1.85,n_exit=1.33,angle=50)
)

validitySPRD <- function(object){
  ## add real tests here - what can we check? n_entry > n_exit? end_angle > start_angle, end angle < 90
  retval <- NULL
  if(object@angle > 90) {
    retval <- c(retval,"end angle is greater than 90")
  }
  if ( is.null(retval)) return (TRUE)
  else return ( retval )
}

setValidity("SPRD",validitySPRD)

#setters
setGeneric("points<-",function(x,value) standardGeneric("points<-"))
setGeneric("angle<-",function(x,value) standardGeneric("angle<-"))
setGeneric("n_entry<-",function(x,value) standardGeneric("n_entry<-"))
setGeneric("n_exit<-",function(x,value) standardGeneric("n_exit<-"))
setGeneric("lambda<-",function(x,value) standardGeneric("lambda<-"))

setReplaceMethod("points","SPRD", function(x,value) {x@points <- value; validObject(x); x})
setReplaceMethod("angle","SPRD", function(x,value) {x@angle <- value; validObject(x); x})
setReplaceMethod("n_entry","SPRD", function(x,value) {x@n_entry <- value; validObject(x); x})
setReplaceMethod("n_exit","SPRD", function(x,value) {x@n_exit <- value; validObject(x); x})
setReplaceMethod("lambda","SPRD", function(x,value) {x@lambda <- value; validObject(x); x})

setMethod("curve",signature(object="SPRD"),function(object){
  Rpp<-S4_SPRD(object)
  #d_array <- seq(length=object@points,from=object@dstart,to=object@dend)
  #dat <- cbind(d_array,Rpp)
  return(Rpp)
})

setMethod("initialize",signature="SPRD",function(.Object){
  value <- callNextMethod()
  validObject(value) 
  value
})

setMethod("show", signature(object="SPRD"), function(object){
  cat(" SPR base data \n")   
  cat(" Number of data points:", object@points , "\n")
  cat(" Wavelength:", object@lambda , "\n")
  cat(" Angle:", object@angle , "\n")
  cat(" Entry Medium Index:", object@n_entry , "\n")
  cat(" Exit Medium Index:", object@n_exit , "\n")
})

setMethod("+", signature(e1="SPRD",e2="IsoLayer"), function(e1,e2){
  e1@layers <- c(e1@layers,e2)
  structure(e1,class="SPRD")
})