solution "undicht_engine"
    language "C++"
    buildoptions "-std=c++11"
    configurations { "debug - windows","debug - linux", "release - windows", "release - linux" }



-- file for the engine project

dofile "premake4_include_engine.lua"
	
    
