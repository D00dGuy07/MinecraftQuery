# MinecraftQuery

This library is a C++ interface to get information from a Minecraft server using the query protocol. It only supports Windows.

The [example](https://github.com/D00dGuy07/MinecraftQuery/blob/master/example/example.cpp) file shows how to use this library.

# Linking

This repository is a Visual Studio project that is set up to build as a static library.

After cloning the repository you can add it to a Visual Studio solution.

1. Add the include folder to `Properties->C/C++->General->Additional Include Directories`.

2. Add the following to `Properties->Linker->General->Additional Library Directories`
	```
	$(SolutionDir)bin\$(Platform)-$(Configuration)\MinecraftQuery\
	```

3. Add the following to `Properties->Linker->Include->Additional Dependencies`
	```
	MinecraftQuery.lib;Ws2_32.lib;
	```

If you want to build it differently then you can configure it however you want.

# Details

* All of the functions defined in [MinecraftQuery.h](https://github.com/D00dGuy07/MinecraftQuery/blob/master/include/MinecraftQuery/MinecraftQuery.h) return false if they failed.
* The UDP sockets will timeout after 2 seconds.