
##
##    List of Installs.
##

package_includedir      =  ${includedir}/${INCPKG_DIR_NAME}
package_libdir          =  ${libdir}

module_includedir       =  ${package_includedir}/${MODULE_DIR_NAME}
module_libdir           =  ${package_libdir}/${MODULE_DIR_NAME}

module_include_HEADERS  =  ${INCLIB_HEADER_FILES}
module_lib_HEADERS      =  ${LIBRARY_INSTALL_SRCFILES}
module_lib_LTLIBRARIES  =  ${SHARED_LIBRARIES_LIST}
module_lib_LIBRARIES    =  ${STATIC_LIBRARIES_LIST}

dist_noinst_DATA        =  ${DIST_NOINST_DATA_FILES}
dist_noinst_HEADERS     =  ${DIST_NOINST_HEADER_FILES}

##
##    List of (No Dist) Installs.
##

nodist_module_include_HEADERS   =  ${INCLIB_NODIST_HEADER_FILES}

