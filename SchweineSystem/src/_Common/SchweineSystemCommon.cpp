#include "SchweineSystemCommon.h"

const SchweineSystem::Common::MidiInterfaceMap SchweineSystem::Common::midiInterfaceMap = {
   {Midi::Device::Splitter, "ESI M4U eX Port 4"},
   {Midi::Device::DopeferQuad1, "ESI M4U eX Port 1"},
   {Midi::Device::DopeferQuad2, "ESI M4U eX Port 1"},
   {Midi::Device::DopeferQuad3, "ESI M4U eX Port 1"},
   {Midi::Device::DopeferQuad4, "ESI M4U eX Port 1"},
   {Midi::Device::KeyStep1, "ESI M4U eX Port 5"},
   {Midi::Device::KeyStep2, "ESI M4U eX Port 5"},
   {Midi::Device::KeyStep3, "ESI M4U eX Port 6"},
   {Midi::Device::KeyStep4, "ESI M4U eX Port 6"},
   {Midi::Device::Daisy, "ESI M4U eX Port 4"},
   {Midi::Device::DrumTrigger, "ESI M4U eX Port 5"},
   {Midi::Device::VCVRack, "ESI M4U eX Port 6"},
   {Midi::Device::FlameCC, "ESI M4U eX Port 7"},
   {Midi::Device::BitBox, "ESI M4U eX Port 4"},
   {Midi::Device::BitBoxMicro, "ESI M4U eX Port 4"},
   {Midi::Device::UnusedA, ""},
   {Midi::Device::UnusedB, ""},
};
