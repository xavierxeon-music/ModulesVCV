#ifndef SvinJsonH
#define SvinJsonH

#include <jansson.h>
#include <map>
#include <string>
#include <vector>

#include <MusicTools.h>

namespace Svin
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
         Value(const uint8_t& value);
         Value(const uint16_t& value);
         Value(const uint32_t& value);
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
         size_t size() const;
         void append(const Value& value);
         Value at(const size_t& index) const;
      };

      class Object : public Value
      {
      public:
         Object(json_t* object = nullptr);
         Object(const Bytes& data);
         Object(const std::string& data);

      public:
         void set(const std::string& key, const Value& value);
         void set(const std::string& key, const char* text); // override for strings, else produces bool
         Value get(const std::string& key) const;
         bool hasKey(const std::string& key) const;
         std::vector<std::string> compileKeyList() const;

         Bytes toBytes() const;
         std::string toString() const;
      };

   } // namespace Json
} // namespace Svin

#endif // NOT SvinJsonH
