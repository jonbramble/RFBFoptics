
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
         prototype(points=100,lambda=633e-9,n_entry=1.85,n_exit=1.33,start_angle=10,end_angle=90)
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
  Rpp <-spr(object@points,object@lambda,object@n_entry,object@n_exit,object@start_angle,object@end_angle,object@layers)
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