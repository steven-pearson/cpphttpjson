#include "ISerializable.h"

class Forecast : ISerializable<Forecast> {

  public:
    double latitude;
    double longitude;
    double generationtime_ms;
    u_int16_t utc_offset_seconds;
    std::string timezone;
    std::string timezone_abbreviation;
    int16_t elevation;

    virtual const void toJson(Json::Value& root) {

      root["latitude"] = latitude;
      root["longitude"] = longitude;
      root["generationtime_ms"] = generationtime_ms;
      root["utc_offset_seconds"] = utc_offset_seconds;
      root["timezone"] = timezone;
      root["timezone_abbreviation"] = timezone_abbreviation;
      root["elevation"] = elevation;
    }
};

static Forecast forecastFromJson(const std::string& jsonData) {
  Forecast forecast = Forecast();

  Json::Value json;
  Json::Reader reader;
  if (!reader.parse(jsonData, json)) {
    std::cout << "Error parsing json" << std::endl;
  } else {
    forecast.latitude = json.get("latitude", 0.0).asDouble();
    forecast.longitude = json.get("longitude", 0.0).asDouble();
    forecast.generationtime_ms = json.get("generationtime_ms", 0.0).asDouble();
    forecast.timezone = json.get("timezone", "").asString();
    forecast.elevation = json.get("elevation", 0).asInt();
    forecast.timezone_abbreviation = json.get("timezone_abbreviation", "").asString();
  }

  return forecast;
}