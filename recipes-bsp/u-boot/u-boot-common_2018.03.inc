HOMEPAGE = "http://www.denx.de/wiki/U-Boot/WebHome"
SECTION = "bootloaders"

LICENSE = "GPLv2+"
LIC_FILES_CHKSUM = "file://Licenses/gpl-2.0.txt;md5=b234ee4d69f5fce4486a80fdaf4a4263"
FILESEXTRAPATHS_prepend := "${THISDIR}/files:"

SRCBRANCH = "imx_v2018.03_4.14.78_1.0.0_ga"
UBOOT_SRC ?= "git://source.codeaurora.org/external/imx/uboot-imx.git;protocol=https"
SRCREV = "7ade5b407fe6164c0d07f32f72e487ae5f6f3964"
SRC_URI = "${UBOOT_SRC};branch=${SRCBRANCH} \
		file://0001-iwave_${PV}.patch"

S = "${WORKDIR}/git"
