#ifndef IBUS_ANALYZER_H
#define IBUS_ANALYZER_H

#include <Analyzer.h>
#include "ibusAnalyzerResults.h"
#include "ibusSimulationDataGenerator.h"

class ibusAnalyzerSettings;
class ANALYZER_EXPORT ibusAnalyzer : public Analyzer2
{
public:
	ibusAnalyzer();
	virtual ~ibusAnalyzer();

	virtual void SetupResults();
	virtual void WorkerThread();

	virtual U32 GenerateSimulationData( U64 newest_sample_requested, U32 sample_rate, SimulationChannelDescriptor** simulation_channels );
	virtual U32 GetMinimumSampleRateHz();

	virtual const char* GetAnalyzerName() const;
	virtual bool NeedsRerun();

protected: //vars
	std::auto_ptr< ibusAnalyzerSettings > mSettings;
	std::auto_ptr< ibusAnalyzerResults > mResults;
	AnalyzerChannelData* mSerial;

	ibusSimulationDataGenerator mSimulationDataGenerator;
	bool mSimulationInitilized;

	//Serial analysis vars:
	U32 mSampleRateHz;
	U32 mStartOfStopBitOffset;
	U32 mEndOfStopBitOffset;
};

extern "C" ANALYZER_EXPORT const char* __cdecl GetAnalyzerName();
extern "C" ANALYZER_EXPORT Analyzer* __cdecl CreateAnalyzer( );
extern "C" ANALYZER_EXPORT void __cdecl DestroyAnalyzer( Analyzer* analyzer );

#endif //IBUS_ANALYZER_H
