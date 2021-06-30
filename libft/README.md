![abrabant's stats](https://badge42.herokuapp.com/api/stats/abrabant)

# libft

![tests](https://github.com/aurelien-brabant/libft/actions/workflows/tests.yml/badge.svg)
![norminette](https://github.com/aurelien-brabant/libft/actions/workflows/norminette.yml/badge.svg)

libft is my own C library,  made from scratch with the most basic features and functions of the C programming language. It's also the first project of the 42cursus at #42Born2Code.

This version is the one I maintain as long as I need to for my C projects at 42. You can find the graded and original version [here]().

## 42 school's linter

For the common core projects, we have to use the 42 school's linter, the [norminette](https://github.com/42School/norminette),
in order to ensure that our C code respects all the [rules](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf).

The norm is a good way for us to learn without coding badly, even if some constraints can be really questionable.

## Testing

### Using docker

You can test the libft easily by building the test image:

```bash
docker build -t abrabant/libft-test test
```

Then run a container based on the `abrabant/libft-test` and don't forget to
bind the root of the libft to `/libft` in the container. Assuming all of this
is done from the root of the libft you can do:

`docker run -v $PWD:/libft abrabant/libft-test`

### On any linux system

While the docker way is recommended, you can also test the libft on your own
system as long as the criterion test API is installed. Take a look at the
`test/README.md` file for more informations.

## Motivations
If you're not a 42 school, you may ask what is the purpose of "reinventing" the wheel with this library. At 42, we do not have
access to the standard library, or only to basic system call implementations such as `write` or `malloc`. This is why we can implement these useful and missing functions by ourselves and then use them in future projects. 

Of course, 99.99% of the time my own implementations will be less efficient than the original implementation, made by experienced programmers. But keep in mind that the goal here is to LEARN. Reinventing the wheel is bad, unless you do it for learning purposes!

Moreover, you'll find a lot of non-standard functions that are my pure creation, and this is also what makes the libft very personal at the end (and useful).

I always try and like to provide good documentation about what I am coding, therefore you'll find a lot of comments explaining things about how and why I implemented some things.

## Related

- [42school/norminette](https://github.com/42School/norminette)
- [alexandregv/norminette-action](https://github.com/alexandregv/norminette-action)
