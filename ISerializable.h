#include <string>
#include <json/json.h>

template <typename T>
class ISerializable {
public:  
  virtual const void toJson(Json::Value& root) = 0;
  virtual ~ISerializable(){};
};
