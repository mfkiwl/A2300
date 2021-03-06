/** Name: ConfigDduc.h
*
* Copyright(c) 2013 Loctronix Corporation
* http://www.loctronix.com
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*/

#ifndef CONFIGDDUC_H_
#define CONFIGDDUC_H_

#include <A2300/A2300_Defs.h>
#include <A2300/A2300InterfaceDefs.h>
#include <System/DataTypes.h>
#include <string>

namespace A2300 {

class ConfigDevice;

/**
* Configuration class for WCA sdtandard Digital Down / Up Conversion DSP logic.
*/
class ConfigDduc  : public IConfigComponent{
public:


	/**
	* DDUC operating configurations.
	*/
	enum ModeEnum{
		Default				= 0x00,
		Normal				= 0x00,
		BypassCordic		= 0x04,
		BypassCic			= 0x08,
		BypassHalfband		= 0x20,
		SynchronizeReset	= 0x40  //Synchronizes data streams with other DDUC channels
	};

public:
	ConfigDduc(byte idComponent, const std::string& sname, ConfigDevice* pDevice,
		   bool bReset = true, double uiSamplingRateHz = A2300_MAX_SAMPLING_FREQ );
	virtual ~ConfigDduc();

	/* Define IConfigComponent interface*/
	virtual std::string name();
	virtual byte componentId();

	/**
	* Resets fifos and counters and disables the channel.
	*/
	virtual void Reset();

	/**
	* Synchronizes object configuration with device configuration.  
	*/
	virtual void Synch();

	void Enable( bool bEnable);
	bool IsEnabled() const { return m_bEnable;}

	void Reset( double uiSamplingRateHz);

	/** 
	* Clears fifos and counters without disabling streams.
	*/
	void Clear();

	/**
	* Returns the Sampling rate.
	*/
	double SamplingRate() const { return m_uiSampRate;}

	/**
	* Sets thes DDUC operating mode.
	*/
	void Mode( byte modeFlags);
	byte Mode() const { return m_byteMode;}

	/** 
	* Sets the hose sampling rate which is a multiple of the
	* Default sampling rate.  Decimation / Integration sampling
	* rate conversion .  This is the rate for down/up sampling
	* sampling the 32 MHz sampling rate.  Valid range is 1 to 8192
	* equivalent to 32 MHz to 3906.25 KHz.
	*/
	double HostSamplingRate( double  dRateHz, bool bAutoSetMode = false);
	double HostSamplingRate() const { return m_uiSampRate / ((double) m_uiSamplingDivisor); }

	double FrequencyOffset( double dOffsetHz);
	double FrequencyOffset() const { return ((double) m_iPhaseRate) * m_uiSampRate / A2300_CORDIC_RES; }

private:
	byte  m_idComponent;
	std::string m_sName;
	ConfigDevice* m_pDevice;

	bool m_bEnable;
	byte m_byteMode;

	double m_uiSampRate;
	uint16 m_uiSamplingDivisor;
	int32  m_iPhaseRate;
};

} /* namespace A2300 */

#endif /* CONFIGDSP_H_ */
