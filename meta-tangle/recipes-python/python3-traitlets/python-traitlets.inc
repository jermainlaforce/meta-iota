# this recipe was borrowed from meta-jupyter
# it was originally written by Manjukumar H. Matha <manjukumar.harthikote-matha@xilinx.com> and Sai H. C. Kalluri <chandana.kalluri@xilinx.com>
# the original version can be found at:
# https://github.com/Xilinx/meta-jupyter

SUMMARY = "Traitlets Python config system"
LICENSE = "BSD"
LIC_FILES_CHKSUM = "file://PKG-INFO;beginline=8;endline=8;md5=e910b35b0ef4e1f665b9a75d6afb7709"

SRC_URI[md5sum] = "3068663f2f38fd939a9eb3a500ccc154"
SRC_URI[sha256sum] = "9c4bd2d267b7153df9152698efb1050a5d84982d3384a37b2c1f7723ba3e7835"

RDEPENDS_${PN} += " \
	${PYTHON_PN}-six \
	${PYTHON_PN}-decorator \
	${PYTHON_PN}-ipython-genutils \
	"

BBCLASSEXTEND = "native"
