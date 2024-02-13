function(add_compile_definitions_for_generator genrator)
	if (CMAKE_GENERATOR MATCHES "${generator}")
		add_compile_definitions("${ARGN}")
	endif()
endfunction()

function(target_compile_definitions_for_generator target genrator)
	if (CMAKE_GENERATOR MATCHES "${generator}")
		target_compile_definitions("${target}" "${ARGN}")
	endif()
endfunction()

