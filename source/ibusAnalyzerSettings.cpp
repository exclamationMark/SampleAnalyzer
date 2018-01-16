#include "ibusAnalyzerSettings.h"
#include <AnalyzerHelpers.h>


ibusAnalyzerSettings::ibusAnalyzerSettings()
:	mInputChannel( UNDEFINED_CHANNEL ),
	mBitRate( 115200 ),
	mRCChannel(1)
{
	mInputChannelInterface.reset( new AnalyzerSettingInterfaceChannel() );
	mInputChannelInterface->SetTitleAndTooltip( "Serial", "Standard ibus" );
	mInputChannelInterface->SetChannel( mInputChannel );

	mBitRateInterface.reset( new AnalyzerSettingInterfaceInteger() );
	mBitRateInterface->SetTitleAndTooltip( "Bit Rate (Bits/S)",  "Specify the bit rate in bits per second." );
	mBitRateInterface->SetMax( 6000000 );
	mBitRateInterface->SetMin( 1 );
	mBitRateInterface->SetInteger( mBitRate );

	mRCChannelInterface.reset( new AnalyzerSettingInterfaceInteger() );
	mRCChannelInterface->SetTitleAndTooltip( "RC channel (1-14)",  "Specify RC channel to decode." );
	mRCChannelInterface->SetMax( 14 );
	mRCChannelInterface->SetMin( 1 );
	mRCChannelInterface->SetInteger( mRCChannel );

	AddInterface( mInputChannelInterface.get() );
	AddInterface( mBitRateInterface.get() );
	AddInterface( mRCChannelInterface.get() );

	AddExportOption( 0, "Export as text/csv file" );
	AddExportExtension( 0, "text", "txt" );
	AddExportExtension( 0, "csv", "csv" );

	ClearChannels();
	AddChannel( mInputChannel, "Serial", false );
}

ibusAnalyzerSettings::~ibusAnalyzerSettings()
{
}

bool ibusAnalyzerSettings::SetSettingsFromInterfaces()
{
	mInputChannel = mInputChannelInterface->GetChannel();
	mBitRate = mBitRateInterface->GetInteger();
	mRCChannel = mRCChannelInterface->GetInteger();

	ClearChannels();
	AddChannel( mInputChannel, "ibus", true );

	return true;
}

void ibusAnalyzerSettings::UpdateInterfacesFromSettings()
{
	mInputChannelInterface->SetChannel( mInputChannel );
	mBitRateInterface->SetInteger( mBitRate );
	mRCChannelInterface->SetInteger( mRCChannel );
}

void ibusAnalyzerSettings::LoadSettings( const char* settings )
{
	SimpleArchive text_archive;
	text_archive.SetString( settings );

	text_archive >> mInputChannel;
	text_archive >> mBitRate;
	text_archive >> mRCChannel;

	ClearChannels();
	AddChannel( mInputChannel, "ibus", true );

	UpdateInterfacesFromSettings();
}

const char* ibusAnalyzerSettings::SaveSettings()
{
	SimpleArchive text_archive;

	text_archive << mInputChannel;
	text_archive << mBitRate;
	text_archive << mRCChannel;

	return SetReturnString( text_archive.GetString() );
}
