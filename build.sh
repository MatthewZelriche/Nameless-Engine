#!/bin/bash                                                                                                           
if [ -z $1 ]; then
    buildType="Release"
else
    buildType=$1
fi
 
build () {
    cmake -S. -Bbuild/$buildType -DCMAKE_BUILD_TYPE=$buildType -DBUILD_SHARED_LIBS:BOOL=ON -DBUILD_TESTS:BOOL=OFF
    make -Cbuild/$buildType -j8
    dotnet build NamelessLib/CSharpLibs -o build/$buildType/bin/
}
 
echo "Building Application..."
build
