library(FBFoptics)
library(ggplot2)

#create some isotropic layers
au <- IsoLayer(d=50e-9,eps=-11+1.01i)
dopc <- IsoLayer(d=5e-9,eps=1.450^2+0i)
popc <- IsoLayer(d=5e-9,eps=1.470^2+0i)
sm <- IsoLayer(d=5e-9,eps=1.525^2+0i)
spri <- SPRI(n_entry=1.78, points=1000)

sprg <- SPRG(n_entry=1.78,n_exit=1.34, points=1000) 
stack_spr <- sprg + au + popc
#print(min_angle)

#spr_curve_df <- data.frame(curve(stack_spr))
#sprg_plot <- ggplot(spr_curve_df, aes(x=int_angle,y=Rpp))
#sprg_plot + geom_line() + xlab("Internal Angle") + ylab("Rpp") + theme_minimal()

spri_n <- function(n,p,a) {
  mod_amplitude(spri) <- 2.405
  n_exit(spri) <- 1.33
  angle(spri) <- 55.2
  polariser(spri) <- p
  analyser(spri) <- a
  lipid <- IsoLayer(d=5e-9,eps=(n^2)+0i)
  stack_spri <- spri + au + lipid
  m <- run(stack_spri)[4]
}

step = 0.001
n_exit_seq = seq(1.35,1.55,by=step)

an <- 167

md_n_exit <- sapply(n_exit_seq,spri_n,20,an)
n_exit_df_20=data.frame(n_exit_seq,md_n_exit)
n_exit_df_20$Polariser = 20

md_n_exit <- sapply(n_exit_seq,spri_n,30,an)
n_exit_df_30=data.frame(n_exit_seq,md_n_exit)
n_exit_df_30$Polariser = 30

md_n_exit <- sapply(n_exit_seq,spri_n,40,an)
n_exit_df_40=data.frame(n_exit_seq,md_n_exit)
n_exit_df_40$Polariser = 40

md_n_exit <- sapply(n_exit_seq,spri_n,50,an)
n_exit_df_50=data.frame(n_exit_seq,md_n_exit)
n_exit_df_50$Polariser = 50

md_n_exit <- sapply(n_exit_seq,spri_n,60,an)
n_exit_df_60=data.frame(n_exit_seq,md_n_exit)
n_exit_df_60$Polariser = 60

md_n_exit <- sapply(n_exit_seq,spri_n,70,an)
n_exit_df_70=data.frame(n_exit_seq,md_n_exit)
n_exit_df_70$Polariser = 70

md_n_exit <- sapply(n_exit_seq,spri_n,80,an)
n_exit_df_80=data.frame(n_exit_seq,md_n_exit)
n_exit_df_80$Polariser = 80


n_exit_all <- rbind(n_exit_df_20, n_exit_df_30,n_exit_df_40,n_exit_df_50,n_exit_df_60,n_exit_df_70,n_exit_df_80)

n_exit_plot <- ggplot(n_exit_all, aes(x=n_exit_seq,y=md_n_exit, color=factor(Polariser), group=Polariser))
n_exit_plot + geom_line() + xlab("Lipid Refractive Index ") +ylim(0,1.2) + ylab("Modulation Responsivity") + scale_color_discrete(name="Polariser\nAngle") + theme_minimal(base_size=22)


p <- 45

md_n_exit <- sapply(n_exit_seq,spri_n,p,140)
n_exit_df_a_140=data.frame(n_exit_seq,md_n_exit)
n_exit_df_a_140$Analyser = 140

md_n_exit <- sapply(n_exit_seq,spri_n,p,150)
n_exit_df_a_150=data.frame(n_exit_seq,md_n_exit)
n_exit_df_a_150$Analyser = 150

md_n_exit <- sapply(n_exit_seq,spri_n,p,160)
n_exit_df_a_160=data.frame(n_exit_seq,md_n_exit)
n_exit_df_a_160$Analyser = 160

md_n_exit <- sapply(n_exit_seq,spri_n,p,170)
n_exit_df_a_170=data.frame(n_exit_seq,md_n_exit)
n_exit_df_a_170$Analyser = 170

md_n_exit <- sapply(n_exit_seq,spri_n,p,185)
n_exit_df_a_185=data.frame(n_exit_seq,md_n_exit)
n_exit_df_a_185$Analyser = 185

n_exit_a_all <- rbind(n_exit_df_a_140,n_exit_df_a_150,n_exit_df_a_160,n_exit_df_a_170,n_exit_df_a_185)
n_exit_plot <- ggplot(n_exit_a_all, aes(x=n_exit_seq,y=md_n_exit, color=Analyser, group=Analyser))
n_exit_plot + geom_line() + xlab("Lipid Refractive Index ") + ylim(0,1.5) +ylab("Modulation Responsivity") + theme_minimal(base_size=22)


