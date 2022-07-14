cmake_minimum_required(VERSION 3.16)
project(Search_Engine)

set(CMAKE_CXX_STANDARD 14)
# The configure_file statements below ensure that files are copied into the data
# folder that will be created in the build folder.
file(COPY sample_data/ DESTINATION sample_data/)


# This target is for the main project.  Add in any additional files you need or that you're copying
# over from a previous project.
add_executable(Search_Engine main.cpp DSVector.h Document_parser.cpp Document_parser.h porter2_stemmer.cpp porter2_stemmer.h AVLTree.h Article.h Query_processor.h Query_processor.cpp User_interface.h User_interface.cpp Article.cpp Article.cpp Relevancy_ranking.cpp Relevancy_ranking.h)

# this is the testing target.  Don't include your main driver.cpp file in this target.
add_executable(Search_Engine_tests DSVector.h catch.hpp catch_setup.cpp DataStructure_Tests.cpp catch_setup.h Relevancy_ranking.cpp Relevancy_ranking.h)