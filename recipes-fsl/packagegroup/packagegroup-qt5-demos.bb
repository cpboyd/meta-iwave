# Copyright (C) 2014 Freescale Semiconductor
# Released under the MIT license (see COPYING.MIT for the terms)

DESCRIPTION = "Package group for Qt5 demos"
LICENSE = "MIT"

inherit packagegroup

RDEPENDS_${PN} += " \
    qtbase-examples \
    qtdeclarative-examples \
    qtsmarthome \
    qt5ledscreen \
    quitbattery \
    qt5everywheredemo \
    qt5nmapcarousedemo \
    qt5nmapper \
    cinematicexperience \
    quitindicators \
    qt5-demo-extrafiles \
"

RDEPENDS_${PN}_append_imxgpu3d = " \
    qt3d-examples \
"

RDEPENDS_${PN}_remove = " \
    qtbase-examples \
    qtdeclarative-examples \
    qt3d-examples \
"