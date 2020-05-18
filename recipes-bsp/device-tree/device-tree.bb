SUMMARY = "iWave BSP device trees"
DESCRIPTION = "iWave BSP device trees"
SECTION = "bsp"

# the device trees from within the layer are licensed as MIT, kernel includes are GPL
LICENSE = "MIT & GPLv2"
LIC_FILES_CHKSUM = " \
		file://${COMMON_LICENSE_DIR}/MIT;md5=0835ade698e0bcf8506ecda2f7b4f302 \
		file://${COMMON_LICENSE_DIR}/GPL-2.0;md5=801f80980d171dd6425610833a22dbe6 \
"

inherit devicetree

PROVIDES = "virtual/dtb"

SRC_URI_append_mx6iwave = " \
	file://imx6qdl-iwg15m-sm.dtsi \
	file://imx6dls-iwg15m-sm_ldoactive.dts \
	file://imx6dls-iwg15m-sm_ldobypass.dts \
	file://imx6qd-iwg15m-sm_ldoactive.dts \
	file://imx6qd-iwg15m-sm_ldobypass.dts \
"

# device tree sources for the various machines
COMPATIBLE_MACHINE_mx6iwave = ".*"
