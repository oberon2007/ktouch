kde4_header()
project(ktouch)

add_subdirectory( src ) 
add_subdirectory( keyboards ) 
add_subdirectory( training ) 
add_subdirectory( sounds ) 
add_subdirectory( graphics ) 
add_subdirectory( icons ) 

include_directories( ${KDE4_INCLUDE_DIR} ${QT_INCLUDES} ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}  )


########### install files ###############

install_files( ${XDG_APPS_DIR} FILES ktouch.desktop )

kde4_create_doxygen_docs(  )

kde4_footer()



#original Makefile.am contents follow:

## This file you have to edit. Change the name here
#SUBDIRS = src keyboards training sounds graphics icons
#
## not a GNU package. You can remove this line, if
## have all needed files, that a GNU package needs
#AUTOMAKE_OPTIONS = foreign
#
## place KTouch in the start menu under edutainment
#xdg_apps_DATA = ktouch.desktop
#
#
#
#include ../admin/Doxyfile.am