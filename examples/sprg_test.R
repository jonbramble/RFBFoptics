library(FBFoptics)

sprg <- SPRG()  #setup an SPR simulations
points(sprg) <- 5000
end_angle(sprg) <- 90
n_exit(sprg) <- 1.33