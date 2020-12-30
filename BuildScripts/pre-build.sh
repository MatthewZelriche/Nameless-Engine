#!/bin/bash

dotNetVersion="5.0.101"

prep() {
    if [ $(command -v dotnet) ] || [ -d "/home/$USER/.dotnet" ]; then
        echo "Dotnet already installed, skipping installation..."
    else
        echo "Installing .NET 5.0 SDK..."
        ./dotnet-install.sh --version "$dotNetVersion" --architecture "x64"
    fi
}

echo "Preparing Dev Environment..."
prep

echo "
****     Pre-build setup completed. If you are running this script in an interactive shell, please 
****     reload your shell configuration file for the new PATH variable to take effect.
****     On bash: 'source ~/.bashrc'.
****     On fish: 'source ~/.config/fish/config.fish'.
****     This must be done before running build.sh"
