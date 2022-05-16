# Version comparison specifications

The CPM assumes the [semantic versioning](https://semver.org/) for versioning in `packages_cpm.txt` files. But the CPM can use version with more than 4 version numbers separated by the period (`.`), such as `x.y.z.a`, `x.y.z.a.b.c` or `x.y.z.a.b.c.d.e...` . And the delimited version number is treated as a larger value as the number is closer to the beginning. When the each delimited version number is not an Arabic numerals, the CPM defines a character's big or small according to the order of the ASCII Code.

The CPM can use wildcards such as `*` and `?` as an experimental trial. But note that the version processing between versions that include wildcards are not complete.

For other detailed operations, check the test code or try it. (Test code is in `cpm/test/version_processor.hpp`).
