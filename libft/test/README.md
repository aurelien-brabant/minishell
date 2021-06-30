# Testing libft

## Dependencies

- The criterion testing framework [criterion test API](https://github.com/Snaipe/Criterion).
- `libbsd` to test some BSD-specific functions.

## Usage

### Running all the tests

Simply run `make test` from the root of the repository.

### Running a test suite individually

Just compile the test suite manually, and don't forget to link all the required dependencies and include the correct headers.
The following example command must be run at the root of the repository:

`$CC -lcriterion -lbsd -L. -lft -Iinclude test/suite/ft_strcmp_suite.c -o test_strcmp`

Where `$CC` is your compiler.
