#
# 'show-header-target-option-with-t-tests'

add_executable(show-header-target-option-with-t-tests)

target_compile_features(show-header-target-option-with-t-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-header-target-option-with-t-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_HEADER
		TRACE_OUT_SHOW_HEADER_TARGET="$<TARGET_FILE_NAME:show-header-target-option-with-t-tests>"
)

target_link_libraries(show-header-target-option-with-t-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(show-header-target-option-with-t-tests
	PRIVATE
		show-header-target-option-with-t.tests.cpp
)

catch_discover_tests(show-header-target-option-with-t-tests)

#
# 'show-header-target-option-with-tbin-tests'

add_executable(show-header-target-option-with-tbin-tests)

target_compile_features(show-header-target-option-with-tbin-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-header-target-option-with-tbin-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_HEADER
		TRACE_OUT_SHOW_HEADER_TARGET="$<TARGET_FILE_NAME:show-header-target-option-with-tbin-tests>"
)

target_link_libraries(show-header-target-option-with-tbin-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(show-header-target-option-with-tbin-tests
	PRIVATE
		show-header-target-option-with-tbin.tests.cpp
)

catch_discover_tests(show-header-target-option-with-tbin-tests)

#
# 'show-header-target-option-with-toct-tests'

add_executable(show-header-target-option-with-toct-tests)

target_compile_features(show-header-target-option-with-toct-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-header-target-option-with-toct-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_HEADER
		TRACE_OUT_SHOW_HEADER_TARGET="$<TARGET_FILE_NAME:show-header-target-option-with-toct-tests>"
)

target_link_libraries(show-header-target-option-with-toct-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(show-header-target-option-with-toct-tests
	PRIVATE
		show-header-target-option-with-toct.tests.cpp
)

catch_discover_tests(show-header-target-option-with-toct-tests)

#
# 'show-header-target-option-with-thex-tests'

add_executable(show-header-target-option-with-thex-tests)

target_compile_features(show-header-target-option-with-thex-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-header-target-option-with-thex-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_HEADER
		TRACE_OUT_SHOW_HEADER_TARGET="$<TARGET_FILE_NAME:show-header-target-option-with-thex-tests>"
)

target_link_libraries(show-header-target-option-with-thex-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(show-header-target-option-with-thex-tests
	PRIVATE
		show-header-target-option-with-thex.tests.cpp
)

catch_discover_tests(show-header-target-option-with-thex-tests)

#
# 'show-header-target-option-with-tr-begin-end-tests'

add_executable(show-header-target-option-with-tr-begin-end-tests)

target_compile_features(show-header-target-option-with-tr-begin-end-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-header-target-option-with-tr-begin-end-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_HEADER
		TRACE_OUT_SHOW_HEADER_TARGET="$<TARGET_FILE_NAME:show-header-target-option-with-tr-begin-end-tests>"
)

target_link_libraries(show-header-target-option-with-tr-begin-end-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(show-header-target-option-with-tr-begin-end-tests
	PRIVATE
		show-header-target-option-with-tr-begin-end.tests.cpp
)

catch_discover_tests(show-header-target-option-with-tr-begin-end-tests)

#
# 'show-header-target-option-with-tr-begin-how-much-tests'

add_executable(show-header-target-option-with-tr-begin-how-much-tests)

target_compile_features(show-header-target-option-with-tr-begin-how-much-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-header-target-option-with-tr-begin-how-much-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_HEADER
		TRACE_OUT_SHOW_HEADER_TARGET="$<TARGET_FILE_NAME:show-header-target-option-with-tr-begin-how-much-tests>"
)

target_link_libraries(show-header-target-option-with-tr-begin-how-much-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(show-header-target-option-with-tr-begin-how-much-tests
	PRIVATE
		show-header-target-option-with-tr-begin-how-much.tests.cpp
)

catch_discover_tests(show-header-target-option-with-tr-begin-how-much-tests)

#
# 'show-header-target-option-with-tr-begin-end-how-much-tests'

add_executable(show-header-target-option-with-tr-begin-end-how-much-tests)

target_compile_features(show-header-target-option-with-tr-begin-end-how-much-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-header-target-option-with-tr-begin-end-how-much-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_HEADER
		TRACE_OUT_SHOW_HEADER_TARGET="$<TARGET_FILE_NAME:show-header-target-option-with-tr-begin-end-how-much-tests>"
)

target_link_libraries(show-header-target-option-with-tr-begin-end-how-much-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(show-header-target-option-with-tr-begin-end-how-much-tests
	PRIVATE
		show-header-target-option-with-tr-begin-end-how-much.tests.cpp
)

catch_discover_tests(show-header-target-option-with-tr-begin-end-how-much-tests)

#
# 'show-header-target-option-with-m-tests'

add_executable(show-header-target-option-with-m-tests)

target_compile_features(show-header-target-option-with-m-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-header-target-option-with-m-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_HEADER
		TRACE_OUT_SHOW_HEADER_TARGET="$<TARGET_FILE_NAME:show-header-target-option-with-m-tests>"
)

target_link_libraries(show-header-target-option-with-m-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(show-header-target-option-with-m-tests
	PRIVATE
		show-header-target-option-with-m.tests.cpp
)

catch_discover_tests(show-header-target-option-with-m-tests)

#
# 'show-header-target-option-with-s-tests'

add_executable(show-header-target-option-with-s-tests)

target_compile_features(show-header-target-option-with-s-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-header-target-option-with-s-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_HEADER
		TRACE_OUT_SHOW_HEADER_TARGET="$<TARGET_FILE_NAME:show-header-target-option-with-s-tests>"
)

target_link_libraries(show-header-target-option-with-s-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(show-header-target-option-with-s-tests
	PRIVATE
		show-header-target-option-with-s.tests.cpp
)

catch_discover_tests(show-header-target-option-with-s-tests)

#
# 'show-header-target-option-with-f-tests'

add_executable(show-header-target-option-with-f-tests)

target_compile_features(show-header-target-option-with-f-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-header-target-option-with-f-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_HEADER
		TRACE_OUT_SHOW_HEADER_TARGET="$<TARGET_FILE_NAME:show-header-target-option-with-f-tests>"
)

target_link_libraries(show-header-target-option-with-f-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(show-header-target-option-with-f-tests
	PRIVATE
		show-header-target-option-with-f.tests.cpp
)

catch_discover_tests(show-header-target-option-with-f-tests)

#
# 'show-header-target-option-with-return-tests'

add_executable(show-header-target-option-with-return-tests)

target_compile_features(show-header-target-option-with-return-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-header-target-option-with-return-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_HEADER
		TRACE_OUT_SHOW_HEADER_TARGET="$<TARGET_FILE_NAME:show-header-target-option-with-return-tests>"
)

target_link_libraries(show-header-target-option-with-return-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(show-header-target-option-with-return-tests
	PRIVATE
		show-header-target-option-with-return.tests.cpp
)

catch_discover_tests(show-header-target-option-with-return-tests)

#
# 'show-header-target-option-with-if-tests'

add_executable(show-header-target-option-with-if-tests)

target_compile_features(show-header-target-option-with-if-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-header-target-option-with-if-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_HEADER
		TRACE_OUT_SHOW_HEADER_TARGET="$<TARGET_FILE_NAME:show-header-target-option-with-if-tests>"
)

target_link_libraries(show-header-target-option-with-if-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(show-header-target-option-with-if-tests
	PRIVATE
		show-header-target-option-with-if.tests.cpp
)

catch_discover_tests(show-header-target-option-with-if-tests)

#
# 'show-header-target-option-with-for-tests'

add_executable(show-header-target-option-with-for-tests)

target_compile_features(show-header-target-option-with-for-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-header-target-option-with-for-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_HEADER
		TRACE_OUT_SHOW_HEADER_TARGET="$<TARGET_FILE_NAME:show-header-target-option-with-for-tests>"
)

target_link_libraries(show-header-target-option-with-for-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(show-header-target-option-with-for-tests
	PRIVATE
		show-header-target-option-with-for.tests.cpp
)

catch_discover_tests(show-header-target-option-with-for-tests)

#
# 'show-header-target-option-with-while-tests'

add_executable(show-header-target-option-with-while-tests)

target_compile_features(show-header-target-option-with-while-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-header-target-option-with-while-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_HEADER
		TRACE_OUT_SHOW_HEADER_TARGET="$<TARGET_FILE_NAME:show-header-target-option-with-while-tests>"
)

target_link_libraries(show-header-target-option-with-while-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(show-header-target-option-with-while-tests
	PRIVATE
		show-header-target-option-with-while.tests.cpp
)

catch_discover_tests(show-header-target-option-with-while-tests)

#
# 'show-header-target-option-with-time-tests'

add_executable(show-header-target-option-with-time-tests)

target_compile_features(show-header-target-option-with-time-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-header-target-option-with-time-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_HEADER
		TRACE_OUT_SHOW_HEADER_TARGET="$<TARGET_FILE_NAME:show-header-target-option-with-time-tests>"
)

target_link_libraries(show-header-target-option-with-time-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(show-header-target-option-with-time-tests
	PRIVATE
		show-header-target-option-with-time.tests.cpp
)

catch_discover_tests(show-header-target-option-with-time-tests)

#
# 'show-header-target-option-with-time-stats-tests'

add_executable(show-header-target-option-with-time-stats-tests)

target_compile_features(show-header-target-option-with-time-stats-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-header-target-option-with-time-stats-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_HEADER
		TRACE_OUT_SHOW_HEADER_TARGET="$<TARGET_FILE_NAME:show-header-target-option-with-time-stats-tests>"
)

target_link_libraries(show-header-target-option-with-time-stats-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(show-header-target-option-with-time-stats-tests
	PRIVATE
		show-header-target-option-with-time-stats.tests.cpp
)

catch_discover_tests(show-header-target-option-with-time-stats-tests)

#
# 'show-header-target-option-with-clocks-tests'

add_executable(show-header-target-option-with-clocks-tests)

target_compile_features(show-header-target-option-with-clocks-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-header-target-option-with-clocks-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_HEADER
		TRACE_OUT_SHOW_HEADER_TARGET="$<TARGET_FILE_NAME:show-header-target-option-with-clocks-tests>"
)

target_link_libraries(show-header-target-option-with-clocks-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(show-header-target-option-with-clocks-tests
	PRIVATE
		show-header-target-option-with-clocks.tests.cpp
)

catch_discover_tests(show-header-target-option-with-clocks-tests)

#
# 'show-header-target-option-with-clock-stats-tests'

add_executable(show-header-target-option-with-clock-stats-tests)

target_compile_features(show-header-target-option-with-clock-stats-tests
	PRIVATE
		cxx_std_11
)

target_compile_definitions(show-header-target-option-with-clock-stats-tests
	PRIVATE
		TRACE_OUT_STREAM_TO=trace_out_to_test_stream
		TRACE_OUT_STREAM_WIDTH=70
		TRACE_OUT_SHOW_HEADER
		TRACE_OUT_SHOW_HEADER_TARGET="$<TARGET_FILE_NAME:show-header-target-option-with-clock-stats-tests>"
)

target_link_libraries(show-header-target-option-with-clock-stats-tests
	PRIVATE
		helpers
		Catch2::Catch2WithMain
		trace-out
)

target_sources(show-header-target-option-with-clock-stats-tests
	PRIVATE
		show-header-target-option-with-clock-stats.tests.cpp
)

catch_discover_tests(show-header-target-option-with-clock-stats-tests)

#
# IDE

set_target_properties(show-header-target-option-with-t-tests PROPERTIES FOLDER tests)
set_target_properties(show-header-target-option-with-tbin-tests PROPERTIES FOLDER tests)
set_target_properties(show-header-target-option-with-toct-tests PROPERTIES FOLDER tests)
set_target_properties(show-header-target-option-with-thex-tests PROPERTIES FOLDER tests)
set_target_properties(show-header-target-option-with-tr-begin-end-tests PROPERTIES FOLDER tests)
set_target_properties(show-header-target-option-with-tr-begin-how-much-tests PROPERTIES FOLDER tests)
set_target_properties(show-header-target-option-with-tr-begin-end-how-much-tests PROPERTIES FOLDER tests)
set_target_properties(show-header-target-option-with-m-tests PROPERTIES FOLDER tests)
set_target_properties(show-header-target-option-with-s-tests PROPERTIES FOLDER tests)
set_target_properties(show-header-target-option-with-f-tests PROPERTIES FOLDER tests)
set_target_properties(show-header-target-option-with-return-tests PROPERTIES FOLDER tests)
set_target_properties(show-header-target-option-with-if-tests PROPERTIES FOLDER tests)
set_target_properties(show-header-target-option-with-for-tests PROPERTIES FOLDER tests)
set_target_properties(show-header-target-option-with-while-tests PROPERTIES FOLDER tests)
set_target_properties(show-header-target-option-with-time-tests PROPERTIES FOLDER tests)
set_target_properties(show-header-target-option-with-time-stats-tests PROPERTIES FOLDER tests)
set_target_properties(show-header-target-option-with-clocks-tests PROPERTIES FOLDER tests)
set_target_properties(show-header-target-option-with-clock-stats-tests PROPERTIES FOLDER tests)

#
# Build optimizations

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-header-target-option-with-t-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-header-target-option-with-tbin-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-header-target-option-with-toct-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-header-target-option-with-thex-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-header-target-option-with-tr-begin-end-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-header-target-option-with-tr-begin-how-much-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-header-target-option-with-tr-begin-end-how-much-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-header-target-option-with-m-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-header-target-option-with-s-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-header-target-option-with-f-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-header-target-option-with-return-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-header-target-option-with-if-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-header-target-option-with-for-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-header-target-option-with-while-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-header-target-option-with-time-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-header-target-option-with-time-stats-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-header-target-option-with-clocks-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

if (TRACE_OUT_USE_PCH)
	target_link_libraries(show-header-target-option-with-clock-stats-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

