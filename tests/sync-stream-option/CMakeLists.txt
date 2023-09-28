add_executable(sync-stream-option-tests)

target_compile_features(sync-stream-option-tests
	PUBLIC
		cxx_std_11
)

target_compile_definitions(sync-stream-option-tests
	PRIVATE
		TRACE_OUT_STREAM=test
		TRACE_OUT_WIDTH=70
		TRACE_OUT_SYNC_STREAM
)

target_link_libraries(sync-stream-option-tests
	PRIVATE
		trace-out
		Catch2::Catch2WithMain
		helpers
)

target_sources(sync-stream-option-tests
	PRIVATE
		sync-stream-option.tests.cpp
)

add_test(NAME [[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$t(...)']]
	COMMAND
		${CMAKE_CURRENT_BINARY_DIR}/sync-stream-option-tests
		[["no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$t(...)'"]]
)
set_tests_properties([[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$t(...)']]
	PROPERTIES
		TIMEOUT 5
)

add_test(NAME [[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$r(...)']]
	COMMAND
		${CMAKE_CURRENT_BINARY_DIR}/sync-stream-option-tests
		[["no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$r(...)'"]]
)
set_tests_properties([[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$r(...)']]
	PROPERTIES
		TIMEOUT 5
)

add_test(NAME [[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$m(...)']]
	COMMAND
		${CMAKE_CURRENT_BINARY_DIR}/sync-stream-option-tests
		[["no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$m(...)'"]]
)
set_tests_properties([[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$m(...)']]
	PROPERTIES
		TIMEOUT 5
)

add_test(NAME [[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$s(...)']]
	COMMAND
		${CMAKE_CURRENT_BINARY_DIR}/sync-stream-option-tests
		[["no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$s(...)'"]]
)
set_tests_properties([[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$s(...)']]
	PROPERTIES
		TIMEOUT 5
)

add_test(NAME [[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$f(...)']]
	COMMAND
		${CMAKE_CURRENT_BINARY_DIR}/sync-stream-option-tests
		[["no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$f(...)'"]]
)
set_tests_properties([[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$f(...)']]
	PROPERTIES
		TIMEOUT 5
)

add_test(NAME [[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$if(...)']]
	COMMAND
		${CMAKE_CURRENT_BINARY_DIR}/sync-stream-option-tests
		[["no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$if(...)'"]]
)
set_tests_properties([[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$if(...)']]
	PROPERTIES
		TIMEOUT 5
)

add_test(NAME [[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$for(...)']]
	COMMAND
		${CMAKE_CURRENT_BINARY_DIR}/sync-stream-option-tests
		[["no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$for(...)'"]]
)
set_tests_properties([[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$for(...)']]
	PROPERTIES
		TIMEOUT 5
)

add_test(NAME [[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$while(...)']]
	COMMAND
		${CMAKE_CURRENT_BINARY_DIR}/sync-stream-option-tests
		[["no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$while(...)'"]]
)
set_tests_properties([[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$while(...)']]
	PROPERTIES
		TIMEOUT 5
)

add_test(NAME [[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$time(...)']]
	COMMAND
		${CMAKE_CURRENT_BINARY_DIR}/sync-stream-option-tests
		[["no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$time(...)'"]]
)
set_tests_properties([[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$time(...)']]
	PROPERTIES
		TIMEOUT 5
)

add_test(NAME [[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$time_stats(...)']]
	COMMAND
		${CMAKE_CURRENT_BINARY_DIR}/sync-stream-option-tests
		[["no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$time_stats(...)'"]]
)
set_tests_properties([[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$time_stats(...)']]
	PROPERTIES
		TIMEOUT 5
)

add_test(NAME [[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$clocks(...)']]
	COMMAND
		${CMAKE_CURRENT_BINARY_DIR}/sync-stream-option-tests
		[["no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$clocks(...)'"]]
)
set_tests_properties([[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$clocks(...)']]
	PROPERTIES
		TIMEOUT 5
)

add_test(NAME [[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$clock_stats(...)']]
	COMMAND
		${CMAKE_CURRENT_BINARY_DIR}/sync-stream-option-tests
		[["no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$clock_stats(...)'"]]
)
set_tests_properties([[no deadlock with 'TRACE_OUT_SYNC_STREAM' and '$clock_stats(...)']]
	PROPERTIES
		TIMEOUT 5
)

