# Copyright (c) 2015 iWave Systems Technologies Pvt. Ltd.

DESCRIPTION = "U-Boot provided by Freescale with focus on i.MX reference boards."

inherit fsl-u-boot-localversion

LOCALVERSION ?= "-${SRCBRANCH}"

PROVIDES += "u-boot"

PACKAGE_ARCH = "${MACHINE_ARCH}"
COMPATIBLE_MACHINE = "(imx6qdl-iwg15-sm)"
