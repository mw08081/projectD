// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class ProjectD : ModuleRules
{
	public ProjectD(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        PrivateDependencyModuleNames.AddRange(new string[] {  });

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        //PrivateDependencyModuleNames.AddRange( new string[] { "Slate", "SlateCore", "EditorStyle", "UnrealEd" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true

        // Editor 모듈 추가
        //if (Target.bBuildEditor)
        //{
        //    PrivateDependencyModuleNames.Add("UnrealEd");
        //}
    }
}
