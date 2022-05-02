cmake_minimum_required(VERSION 3.15.3)

project(Reactor LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Ofast -Wextra -Wall -fno-omit-frame-pointer -fasynchronous-unwind-tables -fpie -fpic -fstack-protector -pipe -Werror=format-security")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEBUG -O0 -g -ggdb -Wextra -Wall -fno-omit-frame-pointer -fasynchronous-unwind-tables -fpie -fpic -fstack-protector -pipe -Werror=format-security")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEBUG -O0 -g -ggdb -Wextra -Wall -fno-omit-frame-pointer -fasynchronous-unwind-tables -fpie -fpic -fstack-protector -pipe -Werror=format-security -fsanitize=address -fsanitize=undefined -static-libasan -static-libubsan")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEBUG -O0 -g -ggdb -Wextra -Wall -fno-omit-frame-pointer -fasynchronous-unwind-tables -fpie -fpic -fstack-protector -pipe -Werror=format-security -fsanitize=address -static-libasan")

enable_testing()

add_subdirectory(src)
add_subdirectory(ext)