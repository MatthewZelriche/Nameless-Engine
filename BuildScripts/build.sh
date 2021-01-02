#!/bin/bash                                                                                                           
if [ -z $1 ]; then
    buildType="Release"
else
    buildType=$1
fi

dotNetVersion="5.0.1"
 
build () {

    export PATH=$PATH:/home/$USER/.dotnet

    # Why is this necessary? dotnet build keeps creating an empty file instead of a directory
    if [ ! -d "../build/$buildType/bin/NLSharp" ]; then 
        mkdir -p "../build/$buildType/bin/NLSharp"
    fi

    cmake -S../ -B../build/$buildType -DCMAKE_BUILD_TYPE=$buildType -DBUILD_SHARED_LIBS:BOOL=ON -DBUILD_TESTS:BOOL=OFF
    make -C../build/$buildType -j8


    dotnet build ../NLSharp/CSharpCompiler -o ../build/$buildType/bin/NLSharp
    dotnet build ../NLSharp/CoreLibs -o ../build/$buildType/bin/NLSharp

}

echo "Building Application..."
build