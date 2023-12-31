# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION 3.5)

if(EXISTS "C:/Users/Huawei/Desktop/progettopcs/externals/Eigen-prefix/src/Eigen-stamp/Eigen-gitclone-lastrun.txt" AND EXISTS "C:/Users/Huawei/Desktop/progettopcs/externals/Eigen-prefix/src/Eigen-stamp/Eigen-gitinfo.txt" AND
  "C:/Users/Huawei/Desktop/progettopcs/externals/Eigen-prefix/src/Eigen-stamp/Eigen-gitclone-lastrun.txt" IS_NEWER_THAN "C:/Users/Huawei/Desktop/progettopcs/externals/Eigen-prefix/src/Eigen-stamp/Eigen-gitinfo.txt")
  message(STATUS
    "Avoiding repeated git clone, stamp file is up to date: "
    "'C:/Users/Huawei/Desktop/progettopcs/externals/Eigen-prefix/src/Eigen-stamp/Eigen-gitclone-lastrun.txt'"
  )
  return()
endif()

execute_process(
  COMMAND ${CMAKE_COMMAND} -E rm -rf "C:/Users/Huawei/Desktop/progettopcs/externals/Main_Source/eigen3"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to remove directory: 'C:/Users/Huawei/Desktop/progettopcs/externals/Main_Source/eigen3'")
endif()

# try the clone 3 times in case there is an odd git clone issue
set(error_code 1)
set(number_of_tries 0)
while(error_code AND number_of_tries LESS 3)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe" 
            clone --no-checkout --depth 1 --no-single-branch --progress --config "advice.detachedHead=false" "https://gitlab.com/libeigen/eigen.git" "eigen3"
    WORKING_DIRECTORY "C:/Users/Huawei/Desktop/progettopcs/externals/Main_Source"
    RESULT_VARIABLE error_code
  )
  math(EXPR number_of_tries "${number_of_tries} + 1")
endwhile()
if(number_of_tries GREATER 1)
  message(STATUS "Had to git clone more than once: ${number_of_tries} times.")
endif()
if(error_code)
  message(FATAL_ERROR "Failed to clone repository: 'https://gitlab.com/libeigen/eigen.git'")
endif()

execute_process(
  COMMAND "C:/Program Files/Git/cmd/git.exe" 
          checkout "3147391d946bb4b6c68edd901f2add6ac1f31f8c" --
  WORKING_DIRECTORY "C:/Users/Huawei/Desktop/progettopcs/externals/Main_Source/eigen3"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to checkout tag: '3147391d946bb4b6c68edd901f2add6ac1f31f8c'")
endif()

set(init_submodules TRUE)
if(init_submodules)
  execute_process(
    COMMAND "C:/Program Files/Git/cmd/git.exe" 
            submodule update --recursive --init 
    WORKING_DIRECTORY "C:/Users/Huawei/Desktop/progettopcs/externals/Main_Source/eigen3"
    RESULT_VARIABLE error_code
  )
endif()
if(error_code)
  message(FATAL_ERROR "Failed to update submodules in: 'C:/Users/Huawei/Desktop/progettopcs/externals/Main_Source/eigen3'")
endif()

# Complete success, update the script-last-run stamp file:
#
execute_process(
  COMMAND ${CMAKE_COMMAND} -E copy "C:/Users/Huawei/Desktop/progettopcs/externals/Eigen-prefix/src/Eigen-stamp/Eigen-gitinfo.txt" "C:/Users/Huawei/Desktop/progettopcs/externals/Eigen-prefix/src/Eigen-stamp/Eigen-gitclone-lastrun.txt"
  RESULT_VARIABLE error_code
)
if(error_code)
  message(FATAL_ERROR "Failed to copy script-last-run stamp file: 'C:/Users/Huawei/Desktop/progettopcs/externals/Eigen-prefix/src/Eigen-stamp/Eigen-gitclone-lastrun.txt'")
endif()
