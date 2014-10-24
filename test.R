library(FBFoptics)
source('~/Programming/R/RFBFoptics/R/layer_class.r')
source('~/Programming/R/RFBFoptics/R/spr_class.r')

s <- SPR()  #setup an SPR simulations
s@points = 1000

#create some layers
au <- Layer(type="isotropic",d=49e-9,eps=-11+1.01i)
sam <- Layer(type="isotropic",d=2e-9,eps=2.1+0i)

#add up those layers
l <- s+au+sam
ptm <- proc.time()
x<-run(l)
tm <- proc.time() - ptm
tm
plot(x[,1],x[,2],type="l")




