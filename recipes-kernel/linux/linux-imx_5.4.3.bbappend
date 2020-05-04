# Copyright (C) 2020 Christopher Boyd
FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
	file://dts/imx6dls-iwg15m-sm_ldoactive.dts \
	file://dts/imx6dls-iwg15m-sm_ldobypass.dts \
	file://dts/imx6qd-iwg15m-sm_ldoactive.dts \
	file://dts/imx6qd-iwg15m-sm_ldobypass.dts \
	file://dts/imx6qdl-iwg15m-sm.dtsi \
	file://0001-nxp-flexcan.patch \
	file://0001-iwave-linux.patch \
"

do_configure_prepend() {
	# install device tree files
	install -m 0644 ${WORKDIR}/dts/* ${S}/arch/arm/boot/dts
}

# Pull in the devicetree files into the rootfs
RDEPENDS_${KERNEL_PACKAGE_NAME}-base += "kernel-devicetree"
