#ifndef IBUS_ANALYZER_SETTINGS
#define IBUS_ANALYZER_SETTINGS

#include <AnalyzerSettings.h>
#include <AnalyzerTypes.h>

class ibusAnalyzerSettings : public AnalyzerSettings
{
public:
	ibusAnalyzerSettings();
	virtual ~ibusAnalyzerSettings();

	virtual bool SetSettingsFromInterfaces();
	void UpdateInterfacesFromSettings();
	virtual void LoadSettings( const char* settings );
	virtual const char* SaveSettings();

	
	Channel mInputChannel;
	U32 mBitRate;
	U32 mRCChannel;

protected:
	std::auto_ptr< AnalyzerSettingInterfaceChannel >	mInputChannelInterface;
	std::auto_ptr< AnalyzerSettingInterfaceInteger >	mBitRateInterface;
	std::auto_ptr< AnalyzerSettingInterfaceInteger >	mRCChannelInterface;
};

#endif //IBUS_ANALYZER_SETTINGS
