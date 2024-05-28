#!/bin/bash

DIR="."
CC=g++
CPPFLAGS=`pkg-config --cflags glew glfw3 assimp`
CPPFLAGS="$CPPFLAGS -I$DIR/ -ggdb3"
LDFLAGS=`pkg-config --libs glew glfw3 assimp`
LDFLAGS="$LDFLAGS -lX11 -ldl"
SOURCES="graphique.cc \
	$DIR/util.cc \
	$DIR/math3D.cc \
	$DIR/camera.cc \
	$DIR/monde_transformation.cc \
	$DIR/texture.cc \
	$DIR/lumiere.cc \
	$DIR/renderer.cc \
	$DIR/mesh.cc \
	$DIR/squelette_mesh.cc \
	$DIR/logiciel_tiers/stb_image.cc \
	$DIR/technique.cc \
	$DIR/texture_technique.cc \
	$DIR/squelette_technique.cc \
	$DIR/triangle_list.cc \
	$DIR/terrain.cc \
	$DIR/terrain_technique.cc \
	$DIR/glfw.cc "

$CC $SOURCES $CPPFLAGS $LDFLAGS -o graphique
