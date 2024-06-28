#ifndef SvinModuleH
#define SvinModuleH

#include <rack.hpp>

#include <MusicTools.h>

#include <SvinJson.h>
#include <SvinMidi.h>

namespace Svin
{
   class Module : public rack::Module
   {
   public:
      using Queue = std::list<Bytes>;

      enum class Side
      {
         Left,
         Right
      };

   public:
      Module();
      ~Module();

   public:
      virtual void updateDisplays();
      std::string getOpenFileName(const std::string& filter) const;

      template <typename DataType>
      Module* busModule(const Side& side) const;

   protected:
      template <typename DataType>
      struct Message
      {
         DataType data;
         Json::Object document;
         const Module* sender;

         using List = std::list<Message>;
      };

   protected:
      virtual void load(const Json::Object& rootObject);
      virtual void save(Json::Object& rootObject);
      float getSampleRate() const;

      // hub client
      bool LinkControled();
      void connectToHub();
      bool registerHubClient(const std::string& name);
      void sendDocumentToHub(const ::Midi::Channel& channel, const Json::Object& object, const uint8_t docIndex = 0);
      virtual void receivedDocumentFromHub(const ::Midi::Channel& channel, const Json::Object& object, const uint8_t docIndex);

      // bus
      template <typename DataType>
      void registerAsBusModule();

      template <typename DataType>
      void sendBusData(const Side& side, const DataType& data);

      template <typename DataType>
      DataType getBusData(const Side& side);

      // bus search
      template <typename DataType>
      uint8_t indexOfBusModule(const Side& side, Module* module);

      template <typename DataType, typename ModuleType>
      ModuleType* findFirstBusModule(const Side& side);

      template <typename DataType, typename ModuleType>
      ModuleType* findLastBusModule(const Side& side, bool consecutive);

      // bus broadcast
      template <typename DataType>
      void broadcastMessage(const DataType& data, const Json::Object& document, const Module* target = nullptr);

      template <typename DataType>
      bool hasMessage();

      template <typename MessageType>
      Message<MessageType> popMessage();

   private:
      using Map = std::map<std::string, Module*>;

      class Majordomo : public Svin::MidiInput, public Svin::MidiOutput
      {
      public:
         Majordomo();
         ~Majordomo();

      public:
         bool add(Module* module, const std::string& name); // true if name not already registerred
         bool remove(Module* module);                       // true if no more modules are registerred
         bool connected();
         void tryConnect();

      private:
         void document(const ::Midi::Channel& channel, const Json::Object& object, const uint8_t docIndex) override;

      private:
         Map moduleMap;
      };

      class BusAbstract
      {
      public:
         using List = std::list<BusAbstract*>;

      public:
         BusAbstract();
         virtual ~BusAbstract();

      public:
         static void removeModuleFromAllBuses(Module* module);

      protected:
         virtual void removeModule(Module* module) = 0;

      protected:
         static List busList;
      };

      template <typename DataType>
      class Bus : public BusAbstract
      {
      public:
         using InstanceMap = std::map<Module*, typename Message<DataType>::List>;

      public:
         static Bus* the();
         void append(Module* module);
         bool contains(Module* module);

         void queue(const DataType& data, const Json::Object& document, const Module* sender, const Module* target);
         bool empty(Module* module) const;
         Message<DataType> takeFirst(Module* module);

      private:
         friend class BusAbstract;
         friend class Module;

      private:
         Bus();

      private:
         void removeModule(Module* module) override final;

      private:
         static Bus* me;
         InstanceMap instanceMap;
         mutable std::mutex mutex;
      };

   private:
      void dataFromJson(json_t* rootJson) override final;
      json_t* dataToJson() override final;

   private:
      static Majordomo* majordomo;
   };
} // namespace Svin

#ifndef SvinModuleHPP
#include "SvinModule.hpp"
#endif // NOT SvinModuleHPP

#endif // NOT SvinModuleH
