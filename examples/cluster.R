step = 0.1e-9
d_seq= seq(0,20e-9,by=step)
md_d <- sapply(d_seq,spri_d)

nCores <- detectCores()
cluster <- makeCluster(nCores)

clusterExport(cluster,"spri")
clusterExport(cluster,"au")
clusterExport(cluster,"adlayer")
clusterEvalQ(cluster,library(FBFoptics))

md_d <- parSapply(cl=cluster,d_seq,FUN=spri_d)
d_df=data.frame(d_seq,md_d)

stopCluster(cluster)

max_array(angle_seq,md_angle)

d_plot <- ggplot(d_df, aes(x=d_seq,y=md_d))
d_plot + geom_line() + xlab("Thickness") + ylab("Modulation Responsivity") + theme_minimal()

md_angle_diff <- diff(md_angle)/step
angle_diff_seq = seq(54+step/2,56,by=step)
angle_diff_df=data.frame(angle_diff_seq,md_angle_diff)
max_array(angle_diff_seq,md_angle_diff)

angle_plot_diff <- ggplot(angle_diff_df, aes(x=angle_diff_seq,y=md_angle_diff))
angle_plot_diff + geom_line() + xlab("Incident Angle") + ylab("Modulation Responsivity") + theme_minimal()

step = 0.0001
n_exit_seq = seq(1.330,1.350,by=step)
md_n_exit <- sapply(n_exit_seq,spri_n)
n_exit_df=data.frame(n_exit_seq,md_n_exit)

n_exit_plot <- ggplot(n_exit_df, aes(x=n_exit_seq,y=md_n_exit))
n_exit_plot + geom_line() + xlab("Exit Refractive Index ") + ylab("Modulation Responsivity") + theme_minimal()

n_exit_diff <- diff(md_n_exit/step)  # to match paper
n_exit_diff_seq = seq(1.330+step/2,1.350,by=step)
n_exit_diff_df=data.frame(n_exit_diff_seq,n_exit_diff)

n_exit_diff_plot <- ggplot(n_exit_diff_df, aes(x=n_exit_diff_seq,y=n_exit_diff))
n_exit_diff_plot + geom_line() + xlab("Exit Refractive Index ") + ylim(c(0,1200)) + ylab("Modulation Responsivity /RIU") + theme_minimal()

## set a range of values to operator over
arange = seq(54,56,by=0.1)
prange = seq(-90,90,by=1)
anrange = seq(-10,10,by=0.1)

cluster <- makeCluster(nCores)
clusterEvalQ(cluster,library(FBFoptics))
clusterExport(cluster,"spri")
clusterExport(cluster,"au")
clusterExport(cluster,"adlayer")
clusterExport(cluster,"spri_n_pol_an")
clusterExport(cluster,"spri_pol_an_dn")

md_data <- expand.grid(prange,anrange)
ptm <- proc.time()
#output = apply(md_data, 1,function(x,y,z) spri_pol_an(55.5,x[1],x[2]) )
output = parApply(cl=cluster,md_data,1,function(x,y,z) spri_pol_an(55.5,x[1],x[2]))
proc.time() - ptm
md_data$md <- output

stopCluster(cluster)

ggplot(md_data, aes(x=Var1,y=Var2,fill=md)) + geom_raster() + 
  theme_minimal() + scale_fill_gradient2() + xlab("Polariser") + ylab("Analyser")

md_data <- expand.grid(prange,anrange)
output = parApply(cl=cluster,md_data, 1, function(x,y,z) spri_pol_an_dn(pol=x[1],an=x[2]))
md_data$md <- output
ggplot(md_data, aes(x=Var1,y=Var2,fill=md)) + geom_raster() + 
  theme_minimal() + scale_fill_gradient2() + xlab("Polariser") + ylab("Analyser")

md_data_angle <- expand.grid(arange,anrange)
polariser = -45
output = apply(md_data_angle, 1, function(x,y,z) spri_pol_an(x[1],polariser,x[2]))
md_data_angle$md <- output
ggplot(md_data_angle, aes(x=Var1,y=Var2,fill=md)) + geom_raster() + scale_fill_gradient2()  + ylab("Analyser") + xlab("Input Angle")

### OLD CALCULATIONS
#spri <- SPRI(angle=55.1,mod_amplitude=2,,n_exit=1.34,polariser=30,modulator=30,analyser=166)
#stack_spri <- spri + au
#stack_spri_dopc <- spri + au + dopc
#stack_spri_popc <- spri + au + popc
#stack_spri_sm <- spri + au + sm

#run(stack_spri)[4]
#run(stack_spri_dopc)[4]
#run(stack_spri_popc)[4]
#run(stack_spri_sm)[4]