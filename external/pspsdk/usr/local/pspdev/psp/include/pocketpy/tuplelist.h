#pragma once

#include "common.h"
#include "memory.h"
#include "str.h"
#include "vector.h"

namespace pkpy {

using List = pod_vector<PyObject*>;

struct Tuple {
    PyObject** _args;
    PyObject* _inlined[3];
    int _size;

    Tuple(int n);
    Tuple(std::initializer_list<PyObject*> list);
    Tuple(const Tuple& other);
    Tuple(Tuple&& other) noexcept;
    Tuple(List&& other) noexcept;
    ~Tuple();

    bool is_inlined() const { return _args == _inlined; }
    PyObject*& operator[](int i){ return _args[i]; }
    PyObject* operator[](int i) const { return _args[i]; }

    int size() const { return _size; }

    PyObject** begin() const { return _args; }
    PyObject** end() const { return _args + _size; }
};

// a lightweight view for function args, it does not own the memory
struct ArgsView{
    PyObject** _begin;
    PyObject** _end;

    ArgsView(PyObject** begin, PyObject** end) : _begin(begin), _end(end) {}
    ArgsView(const Tuple& t) : _begin(t.begin()), _end(t.end()) {}

    PyObject** begin() const { return _begin; }
    PyObject** end() const { return _end; }
    int size() const { return _end - _begin; }
    bool empty() const { return _begin == _end; }
    PyObject* operator[](int i) const { return _begin[i]; }

    List to_list() const;
    Tuple to_tuple() const;
};

}   // namespace pkpy