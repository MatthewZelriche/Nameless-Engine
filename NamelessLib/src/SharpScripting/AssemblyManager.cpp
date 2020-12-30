#include "NLS-Engine/SharpScripting/AssemblyManager.hpp"

#include <filesystem>
#include <memory>

#include <Log.hpp>

#include <tinyxml2.h>

#include <CoreCLR/coreclr_delegates.h>


// TODO when editor GUI is in progress, dehardcode Project creation path.
bool AssemblyManager::CreateNewProject(std::string projectName) {
    if (!std::filesystem::create_directories("../../../Projects/" + projectName)) {
        NLSLOG::Warn("Engine", "Could not create project {} directory", projectName);
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