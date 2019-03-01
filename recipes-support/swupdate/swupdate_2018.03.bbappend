FILESEXTRAPATHS_prepend := "${THISDIR}/${PN}:"

SRC_URI += "\
	file://0001-Update-index.html-Fixed-typos-and-improved-text.patch \
	file://0001-remove-background.patch \
	file://0001-web-app-remove-limit-on-fileSize-for-dropzone.patch \
"

do_install_append() {
    # Remove background image
    rm -f ${D}/www/images/background.jpg
}