#include "Runtime/Engine.hpp"
#include "Runtime/TimeManager.hpp"
#include "Library/Name.hpp"
#include "File/FileHandle.hpp"

Azgard::Engine gEngine; // Start Engine

void frame() {
    AZG_DEBUG_SCOPE
    Azgard::TimeManager::getSingletonPtr()->sleepFor(15);
}

int main() {
    // Azgard::FileHandle handle;
    // handle.syncOpen("Assets/txt/teste.txt", Azgard::FileMode::binary | Azgard::FileMode::read | Azgard::FileMode::write);
    // Azgard::String str = handle.syncRead(0, 10);
    // AZG_LOG("%u", handle.getFileSize());
    // AZG_LOG("%s", str.cString());
    // handle.syncClose();
    // Azgard::Name teste = "teste";
    for(int i=0; i<10000000; i++) {
        AZG_DEBUGGER_FRAME_MARK
        frame();
    }
	return 0;
}

