add_executable(ChimericTest main.cpp ResourceManagerTest.cpp HashedArrayTreeTest.cpp common.h ComponentTraits.cpp VecStoreTest.cpp BitsetTest.cpp Flat_setTest.cpp EntityComponentTest.cpp SubscriptionTest.cpp)

target_link_libraries(ChimericTest Chimeric)