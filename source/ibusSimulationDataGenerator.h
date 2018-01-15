#ifndef IBUS_SIMULATION_DATA_GENERATOR
#define IBUS_SIMULATION_DATA_GENERATOR

#include <SimulationChannelDescriptor.h>
#include <string>
class ibusAnalyzerSettings;

class ibusSimulationDataGenerator
{
public:
	ibusSimulationDataGenerator();
	~ibusSimulationDataGenerator();

	void Initialize( U32 simulation_sample_rate, ibusAnalyzerSettings* settings );
	U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channel );

protected:
	ibusAnalyzerSettings* mSettings;
	U32 mSimulationSampleRateHz;

protected:
	void CreateSerialByte();
	std::string mSerialText;
	U32 mStringIndex;

	SimulationChannelDescriptor mSerialSimulationData;

};
#endif //IBUS_SIMULATION_DATA_GENERATOR