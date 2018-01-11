# http://xit0.org/2013/04/cmake-use-git-branch-and-commit-details-in-project/

# Get the current working branch
execute_process(
        COMMAND git rev-parse --abbrev-ref HEAD
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_BRANCH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

if (NOT GIT_BRANCH)
    message(FATAL_ERROR "Unable to retrieve the current git branch")
endif (NOT GIT_BRANCH)

# Get the latest abbreviated commit hash of the working branch
execute_process(
        COMMAND git log -1 --format=%h
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
)

if (NOT GIT_COMMIT_HASH)
    message(FATAL_ERROR "Unable to retrieve the current git commit hash")
endif (NOT GIT_COMMIT_HASH)

add_definitions("-DGIT_COMMIT_HASH=${GIT_COMMIT_HASH}")
add_definitions("-DGIT_BRANCH=${GIT_BRANCH}")