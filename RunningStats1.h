/*
 * cumulative/running statistical computations, work in progress
 * A work in progress.

Copyright © 2020-2021 David L. Hoke

Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
and associated documentation files (the “Software”), to deal in the Software without 
restriction, including without limitation the rights to use, copy, modify, merge, publish, 
distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the 
Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or 
substantial portions of the Software.

THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING 
BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND 
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, 
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING 
FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE. 

 * 
 * 
 *
 * references:
 * https://stackoverflow.com/questions/17052395/calculate-the-running-standard-deviation/
 * ...https://stackoverflow.com/a/17053010 (answer in previous thread)
 * https://stackoverflow.com/questions/1174984/how-to-efficiently-calculate-a-running-standard-deviation/20832236#20832236
 * https://stackoverflow.com/questions/1174984/how-to-efficiently-calculate-a-running-standard-deviation
 * https://subluminal.wordpress.com/2008/07/31/running-standard-deviations/#more-15
 * https://subluminal.wordpress.com/2008/07/31/running-standard-deviations/#more-15
 */


#include <cmath>
#include <limits>
#include <stdint.h>

class libBFRunningStats;
class ArbitraireRunningStats;
class MAPMRunningStats;
class GMPRunningStats;
class MPFRRunningStats;

class RunningStats1
{
	friend class libBFRunningStats;
	friend class ArbitraireRunningStats;
	friend class MAPMRunningStats;
	friend class GMPRunningStats;
	friend class MPFRRunningStats;
	
public:
	RunningStats1()
		: m_n(0.0)
	    , m_mean(0.0)
		, m_SumMeanSqrd(0.0)
		, m_minval(std::numeric_limits<double>::max())
		, m_maxval(std::numeric_limits<double>::min())
	{
	}
	
	void reset()
	{
		m_n = 0.0;
		m_mean = 0.0;
		m_SumMeanSqrd = 0.0;
	    m_minval = std::numeric_limits<double>::max();
		m_maxval = std::numeric_limits<double>::min();
	}
	
	void update(double newval)
	{
		//https://stackoverflow.com/questions/1848700/biggest-integer-that-can-be-stored-in-a-double
		//https://stackoverflow.com/a/1848953
		if(m_n >= 9007199254740992.0)
			//maxed out last time. 
			//TBD: How to handle? 
			//maybe 'rollup' to something supporting larger stores and reset?
			//GMP?
			//Arbitraire, MAPM, LibBF?
			;

		++m_n;

		if(newval > m_maxval) m_maxval = newval;
		if(newval < m_minval) m_minval = newval;

		while(1)
		{
			double deltafromoldmean = newval - m_mean;
			auto newmean = m_mean + deltafromoldmean / (m_n);
			if(newmean != newmean) //TBD: nan'd?
				//rollup into accumulator
				//'reset' current as necessary to start new subset
				//continue, restarting to compute that next subset with most recent incoming value
				;
			m_mean = newmean;
			//note: both/either cum sum and n will eventually max/nan when input has 'too large' values or 'too long' series of values
			auto deltafromnewmean = newval - m_mean;
			auto newSumMeanSqrd = m_SumMeanSqrd + deltafromoldmean * (deltafromnewmean); //note: 'mean' value here diff from that used to calculate 'delta' above
			if(newSumMeanSqrd != newSumMeanSqrd) //TBD: nan'd?
				//rollup into accumulator
				//'reset' current as necessary to start new subset
				//continue, restarting to compute that next subset with most recent incoming value
				;
			m_SumMeanSqrd = newSumMeanSqrd;
		    break;
		}
	}
	
	double varianceSample()
	{
		if(m_n <= 1) return 0.0; //TBD: std::nan(NULL) better?
		return m_SumMeanSqrd / (m_n-1);
	}

	double variancePopulation()
	{
		if(m_n <= 1) return 0.0;  //TBD: std::nan(NULL) better?
		else return m_SumMeanSqrd / (m_n);
	}
	
	double stddevSample()
	{
		
		if(m_n < 1) return std::nan(NULL);
		else if(m_n < 2) return 0.0;
		return sqrt(varianceSample());
	}

	double stddevPopulation()
	{
		
		if(m_n < 1) return std::nan(NULL);
		else if(m_n < 2) return 0.0;
		return sqrt(variancePopulation());
	}

	double mean()
	{
		return m_mean;
	}
	
private:
	double m_minval, m_maxval;
	double m_mean;
	long double m_SumMeanSqrd;
	double m_n;
};//RunningStats1

class libBFRunningStats
{
public:
	libBFRunningStats()
	{
	}
private:
};

class ArbitraireRunningStats
{
public:
	ArbitraireRunningStats()
	{
	}
private:
};

class MAPMRunningStats
{
public:
	MAPMRunningStats()
	{
	}
private:
};

class GMPRunningStats
{
public:
	GMPRunningStats()
	{
	}
private:
#if 0
	mpf_t minval, maxval;
	mpf_t mean;
	mpf_t SumMeanSqrd;
	mpf_t n;
#endif
};

class MPFRRunningStats
{
	const int fltbits = 200;
public:
#if 0
	MPFRRunningStats()
	{

		mpfr_init2(minval,      fltbits);
		mpfr_init2(maxval,      fltbits);
		mpfr_init2(mean,        fltbits);
		mpfr_init2(SumMeanSqrd, fltbits);
		mpfr_init2(n, fltbits);

		mpfr_set_d(n, 0.0, MPFR_RNDD);
	    mpfr_set_d(mean, 0.0, MPFR_RNDD);
		mpfr_set_d(SumMeanSqrd, 0.0, MPFR_RNDD);
		, minval(std::numeric_limits<double>::max())
		, maxval(std::numeric_limits<double>::min())
	}
#endif
	
private:
#if 0
	mpf_t minval, maxval;
	mpf_t mean;
	mpf_t SumMeanSqrd;
	mpf_t n;
#endif
};
