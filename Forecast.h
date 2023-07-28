#include "ISerializable.h"
#include <json/json.h>

class Forecast : ISerializable<Forecast> {

  public:
    double latitude;
    double longitude;
    double generationtime_ms;
    u_int16_t utc_offset_seconds;
    std::string timezone;
    std::string timezone_abbreviation;
    int16_t elevation;

    virtual const std::string toJson() {

      Json::Value root;
      root["latitude"] = latitude;
      root["longitude"] = longitude;
      root["generationtime_ms"] = generationtime_ms;
      root["utc_offset_seconds"] = utc_offset_seconds;
      root["timezone"] = timezone;
      root["timezone_abbreviation"] = timezone_abbreviation;
      root["elevation"] = elevation;

      Json::StyledWriter writer;      
      return writer.write( root );
    }
};

static Forecast forecastFromJson(const std::string& jsonData) {
  Forecast forecast = Forecast();

  Json::Value json;
  Json::Reader reader;
  if (!reader.parse(jsonData, json)) {
    std::cout << "Error parsing json" << std::endl;
  } else {
    forecast.latitude = json["latitude"].asDouble();
    forecast.longitude = json["longitude"].asDouble();
    forecast.generationtime_ms = json["generationtime_ms"].asDouble();
    forecast.timezone = json["timezone"].asString();
    forecast.elevation = json["elevation"].asInt();
    forecast.timezone_abbreviation = json["timezone_abbreviation"].asString();
  }

  return forecast;
}