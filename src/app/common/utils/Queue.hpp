#pragma once

#include <cstdint>
#include <vector>

namespace app
{

template <typename TYPE>
class Queue
{
public:
    Queue(Queue const&) = delete;
    Queue& operator=(Queue const&) = delete;

    explicit Queue(std::size_t capacity_)
        : capacity(capacity_)
        , len(0)
        , begin(0)
        , end(0)
    {
        data.reserve(capacity);
    }
    ~Queue()
    {}
    void push(TYPE const& val)
    {
        data[end] = val;
        end = (end + 1) % capacity;
        len += 1;
    }
    void pop()
    {
        begin = (begin + 1) % capacity;
        len -= 1;
    }
    TYPE const& front() const
    {
        return data[begin];
    }
    bool empty() const
    {
        return len == 0;
    }
private:
    std::size_t const capacity;
    std::vector<TYPE> data;
    std::size_t len;
    std::size_t begin;
    std::size_t end;
};


} // namespace app
