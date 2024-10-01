#!/usr/bin/bash
#
#   local.sh - function for handling the "download" of local sources
#
#   Copyright (c) 2015-2021 Pacman Development Team <pacman-dev@archlinux.org>
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

[[ -n "$LIBMAKEPKG_SOURCE_LOCAL_SH" ]] && return
LIBMAKEPKG_SOURCE_LOCAL_SH=1


LIBRARY=${LIBRARY:-"${PSPDEV}/share/makepkg"}

source "$LIBRARY/util/message.sh"
source "$LIBRARY/util/pkgbuild.sh"


download_local() {
	local netfile=$1
	local filepath=$(get_filepath "$netfile")

	if [[ -n "$filepath" ]]; then
		msg2 "$(gettext "Found %s")" "${filepath##*/}"
	else
		local filename=$(get_filename "$netfile")
		error "$(gettext "%s was not found in the build directory and is not a URL.")" "$filename"
		exit 1 # $E_MISSING_FILE
	fi
}
