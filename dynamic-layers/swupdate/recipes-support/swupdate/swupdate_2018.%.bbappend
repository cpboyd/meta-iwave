FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += " \
	file://0001-remove-background.patch \
"

do_install_append() {
	# Remove background image
	rm -f ${D}/www/images/background.jpg
}