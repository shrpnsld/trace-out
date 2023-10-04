# automated tests are a bit tricky for this one,
# so making this as utility for manual testing

if (NOT WIN32)
	return()
endif()

add_executable(stream-to-wdo-option-tests)

target_compile_definitions(stream-to-wdo-option-tests
	PRIVATE
		TRACE_OUT_STREAM_TO_WDO
		TRACE_OUT_MARKER="@@"
		TRACE_OUT_SHOW_FILE_LINE
		TRACE_OUT_INDENTATION="  "
		TRACE_OUT_STRIP_SCOPE=1
		TRACE_OUT_SYNC_STREAM
		TRACE_OUT_SHOW_THREAD
		TRACE_OUT_WIDTH=70
)

target_link_libraries(stream-to-wdo-option-tests
	PRIVATE
		helpers
		trace-out
)

target_sources(stream-to-wdo-option-tests
	PRIVATE
		stream-to-wdo-option.tests.cpp
)

