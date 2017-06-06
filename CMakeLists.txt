################################################################################
#                                                                              #
# The distributed list (dlist) library provides very light-weight real-time    #
# capable list classes with can optionally be ordered or circular.             #
# Copyright (C) 2017..2017  Thomas Schöpping                                   #
#                                                                              #
# This program is free software: you can redistribute it and/or modify         #
# it under the terms of the GNU General Public License as published by         #
# the Free Software Foundation, either version 3 of the License, or            #
# (at your option) any later version.                                          #
#                                                                              #
# This program is distributed in the hope that it will be useful,              #
# but WITHOUT ANY WARRANTY; without even the implied warranty of               #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                #
# GNU General Public License for more details.                                 #
#                                                                              #
# You should have received a copy of the GNU General Public License            #
# along with this program.  If not, see <http://www.gnu.org/licenses/>.        #
#                                                                              #
################################################################################

cmake_minimum_required(VERSION 2.6)

project(dlist)

include_directories(${CMAKE_SOURCE_DIR})

set(INCLUDES ${CMAKE_SOURCE_DIR}/dlist.hpp ${CMAKE_SOURCE_DIR}/dlist.tpp)
set(SOURCES ${CMAKE_SOURCE_DIR}/dlist_test.cpp)

add_executable (dlist_test ${INCLUDES} ${SOURCES})
