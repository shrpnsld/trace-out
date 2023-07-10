# trace-out

Printf debugging done the right way

Code:

```c++
#include "trace-out.hpp"

int main()
{
    $f // pretty-print when function is called and returned

    int answer {42};
    std::string moto {"hellomoto!"};
    $w(answer, moto) // print "answer" and "moto" values

    $if (answer == 42) // print condition value
        $return answer; // print return value

    $return 0; // print return value
}
```

Output:

```
int main()
{
    answer = 42
    moto = "hellomoto!"
    if (answer == 42) => true
        return 42
        
}    // int main()
```


## Features

* Easy to use.
* No additional dependencies.
* Output can be redirected.
* Crossplatform. Tested with:
  * Apple LLVM version 12.0.5
  * Microsoft Visual Studio 2019
* Free for all ([MIT license](LICENSE.txt)).



# Usage

Add trace-out files to your project and you're ready to go.


## Interface

trace-out's interface is based on macros that pretty-print information about their arguments.

### Value printing

`$w(<variable>)` *[C++03]* – print value of a variable.

`$w(<variable1>, <variable2>, ...)` *[C++11 and later]* – print values of listed variables.

`$e(<expression>)` – print value of passed in expression and return that value (can be used inside other expressions).

`$r(<begin>, <end>)`, `$r(<begin>, <how-much>)` – print values from range defined by iterators.

`$m(<pointer>, <size>, <base> | <byte-order>)` – print memory under `<pointer>`.

`<pointer>` – address of the memory to be printed. Type of the pointer defines byte grouping and default `<base>`. For example, memory under `unsigned char *` pointer will be grouped by 1 byte and hexadecimal numbers will be used; memory under `int *` will be grouped by 4 (or 8) bytes and signed decimal numbers will be used. For unknown types default grouping is by 1 byte and numerical base is hexadecimal.

`<size>` – size of memory in bytes.

`<base> | <byte-order>` (both optional) – numerical base for value representation and order of the bytes to use when converting bytes to the numeric values.

Numerical base flags (default value is determined as described above):

* `trace_out::BIN` – binary
* `trace_out::SDEC` – signed decimal
* `trace_out::UDEC` – unsigned decimal
* `trace_out::HEX` – hexadecimal (default)
* `trace_out::FLT` – single precision floating point number
* `trace_out::DBL` – double precision floating point number
* `trace_out::LDBL` – floating point number with precision equal to `long double` for current platform

Byte order flags (default value is determined automatically):

* `trace_out::LITTLE` – big-endian
* `trace_out::BIG` – little-endian

### Statement printing

`$if (<condition>)` – print condition value of the `if` statement.

`$for (<statements>)` – print number for each iteration of the `for` loop.

`$while (<condition>)` – print condition value for each iteration of the `while` loop.

`$return <expression>` – print expression value passed to the `return` statement.

### Other

`$f` – print function call and return labels. Must be used inside a function.

`$thread(<name>)` – set thread name that will be printed in the thread header.

`$p(<format>, ...)` – `printf`-like function.

`$time(<name>, <any-code>)` – measure code execution time in milliseconds.

`$clocks(<name>, <any-code>)` – measure code execution time in clocks.

`$time_stats(<name>, <passes>, <any-code>)` – gather code execution time measurements in milliseconds and print statistics (average, median, mode, range) each time number of passes has reached `<passes>` value.

`$clock_stats(<name>, <passes>, <any-code>)` – gather code execution time measurements in clocks and print statistics (average, median, mode, range) each time number of passes has reached `<passes>` value.

---

Macros `$w`, `$e`, `$return`, `$if` and `$while` support following types:

* all fundamental types, raw pointers, standard smart pointers, `std::string`, `std::pair`, `std::tuple`, `std::bitset`
* types that define member functions `.begin()` and `.end()` which return iterators
* sturctures and classes with data members or member functions `x`, `y`, `z`, `w`, `width`, `height`, `origin`, `size`, `left`, `top`, `right`, `bottom`, `real`, `imag` in both lowcase and Capital
* Unreal Engine 4 data types and containers (currently except `TMap`)

