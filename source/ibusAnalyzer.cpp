#include "ibusAnalyzer.h"
#include "ibusAnalyzerSettings.h"
#include <AnalyzerChannelData.h>

ibusAnalyzer::ibusAnalyzer()
:	Analyzer2(),  
	mSettings( new ibusAnalyzerSettings() ),
	mSimulationInitilized( false )
{
	SetAnalyzerSettings( mSettings.get() );
}

ibusAnalyzer::~ibusAnalyzer()
{
	KillThread();
}

void ibusAnalyzer::SetupResults()
{
	mResults.reset( new ibusAnalyzerResults( this, mSettings.get() ) );
	SetAnalyzerResults( mResults.get() );
	mResults->AddChannelBubblesWillAppearOn( mSettings->mInputChannel );
}

void ibusAnalyzer::WorkerThread()
{
	mSampleRateHz = GetSampleRate();

	mSerial = GetAnalyzerChannelData( mSettings->mInputChannel );

	if( mSerial->GetBitState() == BIT_LOW )
		mSerial->AdvanceToNextEdge();

	U32 samples_per_bit = mSampleRateHz / mSettings->mBitRate;
	U32 samples_to_first_center_of_first_data_bit = U32( 1.5 * double( mSampleRateHz ) / double( mSettings->mBitRate ) );

	U8 lowerByte = mSettings->mRCChannel*2 + 1;
	U8 upperByte = mSettings->mRCChannel*2 + 2;

	U8 msgByteCounter=0;
	U64 ibusFrameStart=0;
	U64 lastFrame=0;
	U16 channelData=0;
	U64 timeoutFrames = U32(double(mSampleRateHz) * 0.001);

	for( ; ; )
	{
		U8 data = 0;
		U8 mask = 1;

		mSerial->AdvanceToNextEdge(); //falling edge -- beginning of the start bit
		U64 starting_sample = mSerial->GetSampleNumber();

		if(starting_sample - lastFrame > timeoutFrames){
			msgByteCounter=0;
			ibusFrameStart = starting_sample;
		}
		lastFrame = mSerial->GetSampleNumber();
		
		mSerial->Advance( samples_to_first_center_of_first_data_bit );

		for( U32 i=0; i<8; i++ )
		{
			//let's put a dot exactly where we sample this bit:
			mResults->AddMarker( mSerial->GetSampleNumber(), AnalyzerResults::Dot, mSettings->mInputChannel );

			if( mSerial->GetBitState() == BIT_HIGH )
				data |= mask;

			mSerial->Advance( samples_per_bit );

			mask = mask << 1;
		}

		msgByteCounter++;

		if(msgByteCounter==lowerByte){
			channelData = data;
		}
		if(msgByteCounter==upperByte){
			channelData += data*256;
		}

		if(msgByteCounter==32){
			//we have a byte to save. 
			msgByteCounter=0;

			Frame frame;
			frame.mData1 = channelData;
			frame.mFlags = 0;
			frame.mStartingSampleInclusive = ibusFrameStart;
			frame.mEndingSampleInclusive = mSerial->GetSampleNumber();

			mResults->AddFrame( frame );
			mResults->CommitResults();

		}
	}
}

bool ibusAnalyzer::NeedsRerun()
{
	return false;
}

U32 ibusAnalyzer::GenerateSimulationData( U64 minimum_sample_index, U32 device_sample_rate, SimulationChannelDescriptor** simulation_channels )
{
	if( mSimulationInitilized == false )
	{
		mSimulationDataGenerator.Initialize( GetSimulationSampleRate(), mSettings.get() );
		mSimulationInitilized = true;
	}

	return mSimulationDataGenerator.GenerateSimulationData( minimum_sample_index, device_sample_rate, simulation_channels );
}

U32 ibusAnalyzer::GetMinimumSampleRateHz()
{
	return mSettings->mBitRate * 4;
}

const char* ibusAnalyzer::GetAnalyzerName() const
{
	return "ibus";
}

const char* GetAnalyzerName()
{
	return "ibus";
}

Analyzer* CreateAnalyzer()
{
	return new ibusAnalyzer();
}

void DestroyAnalyzer( Analyzer* analyzer )
{
	delete analyzer;
}