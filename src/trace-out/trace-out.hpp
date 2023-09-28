#pragma once

#if !defined(TRACE_OUT_OFF)

//
// Public

#define $t(...) \
			trace_out::trace(TRACE_OUT_STREAM_NAMESPACE::stream(), TRACE_OUT_FILE_LINE, #__VA_ARGS__, ##__VA_ARGS__)

#define $r(begin, end_OR_how_much) \
			trace_out::range(TRACE_OUT_STREAM_NAMESPACE::stream(), TRACE_OUT_FILE_LINE, #begin, #end_OR_how_much, (begin), (end_OR_how_much));

#define $bin trace_out::bin_or_hex_option(trace_out::BIN)
#define $hex trace_out::bin_or_hex_option(trace_out::HEX)
#define $sdec trace_out::decimal_option(trace_out::SDEC)
#define $udec trace_out::decimal_option(trace_out::UDEC)
#define $flt trace_out::floating_point_option(trace_out::FLT)
#define $dbl trace_out::floating_point_option(trace_out::DBL)
#define $ldbl trace_out::floating_point_option(trace_out::LDBL)
#define $be trace_out::BIG
#define $le trace_out::LITTLE
#define $col(value) trace_out::column_count_option(value)

#define $m(pointer, ...) \
			trace_out::print_memory(TRACE_OUT_STREAM_NAMESPACE::stream(), TRACE_OUT_FILE_LINE, #pointer, reinterpret_cast<const trace_out::standard::uint8_t *>(pointer), ##__VA_ARGS__);

#define $f \
			trace_out::function_printer trace_out_private__unify(trace_out_f) = trace_out::function_printer(TRACE_OUT_STREAM_NAMESPACE::stream(), TRACE_OUT_FILE_LINE, trace_out_private__strip_scope(TRACE_OUT_FUNCTION_SIGNATURE));

#define $return \
			return trace_out::return_printer(TRACE_OUT_STREAM_NAMESPACE::stream(), TRACE_OUT_FILE_LINE) ,

#define $if(...) \
			if (trace_out::if_block trace_out_private__unify(trace_out_if_block) = trace_out::if_block(TRACE_OUT_STREAM_NAMESPACE::stream(), TRACE_OUT_FILE_LINE, #__VA_ARGS__, (__VA_ARGS__)))

#define $for(...) \
			trace_out_private__loop(trace_out_private__unify(trace_out_for_block), for, ##__VA_ARGS__)

#define $while(...) \
			trace_out_private__loop(trace_out_private__unify(trace_out_for_block), while, ##__VA_ARGS__)

#define $s(...) \
			trace_out_private__statement(trace_out_private__unify(trace_out_tracing_stream), ##__VA_ARGS__)

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
			if (trace_out::loop_block block_variable_name = trace_out::loop_block(TRACE_OUT_STREAM_NAMESPACE::stream(), TRACE_OUT_FILE_LINE, #loop" ("#__VA_ARGS__")")) {} else \
				loop (__VA_ARGS__) \
					if (trace_out::iteration_block trace_out_private__unify(trace_out_iteration_block) = trace_out::iteration_block(TRACE_OUT_STREAM_NAMESPACE::stream(), TRACE_OUT_FILE_LINE, #loop, block_variable_name.iteration())) {} else

#define trace_out_private__statement(stream_variable_name, ...) \
			trace_out::trace(TRACE_OUT_STREAM_NAMESPACE::stream(), TRACE_OUT_FILE_LINE, NULL, #__VA_ARGS__ " // running..."); \
			__VA_ARGS__ \
			trace_out::trace(TRACE_OUT_STREAM_NAMESPACE::stream(), TRACE_OUT_FILE_LINE, NULL, #__VA_ARGS__ " // done.");

#define trace_out_private__time(start_time, execution_time, label, ...) \
			trace_out::standard::uint64_t start_time = trace_out::system::time_in_milliseconds(); \
			trace_out::trace(TRACE_OUT_STREAM_NAMESPACE::stream(), TRACE_OUT_FILE_LINE, NULL, "timing \"" label "\"..."); \
			__VA_ARGS__ \
			trace_out::standard::uint64_t execution_time = trace_out::system::time_in_milliseconds() - start_time; \
			trace_out::print_execution_time_in_milliseconds(TRACE_OUT_STREAM_NAMESPACE::stream(), TRACE_OUT_FILE_LINE, label, execution_time);

#define trace_out_private__clocks(start_clocks, execution_clocks, label, ...) \
			std::clock_t start_clocks = std::clock(); \
			trace_out::trace(TRACE_OUT_STREAM_NAMESPACE::stream(), TRACE_OUT_FILE_LINE, NULL, "clocking \"" label "\"..."); \
			__VA_ARGS__ \
			std::clock_t execution_clocks = std::clock() - start_clocks; \
			trace_out::print_execution_time_in_clocks(TRACE_OUT_STREAM_NAMESPACE::stream(), TRACE_OUT_FILE_LINE, label, execution_clocks, static_cast<double>(execution_clocks) / CLOCKS_PER_SEC * 1000.0);

#define trace_out_private__time_stats(start_time, execution_time, results, measurements, label, passes, ...) \
			static std::vector<trace_out::standard::uint64_t> results; \
			results.reserve(passes); \
			trace_out::standard::uint64_t start_time = trace_out::system::time_in_milliseconds(); \
			__VA_ARGS__ \
			trace_out::standard::uint64_t execution_time = trace_out::system::time_in_milliseconds() - start_time; \
			results.push_back(execution_time); \
			if (results.size() == passes) \
			{ \
				trace_out::print_execution_statistics(TRACE_OUT_STREAM_NAMESPACE::stream(), TRACE_OUT_FILE_LINE, label, results, "ms"); \
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
				trace_out::print_execution_statistics(TRACE_OUT_STREAM_NAMESPACE::stream(), TRACE_OUT_FILE_LINE, label, results, "clocks"); \
				results.clear(); \
			}

#else

#define $t(...) \
			__VA_ARGS__

#define $r(...)

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
#include "trace-out/pretty-range.hpp"
#include "trace-out/pretty-return.hpp"
#include "trace-out/pretty-time.hpp"
#include "trace-out/pretty-trace.hpp"
#include "trace-out/time.hpp"
#include <ctime>
#include <ostream>
#include <vector>

#if defined(TRACE_OUT_STREAM)
	#define TRACE_OUT_STREAM_NAMESPACE TRACE_OUT_STREAM
	#if !defined(TRACE_OUT_STREAM_STORAGE)
		#define TRACE_OUT_STREAM_STORAGE extern
	#endif
#elif defined(TRACE_OUT_TO_FILE)
	#define TRACE_OUT_STREAM_NAMESPACE trace_out_to_file
	#define TRACE_OUT_STREAM_STORAGE static
	#include "trace-out/to-file.hpp"
#elif defined(TRACE_OUT_TO_WDO)
	#define TRACE_OUT_STREAM_NAMESPACE trace_out_to_wdo
	#define TRACE_OUT_STREAM_STORAGE static
	#include "trace-out/to-wdo.hpp"
#elif defined(TRACE_OUT_TO_NETWORK)
	#define TRACE_OUT_STREAM_NAMESPACE trace_out_to_network
	#define TRACE_OUT_STREAM_STORAGE static
	#include "trace-out/to-network.hpp"
#else
	#define TRACE_OUT_TO_STDOUT
	#define TRACE_OUT_STREAM_NAMESPACE trace_out_to_stdout
	#define TRACE_OUT_STREAM_STORAGE static
	#include "trace-out/to-stdout.hpp"
#endif

namespace TRACE_OUT_STREAM_NAMESPACE
{

TRACE_OUT_STREAM_STORAGE std::ostream &stream();

}

