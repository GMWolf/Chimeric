add_executable(ChimericTest main.cpp core/ResourceManagerTest.cpp core/HashedArrayTreeTest.cpp core/common.h core/ComponentTraits.cpp core/VecStoreTest.cpp core/BitsetTest.cpp core/Flat_setTest.cpp core/EntityComponentTest.cpp core/SubscriptionTest.cpp core/SystemTest.cpp core/FullTest.cpp events/EventSystemTest.cpp)

target_link_libraries(ChimericTest Chimeric)