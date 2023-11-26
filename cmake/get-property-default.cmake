# TODO:
#function(get_property_default)
#	...
#endfunction()

function(get_target_property_default variable target property default)
	get_target_property(value "${target}" "${property}")
	if ("${value}" STREQUAL "value-NOTFOUND")
		set(${variable} "${default}" PARENT_SCOPE)
	else()
		set(${variable} "${value}" PARENT_SCOPE)
	endif()
endfunction()

