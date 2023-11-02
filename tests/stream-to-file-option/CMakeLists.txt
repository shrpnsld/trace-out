add_executable(stream-to-file-option-tests)

target_compile_definitions(stream-to-file-option-tests
	PRIVATE
		TRACE_OUT_STREAM_TO_FILE="${CMAKE_CURRENT_BINARY_DIR}/trace-out-stream-to-file.log.cpp"
		TRACE_OUT_MARKER="@@"
		TRACE_OUT_SHOW_FILE_LINE
		TRACE_OUT_INDENTATION="  "
		TRACE_OUT_STRIP_SCOPE=1
		TRACE_OUT_SYNC_STREAM
		TRACE_OUT_SHOW_THREAD
		TRACE_OUT_WIDTH=70
)

target_link_libraries(stream-to-file-option-tests
	PRIVATE
		Catch2::Catch2WithMain
		helpers
		trace-out
)

target_sources(stream-to-file-option-tests
	PRIVATE
		stream-to-file-option.tests.cpp
)

catch_discover_tests(stream-to-file-option-tests)

set_target_properties(stream-to-file-option-tests PROPERTIES FOLDER tests)

if (TRACE_OUT_USE_PCH)
	target_link_libraries(stream-to-file-option-tests
		PRIVATE
			pch-helpers
			pch-standard
	)
endif()

