version 0.8.0 not yet released
========================
* made the framework compile and run on Mac OSX M1 (not using OpenGL ES 2.0 but Metal!)
* cleaned the code
* added: config.fh, a file separated from main.fh which is used for
	configurations (FH only)
* added: love_math_isConvex (FH only)
* added: love_graphics_points, love_graphics_line and love_graphics_polygon (FH only)
* added: Render To Texture (canvas) system (FH only)
* added: love_filesystem_getInfo (FH only).
* added: New particle module.
* added: New UI module.
* added: love_window_setMaxSize.
* added: New scripting language, FH.
* added: Misc math utilities.
* added: Very powerful particle system.
* added: Lua can be enabled or disabled at compile time.
* added: Build system for web!
* added: More C flags for compilation.
* added: CLove can be compiled as shared or static library.
* added: 'set' function to batch.c. Allows for changing the structure of an entity which is part of the batch.
* added: love.system.setClipboardText(text).
* added: love_system_getClipboardText().
* added: love_system_getProcessorCount().

* fixed: graphics#setFullscreen.
* fixed: newImageFont is not broken anymore.

* modify: Changed the structure of folders, enabling the usage of the framework as a library.
* modify: Removed OpenAL and replaced it with MojoAL.

* removed: C++ support

version 0.7.1 22.07.2017:
========================

* internally: added Zlib
* modify: love.filesystem.read to support Physfs
* modify: love.filesystem.write to support Physfs
* modify: love.filesystem.append to support Physfs
* modify: love.filesystem.exists to support Physfs
* added: love.filesystem.setIdentity(name)
* added: conf.lua accepts t.window.identity
* added: love.filesystem.enumarate(path)
* added: love.filesystem.isDir(path)
* added: love.filesystem.mkDir(path)
* added: love.filesystem.getUsrDir()
* added: love.filesystem.unmount(path)
* added: love.filesystem.mount(path)
* added: love.system.getPowerInfo()
* added Physfs as default filesystem manager. You can still use the old one if you want
* some work on emscripten (web support)
* some work on module: love.physics. I won't finish it!
* added: love.filesystem.equals(String1, String2, length(optional))
which lets you see if two strings are equal till a certain length. By default
it takes the full length of the strings.
* added: possibility to hide and create window when you want using conf.lua
* fixed: imageData: getChannel, getPixel, now accepting: grey, grey_alpha, rgb, rgba
* added: newImageFont. BitmapFonts. You can draw fonts using images (see examples for more info)
* added: networking. TCP using IPv4 or UPv6 for UNIX (see examples)
* some work on: Android port
* added: Clove compiles with C++ for more future features
* added: *.clove.tar, see examples folder -> package.
* added: love.filesystem.require("file.lua"). Acts like require even in packaging mode

version 0.7.0 04.03.2017:
=======================

* added: native which lets you code your games in C or C++ !
* added: love.graphics.newMesh
* removed: physfs and zlib
* added: build script for unix systems
* fixed: functions which were supported due to physfs
* fixed: static linking for SDL. You got to use make install just to be sure clove can
* be run and use the folder produced for deploying.
* fixed?: fixed stream support with vorbis files
* fixed: rectangles and circles alpha when using love.graphics.setColor
* fixed: Windows support should be totally functional


version 0.6.3 29.01.2017:
========================

* added full joystick support. The API is different than Love's !
* added love.filesystem.getSaveDirectory(optional: game, optional: company)
* added batch system to fonts
* added font:getWidth
* added font:getHeight
* fixed: build system for windows
* fixed: font
* fixed: https://github.com/Murii/CLove/issues/26
* fixed: love.mouse.isDown()

version 0.6.2 12.01.2017:
========================

* added No game screen
* added love.window.getDesktopDimensions()
* added love.window.getDisplayName()
* added love.window.getDisplays()
* added love.window.hasFocus()
* added love.window.hasMouseFocus()
* added love.timer.sleep(seconds)
* added love.window.setIcon(imageData)
* added love.window.getIcon(),it does not behave like Love.Clove returns the name of the file
* added pixels = ImageData:getString()
* added love.filesystem.load(fileName) see: https://love2d.org/wiki
* internal: added more functions to image_ImageData
* fixed: build system for physfs on linux

