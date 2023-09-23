# Science Engine

A C++ Toolkit for Scientific Computing (Work In Progress)

## Full Build
```bash
cmake -B build -DBUILD_EXAMPLES=ON -DBUILD_TESTS=ON
```

## Build Examples Only
```bash
cmake -B build -DBUILD_EXAMPLES=ON -DBUILD_TESTS=OFF
```

## TODO
- [ ] Carefully deal with all the pointers, especially at finalization.
- [ ] JSON for computation graph
