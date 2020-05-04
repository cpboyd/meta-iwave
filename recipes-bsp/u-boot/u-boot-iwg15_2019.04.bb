# Copyright (C) 2013-2016 Freescale Semiconductor
# Copyright 2018 (C) O.S. Systems Software LTDA.
# Copyright 2017-2019 NXP

require recipes-bsp/u-boot/u-boot.inc
require u-boot-common.inc

SRC_URI += "file://0001-Add-target-to-generate-initial-environment.patch"

PROVIDES += "u-boot"

PACKAGE_ARCH = "${MACHINE_ARCH}"
COMPATIBLE_MACHINE = "(imx6qdl-iwg15-sm)"
