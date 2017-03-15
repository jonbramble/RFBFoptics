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

#' An S4 class to represent a SPR experiment over a range of thicknesses for one layer.
#' 
#'
#' @slot lambda Wavelength of light
#' @slot n_entry Refractive index of the entry medium, eg a Prism
#' @slot angle Exterior angle in degrees
#' @slot n_exit Refractive index of the exit medium
#' 
SPRD <- setClass("SPRD", 
                 slots=c(
                   points="numeric",
                   lambda="numeric",
                   n_entry="numeric",
                   n_exit="numeric",
                   angle="numeric",
                   layers="list"
                 ),
                 prototype = list(lambda=633e-9,n_entry=1.85,n_exit=1.33,angle=50)
)

#' An S4 class to represent a SPR experiment over a range of angles.
#' G represents an angular variation to produce the classic spr curve
#'
#' @slot points The number of data points
#' @slot lambda Wavelength of light
#' @slot n_entry Refractive index of the entry medium, eg a Prism
#' @slot n_exit Refractive index of the exit medium
#' @slot start_angle Exterior starting angle in degrees
#' @slot end_angle Exterior ending angle in degrees
#' 
SPRG <- setClass("SPRG", 
                 representation(
                   points="numeric",
                   lambda="numeric",
                   n_entry="numeric",
                   n_exit="numeric",
                   start_angle="numeric",
                   end_angle="numeric",
                   layers="list"
                 ),
                 prototype(points=100,lambda=633e-9,n_entry=1.78,n_exit=1.33,start_angle=45,end_angle=60)
)

#' An S4 class to represent a SPR experiment over a range of thicknesses for one layer.
#' 
#'
#' @slot lambda Wavelength of light
#' @slot n_entry Refractive index of the entry medium, eg a Prism
#' @slot angle Exterior angle in degrees
#' @slot n_exit Refractive index of the exit medium
#' @slot polariser Input polariser angle
#' @slot modulator Input modulator angle
#' @slot analyser Exit polariser angle
#' @slot mod_amplitude amount of amplitude modulation applied to the input
#' @slot layers A list of n isotropic layers representing the optical stack
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
                 prototype(lambda=633e-9,n_entry=1.78,n_exit=1.33,angle=50,polariser=30,modulator=30,analyser=172,mod_amplitude=1)
)

SPRAN <- setClass("SPRAN",
                 slots = c(
                   points="numeric",
                   lambda="numeric",
                   n_entry="numeric",
                   n_exit="numeric",
                   angle="numeric",
                   polariser="numeric",
                   modulator="numeric",
                   analyser="numeric",
                   mod_amplitude="numeric",
                   layers="list",
                   anisolayer="AnisoLayer"     
                  ),
                 contains = "AnisoLayer"
)

validitySPR <- function(object){
  retval <- NULL
  if(object@angle > 90) {
    retval <- c(retval,"angle is greater than 90")
  }
  if ( is.null(retval)) return (TRUE)
  else return ( retval )
}

validitySPRG <- function(object){
  ## add real tests here - what can we check? n_entry > n_exit? end_angle > start_angle, end angle < 90
  retval <- NULL
  if(object@end_angle > 90) {
    retval <- c(retval,"end angle is greater than 90")
  }
  if ( is.null(retval)) return (TRUE)
  else return ( retval )
}

validitySPRD <- function(object){
  ## add real tests here - what can we check? n_entry > n_exit? end_angle > start_angle, end angle < 90
  retval <- NULL
  if(object@angle > 90) {
    retval <- c(retval,"end angle is greater than 90")
  }
  if ( is.null(retval)) return (TRUE)
  else return ( retval )
}


setValidity("SPR",validitySPR)
setValidity("SPRD",validitySPRD)
setValidity("SPRG",validitySPRG)
setValidity("SPRI",validitySPR)

