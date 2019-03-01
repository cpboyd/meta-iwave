HOMEPAGE = "http://www.denx.de/wiki/U-Boot/WebHome"
SECTION = "bootloaders"

LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://Licenses/gpl-2.0.txt;md5=b234ee4d69f5fce4486a80fdaf4a4263"
FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRCBRANCH = "nxp/imx_v2016.03_4.1.15_2.0.0_ga"
UBOOT_SRC ?= "git://source.codeaurora.org/external/imx/uboot-imx.git;protocol=https"
SRCREV = "a57b13b942d59719e3621179e98bd8a0ab235088"
SRC_URI = "${UBOOT_SRC};branch=${SRCBRANCH} \
		file://0001-iwave_${PV}.patch"

S = "${WORKDIR}/git"
