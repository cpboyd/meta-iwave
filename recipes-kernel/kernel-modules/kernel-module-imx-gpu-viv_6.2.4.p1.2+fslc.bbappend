SRCBRANCH = "imx_4.1.15_2.0.0_ga"
LOCALVERSION = "-${SRCBRANCH}"

KERNEL_SRC ?= "git://source.codeaurora.org/external/imx/linux-imx.git;protocol=https"
SRCREV = "30278abfe0977b1d2f065271ce1ea23c0e2d1b6e"
SRC_URI = "${KERNEL_SRC};branch=${SRCBRANCH};subpath=drivers/mxc/gpu-viv;destsuffix=git/src"

SRC_URI += " \
    file://Add-makefile.patch \
"

EXTRA_OEMAKE += "CONFIG_MXC_GPU_VIV=m"