#setters
setGeneric("points<-",function(x,value) standardGeneric("points<-"))
setGeneric("angle<-",function(x,value) standardGeneric("angle<-"))
setGeneric("n_entry<-",function(x,value) standardGeneric("n_entry<-"))
setGeneric("n_exit<-",function(x,value) standardGeneric("n_exit<-"))
setGeneric("start_angle<-",function(x,value) standardGeneric("start_angle<-"))
setGeneric("end_angle<-",function(x,value) standardGeneric("end_angle<-"))
setGeneric("lambda<-",function(x,value) standardGeneric("lambda<-"))
setGeneric("polariser<-",function(x,value) standardGeneric("polariser<-"))
setGeneric("analyser<-",function(x,value) standardGeneric("analyser<-"))
setGeneric("mod_amplitude<-",function(x,value) standardGeneric("mod_amplitude<-"))
setGeneric("modulator<-",function(x,value) standardGeneric("modulator<-"))
setGeneric("run", function(object) {standardGeneric("run")})

setReplaceMethod("points","SPR", function(x,value) {x@points <- value; validObject(x); x})
setReplaceMethod("angle","SPR", function(x,value) {x@angle <- value; validObject(x); x})
setReplaceMethod("n_entry","SPR", function(x,value) {x@n_entry <- value; validObject(x); x})
setReplaceMethod("n_exit","SPR", function(x,value) {x@n_exit <- value; validObject(x); x})
setReplaceMethod("lambda","SPR", function(x,value) {x@lambda <- value; validObject(x); x})

setReplaceMethod("points","SPRD", function(x,value) {x@points <- value; validObject(x); x})
setReplaceMethod("angle","SPRD", function(x,value) {x@angle <- value; validObject(x); x})
setReplaceMethod("n_entry","SPRD", function(x,value) {x@n_entry <- value; validObject(x); x})
setReplaceMethod("n_exit","SPRD", function(x,value) {x@n_exit <- value; validObject(x); x})
setReplaceMethod("lambda","SPRD", function(x,value) {x@lambda <- value; validObject(x); x})

setReplaceMethod("points","SPRG", function(x,value) {x@points <- value; validObject(x); x})
setReplaceMethod("start_angle","SPRG", function(x,value) {x@start_angle <- value; validObject(x); x})
setReplaceMethod("end_angle","SPRG", function(x,value) {x@end_angle <- value; validObject(x); x})
setReplaceMethod("n_entry","SPRG", function(x,value) {x@n_entry <- value; validObject(x); x})
setReplaceMethod("n_exit","SPRG", function(x,value) {x@n_exit <- value; validObject(x); x})
setReplaceMethod("lambda","SPRG", function(x,value) {x@lambda <- value; validObject(x); x})

setReplaceMethod("points","SPRI", function(x,value) {x@points <- value; validObject(x); x})
setReplaceMethod("angle","SPRI", function(x,value) {x@angle <- value; validObject(x); x})
setReplaceMethod("n_entry","SPRI", function(x,value) {x@n_entry <- value; validObject(x); x})
setReplaceMethod("n_exit","SPRI", function(x,value) {x@n_exit <- value; validObject(x); x})
setReplaceMethod("lambda","SPRI", function(x,value) {x@lambda <- value; validObject(x); x})
setReplaceMethod("polariser","SPRI", function(x,value) {x@polariser <- value; validObject(x); x})
setReplaceMethod("analyser","SPRI", function(x,value) {x@analyser <- value; validObject(x); x})
setReplaceMethod("mod_amplitude","SPRI", function(x,value) {x@mod_amplitude <- value; validObject(x); x})
setReplaceMethod("modulator","SPRI", function(x,value) {x@modulator <- value; validObject(x); x})


setGeneric("curve", function(object) {standardGeneric("curve")})
setGeneric("sprmin", function(object){standardGeneric("sprmin")})
setGeneric("rppval", function(e1,e2) {standardGeneric("rppval")})
setGeneric("delta", function(stack,angle) {standardGeneric("delta")})

setMethod("rppval",signature(e1="SPR",e2="numeric"),function(e1,e2){
  Rpp<-S4_SPRVAL(e1,e2)
  return(Rpp)
})

