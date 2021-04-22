# CS3560-C--group-3
C++ Group 3
Morning Session
Group Members:
    Roland Allaire
    Rocco Pearce
    Lucas Advent
    Maggie Morgan


Team Project: Design a discord bot 
    This Discord bot will be an RPG simulator accessed through discord
    Bot will be similarly modeled to Epic RPG Maker
    It will have distinct differences and unique features, potentially including:
        More specified Combat: Strategic options and flee option instead of having a random outcome
        A better interface: combining inventory with profile stats instead of having them both separate
        Add a party aspect: allowing players to communicate with one another
                            allowing players to fight together
        Adding different weapon options / armor options
        Adding different classes that players choose: boosts certain stats based on chosen class
Target Technology Platform:
    Discord, an internet application that functions as a social networking platform
    The target software design is a Discord Bot that responds to user commands

    
Instructions (You will need your own bot in discord and bot token to run this code): 


    1. Clone the source code of Aegis.cpp down


        git clone --recursive https://github.com/zeroxs/aegis.cpp.git
        
        
    2. Install vcpkg


        Get into aegic.spp folder. (cd aegis.cpp).
        
        
        git clone https://github.com/microsoft/vcpkg
        
        
        .\vcpkg\bootstrap-vcpkg.bat
        
        
    3. Install openssl, zlib


        .\vcpkg\vcpkg.exe install openssl:x64-windows zlib:x64-windows
        
        
        .\vcpkg\vcpkg.exe list
        
        
        .\vcpkg\vcpkg.exe remove openssl zlib
        
        
    4. Open the folder in Visual Studio.


        There will be an error, this is ecpected.
        
        
    5. Edit the CMakeLists.txt's settings.


        Right click on the CMakeLists.txt and click on CMake Settings
        
        
        Change CMake toolchain file to a full path to vcpkg.cmake e.g.
        
        
        C:/Users/chusa/projects/aegis.cpp/vcpkg/scripts/buildsystems/vcpkg.cmake
        
        
        Add -DBUILD_EXAMPLES=1 -DCMAKE_CXX_STANDARD=17 to "CMake command arguments" under "Command arguments"
        
        
        Save the file. Visual Studio should start cmake generation process again.
        
        
        This time there should be no error.
        
        
    6. Edit CMakeLists.txt


        Comment line 17 and 18 out.
        
        
        On line 41 remove dl from the list.
        
        
        It is after the "Asio::Asio" and before "Threads::Threads"
        
        
        Save the file. Visual Studio will generate cmake again.
        
        
    7. Right click on CMakeLists.txt and click Build.
    
    
    8. Test the build.


        Go into bin/ folder and run aegis_minimal.exe in a terminal.
        
        
        It should "Creating websocket" and then exit.
        
        
    9. Modify the src/minimal.cpp
        
        
        Copy our main_minimal.cpp into the minimal.cpp.
        

        Replace the "TOKEN" with the your own bot token.
        
        
        Recompile by right click on CMakeLists.txt and then select "Build"
        
        
        Run the ./bin/aegis_minimal.exe again this time it should not stop.
   

Github Repo link: 
    https://github.com/roland199/CS3560-C--group-3.git

Client ID: 
814976783052570624

Public Key: 
ac25bc5a1994ec27c513ca2919831eacd0662f2842dc3eb9236a7545b89ace63
