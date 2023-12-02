cmake_minimum_required(VERSION 3.10)

project(AmazonDelivery)

set(CMAKE_CXX_STANDARD 11)

#add_executable(AmazonDelivery amazon_delivery.cpp)

add_executable(SmallTest src/SmallTest.cpp)
target_include_directories(SmallTest PUBLIC include)

add_executable(RandomAddresses src/RandomAddresses.cpp)
target_include_directories(RandomAddresses PUBLIC include)

add_executable(MultiRouteTest src/MultiRouteTest.cpp)
target_include_directories(MultiRouteTest PUBLIC include)
