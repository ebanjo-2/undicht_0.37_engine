-- inlcude core projects
dofile "undicht_core/premake4_include_core_projects.lua"

project "engine"
    kind "SharedLib"

	files {  "src/**.*" }

	includedirs { "undicht_core/include", "src", "vendor" }
	
	links { "core"  }
	
	configuration "debug - linux"
		links { "dl" }
		flags { "Symbols" }
		
	configuration "release - linux"
		links { "dl" }
		flags { "OptimizeSpeed" }
		
	configuration "debug - windows"
		flags { "Symbols" }

	configuration "release - windows"
		flags { "OptimizeSpeed" }



	
    
