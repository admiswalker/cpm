# Default archived libraries for CPM

See `cpm/packages` directory or [cpm_archive](https://github.com/admiswalker/cpm_archive) repository.

## Appendix

### Compression format and its compression ratio
CPM uses tar.xz to reduce the load on the distribution server based on the following results.

**Table:** Comparison results of compression local gcc-8.4.0 head and binaries.
|         |  compress<br>or archive | decompress<br>or unpack | file size |
| ------- | ---------- | ---------- | --------- |
| tar     |  0m 52s    |  0m 12s    |  331.6 MB |
| tar.bz2 |  1m 21s    |  0m 44s    |  318.5 MB |
| tar.gz  |  0m 52s    |  0m 12s    |  331.6 MB |
| tar.xz  |  6m 53s    |  0m 17s    |  180.4 MB |
| zip     |  1m 06s    |  0m 22s    |  377.3 MB |


### Build time
**Table:** Build time.
| build target | environment                                           | build time     |
| ------------ | ----------------------------------------------------- | -------------- |
| sstd-1.0.0   | 8 core, 32 GB / gcc-8.4.0 / Ubuntu 20.04 LTS          |  0 mins 20 sec |
| gcc-8.4.0    | 8 core, 32 GB / gcc-7.5.0 / Ubuntu 18.04 LTS (Docker) | 70 mins        |
| cmake-3.20.1 | 8 core, 32 GB / gcc-8.4.0 / Ubuntu 20.04 LTS          | 45 mins        |

Note. Building gcc and cmake may require a lot of memory. In this case, we recommend to use 32 or 64 GB RAM machine and adding a swap memory as insurance.
