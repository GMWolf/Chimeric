add_executable(ChimericTest main.cpp ResourceManagerTest.cpp HashedArrayTreeTest.cpp common.h StoreTypeTest.cpp VecStoreTest.cpp BitsetTest.cpp Flat_setTest.cpp EntityComponentTest.cpp)

target_link_libraries(ChimericTest Chimeric)