# trace-out

Printf debugging done the right way

## Features

* Header-only.
* No additional dependencies.
* Output can be redirected.
* Crossplatform.
* Free for all ([MIT license](LICENSE.txt)).

### Quick example

Code:

```c++
#include "trace-out.hpp"

int main(int argc, const char *argv[])
{
    $f // pretty-print when function is called and returned
    $t("ah sh1t, here we go again.");

    int answer {42};
    std::string moto {"hellomoto!"};
    $t(answer, moto); // print "answer" and "moto" values

    $if (answer == 42) // print condition value
        $return answer; // print return value

    $return 0; // print return value
}
```

Output:

```c++
int main(int argc, const char *argv[])
{
    // ah sh1t, here we go again.
    answer = 42
    moto = "hellomoto!"
    if (answer == 42) => true
    {
        return 42
    }
        
} // int main(int argc, const char *argv[])
```

# Usage

## Get it

You can get it any way you want, as long as it's one of these

### Download release

[Here](https://github.com/shrpnsld/trace-out/releases/latest)

### Install system-wide

```bash
$ git clone https://github.com/shrpnsld/trace-out  # 1. Download
$ cd trace-out; mkdir build; cd build; cmake ..    # 2. Generate build files
$ cmake --install .                                # 3. Install
```

### Generate single header manually

```bash
$ git clone https://github.com/shrpnsld/trace-out  # 1. Download
$ cd trace-out; mkdir build; cd build; cmake ..    # 2. Generate build files
$ cmake --build . --target trace-out.hpp           # 3. Generate single header
```

Then, you can find single header at `trace-out-amalgamated/trace-out.hpp` inside the build directory.

## Pretty-printing

trace-out has several macros defined that pretty-print information about code.

### Values

`$t(<variable>)` *[C++98]* – print value of a variable (can be used inside expressions).

`$t(<variable>...)` *[C++11 and later]* – print values of listed variables (can be used inside expresssions if one argument was passed).

`$t("<C-string-literal>")` – print some string.

`$tr(<begin>, <end>|<how_much>)` – print values from a range defined by a pair of iterators or iterator and item count.

### Memory

`$m(<pointer>, <size>, [$<base>], [$grp(<count>)], [$be|$le], [$col(<count>)])` – print memory under `<pointer>`.

* `<pointer>` – address of the memory to be printed
* `<size>` – size of the memory in bytes
* `$<base>` – numerical base; can be one of the following values: `$bin`, `$hex`, `$sdec`, `$udec`, `$flt`, `$dbl`, `$ldbl`
* `$grp(<count>)` – how much bytes should be grouped together in a single column (`1`, `2`, `4` or `8`); this affects only `$bin`, `$hex`, `$sdec`, `$udec` bases
*  `$be` and `$le` are big-endian and little-endian byte orders
* `$col(<count>)` – print memory in specified column count; if printing exceeds output stream width, then more optimal value will be calculated

`$<base>`, `$grp`, `$be`, `$le` and `$col` are all optional and non-positional, but should be listed after `<pointer>` and `<size>`.

The default memory representation is single-byte hexadecimals, with column count set to the maximum power of 2 that fits console width.

### Statements

`$if(<condition>)` – pretty-print `if` statement.

`$for(<statements>)` – pretty-print`for` loop.

`$while(<condition>)` – pretty-print `while` loop.

`$f` – print function call start and call end labels. Must be used inside a function.

`$return <expression>` – print expression value passed to the `return` statement.

`$s(...)` – trace statement execution.

Macros `$f`, `$if`, `$for` and `$while` shift output indentation inside their scope, and each thread has its own indentation.

### Other

`$thread(<name>)` – set thread name that will be printed in the thread header.

`$time(<name>, <any-code>)` – measure code execution time in milliseconds.

`$clocks(<name>, <any-code>)` – measure code execution time in clocks.

`$time_stats(<name>, <passes>, <any-code>)` – gather code execution time measurements in milliseconds and print statistics (average, median, mode, range) each time number of passes has reached `<passes>` value.

`$clock_stats(<name>, <passes>, <any-code>)` – gather code execution time measurements in clocks and print statistics (average, median, mode, range) each time number of passes has reached `<passes>` value.

### Supported types

* all fundamental types, raw pointers, most of standard library types
* types that define member functions `.begin()` and `.end()` which return iterators
* sturctures and classes with data members or member functions `x`, `y`, `z`, `w`, `width`, `height`, `origin`, `size`, `left`, `top`, `right`, `bottom`, `real`, `imag` in both *lowcase* and *Capital*

## Options

You can customize trace-out's behavior by defining the following macros.

### Output

`TRACE_OUT_MARKER` `<string>` – add text marker before every trace-out line.

`TRACE_OUT_SHOW_FILE_LINE` – print file and line.

`TRACE_OUT_STRIP_SCOPE ` `<how-much>` – show only `<how-much>` scope components when using `$f` macro.

`TRACE_OUT_INDENTATION` `<string>` – string that is used as an indentation. Default value is 4 spaces.

`TRACE_OUT_SHOW_THREAD` – show thread information.

### Behavior

`TRACE_OUT_OFF` – turn trace-out off.

`TRACE_OUT_SYNC_STREAM` – enable output syncronization.

`TRACE_OUT_STREAM_WIDTH` `<how-much>` – width to which output is wrapped (actually, only memory output is wrapped).

### Redirection

`TRACE_OUT_STREAM_TO_ENDPOINT` `"<host>:<port>"` – stream to a specified `<host>` and `<port>`.

`TRACE_OUT_STREAM_TO_FILE` `"<file-path>"` – stream to a specified file.

`TRACE_OUT_STREAM_TO_WDO` – stream to Windows debug output.

#### Custom redirection

If predefined redirections aren't enough, you can make your own (though with some involvement). To do this:

1. Create a derived implementation of `std::basic_streambuf<char>` that outputs wherever you want.
2. Create function `std::ostream &stream()` within some namespace. This function should return `std::ostream` instance, which uses your implementation of `std::basic_streambuf<char>`.
3. Define macro `TRACE_OUT_STREAM_TO` with the namespace where you've created `std::ostream &stream()`.

As an example, look at `trace-out-to-endpoint.hpp` or `trace-out-to-wdo.hpp` in `src/trace-out/` directory.

### Compatibility

`TRACE_OUT_CPP_VERSION` `<number>` – specify C++ standard version using same format as `__cplusplus` macro. Why? Visual Studio defines `__cplusplus` macro with the wrong value, and while it offers a fix with `/Zc:__cplusplus`, it can still cause issues in your project's code. So, to keep your project intact, you can use this macro, and it will only affect trace-out.
