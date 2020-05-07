Documenting a C extension with stub files
=========================================

This is a working example for the use case described in [this comment](https://github.com/sphinx-doc/sphinx/pull/4824#issuecomment-625215984).

Naturally, it's not possible to extract the exact signature of `Buzz.fuzz` with `inspect.getfullargspec`, `inspect.signature` etc,
but Sphinx could make use of the PEP 484 stubs when provided. In this example, while a stub `fizz/__init__.pyi` is provided:

```python
class Buzz:
    def fuzz(self, x: str) -> None: ...
```

Sphinx renders a method with no arguments:


![no args](https://github.com/hoefling/sphinx-autodoc-c-ext-type-hints/raw/master/fizzext.png)

Using the signatures from stubs, the result could be:

![full sig](https://github.com/hoefling/sphinx-autodoc-c-ext-type-hints/raw/master/fizzext2.png)
