library(FBFoptics)
source('~/Programming/R/RFBFoptics/R/layer_class.r')
source('~/Programming/R/RFBFoptics/R/spr_class.r')

s <- SPR()  #setup an SPR simulations
s@points = 10000

#create some isotropic layers
au <- IsoLayer(d=49e-9,eps=-11+1.01i)
sam <- IsoLayer(d=3e-9,eps=2.1+0i)

# simply add up those layers, starting with the SPR system
l <- s + au + sam
ptm <- proc.time()
x <- run(l)
proc.time() - ptm
#plot results
plot(x[,1],x[,2],type="l",xlab="Angle",ylab="rpp")





