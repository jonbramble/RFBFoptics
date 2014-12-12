library(FBFoptics)
library(microbenchmark)
source('~/Programming/R/RFBFoptics/R/layer_class.r')
source('~/Programming/R/RFBFoptics/R/spr_class.r')

s <- SPR()  #setup an SPR simulations
s@points = 5000
s@end_angle=60

#create some isotropic layers
au <- IsoLayer(d=49e-9,eps=-11+1.01i)
sam <- IsoLayer(d=2e-9,eps=1.45+0i)

# simply add up those layers, starting with the SPR system

l <- s + au + sam
microbenchmark(
x <- run(l)
)

microbenchmark(
v <- rppval(l,52)
)

print(v)
#plot results
plot(x[,1],x[,2],type="l",xlab="Angle",ylab="rpp")





