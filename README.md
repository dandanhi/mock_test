# mock test

## make test

- `docker run -v $(pwd):/code sungyong/gtest bash -c "make && ./client"`

## mock test
 - 1st
 ```
 ➜  db_mock docker run -v $(pwd):/code sungyong/gtest bash -c "make && ./Test"
 ```