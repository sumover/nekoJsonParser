include(FetchContent)
# 把gtest从github上作为模块导入
# 导入后的代码在输出文件夹下的/_deps/gtest-src
FetchContent_Declare(gtest
        QUIET
        URL https://github.com/google/googletest/archive/release-1.10.0.tar.gz
        )

# configure build of googletest
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(gtest)

# 添加一个测试文件
add_executable(
        tests
        test1.cpp
        NullParserTest.cpp BoolParserTest.cpp NumberParserTest.cpp StringParserTest.cpp ArrayTest.cpp JSONObjectTest.cpp)

# 链接模块
target_link_libraries(tests
        PRIVATE
        parser
        gtest_main
        )

# 导入GoogleTest模块
include(GoogleTest)
gtest_discover_tests(tests
        PROPERTIES
        LABELS "unit"
        DISCOVERY_TIMEOUT
        240
        )