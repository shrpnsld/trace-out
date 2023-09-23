#pragma once

#include "trace-out/function-printer.hpp"
#include "trace-out/memory-printer.hpp"
#include "trace-out/out-stream.hpp"
#include "trace-out/range-printer.hpp"
#include "trace-out/return-printer.hpp"
#include "trace-out/statements-printer.hpp"
#include "trace-out/time-printer.hpp"
#include "trace-out/watch-printer.hpp"
#include "trace-out/integer.hpp"
#include "trace-out/filename-line.hpp"
#include "trace-out/macro-magic.hpp"
#include "trace-out/platform-detection.hpp"
#include "trace-out/time.hpp"
#include <ctime>
#include <vector>

#if defined(TRACE_OUT_CLANG)
	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
	#pragma clang diagnostic ignored "-Wvariadic-macros"
	#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"
#elif defined(TRACE_OUT_GCC) || defined(TRACE_OUT_MINGW)
	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wvariadic-macros" // seems it does not turn off the warning if there's no C++11
#endif

#if !defined(TRACE_OUT_OFF)

//
// Public

#define $e(...) \
			trace_out::expression(TRACE_OUT_FILENAME_LINE, #__VA_ARGS__, ##__VA_ARGS__)

#define $w(...) \
			trace_out::watch(TRACE_OUT_FILENAME_LINE, #__VA_ARGS__, ##__VA_ARGS__);

#define $r(begin, end_OR_how_much) \
			trace_out::range(TRACE_OUT_FILENAME_LINE, #begin, #end_OR_how_much, (begin), (end_OR_how_much));

#define $m(pointer, ...) \
			trace_out::print_memory(TRACE_OUT_FILENAME_LINE, #pointer, reinterpret_cast<const trace_out::standard::uint8_t *>(pointer), ##__VA_ARGS__);

#define $f \
			trace_out::function_printer trace_out_private__unify(trace_out_f) = trace_out::make_function_printer(TRACE_OUT_FILENAME_LINE, TRACE_OUT_FUNCTION_SIGNATURE);

#define $return \
			return trace_out::make_return_printer(TRACE_OUT_FILENAME_LINE) ,

#define $if(...) \
			if (trace_out::if_block trace_out_private__unify(trace_out_if_block) = trace_out::make_if_block(TRACE_OUT_FILENAME_LINE, #__VA_ARGS__, (__VA_ARGS__)))

#define $for(...) \
			trace_out_private__loop(trace_out_private__unify(trace_out_for_block), for, ##__VA_ARGS__)

#define $while(...) \
			trace_out_private__loop(trace_out_private__unify(trace_out_for_block), while, ##__VA_ARGS__)

#define $t(...) \
			trace_out_private__trace(trace_out_private__unify(trace_out_tracing_stream), ##__VA_ARGS__)

#define $p(format, ...) \
			{ \
				trace_out::out_stream stream(TRACE_OUT_FILENAME_LINE); \
				stream.printf(format, ##__VA_ARGS__); \
				stream << trace_out::ENDLINE; \
			}

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
			if (trace_out::loop_block block_variable_name = trace_out::make_loop_block(TRACE_OUT_FILENAME_LINE, #loop" ("#__VA_ARGS__")")) {} else \
				loop (__VA_ARGS__) \
					if (trace_out::block trace_out_private__unify(trace_out_iteration_block) = trace_out::iteration_block(TRACE_OUT_FILENAME_LINE, #loop, block_variable_name.iteration())) {} else

#define trace_out_private__trace(stream_variable_name, ...) \
			trace_out::out_stream(TRACE_OUT_FILENAME_LINE) << #__VA_ARGS__; \
			__VA_ARGS__ \
			trace_out::out_stream(trace_out::CONTINUE) << " // trace-out: statement passed" << trace_out::ENDLINE;

#define trace_out_private__time(start_time, execution_time, label, ...) \
			trace_out::standard::uint64_t start_time = trace_out::system::time_in_milliseconds(); \
			__VA_ARGS__ \
			trace_out::standard::uint64_t execution_time = trace_out::system::time_in_milliseconds() - start_time; \
			trace_out::print_execution_time_in_milliseconds(TRACE_OUT_FILENAME_LINE, label, execution_time);

#define trace_out_private__clocks(start_clocks, execution_clocks, label, ...) \
			std::clock_t start_clocks = std::clock(); \
			__VA_ARGS__ \
			std::clock_t execution_clocks = std::clock() - start_clocks; \
			trace_out::print_execution_time_in_clocks(TRACE_OUT_FILENAME_LINE, label, execution_clocks, static_cast<double>(execution_clocks) / CLOCKS_PER_SEC * 1000.0);

#define trace_out_private__time_stats(start_time, execution_time, results, measurements, label, passes, ...) \
			static std::vector<trace_out::standard::uint64_t> results; \
			results.reserve(passes); \
			trace_out::standard::uint64_t start_time = trace_out::system::time_in_milliseconds(); \
			__VA_ARGS__ \
			trace_out::standard::uint64_t execution_time = trace_out::system::time_in_milliseconds() - start_time; \
			results.push_back(execution_time); \
			if (results.size() == passes) \
			{ \
				trace_out::print_execution_statistics(TRACE_OUT_FILENAME_LINE, label, results, "ms"); \
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
				trace_out::print_execution_statistics(TRACE_OUT_FILENAME_LINE, label, results, "clocks"); \
				results.clear(); \
			}

#else

#define $e(...) \
			__VA_ARGS__

#define $w(...)

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

#define $p(format, ...)

#define $t(...) \
			__VA_ARGS__

#define $thread(name)

#define $time(label, ...) \
			__VA_ARGS__

#define $clocks(label, ...) \
			__VA_ARGS__

#define $time_stats(label, how_much, ...)

#define $clock_stats(label, how_much, ...)

#endif

#if defined(TRACE_OUT_CLANG)
	#pragma clang diagnostic pop
#elif defined(TRACE_OUT_GCC) || defined(TRACE_OUT_MINGW)
	#pragma GCC diagnostic pop
#endif

