# The problem
When you develop C/C++ projects, it's quite hard to handle your development environment.
For a long time, I end up with Makefile full of commands to __prepare__ the build environment. This command was in charge of installing needed libraries using tools like apt/macport/hombrew.

This approach is not crossplatform and doesn't manage library version you used => When two projects on the same CI server depends on two different versions of a library, it can become a nightmare.

I solve this problem by using CMake and its new **ExternalProject** command. Within a CMakeLists.txt file I define the External Libraries I used and how to install it. 

But it's hard to share the **ExternalProject** recipes I have written: To do so, you have to put it on the web and other developers will have to:
* find it searching on GitHub/Bitbucket/GoogleCode ...
* copy it to their CMakeLists.txt file
* Use it

# The project

## Usage

From a file defining the list of dependencies (libraries/tools), the C/C++ developer will be able to prepapre his build environment.

```ruby
    dmc 'Igloo', '~> 0.8'
    dmc 'HippoMock', '~> 3.1'
```

Preparing **build environment** will mean the following steps:

 * Fetching/loading recipes to generate a first CMakeLists.txt file (with ExternalProject_Add commands) used to install libraries.
 * Launching CMake a first time to install these libraries at a given location
 * Generating a CMakeLists.txt file that contains informations about where to find headers and libraries
 * Launching CMake a second time to generate the build environment of your choice (GNU Make, Code::Blocks, Visual Studio, XCode ...)

## Dependencies handling

In a first time, DMC will only install libraries that are defined inside the *dependencies* file. You will have to handle dependencies by your self: If your project depends on [Cinder](http://libcincder.org) you will have to specify Cinder and Boost

In a second time, we will handle dependecies by ourself: you will just need to specify Cinder and we will install the Boost version as indicated inside Cinder recipe.


# CMake: ExternalProject_Add command

From version 2.8 [CMake](http://cmake.org) comes with a new **ExternalProject** set of commands that allow to define how to download, build and install external libraries/tools. It's really usefull, but you can't use **find_package** to check headers/libraries existence and link your project with them. Indeed, at the time CMakeLists.txt file is parsed, these **ExternalProject** packages (headers/libraries) have not been handled by CMake => they cannot be found. 

The best practice is to build and install all the ExternalProject packages in a known location (${CMAKE_SOURCE_DIR}/vendors) and to add these locations to the build process with **link_directories**/**include_directories**: 

 * http://stackoverflow.com/questions/6351609/cmake-linking-to-library-downloaded-from-externalproject-add
 
 * http://cmake.3232098.n2.nabble.com/ExternalProject-dependency-question-td6934209.html

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

# Existing solutions

Idea is too provide tools like gem or pip but for C++ developers.

Closest solution is [CocoaPods](http://cocoapods.org) that manage library dependencies for Objective-C projects. It downloads libraries and make them available generating adapted XCode workspace file.
