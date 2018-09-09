#pragma once

#include <ctime>
#include <vector>

#include "trace-out/detail/stuff/platform-detection.hpp"
#include "trace-out/detail/standard/integer.hpp"
#include "trace-out/detail/pretty-printing/out-stream.hpp"
#include "trace-out/detail/pretty-printing/watch-printer.hpp"
#include "trace-out/detail/pretty-printing/range-printer.hpp"
#include "trace-out/detail/pretty-printing/function-printer.hpp"
#include "trace-out/detail/pretty-printing/memory-printer.hpp"
#include "trace-out/detail/pretty-printing/statements-printer.hpp"
#include "trace-out/detail/pretty-printing/time-printer.hpp"
#include "trace-out/detail/system/time.hpp"


#if defined(TRACE_OUT_CLANG)

	#pragma clang diagnostic push
	#pragma clang diagnostic ignored "-Wdollar-in-identifier-extension"
	#pragma clang diagnostic ignored "-Wvariadic-macros"
	#pragma clang diagnostic ignored "-Wgnu-zero-variadic-macro-arguments"

#elif defined(TRACE_OUT_GCC) || defined(TRACE_OUT_MINGW)

	#pragma GCC diagnostic push
	#pragma GCC diagnostic ignored "-Wvariadic-macros" // seems it does not turn off the warning if there's no C++11

#endif


#if (!defined(NDEBUG) && !defined(TRACE_OUT_OFF)) || defined(TRACE_OUT_ON)

	#define $e(...) \
				trace_out::detail::expression(TRACE_OUT_FILENAME_LINE, #__VA_ARGS__, ##__VA_ARGS__)

	#define $w(...) \
				trace_out::detail::watch(TRACE_OUT_FILENAME_LINE, #__VA_ARGS__, ##__VA_ARGS__);

	#define $r(begin, end_OR_how_much) \
				trace_out::detail::range(TRACE_OUT_FILENAME_LINE, #begin, #end_OR_how_much, (begin), (end_OR_how_much));

	#define $m(pointer, ...) \
				trace_out::detail::print_memory(TRACE_OUT_FILENAME_LINE, #pointer, pointer, ##__VA_ARGS__);

	#define $f \
				trace_out::detail::function_printer trace_out_private__unify(trace_out_f) = trace_out::detail::make_function_printer(TRACE_OUT_FILENAME_LINE, TRACE_OUT_FUNCTION_SIGNATURE);

	#define $return \
				return trace_out::detail::make_return_printer(TRACE_OUT_FILENAME_LINE) ,

	#define $if(...) \
				if (trace_out::detail::block trace_out_private__unify(trace_out_if_block) = trace_out::detail::if_block(TRACE_OUT_FILENAME_LINE, #__VA_ARGS__, (__VA_ARGS__)))

	#define trace_out_private__for(block_variable_name, ...) \
				if (trace_out::detail::for_block block_variable_name = trace_out::detail::make_for_block(TRACE_OUT_FILENAME_LINE, #__VA_ARGS__)) {} else \
					for (__VA_ARGS__) \
						if (trace_out::detail::block trace_out_private__unify(trace_out_iteration_block) = trace_out::detail::iteration_block(TRACE_OUT_FILENAME_LINE, block_variable_name.iteration())) {} else

	#define $for(...) \
				trace_out_private__for(trace_out_private__unify(trace_out_for_block), ##__VA_ARGS__)

	#define $while(...) \
				if (trace_out::detail::print_while_header(TRACE_OUT_FILENAME_LINE, #__VA_ARGS__), false) {} else \
					while (trace_out::detail::block trace_out_private__unify(trace_out_while_block) = trace_out::detail::while_block(TRACE_OUT_FILENAME_LINE, #__VA_ARGS__, (__VA_ARGS__)))

	#define $p(format, ...) \
				{ \
					trace_out::detail::out_stream stream(TRACE_OUT_FILENAME_LINE); \
					stream.printf(format, ##__VA_ARGS__); \
					stream << trace_out::detail::ENDLINE; \
				}

	#define $thread(name) \
				trace_out::detail::set_current_thread_name(#name);

	#define trace_out_private__time(start_time, execution_time, label, ...) \
				trace_out::detail::standard::uint64_t start_time = trace_out::detail::system::time_in_milliseconds(); \
				__VA_ARGS__ \
				trace_out::detail::standard::uint64_t execution_time = trace_out::detail::system::time_in_milliseconds() - start_time; \
				trace_out::detail::print_execution_time_in_milliseconds(TRACE_OUT_FILENAME_LINE, label, execution_time);

	#define $time(label, ...) \
				trace_out_private__time(trace_out_private__unify(trace_out_start_time), trace_out_private__unify(trace_out_end_time), label, ##__VA_ARGS__)

	#define trace_out_private__clocks(start_clocks, execution_clocks, label, ...) \
				std::clock_t start_clocks = std::clock(); \
				__VA_ARGS__ \
				std::clock_t execution_clocks = std::clock() - start_clocks; \
				trace_out::detail::print_execution_time_in_clocks(TRACE_OUT_FILENAME_LINE, label, execution_clocks, static_cast<double>(execution_clocks) / CLOCKS_PER_SEC * 1000.0);

	#define $clocks(label, ...) \
				trace_out_private__clocks(trace_out_private__unify(trace_out_start_clocks), trace_out_private__unify(trace_out_execution_clocks), label, ##__VA_ARGS__)

	#define trace_out_private__time_stats(start_time, execution_time, results, measurements, label, how_much, ...) \
				std::vector<trace_out::detail::standard::uint64_t> results; \
				for (unsigned int measurements = how_much; measurements > 0; --measurements) \
				{ \
					trace_out::detail::standard::uint64_t start_time = trace_out::detail::system::time_in_milliseconds(); \
					__VA_ARGS__ \
					trace_out::detail::standard::uint64_t execution_time = trace_out::detail::system::time_in_milliseconds() - start_time; \
					results.push_back(execution_time); \
				} \
				trace_out::detail::print_execution_statistics(TRACE_OUT_FILENAME_LINE, label, results, "ms");

	#define $time_stats(label, how_much, ...) \
				trace_out_private__time_stats(trace_out_private__unify(trace_out_start_time), trace_out_private__unify(trace_out_execution_time), trace_out_private__unify(results), trace_out_private__unify(trace_out_measurements), label, how_much, ##__VA_ARGS__)

	#define trace_out_private__clock_stats(start_time, execution_time, results, measurements, label, how_much, ...) \
				std::vector<trace_out::detail::standard::uint64_t> results; \
				for (unsigned int measurements = how_much; measurements > 0; --measurements) \
				{ \
					trace_out::detail::standard::uint64_t start_time = trace_out::detail::system::time_in_milliseconds(); \
					__VA_ARGS__ \
					trace_out::detail::standard::uint64_t execution_time = trace_out::detail::system::time_in_milliseconds() - start_time; \
					results.push_back(execution_time); \
				} \
				trace_out::detail::print_execution_statistics(TRACE_OUT_FILENAME_LINE, label, results, "clocks");

	#define $clock_stats(label, how_much, ...) \
				trace_out_private__clock_stats(trace_out_private__unify(trace_out_start_time), trace_out_private__unify(trace_out_execution_time), trace_out_private__unify(results), trace_out_private__unify(trace_out_measurements), label, how_much, ##__VA_ARGS__)

#elif defined(NDEBUG) || defined(TRACE_OUT_OFF)

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

