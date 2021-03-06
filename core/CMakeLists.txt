cmake_minimum_required(VERSION 2.6)
project(LSPL_CORE)


set (CMAKE_CXX_STANDARD 17)
set (CMAKE_POSITION_INDEPENDENT_CODE ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")
### lspl-core library

set(LSPL_CORE_SOURCES
    src/main/lspl/Namespace.cpp
    src/main/lspl/base/Range.cpp
    src/main/lspl/base/RefCountObject.cpp

    src/main/lspl/graphan/Unit.cpp
    src/main/lspl/graphan/Graphan.cpp
    src/main/lspl/graphan/AotGraphan.cpp
    src/main/lspl/graphan/XmorphyGraphan.cpp

    src/main/lspl/morphology/WordForm.cpp
    src/main/lspl/morphology/Morphology.cpp
    src/main/lspl/morphology/AotMorphology.cpp
    src/main/lspl/morphology/XmorphyMorphology.cpp

    src/main/lspl/patterns/Alternative.cpp
    src/main/lspl/patterns/matchers/Context.cpp
    src/main/lspl/patterns/matchers/LoopMatcher.cpp
    src/main/lspl/patterns/matchers/Matcher.cpp
    src/main/lspl/patterns/matchers/WordMatcher.cpp
    src/main/lspl/patterns/matchers/Variable.cpp
    src/main/lspl/patterns/matchers/TokenMatcher.cpp
    src/main/lspl/patterns/matchers/RegexpMatcher.cpp
    src/main/lspl/patterns/matchers/PatternMatcher.cpp
    src/main/lspl/patterns/matchers/MatcherContainer.cpp

    src/main/lspl/patterns/expressions/ConcatenationExpression.cpp
    src/main/lspl/patterns/expressions/Expression.cpp
    src/main/lspl/patterns/expressions/VariableExpression.cpp
    src/main/lspl/patterns/expressions/CurrentAnnotationExpression.cpp
    src/main/lspl/patterns/expressions/ConstantExpression.cpp
    src/main/lspl/patterns/expressions/AttributeExpression.cpp

    src/main/lspl/patterns/restrictions/Restriction.cpp
    src/main/lspl/patterns/restrictions/DictionaryRestriction.cpp
    src/main/lspl/patterns/restrictions/AgreementRestriction.cpp
    src/main/lspl/patterns/restrictions/AndRestriction.cpp

    src/main/lspl/patterns/parsers/Functions.cpp
    src/main/lspl/patterns/Pattern.cpp
    src/main/lspl/patterns/PatternBuilder.cpp
    src/main/lspl/utils/Conversion.cpp
    src/main/lspl/utils/Console.cpp
    src/main/lspl/dictionaries/MemoryDictionary.cpp
    src/main/lspl/dictionaries/Dictionary.cpp

    src/main/lspl/transforms/Normalization.cpp
    src/main/lspl/transforms/TransformBuilder.cpp
    src/main/lspl/transforms/TextTransformBuilder.cpp
    src/main/lspl/transforms/TextTransform.cpp
    src/main/lspl/transforms/PatternTransformBuilder.cpp
    src/main/lspl/transforms/PatternTransform.cpp
    src/main/lspl/transforms/ContextRetriever.cpp

    src/main/lspl/text/markup/Word.cpp
    src/main/lspl/text/markup/Token.cpp
    src/main/lspl/text/Transition.cpp
    src/main/lspl/text/Text.cpp
    src/main/lspl/text/Match.cpp
    src/main/lspl/text/writers/JsonTextWriter.cpp
    src/main/lspl/text/writers/TextWriter.cpp
    src/main/lspl/text/readers/JsonTextReader.cpp
    src/main/lspl/text/readers/TextReader.cpp
    src/main/lspl/text/readers/PlainTextReader.cpp
    src/main/lspl/text/indexes/PatternIndex.cpp
    src/main/lspl/text/indexes/SpeechPartIndex.cpp
    src/main/lspl/text/Node.cpp
    src/main/lspl/text/Loop.cpp
    src/main/lspl/text/TextBuilder.cpp
    src/main/lspl/text/attributes/AttributeContainer.cpp
    src/main/lspl/text/attributes/AttributeValue.cpp
    src/main/lspl/text/attributes/AttributeKey.cpp
    src/main/lspl/text/attributes/SpeechPart.cpp
    src/main/lspl/text/attributes/AttributeType.cpp
)

SET(LSPL_CORE_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}/src/main )

add_library(lspl SHARED ${LSPL_CORE_SOURCES})
target_include_directories(lspl PRIVATE ${AOT_INCLUDE_DIR} PUBLIC ${LSPL_CORE_INCLUDE_DIRS})
target_link_libraries(lspl PRIVATE ${Boost_SYSTEM_LIBRARY})

if(WIN32)
    add_custom_command(TARGET lspl POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy
            "${ICONV_PATH}/bin/libcharset1.dll"
            "${ICONV_PATH}/bin/libiconv2.dll"
            "${ICONV_PATH}/bin/libintl3.dll"
            "${CMAKE_BINARY_DIR}/$<CONFIGURATION>/"
        COMMENT "Copying to output directory")

    target_link_libraries(lspl pcre pcrecpp pcreposix libiconv common GraphanLib LemmatizerLib StructDictLib MorphWizardLib AgramtabLib)
elseif(APPLE)
    target_link_libraries(lspl PRIVATE pcrecpp iconv pcre PUBLIC ${AOT_LIBRARIES})
else(WIN32)
  target_link_libraries(lspl PRIVATE pcrecpp pcre PUBLIC ${AOT_LIBRARIES} ${Xmorphy_LIBRARY})
endif(WIN32)

### lspl-find binary

set(LSPL_FIND_SOURCES
	src/find/find.cpp
)

add_executable(lspl-search ${LSPL_FIND_SOURCES})

target_include_directories(lspl-search PRIVATE ${LSPL_CORE_INCLUDE_DIRS})
target_link_libraries(lspl-search lspl)

### lspl-test binary

set(LSPL_TEST_SOURCES
    src/test/assertions/MatchingAssertions.cpp
    src/test/assertions/PatternsAssertions.cpp
    src/test/tests/RefCountObjectsTest.cpp
    src/test/tests/DictionariesTest.cpp
    src/test/tests/MatchingTest.cpp
    src/test/tests/PatternsTest.cpp
    src/test/tests/TextReadersTest.cpp
    src/test/tests/RightPartTest.cpp
    src/test/LsplTests.cpp
)

add_executable(lspl-test ${LSPL_TEST_SOURCES})

target_link_libraries(lspl-test lspl)
target_include_directories(lspl-test PRIVATE ${LSPL_CORE_INCLUDE_DIRS})

### lspl-benchmark binary

set(LSPL_BENCHMARK_SOURCES
    src/test/LsplBenchmarks.cpp
)

add_executable(lspl-benchmark ${LSPL_BENCHMARK_SOURCES})

target_link_libraries(lspl-benchmark lspl)
target_include_directories(lspl-benchmark PRIVATE ${LSPL_CORE_INCLUDE_DIRS})

# Flags for effective error parsing

if(CMAKE_COMPILER_IS_GNUCC)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fmessage-length=0")
endif(CMAKE_COMPILER_IS_GNUCC)

if(CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fmessage-length=0")
endif(CMAKE_COMPILER_IS_GNUCXX)
