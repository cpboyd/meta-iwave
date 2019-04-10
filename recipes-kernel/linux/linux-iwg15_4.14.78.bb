# Copyright (C) 2013-2016 Freescale Semiconductor
# Copyright 2017-2018 NXP
# Copyright 2018 (C) O.S. Systems Software LTDA.
# Released under the MIT license (see COPYING.MIT for the terms)

SUMMARY = "Linux Kernel provided and supported by NXP"
DESCRIPTION = "Linux Kernel provided and supported by NXP with focus on \
i.MX Family Reference Boards. It includes support for many IPs such as GPU, VPU and IPU."

require recipes-kernel/linux/linux-imx.inc

DEPENDS += "lzop-native bc-native"

KERNEL_SRC ?= "git://source.codeaurora.org/external/imx/linux-imx;protocol=https"
SRCBRANCH = "imx_4.14.78_1.0.0_ga"
LOCALVERSION = "-${SRCBRANCH}"
SRCREV = "94da7bdc489ba686d868bcf80678a37cae22673e"
SRC_URI = "${KERNEL_SRC};branch=${SRCBRANCH} \
	file://dts/imx6dls-iwg15m-sm_ldoactive.dts \
	file://dts/imx6dls-iwg15m-sm_ldobypass.dts \
	file://dts/imx6qd-iwg15m-sm_ldoactive.dts \
	file://dts/imx6qd-iwg15m-sm_ldobypass.dts \
	file://dts/imx6qdl-iwg15m-sm.dtsi \
	file://0001-iwave-linux_${PV}.patch \
	file://defconfig \
"

do_configure_prepend() {
	# install device tree files
	install -m 0644 ${WORKDIR}/dts/* ${S}/arch/arm/boot/dts
}

DEFAULT_PREFERENCE = "1"

# Pull in the devicetree files into the rootfs
RDEPENDS_${KERNEL_PACKAGE_NAME}-base += "kernel-devicetree"

COMPATIBLE_MACHINE = "(mx6|mx7|mx8)"
