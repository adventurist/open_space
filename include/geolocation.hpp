#ifndef __GEO_LOCATION_HPP__
#define __GEO_LOCATION_HPP__

#include <type_traits>
#include <utility>
#include <limits>
#include <random>
#include <string>
#include <iostream>

#define HALF_INT_MAX 1073741823
/**
 * Constants
 */
namespace Constants {
  static constexpr int LAT_LIMIT = 90;
  static constexpr int LNG_LIMIT = 180;

  enum DegreeType {
    LATITUDE = 0, LONGITUDE = 1
  };
} // namespace Constants

using D = Constants::DegreeType;

/**
 * class GeoCoordinate
 *
 * Latitude from -90 to 90 degrees
 * Longitude from -180 to 180 degrees
 */
template <typename T>
class GeoCoordinate {

  T                       value;
  Constants::DegreeType   t;

 protected:
 /**
  * limit
  *
  * @return[out] {T} The absolute value of the limit for this coordinate type
  */
  T limit() {
    return t == Constants::DegreeType::LATITUDE ?
      Constants::LAT_LIMIT :
      Constants::LNG_LIMIT;
  }

/**
 * shift
 *
 * Movement is calculated here
 *
 * @static
 *
 * @param
 * @param
 */
  static void shift(GeoCoordinate<T>& c, T d) {
    std::cout << "adding " << d << " to " << c.getValue() << std::endl;
    if (withinLimit(c, d)) {
      std::cout << "within limit" << std::endl;
      c.value = c.value + d;
    } else {
      std::cout << "outside limit" << std::endl;
      auto modifier = c.getValue() < 0 ? -1 : 1;
      std::cout << "modifier " << modifier << std::endl;
      if (d < 0) {
        c.value = 0 - (d + (c.limit() - (modifier * c.value)));
      } else {
        c.value = 0 - (d - (c.limit() - (modifier * c.value)));
      }
    }
    if (c.getValue() > c.limit()) {
      throw std::logic_error{
        std::string{
          "GeoCoordinate::shift() failed.\nFinal value was" + std::to_string(c.getValue())
        }
      };
    }
  }

 public:
 /**
  * GeoCoordinate
  *
  * constructor
  *
  * @param
  * @param
  */
  GeoCoordinate(T value_, D type_) : value(value_), t(type_) {
    if (!std::is_arithmetic<T>()) {
      throw std::invalid_argument{"Must be numeric"};
    }
  }
  /**
   * GeoCoordinate offset operator
   */
  void operator+(const GeoCoordinate& other) {
    GeoCoordinate::shift(*this, other.getValue());
  }

  /**
   * ostream operator
   */
  friend std::ostream& operator<<(std::ostream& o, const GeoCoordinate<T> c) {
    return (o << c.value);
  }

  /**
   * getValue
   *
   * @returns[out] {T} A const copy of the coordinate value
   */
  T getValue() const { return value; }

  /**
   * type
   *
   * @returns[out] {D} The coordinate type
   */
  D type() const { return t;}
};

template <typename T>
class GeoLocation {
  GeoCoordinate<T> lat;
  GeoCoordinate<T> lgt;

 public:
 /**
  * GeoLocation
  *
  * constructor
  *
  * @param[in] {T} latitude_
  * @param[in] {T} longitude_
  */
  GeoLocation(T latitude_, T longitude_)
      : lat(latitude_, D::LATITUDE),
        lgt(longitude_, D::LONGITUDE) {

        }

  /**
   * GeoLocation offset operator
   */
  void operator+(const GeoLocation<T>& delta) {
    *this + delta.lat;
    *this + delta.lgt;
  }

  /**
   * GeoCoordinate offset operator
   */
  void operator+(const GeoCoordinate<T>& delta) {
    if (delta.type() == D::LATITUDE) {
      lat + delta;
    } else {
      lgt + delta;
    }
  }

  /**
   * ostream operator
   */
  friend std::ostream& operator<<(std::ostream& o, GeoLocation<T>& g) {
    o << g.lat << " : " << g.lgt << std::endl;
    return o;
  }

  static GeoLocation<T> measureDistance(const GeoLocation<T>& a, const GeoLocation<T> b) {
    return GeoLocation<T>{b.latitude() - a.latitude(), b.longitude() - a.longitude()};
  }

  /**
   * longitude
   */
  T longitude() const { return lgt.getValue(); }

  /**
   * latitude
   */
  T latitude() const { return lat.getValue(); }
};

/**
 * @param[in] {const GeoCoordinate<T>&}   c       A const GeoCoordinate reference with
 *                                                a numeric template parameter
 *
 * @param[in] {T}                         delta   The value by which to measure an
 *                                                offset of the geocoordinate
 */
template <typename T>
inline bool withinLimit(const GeoCoordinate<T>& c, T delta) {
  auto bottom = std::is_signed<T>() && c.getValue() < 0;
  if (bottom) {
    return c.type() == D::LATITUDE ?
      (c.getValue() + delta) > (-Constants::LAT_LIMIT) :
      (c.getValue() + delta) > (-Constants::LNG_LIMIT);
  }
  return c.type() == D::LATITUDE ?
     (c.getValue() + delta) < Constants::LAT_LIMIT :
     (c.getValue() + delta) < Constants::LNG_LIMIT;
}

namespace GeoUtil {
/**
 * Poor man's number gen
 */
template <typename T>
inline T getRandom(T min = 1, T max = 10, bool positive_or_negative = false) {
  int random{};
  T modifier = 1;
  if (std::is_signed<T>()) {
    modifier = rand() > HALF_INT_MAX ? modifier * (-1) : modifier;
  }
  while (!((modifier * random) >= min && random <= max)) {
    random = modifier * rand() / 100000000;
  }
  return random;
}

/**
 * getGeoLocation
 *
 * Useful for applying arbitrary deltas to a GeoLocation instance
 *
 *
 */
inline GeoLocation<float> getGeoLocation() {
  return GeoLocation<float>{
    90.0f / getRandom<float>(),
    180.0f / getRandom<float>()
  };
}

/**
 * geoJSONFeature
 *
 * @returns[out] {std::string} A string whose value can be decoded as a complete geoJSON feature
 */
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
} // namespace GeoUtil
#endif // __GEO_LOCATION_HPP__
