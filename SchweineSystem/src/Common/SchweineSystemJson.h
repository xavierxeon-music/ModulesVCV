#ifndef SchweineSystemJsonH
#define SchweineSystemJsonH

#include <jansson.h>
#include <map>
#include <string>
#include <vector>

namespace SchweineSystem
{
   namespace Json
   {
      class Array;
      class Object;

      class Value
      {
      public:
         Value(json_t* value);
         Value(const bool& value);
         Value(const int64_t& value);
         Value(const double& value);
         Value(const std::string& value);

      public:
         Object toObject() const;
         Array toArray();
         bool toBool() const;
         int64_t toInt() const;
         double toReal() const;
         std::string toString() const;
         json_t* toJson() const;

      protected:
         json_t* json;
      };

      class Array : public Value
      {
      public:
         Array(json_t* array = nullptr);

      public:
         size_t size();
         void append(const Value& value);
         Value get(const size_t& index);
         std::vector<Value> asList() const;
      };

      class Object : public Value
      {
      public:
         Object(json_t* object = nullptr);

      public:
         void set(const std::string& key, const Value& value);
         Value get(const std::string& key);
         std::map<std::string, Value> asMap() const;
      };

   } // namespace Json
} // namespace SchweineSystem

#endif // NOT SchweineSystemJsonH
