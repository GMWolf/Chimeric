add_executable(ChimericTest main.cpp TestResourceManager.cpp TestHashedArrayTree.cpp common.h TestStoreType.cpp TestVecStore.cpp TestBitset.cpp)

target_link_libraries(ChimericTest Chimeric)