---

Macros `$f`, `$if`, `$for` and `$while` automatically shift indentation of the output inside their blocks.

---

Output is flushed before reading variables and dereferencing pointers that are passed from the outer context, thus it is more clear where things went wrong when memory was corrupted.

Code:

```c++
int bueno {456};
int &no_bueno {*(int *)nullptr};
$w(bueno, no_bueno) // using GCC will show "Segmentation fault" when try to read "no_bueno" value
```

Output:

```
int main()
{
    bueno = 456
    no_bueno = Segmentation fault: 11
```


## Output Redirection

To make custom redirection implement following functions within some namespace in `.cpp` file (no header required):

* `void print(const char *string)` – print `string`
* `void flush()` – flush output
* `size_t width()` – get width of the output in characters

To use custom redirection you should:

* Add `<redireciton>.cpp` file to a project.
* Define macro `TRACE_OUT_REDIRECTION` with a name of the namespace where redirection functions are defined.

---

There are built-in implementations for redirecting output to Windows debug output and to a file: `trace_out_to_wdo` and `trace_out_to_file` respectively. By defulat `trace_out_to_file` saves output to `trace-out.txt`. To change this define `TRACE_OUT_TO_FILE` with desired file name. No `<redirection>.cpp` files required when using these built-in redirections.


## Notes

trace-out is turned on if `NDEBUG` is not defined or `TRACE_OUT_ON` is defined; turned off if `NDEBUG` or `TRACE_OUT_OFF` is defined.

There is an output synchronization that prevents outputs from different threads to mix up. By default it is turned off. To enable syncronization define macro `TRACE_OUT_OUTPUT_SYNC_ON`.



# Option `#define`s

`TRACE_OUT_ON` – turn trace-out on.

`TRACE_OUT_OFF` – turn trace-out off.

`TRACE_OUT_MARKER` `<string>` – add text marker before every trace-out line (useful when trace-out prints to some shared output).

`TRACE_OUT_SHOW_FILE_LINE` – print file and line information for every trace-out macro.

`TRACE_OUT_INDENTATION` `<string>` – string that is used as an indentation for the actual output. Default value is 4 spaces.

`TRACE_OUT_STRIP_NAMESPACES` `<how-much>` – leave only last `<how-much>` namespace names in identifiers. Default value is `1`.

`TRACE_OUT_REDIRECTION` `<name>` – use redirection from namespace `<name>`.

`TRACE_OUT_OUTPUT_SYNC_ON` – enable output syncronization.

`TRACE_OUT_SHOW_THREAD` – show thread information.

`TRACE_OUT_WIDTH` `<how-much>` – width to which output is wrapped (actually only the thread header and memory output are wrapped). This macro overrides value returned by `<redirection-namespace>::width()` function. Default value for standard output is `79`.

`TRACE_OUT_CPP_VERSION` `<number>` – specify C++ standard version using same format as `__cplusplus` macro. Why? Visual Studio defines `__cplusplus` macro with the wrong value, but has option to fix this – `/Zc:__cplusplus`, which still can break some old code. So, to preserve project integrity, this macro can be used and it will affect only trace-out.



# Troubleshooting

* Passing variable or expression of unknown type to `$w`, `$e`, `$return`, `$if` or `$while` may cause (but usually should not) multiple compiler errors.

	*Fix:* try to cast to one of the supported types or try to pass single fields to these macros if type is struct/class/union.

* Using precompiled headers with Visual Studio will cause compiler error.

	*Fix #1:* exclude `trace-out.cpp` from precompilation process.

	*Fix #2:* the precompiled header should be manually included in the `trace-out.cpp` file.

* Visual Studio errors on using `std::auto_ptr`.

	*Fix #1:* define macro `TRACE_OUT_CPP_VERSION` with value `199711L`, `201103L` or `201402L`.

	*Fix #2:* use compiler option `/Zc:__cplusplus`.
