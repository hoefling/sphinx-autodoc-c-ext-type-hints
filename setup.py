from setuptools import setup, Extension


setup(
    name="fizz",
    version="0.1",
    ext_modules=[Extension("fizz", sources=["src/fizz.c"])],
    packages=["fizz"],
    package_dir={"": "src"},
    package_data={"fizz": ["py.typed", "*.pyi"]},
)