setMethod("delta",signature(stack="SPR",angle="numeric"),function(stack,angle){
  Delta<-S4_DELTAVAL(stack,angle)
  return(Delta)
})

setMethod("sprmin",signature(object="SPR"),function(object){
  Rpp<-S4_SPRMIN(object)
  return(Rpp)
})

setMethod("sprmin",signature(object="SPRG"),function(object){
  Rpp<-S4_SPRMIN(object)
  return(Rpp)
})

setMethod("curve",signature(object="SPRD"),function(object){
  Rpp<-S4_SPRD(object)
  return(Rpp)
})

setMethod("curve",signature(object="SPRG"),function(object){
  Rpp<-S4_SPRG(object)
  int_angle <- seq(length=object@points,from=object@start_angle,to=object@end_angle)
  dat <- cbind(int_angle,Rpp)
  return(dat)
})

setMethod("curve",signature(object="SPRG"),function(object){
  Rpp<-S4_SPRG(object)
  int_angle <- seq(length=object@points,from=object@start_angle,to=object@end_angle)
  dat <- cbind(int_angle,Rpp)
  return(dat)
})

setMethod("run",signature(object="SPRI"),function(object){
  Rpp<-S4_SPRI(object)
  return(Rpp)
})

setMethod("show", signature(object="SPR"), function(object){
  cat(" SPR base data \n")   
  cat(" Wavelength:", object@lambda , "\n")
  cat(" Angle:", object@angle , "\n")
  cat(" Entry Medium Index:", object@n_entry , "\n")
  cat(" Exit Medium Index:", object@n_exit , "\n")
})

setMethod("show", signature(object="SPRD"), function(object){
  cat(" SPRD base data \n")   
  cat(" Number of data points:", object@points , "\n")
  cat(" Wavelength:", object@lambda , "\n")
  cat(" Angle:", object@angle , "\n")
  cat(" Entry Medium Index:", object@n_entry , "\n")
  cat(" Exit Medium Index:", object@n_exit , "\n")
})

setMethod("show", signature(object="SPRG"), function(object){
  cat(" SPRG base data \n")   
  cat(" Number of data points:", object@points , "\n")
  cat(" Wavelength:", object@lambda , "\n")
  cat(" Starting Angle:", object@start_angle , "\n")
  cat(" Ending Angle:", object@end_angle , "\n")
  cat(" Entry Medium Index:", object@n_entry , "\n")
  cat(" Exit Medium Index:", object@n_exit , "\n")
})

setMethod("show", signature(object="SPRI"), function(object){
  cat(" SPRI base data \n")   
  cat(" Number of data points:", object@points , "\n")
  cat(" Wavelength:", object@lambda , "\n")
  cat(" Angle:", object@angle , "\n")
  cat(" Entry Medium Index:", object@n_entry , "\n")
  cat(" Exit Medium Index:", object@n_exit , "\n")
})


setMethod("+", signature(e1="SPR",e2="IsoLayer"), function(e1,e2){
  e1@layers <- c(e1@layers,e2)
  structure(e1,class="SPR")
})

setMethod("+", signature(e1="SPRD",e2="IsoLayer"), function(e1,e2){
  e1@layers <- c(e1@layers,e2)
  structure(e1,class="SPRD")
})

setMethod("+", signature(e1="SPRG",e2="IsoLayer"), function(e1,e2){
  e1@layers <- c(e1@layers,e2)
  structure(e1,class="SPRG")
})

setMethod("+", signature(e1="SPRI",e2="IsoLayer"), function(e1,e2){
  e1@layers <- c(e1@layers,e2)
  structure(e1,class="SPRI")
})

setMethod("+", signature(e1="SPRAN",e2="IsoLayer"),function(e1,e2){
  e1@layers <- c(e1@layers,e2)
  structure(e1,class="SPRAN")
})

setMethod("+", signature(e1="SPRAN",e2="AnisoLayer"),function(e1,e2){
  e1@anisolayer <- e2
  structure(e1,class="SPRAN")
})
