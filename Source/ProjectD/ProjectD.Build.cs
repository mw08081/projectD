// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ProjectD : ModuleRules
{
	public ProjectD(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" , "Json", "JsonUtilities" });

        PrivateDependencyModuleNames.AddRange(new string[] {  });

		//PrivateIncludePaths.Add("ProjectD");
    }
}
