#
# Copyright 2018 Axel Isouard <axel@isouard.fr>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.

project(game)

set(SOURCES
        gamemodule.h
        gamemodule.cpp)

set(PUBLIC_HEADERS
        ../../public/moduleabstract.h
        ../../public/gamehostinterface.h
        ../../public/gamemoduleinterface.h)

add_library(game SHARED ${SOURCES} ${PUBLIC_HEADERS})
set_target_properties(game PROPERTIES PREFIX "")
set_target_properties(game PROPERTIES OUTPUT_NAME "game-${TARGET_CPU}")

install(TARGETS game
        LIBRARY DESTINATION base)

add_style_check_target(game_style "${SOURCES}")