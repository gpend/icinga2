# Icinga 2
# Copyright (C) 2012-2013 Icinga Development Team (http://www.icinga.org/)
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software Foundation
# Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA.

mkclass_target(checkresultreader.ti checkresultreader.th)
mkclass_target(compatlogger.ti compatlogger.th)
mkclass_target(externalcommandlistener.ti externalcommandlistener.th)
mkclass_target(statusdatawriter.ti statusdatawriter.th)

mkembedconfig_target(compat-type.conf compat-type.cpp)

add_library(compat SHARED checkresultreader.cpp checkresultreader.th compatlogger.cpp compatlogger.th externalcommandlistener.cpp externalcommandlistener.th statusdatawriter.cpp statusdatawriter.th compat-type.cpp)

target_link_libraries(compat ${Boost_LIBRARIES} base config icinga)

set_target_properties (
  compat PROPERTIES
  INSTALL_RPATH ${CMAKE_INSTALL_FULL_LIBDIR}/icinga2
  FOLDER Components
)

install(TARGETS compat RUNTIME DESTINATION ${CMAKE_INSTALL_SBINDIR} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/icinga2)

install(CODE "file(MAKE_DIRECTORY \"\$ENV{DESTDIR}${CMAKE_INSTALL_FULL_LOCALSTATEDIR}/log/icinga2/compat/archives\")")
install(CODE "file(MAKE_DIRECTORY \"\$ENV{DESTDIR}${CMAKE_INSTALL_FULL_LOCALSTATEDIR}/cache/icinga2\")")
install(CODE "file(MAKE_DIRECTORY \"\$ENV{DESTDIR}${CMAKE_INSTALL_FULL_LOCALSTATEDIR}/spool/icinga2\")")
install(CODE "file(MAKE_DIRECTORY \"\$ENV{DESTDIR}${CMAKE_INSTALL_FULL_LOCALSTATEDIR}/run/icinga2/cmd\")")

