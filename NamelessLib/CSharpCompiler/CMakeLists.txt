cmake_minimum_required(VERSION 3.13.0)

Project(SharpCompiler CSharp)

add_library(SharpCompiler SHARED
	${CMAKE_CURRENT_SOURCE_DIR}/Compiler.cs)