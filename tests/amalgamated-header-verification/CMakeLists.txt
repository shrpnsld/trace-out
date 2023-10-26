add_executable(amalgamated-header-verification EXCLUDE_FROM_ALL)

target_compile_features(amalgamated-header-verification
	PRIVATE
		cxx_std_11
)

target_compile_definitions(amalgamated-header-verification
	PRIVATE
		TRACE_OUT_MARKER="@@"
		TRACE_OUT_SHOW_FILE_LINE
		TRACE_OUT_INDENTATION="  "
		TRACE_OUT_STRIP_SCOPE=1
		TRACE_OUT_SYNC_STREAM
		TRACE_OUT_SHOW_THREAD
		TRACE_OUT_WIDTH=70
)

target_link_libraries(amalgamated-header-verification
	PRIVATE
		helpers
		trace-out-amalgamated
)

target_sources(amalgamated-header-verification
	PRIVATE
		amalgamated-header-verification.tests.cpp
)

set_target_properties(amalgamated-header-verification PROPERTIES FOLDER tests)

