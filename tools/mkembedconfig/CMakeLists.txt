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

add_executable(mkembedconfig mkembedconfig.c)

set_target_properties (
  mkembedconfig PROPERTIES
  FOLDER Bin
)

macro(MKEMBEDCONFIG_TARGET EmbedInput EmbedOutput)
    add_custom_command(
        OUTPUT ${EmbedOutput}
        COMMAND mkembedconfig
        ARGS ${EmbedInput} ${CMAKE_CURRENT_BINARY_DIR}/${EmbedOutput}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
        DEPENDS mkembedconfig ${EmbedInput}
    )
endmacro()

