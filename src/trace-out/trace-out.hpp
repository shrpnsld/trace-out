#pragma once

#if !defined(TRACE_OUT_OFF)

//
// Public

#define $t(...) \
			trace_out::trace(TRACE_OUT_STREAM_TO::stream(), TRACE_OUT_FILE_LINE, #__VA_ARGS__, ##__VA_ARGS__)

#define $tbin(...) \
			trace_out::trace_binary(TRACE_OUT_STREAM_TO::stream(), TRACE_OUT_FILE_LINE, #__VA_ARGS__, ##__VA_ARGS__)

#define $toct(...) \
			trace_out::trace_octal(TRACE_OUT_STREAM_TO::stream(), TRACE_OUT_FILE_LINE, #__VA_ARGS__, ##__VA_ARGS__)

#define $thex(...) \
			trace_out::trace_hexadecimal(TRACE_OUT_STREAM_TO::stream(), TRACE_OUT_FILE_LINE, #__VA_ARGS__, ##__VA_ARGS__)

#define $tr(first, second) \
			trace_out::trace_range(TRACE_OUT_STREAM_TO::stream(), TRACE_OUT_FILE_LINE, #first, #second, first, second);

#define $bin trace_out::base_option(trace_out::BIN)
#define $hex trace_out::base_option(trace_out::HEX)
#define $sdec trace_out::base_option(trace_out::SDEC)
#define $udec trace_out::base_option(trace_out::UDEC)
#define $flt trace_out::base_option(trace_out::FLT)
#define $dbl trace_out::base_option(trace_out::DBL)
#define $ldbl trace_out::base_option(trace_out::LDBL)
#define $grp(value) trace_out::grouping_option(value)
#define $be trace_out::byte_order_option(trace_out::BIG)
#define $le trace_out::byte_order_option(trace_out::LITTLE)
#define $col(value) trace_out::column_count_option(value)

#define $m(pointer, ...) \
			trace_out::print_memory(TRACE_OUT_STREAM_TO::stream(), TRACE_OUT_FILE_LINE, #pointer, reinterpret_cast<const trace_out::standard::uint8_t *>(pointer), ##__VA_ARGS__);

#define $f \
			trace_out::function_printer trace_out_private__unify(trace_out_f) = trace_out::function_printer(TRACE_OUT_STREAM_TO::stream(), TRACE_OUT_FILE_LINE, trace_out_private__strip_scope(TRACE_OUT_FUNCTION_SIGNATURE));

#define $return \
			return trace_out::return_printer(TRACE_OUT_STREAM_TO::stream(), TRACE_OUT_FILE_LINE) ,

#define $if(...) \
			if (trace_out::if_block trace_out_private__unify(trace_out_if_block) = trace_out::if_block(TRACE_OUT_STREAM_TO::stream(), TRACE_OUT_FILE_LINE, #__VA_ARGS__, (__VA_ARGS__)))

#define $for(...) \
			trace_out_private__loop(trace_out_private__unify(trace_out_for_block), for, ##__VA_ARGS__)

#define $while(...) \
			trace_out_private__loop(trace_out_private__unify(trace_out_for_block), while, ##__VA_ARGS__)

#define $s(...) \
			trace_out::trace(TRACE_OUT_STREAM_TO::stream(), TRACE_OUT_FILE_LINE, NULL, #__VA_ARGS__ " // running..."); \
			__VA_ARGS__ \
			trace_out::trace(TRACE_OUT_STREAM_TO::stream(), TRACE_OUT_FILE_LINE, NULL, #__VA_ARGS__ " // done.");

#define $thread(name) \
			trace_out::set_current_thread_name(#name);

#define $time(label, ...) \
			trace_out_private__time(trace_out_private__unify(trace_out_start_time), trace_out_private__unify(trace_out_end_time), label, ##__VA_ARGS__)

#define $clocks(label, ...) \
			trace_out_private__clocks(trace_out_private__unify(trace_out_start_clocks), trace_out_private__unify(trace_out_execution_clocks), label, ##__VA_ARGS__)

#define $time_stats(label, passes, ...) \
			trace_out_private__time_stats(trace_out_private__unify(trace_out_start_time), trace_out_private__unify(trace_out_execution_time), trace_out_private__unify(results), trace_out_private__unify(trace_out_measurements), label, passes, ##__VA_ARGS__)

#define $clock_stats(label, passes, ...) \
			trace_out_private__clock_stats(trace_out_private__unify(trace_out_start_time), trace_out_private__unify(trace_out_execution_time), trace_out_private__unify(results), trace_out_private__unify(trace_out_measurements), label, passes, ##__VA_ARGS__)

//
// Private

#define trace_out_private__loop(block_variable_name, loop, ...) \
			if (trace_out::loop_block block_variable_name = trace_out::loop_block(TRACE_OUT_STREAM_TO::stream(), TRACE_OUT_FILE_LINE, #loop" ("#__VA_ARGS__")")) {} else \
				loop (__VA_ARGS__) \
					if (trace_out::iteration_block trace_out_private__unify(trace_out_iteration_block) = trace_out::iteration_block(TRACE_OUT_STREAM_TO::stream(), TRACE_OUT_FILE_LINE, #loop, block_variable_name.iteration())) {} else

#define trace_out_private__time(start_time, execution_time, label, ...) \
			trace_out::standard::uint64_t start_time = trace_out::system::time_in_milliseconds(); \
			trace_out::trace(TRACE_OUT_STREAM_TO::stream(), TRACE_OUT_FILE_LINE, NULL, "timing \"" label "\"..."); \
			__VA_ARGS__ \
			trace_out::standard::uint64_t execution_time = trace_out::system::time_in_milliseconds() - start_time; \
			trace_out::print_execution_time_in_milliseconds(TRACE_OUT_STREAM_TO::stream(), TRACE_OUT_FILE_LINE, label, execution_time);

#define trace_out_private__clocks(start_clocks, execution_clocks, label, ...) \
			std::clock_t start_clocks = std::clock(); \
			trace_out::trace(TRACE_OUT_STREAM_TO::stream(), TRACE_OUT_FILE_LINE, NULL, "clocking \"" label "\"..."); \
			__VA_ARGS__ \
			std::clock_t execution_clocks = std::clock() - start_clocks; \
			trace_out::print_execution_time_in_clocks(TRACE_OUT_STREAM_TO::stream(), TRACE_OUT_FILE_LINE, label, execution_clocks, static_cast<double>(execution_clocks) / CLOCKS_PER_SEC * 1000.0);

#define trace_out_private__time_stats(start_time, execution_time, results, measurements, label, passes, ...) \
			static std::vector<trace_out::standard::uint64_t> results; \
			results.reserve(passes); \
			trace_out::standard::uint64_t start_time = trace_out::system::time_in_milliseconds(); \
			__VA_ARGS__ \
			trace_out::standard::uint64_t execution_time = trace_out::system::time_in_milliseconds() - start_time; \
			results.push_back(execution_time); \
			if (results.size() == passes) \
			{ \
				trace_out::print_execution_statistics(TRACE_OUT_STREAM_TO::stream(), TRACE_OUT_FILE_LINE, label, results, "ms"); \
				results.clear(); \
			}

#define trace_out_private__clock_stats(start_time, execution_time, results, measurements, label, passes, ...) \
			static std::vector<trace_out::standard::uint64_t> results; \
			results.reserve(passes); \
			trace_out::standard::uint64_t start_time = trace_out::system::time_in_milliseconds(); \
			__VA_ARGS__ \
			trace_out::standard::uint64_t execution_time = trace_out::system::time_in_milliseconds() - start_time; \
			results.push_back(execution_time); \
			if (results.size() == passes) \
			{ \
				trace_out::print_execution_statistics(TRACE_OUT_STREAM_TO::stream(), TRACE_OUT_FILE_LINE, label, results, "clocks"); \
				results.clear(); \
			}

#else

#define $t(...) \
			__VA_ARGS__

#define $tbin(...) \
			__VA_ARGS__

#define $toct(...) \
			__VA_ARGS__

#define $thex(...) \
			__VA_ARGS__

#define $tr(...)

#define $m(pointer, ...)

#define $f

#define $return \
			return

#define $if(...) \
			if (__VA_ARGS__)

#define $for(...) \
			for (__VA_ARGS__)

#define $while(...) \
			while (__VA_ARGS__)

#define $s(...) \
			__VA_ARGS__

#define $thread(name)

#define $time(label, ...) \
			__VA_ARGS__

#define $clocks(label, ...) \
			__VA_ARGS__

#define $time_stats(label, how_much, ...)

#define $clock_stats(label, how_much, ...)

#endif

#include "trace-out/current-thread-name.hpp"
#include "trace-out/integer.hpp"
#include "trace-out/macro-magic.hpp"
#include "trace-out/platform-detection.hpp"
#include "trace-out/pretty-code-blocks.hpp"
#include "trace-out/pretty-function.hpp"
#include "trace-out/pretty-memory.hpp"
#include "trace-out/pretty-return.hpp"
#include "trace-out/strip-scope.hpp"
#include "trace-out/pretty-time.hpp"
#include "trace-out/pretty-trace.hpp"
#include "trace-out/stream-to-endpoint.hpp"
#include "trace-out/stream-to-file.hpp"
#include "trace-out/stream-to-stdout.hpp"
#include "trace-out/stream-to-wdo.hpp"
#include "trace-out/time.hpp"
#include <ctime>
#include <ostream>
#include <vector>

#if !defined(TRACE_OUT_STREAM_TO)
	#if defined(TRACE_OUT_STREAM_TO_ENDPOINT)
		#define TRACE_OUT_STREAM_TO trace_out_stream_to_endpoint
	#elif defined(TRACE_OUT_STREAM_TO_FILE)
		#define TRACE_OUT_STREAM_TO trace_out_stream_to_file
	#elif defined(TRACE_OUT_STREAM_TO_WDO)
		#define TRACE_OUT_STREAM_TO trace_out_stream_to_wdo
	#else
		#define TRACE_OUT_STREAM_TO trace_out_stream_to_stdout
	#endif
#endif

namespace TRACE_OUT_STREAM_TO
{

std::ostream &stream();

}

