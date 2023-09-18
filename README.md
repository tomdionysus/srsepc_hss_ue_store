# srsRAN EPC HSS UE Store

A concept project to extend [srsRAN](https://github.com/srsran/srsRAN_4G) to load subscriber UE information from a range of database sources, other than CSV.

## Roadmap

* Extract a common interface for loading UE context (complete)
* Implement the standard CSV loader under this interface (complete)
* Implement a MySQL loader under this interface (complete) 
* Implement a PostgreSQL loader under this interface (complete)
* Integrate `srsepc_hss_ue_store` into srsRAN_4G (pending)
	* Fork srsRAN_4G [https://github.com/tomdionysus/srsRAN_4G](https://github.com/tomdionysus/srsRAN_4G) (complete)
	* Bring in this code
	* Add new configuration options into srsEPC to select CSV / MySQL / PostgreSQL and set up the database connection if appropriate (not started)
	* Modify this implementation to handle updating SQN numbers in the DB
	* Open pull request (not started)

## Dependencies

* libmysqlclient-dev ([Debain](https://packages.debian.org/sid/libmysqlclient-dev))
* libpq-dev ([Debian](https://packages.debian.org/sid/libpq-dev))

## Building

Build is with `cmake`.

```bash
mkdir build
cd build
cmake ..

```

## Testing
srsepc_hss_ue_store uses [googletest](https://github.com/google/googletest). Follow the build instructions, then:

```bash
./srsepc_hss_ue_store_test
```

## License

For license details, see [LICENSE](LICENSE) file.