### 1. Engine Architecture:
Our engine uses client/server architecture, what means that a game will just be a programmable app that make requests to our engine server.

    {Game(Client)}   <------EngineAPI------> {Engine(Server)}

    OBS: The engine dont have any defined API and consequently, any capability for Game development at this point in time.
    EnineAPI Example:
    
Ideia for client code:

        "// Api not yet defined, so it is not possible to do this realistically
        #include "Azgard/Entity.hpp"
        #include "Azgard/Mesh.hpp"

        class Game: public AzgardGame {
            ...
            void onStart() {
                Entity ent = new Entity();
                Mesh entMesh = ent.addComponent(Mesh);
            }
            ...
            void onRender() {
                entMesh.render();
            }
            ...
        }"

    Ideia for Api code:
    "//Mesh.hpp
    
    // Ideally, this class should be a dummy class, it should just redirect the call of 'render'
    // to what we have implemented in the engine. 
    class Mesh: public AzgardComponent {
        ...
        void render();
        ...
    }
    ...
    // Mesh.cpp
    Engine* gEngine = EngineRuntime::getSingletonPtr();
    
    void Mesh::render() {
        Promise<void> promise = JobSystem::getSingletonPtr().dispatchJob(gEngine.drawMesh(this->meshHandle));
        // Some calls probably should be sync
        // Probably not in the renderer, just to illustrate our job system and its promisses.
        promise.wait();
    }
    "

### 2. Engine Server
    Design Goals:
    1. Compatibility
    2. Performance
   
#### Target Platforms:
1. Linux
2. Windows
3. MacOS
4. Android
5. IOS

support for consoles (Playstation/Xbox/Switch) are desirably.

All major consoles provide native SDKs writen in C++ and it is the more commom language in game engine development. But take care with the use of libraries and the std libraries, some systems support just a subset of it, like android for instance with the android Native Development Kit(https://developer.android.com/ndk), there is no problem in using it, but if some platform dont give support we will need to add one ourselves, also, some features of recent c++ versions maybe not be supported, try to limit the language features to C++11 that is the last c++ version that feel like C++ anyways.

Libraries and Dependencies: Take cara when choosing to use some library as dependence, desirably it should be cross platform and have support for webassembly. 

#### Options:
    AZGARD_DEBUG_BUILD - Compile azgard as debug build (default ON)
    AZGARD_SHARED_LIB_BUILD - Compile azgard as a shared lib (default OFF).
    AZGARD_USE_STANDART_MATH - Uses standart math library implementation as backend for our math library (default ON)
#### Systems:
1. MemoryMamanger:
    * Desciption: Responsable for managing memory, objects should be allocated from a defined pool or a global pool of the manager.
    * Status: At this point it is good to go. Remains creating base classes for objects that will be AzgardGloballyPooled or AzgardPooled (Maybe we should find na best name kkkk).
2. Logger:
    * Description:  Responsable for logging messages.
    * Status: good to go, it is logging messages in sync and async ways, recomend using sync for engine development and async in any other situation.
3. Debbuger:
    * Desciption: Responsable for tracking engine * performance, memory usage and more things that deals whith developemnt and engine performance. We are using Tracy (https://github.com/wolfpld/tracy), please take a look at the documentation.
    * Status: good to go for now.
4. FileManager:
    * Description: Responsable for loading files in sync async way. Async not tested yet.
    * Status: good for now, but wee still need to add suport for networking(simulating a files system over the network), this is gonna be usefful when we start to add support for browsers with emscripten.
5. PlatformManager:
    * Desciption: Responsable for dealling with platform specific info.
    * Status: Not good to go, not many features implemented.
6. EventManager:
    * Desciption: Responsable for dealing with system and user events.
    * Status: Development has started but it is broken.
7. TimeMamanger:
    * Description: Responsable for dealling with things related to time.
    * Status: Feel features implemented.
8. LibraryManager:
    * Description: Responsable for management on library resources(like name shash table).
    * Status: good for now.
9. RenderManager: N/A
10. JobManager: N/A (implementation is done and tested in jobin/ we should just migrate the code)
11. NetworkManager: N/A (use asio for initial development)


TODOS:
1. JobManager - Migrate jobin code.
2. Renderer - Everything.
a. Implementation should follow parrallel and data oriented design.
b. Initiall API will be GLES3/Opengl3
3. EventManager - Make it work.
4. NetworkManager - Everything, take a look at asio for that