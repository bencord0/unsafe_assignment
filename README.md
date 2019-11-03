# Unsafe Assignments

Some experiments with unsafe assignments, and how languages can guard against them.

## Usage

```
    $ make run
```

or run a specific implementation

```
    $ make -C rust
```

Note: You will need to have the required compilers and interpreters installed.

## Notes

For now, the C example is currently what I'm using as a starting point for other implementations.

"Features" include:

- OS threads (via pthread), this can be relaxed to "green" threads if it makes more sense for the
language/framework. I'm particularly interested in cases where application-aware threading still
requires synchronization primitives when used.

- Shared reference to a single instance of memory. In the C example, the variable to mutate is an
int-on-the-stack. Not all languages/frameworks give the programmer (easy) control over memory
allocation or referencing, so this can be relaxed to be a singleton-object-with-internal-mutability,
which many languages pass by reference.

- Sleep (or suspend if using an async pattern) based on a random bit. This may be relaxed to use a
random byte (or 1-lenght byte array) that is bit masked. The operating system provides the source
of random.

- Error checking left as minimal as possible, I'm more interested to see what debuggers, linters
and other tools can provide to raise the minimum bar required to get a clean run.

- Programs (in general) should be deterministic. This one isn't; multiple runs of these programs
might return different results. I'm looking to find what tooling exists to highlight
non-deterministic behaviour.

Over time, my plan is to integrate them into this repository, and then update the examples to be
the next most naive implementation until it is impossible to run the programs without tools
finding errors.
