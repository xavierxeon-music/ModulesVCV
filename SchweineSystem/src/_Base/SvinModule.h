#ifndef SvinModuleH
#define SvinModuleH

#include <rack.hpp>

#include <rtmidi/RtMidi.h>

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

      template <typename MessageType>
      Module* busModule(const Side& side) const;

   protected:
      virtual void load(const Json::Object& rootObject);
      virtual void save(Json::Object& rootObject);
      float getSampleRate() const;
      // hub client
      bool hubConnected();
      void connectToHub();
      bool registerHubClient(const std::string& name);
      void sendDocumentToHub(const ::Midi::Channel& channel, const Json::Object& object, const uint8_t docIndex = 0);
      virtual void receivedDocumentFromHub(const ::Midi::Channel& channel, const Json::Object& object, const uint8_t docIndex);
      // bus
      template <typename MessageType>
      void registerAsBusModule();

      template <typename MessageType>
      void sendBusMessage(const Side& side, const MessageType& message);

      template <typename MessageType>
      MessageType getBusMessage(const Side& side);

   private:
      using Map = std::map<std::string, Module*>;

      class Majordomo : public Svin::Midi::Input, public Svin::Midi::Output
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

      template <typename MessageType>
      class Bus : public BusAbstract
      {
      public:
         using InstanceList = std::list<Module*>;

      public:
         static Bus* the();
         void append(Module* module);
         bool contains(Module* module);

      private:
         friend class BusAbstract;

      private:
         Bus();

      private:
         void removeModule(Module* module) override final;

      private:
         static Bus* me;
         InstanceList instanceList;
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
