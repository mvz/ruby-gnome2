#!/usr/bin/env ruby
#
# Copyright (C) 2014  Ruby-GNOME2 Project Team
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

ruby_gnome2_base = File.join(File.dirname(__FILE__), "..", "..")
ruby_gnome2_base = File.expand_path(ruby_gnome2_base)

glib_base = File.join(ruby_gnome2_base, "glib2")
atk_base = File.join(ruby_gnome2_base, "atk")
pango_base = File.join(ruby_gnome2_base, "pango")
gdk_pixbuf_base = File.join(ruby_gnome2_base, "gdk_pixbuf2")
cairo_gobject_base = File.join(ruby_gnome2_base, "cairo-gobject")
gobject_introspection_base = File.join(ruby_gnome2_base, "gobject-introspection")
gdk3_base = File.join(ruby_gnome2_base, "gdk3")
gtk3_base = File.join(ruby_gnome2_base, "gtk3")
vte3_base = File.join(ruby_gnome2_base, "vte3")

modules = [
  [glib_base, "glib2"],
  [atk_base, "atk"],
  [pango_base, "pango"],
  [cairo_gobject_base, "cairo-gobject"],
  [gdk_pixbuf_base, "gdk_pixbuf2"],
  [gobject_introspection_base, "gobject-introspection"],
  [gdk3_base, "gdk3"],
  [gtk3_base, "gtk3"],
  [vte3_base, "vte3"],
]

modules.each do |target, module_name|
  makefile = File.join(target, "Makefile")
  if File.exist?(makefile) and system("which make > /dev/null")
    `make -C #{target.dump} > /dev/null` or exit(false)
  end
  $LOAD_PATH.unshift(File.join(target, "ext", module_name))
  $LOAD_PATH.unshift(File.join(target, "lib"))
end

$LOAD_PATH.unshift(File.join(glib_base, "test"))
require "glib-test-init"

$VERBOSE = false # TODO: remove me

$LOAD_PATH.unshift(File.join(vte3_base, "test"))
require "vte3-test-utils"

require "vte3"

exit Test::Unit::AutoRunner.run(true)
