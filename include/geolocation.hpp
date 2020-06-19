#ifndef __GEO_LOCATION_HPP__
#define __GEO_LOCATION_HPP__

#include <type_traits>
#include <utility>
#include <limits>
#include <random>
#include <string>

namespace Constants {
  static constexpr int LAT_LIMIT = 90;
  static constexpr int LNG_LIMIT = 180;
} // namespace Constants

enum DegreeType { LATITUDE = 0, LONGITUDE = 1 };
using D = DegreeType;

template <typename T>
class GeoCoordinate {
  T value;
  D t;

 protected:

  T limit() {
    if (t == DegreeType::LATITUDE) {
      return Constants::LAT_LIMIT;
    }
    return Constants::LNG_LIMIT;
  }

  static void advance(GeoCoordinate<T>& c, T d) {
    if (withinLimit(c, d)) {
      c.value = c.value + d;
    } else {
      c.value = 0 - (d - (c.limit() - c.value));
    }
  }

  static void retreat(GeoCoordinate& c, T d) {
    if (withinLimit(c, d, true)) {
      c.value = c.value - d;
    } else {
      c.value = 0 - (-(c.limit()) - c.value) - d;
    }
  }

 public:
  GeoCoordinate(T value_, D type_) : value(value_), t(type_) {}

  // void operator+(const GeoLocation& other) {

  // }

  void operator+(const GeoCoordinate& other) {
    GeoCoordinate::advance(*this, other.getValue());
  }

  void operator-(const GeoCoordinate& other) {
    GeoCoordinate::retreat(*this, other.getValue());
   }

  friend std::ostream& operator<<(std::ostream& o, const GeoCoordinate<T> c) {
    return (o << c.value);
  }

  T getValue() const { return value; }

  D type() const { return t;}
};

template <typename T>
class GeoLocation {
  GeoCoordinate<T> lat;
  GeoCoordinate<T> lgt;

 public:
  GeoLocation(T latitude_, T longitude_)
      : lat(latitude_, DegreeType::LATITUDE),
        lgt(longitude_, DegreeType::LONGITUDE) {}

  void operator+(const GeoLocation<T>& delta) {
    *this + delta.lat;
    *this + delta.lgt;
  }

  void operator+(const GeoCoordinate<T>& delta) {
    if (delta.type() == D::LATITUDE) {
      lat + delta;
    } else {
      lgt + delta;
    }
  }

  void operator-(const GeoCoordinate<T>& delta) {
    if (delta.type() == D::LATITUDE) {
      lat - delta;
    } else {
      lgt - delta;
    }
  }

  friend std::ostream& operator<<(std::ostream& o, GeoLocation<T>& g) {
    o << g.lat << " : " << g.lgt << std::endl;
    return o;
  }

  T longitude() const {
    return lgt.getValue();
  }

  T latitude() const {
    return lat.getValue();
  }
};

template <typename T>
inline bool withinLimit(const GeoCoordinate<T>& c, T delta, bool bottom = false) {
  if (bottom) {
    return c.type() == DegreeType::LATITUDE ?
      c.getValue() - delta > (-Constants::LAT_LIMIT) :
      c.getValue() - delta > (-Constants::LNG_LIMIT);
  }
  return c.type() == DegreeType::LATITUDE ?
    c.getValue() + delta < Constants::LAT_LIMIT :
    c.getValue() + delta < Constants::LNG_LIMIT;
}

namespace GeoUtil {
  /**
 * Poor man's number gen
 */
template <typename T>
inline T getRandom(T min = 1, T max = 10) {
  int random{};
  while (!(random >= min && random <= max)) {
    random = rand() / 100000000;
  }
  return random;
}

/**
 * Discovery
 */
inline GeoLocation<float> getLocation() {
  return GeoLocation<float>{
    180.0f / getRandom<float>(),
    90.0f / getRandom<float>()
  };
}

inline std::string geoJSONFeature(GeoLocation<float> location, std::string id) {
  std::string geoJSONString{
    "{\"type\": \"Feature\",\
      \"geometry\": {\
        \"type\": \"Point\",\
        \"coordinates\": [" + std::to_string(location.longitude()) + ", " + std::to_string(location.latitude()) + "]\
       },\
      \"properties\": {\
        \"name\":\"" + id + "\"\
        }}"};

  return geoJSONString;
}
}
#endif // __GEO_LOCATION_HPP__
