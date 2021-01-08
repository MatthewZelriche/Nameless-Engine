#include "NLS-Engine/Core/ProjectManager.hpp"

#include <tinyxml2.h>
#include <filesystem>
#include <Log.hpp>

bool ProjectManager::CreateNewProject(std::string projectName, std::string projectDirectoryPath) {
    char slash = '/';
    if (projectDirectoryPath.back() != slash) {
        projectDirectoryPath.append("/");
    }
    if (!std::filesystem::create_directories(projectDirectoryPath + projectName)) {
        NLSLOG::Warn("Engine", "Could not create project {} root directory", projectName);
        return false;
    }

    if (!std::filesystem::create_directories(projectDirectoryPath + projectName + "/" + "AuthorContent") ||
        !std::filesystem::create_directories(projectDirectoryPath + projectName + "/" + "AuthorContent/Scripts") ||
        !std::filesystem::create_directories(projectDirectoryPath + projectName + "/" + "bin")) {
            NLSLOG::Warn("Engine", "Could not create project {} subdirectories", projectName);
            return false;
    }

    // Create new csproj file for user project.
    tinyxml2::XMLDocument csprojFile;
    tinyxml2::XMLElement *root = csprojFile.NewElement("Project");
    root->SetAttribute("Sdk", "Microsoft.NET.Sdk");

    tinyxml2::XMLElement *propertyGroup = csprojFile.NewElement("PropertyGroup");
    propertyGroup->InsertNewChildElement("TargetFramework")->SetText("net5.0");
    propertyGroup->InsertNewChildElement("AssemblyName")->SetText(projectName.c_str());
    root->InsertEndChild(propertyGroup);

    tinyxml2::XMLElement *itemGroup = csprojFile.NewElement("ItemGroup");
// TODO: Think of a less stupid way to do this.
#ifdef NDEBUG
    itemGroup->InsertNewChildElement("Reference")->SetAttribute("Include",
                                        "../../build/Release/bin/NLSharpLib.dll");
#else
    itemGroup->InsertNewChildElement("Reference")->SetAttribute("Include",
                                    "../../build/Debug/bin/NLSharpLib.dll"); 
#endif
    root->InsertEndChild(itemGroup);

    csprojFile.InsertEndChild(root);
    // TODO: Custom save paths in the future.
    std::string savePath("../../../Projects/" + projectName + "/" + projectName + ".csproj");
    csprojFile.SaveFile(savePath.c_str());

    return true;
}


bool ProjectManager::BuildProject(std::string projectName, std::string projectDirectoryPath) {
    NLSLOG::Info("Engine", "Begin building project {}...", projectName);

#ifdef __linux__
    std::string coreExecLocation = "CoreExecutable/CoreExecutable";
    std::string NLSLib = "libNamelessLib.so";
    std::string extensionType = "";
#else
    std::string coreExecLocation = "CoreExecutable/CoreExecutable.exe";
    std::string NLSLibLocation = "NamelessLib.dll";
    std::string extensionType = ".exe";
#endif

    if (std::filesystem::exists(coreExecLocation)) {
        std::filesystem::copy(coreExecLocation, projectDirectoryPath + projectName + "/bin/" + projectName + extensionType);
    } else {
        NLSLOG::Warn("Engine", "Could not locate template core executable, cannot continue with build process for project {}...", projectName);
        return false;
    }

    if (std::filesystem::exists(NLSLib)) {
        std::filesystem::copy(NLSLib, projectDirectoryPath + projectName + "/bin/" + NLSLib);
    } else {
        NLSLOG::Warn("Engine", "Could not locate Nameless-Engine core library (how could this possibly happen?), cannot continue with build process for project {}...", projectName);
        return false;
    }

    std::filesystem::copy_options copyRecursive = std::filesystem::copy_options::recursive;

    if (std::filesystem::exists("NLSharp/")) {
        std::filesystem::copy("NLSharp/", projectDirectoryPath + projectName + "/bin/" + "NLSharp/");
    } else {
        NLSLOG::Warn("Engine", "Could not locate NLSharp assemblies, cannot continue with build process for project {}...", projectName);
        return false;
    }

    NLSLOG::Info("Engine", "Successfully built project {}...", projectName);
    return true;
}