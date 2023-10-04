# automated tests are a bit tricky for this one,
# so making this as utility for manual testing

add_executable(stream-to-endpoint-option-tests)

target_compile_definitions(stream-to-endpoint-option-tests
	PRIVATE
		TRACE_OUT_STREAM_TO_ENDPOINT="127.0.0.1:45678"
		TRACE_OUT_MARKER="@@"
		TRACE_OUT_SHOW_FILE_LINE
		TRACE_OUT_INDENTATION="  "
		TRACE_OUT_STRIP_SCOPE=1
		TRACE_OUT_SYNC_STREAM
		TRACE_OUT_SHOW_THREAD
		TRACE_OUT_WIDTH=70
)

target_link_libraries(stream-to-endpoint-option-tests
	PRIVATE
		helpers
		trace-out
)

target_sources(stream-to-endpoint-option-tests
	PRIVATE
		stream-to-endpoint-option.tests.cpp
)

