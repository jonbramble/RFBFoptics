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
  
## Define the SPR class ##

setClass("SPR", 
         representation(
           points="numeric",
           lambda="numeric",
           n_entry="numeric",
           n_exit="numeric",
           start_angle="numeric",
           end_angle="numeric",
           layers = "list"
           ),
         prototype(points=1000,lambda=633e-9,n_entry=1.85,n_exit=1.33,start_angle=10,end_angle=90)
)

validitySPR <- function(object){
  ## add real tests here
  TRUE
}

setValidity("SPR",validitySPR)

setGeneric("run", function(object) {
  standardGeneric("run")
})

setMethod("run",signature(object="SPR"),function(object){
  Rpp<-S4spr(object)
  int_angle <- seq(length=object@points,from=object@start_angle,to=object@end_angle)
  dat <- cbind(int_angle,Rpp)
  return(dat)
})

setMethod("initialize",signature="SPR",function(.Object){
  value <- callNextMethod()
  validObject(value) 
  value
})

setMethod("show", signature(object="SPR"), function(object){
  cat(" SPR base data \n")   
  cat(" Number of data points:", object@points , "\n")
})

setMethod("+", signature(e1="SPR",e2="Layer"), function(e1,e2){
  e1@layers <- c(e1@layers,e2)
  structure(e1,class="SPR")
})