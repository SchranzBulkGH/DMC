# The problem

When you develop C/C++ projects, it's quite hard to handle your development environment.
For a long time, I end up with Makefile full of commands to __prepare__ your environment. This command was in charge of installing needed libraries.

With this approach it's hard to specify library version you used. When two projects on the same CI server depends on two different versions of a library, it can become a nightmare.

From version 2.8 [CMake](http://cmake.org) comes with a new **ExternalProject** set of commands that allow to define how to download, build and install external libraries/tools. It's really usefull, but you can't use **find_package** to check headers/libraries existence and link your project with them. Indeed, at the time CMakeLists.txt file is parsed, these **ExternalProject** packages (headers/libraries) have not been handled by CMake => they cannot be found. 

The best practice is to build and install all the ExternalProject packages in a known location (${CMAKE_SOURCE_DIR}/vendors) and to add these locations to the build process with **link_directories**/**include_directories**: http://stackoverflow.com/questions/6351609/cmake-linking-to-library-downloaded-from-externalproject-add

```cmake
	ExternalProject_Add(AnExternalLibrary
		...
	)
	
	link_directories(${CMAKE_SOURCE_DIR}/vendors/libs)
	include_directories(${CMAKE_SOURCE_DIR}/vendors/include)
	// Specify libraries our app should be linked to
	target_link_libraries(MyApp AnExternalLibrary_Name)
	// To be sure that ExternalProject is run before trying to build 
	// MyApp
	add_dependencies(MyApp AnExternalLibrary)
```


# The project

From a JSON file defining the list of dependencies (libraries/tools), the C/C++ developer will be able to prepapre his build environment.

A list of recipies (ExternalProject_add commands), will be setup on the web (like homebrew), the tool will just fetch these recipes to install these dependencies at a given place. Then the CMake environement will be updated to be able to find it with **find_package** 