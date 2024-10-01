#!/usr/bin/bash
#
#   lto.sh - Specify flags for building a package with link-time
#            optimisation
#
#   Copyright (c) 2021 Pacman Development Team <pacman-dev@archlinux.org>
#
#   This program is free software; you can redistribute it and/or modify
#   it under the terms of the GNU General Public License as published by
#   the Free Software Foundation; either version 2 of the License, or
#   (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#   but WITHOUT ANY WARRANTY; without even the implied warranty of
#   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#   GNU General Public License for more details.
#
#   You should have received a copy of the GNU General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
#

[[ -n "$LIBMAKEPKG_BUILDENV_LTO_SH" ]] && return
LIBMAKEPKG_BUILDENV_LTO_SH=1

LIBRARY=${LIBRARY:-"${PSPDEV}/share/makepkg"}

source "$LIBRARY/util/option.sh"

build_options+=('lto')
buildenv_functions+=('buildenv_lto')

buildenv_lto() {
	if check_option "lto" "y"; then
		CFLAGS+=" -flto"
		CXXFLAGS+=" -flto"
	fi
}
