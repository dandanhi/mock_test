# Aync Test

## 준비사항
- abseil


## abseil build
```
git clone https://github.com/abseil/abseil-cpp.git
cd abseil-cpp
mkdir build && cd build
cmake -DBUILD_TESTING=ON -DABSL_USE_GOOGLETEST_HEAD=ON -DCMAKE_CXX_STANDARD=11 ..
cd googletest-build
make
```

## replace googletest library with it
