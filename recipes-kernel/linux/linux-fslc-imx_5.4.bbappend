# Copyright (C) 2020 Christopher Boyd

FILESEXTRAPATHS_prepend := "${THISDIR}/linux-imx:"

SRC_URI += " \
	file://0001-nxp-flexcan.patch \
	file://0001-iwave-linux.patch \
"