#include <string>

template <typename T>
class ISerializable {
public:  
  virtual const std::string toJson() = 0;  
  virtual ~ISerializable(){};
};
