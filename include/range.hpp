#ifndef __RANGE_HPP__
#define __RANGE_HPP__

template <class T>
class Range {
private:
  class iter {
   private:
    T at;

   public:
    iter(T at) : at(at) {}
    bool operator!=(iter const& other) const { return at != other.at; }
    T const& operator*() const { return at; }
    iter& operator++() {
      ++at;
      return *this;
    }
  };
  T begin_val;
  T end_val;

 public:
  Range(T begin_val, T end_val) : begin_val(begin_val), end_val(end_val) {}
  iter begin() { return iter(begin_val); }
  iter end() { return iter(end_val); }
};

#endif  // __RANGE_HPP__
