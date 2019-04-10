require u-boot-common_${PV}.inc
require recipes-bsp/u-boot/u-boot.inc

SUMMARY = "U-Boot provided by NXP with focus on i.MX reference boards."

inherit fsl-u-boot-localversion

LOCALVERSION ?= "-${SRCBRANCH}"

PROVIDES += "u-boot"

PACKAGE_ARCH = "${MACHINE_ARCH}"
COMPATIBLE_MACHINE = "(imx6qdl-iwg15-sm)"
