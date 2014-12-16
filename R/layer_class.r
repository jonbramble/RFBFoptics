##
# layer_class.r
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

#' An S4 class to represent a thin dielectric or metallic layer.
#'
#' @slot d Thickness of the layer in m
#' @slot eps The relative permittivity of the material as a complex number
#' 

IsoLayer <- setClass("IsoLayer", 
         representation(
           d="numeric",
           eps="complex"
         )
)

#' An S4 class to represent anisotropic layer.
#'
#' @slot d Thickness of the layer in m
#' @slot epsx The relative permittivity of the material in the x direction
#' @slot epsy The relative permittivity of the material in the y direction
#' @slot epsz The relative permittivity of the material in the z direction
#' @slot theta angle of the molecular axis in relation to the prism axis - see diagram
#' @slot phi angle of the molecular axis in relation to the prism axis - see diagram
#' 

AnIsoLayer <- setClass("AnIsoLayer", 
                     representation(
                       d="numeric",
                       epsx="numeric",
                       epsy="numeric",
                       epsz="numeric",
                       theta="numeric",
                       phi="numeric"
                     )
)

#' An S4 class to represent a thin dielectric or metallic layer.
#'
#' @slot d Thickness of the layer in m
#' @slot eps The relative permittivity of the material as a complex number
#' 

DIsoLayer <- setClass("DIsoLayer", 
                     representation(
                       dstart="numeric",
                       dend="numeric",
                       eps="complex"
                     )
)
