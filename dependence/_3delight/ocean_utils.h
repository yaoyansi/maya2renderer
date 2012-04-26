#ifndef __ocean_utils_h
#define __ocean_utils_h

#include "noise_utils.h"
#include "ramp_utils.h"

#define NUM_WAVES 16
#define SQRT_NUM_WAVES 4

#define WAVE_ACCEL(x) ( sqrt(x * 0.5 * 9.81 / PI) )

#define LENGTH(x, y) ( sqrt(x * x + y * y) )

float
getTurbulence(
	float i_octave;
	float i_u;
	float i_v;
	float i_time;
	float i_waveLength1;
	float i_waveLength2;
	output float o_slopeU;
	output float o_slopeV;)
{
	float turbulence = 0.0;
	float waveLength1 = i_waveLength1;
	float waveLength2 = i_waveLength2;
	float lengthRatio = exp(log(waveLength2 / waveLength1) / (NUM_WAVES - 1));

	if(waveLength1 < EPSILON)
		waveLength1 = EPSILON;
	if(waveLength2 < EPSILON)
		waveLength2 = EPSILON;

	uniform float i = 0;
	for(i = 1; i <= NUM_WAVES; i += 1)
	{
		point noisePoint = cellnoise(i, i_octave);

		float dirU = 2 * xcomp(noisePoint) - 1;
		float dirV = 2 * ycomp(noisePoint) - 1;
		float offset = 2 * zcomp(noisePoint) - 1;

		float dirLength = LENGTH(dirU, dirV);

		if(dirLength > EPSILON)
		{
			dirU /= dirLength;
			dirV /= dirLength;

			float speed = i_time * 0.6 * WAVE_ACCEL(waveLength1);

			float uPos = i_u * 2 * PI + dirU * speed;
			float vPos = i_v * 2 * PI + dirV * speed;

			float wavePos = PI * ((uPos * dirU + vPos * dirV) / 
				(3 * waveLength1) + offset);

			turbulence += waveLength1 * cos(wavePos);

			float s = -PI * sin(wavePos) / waveLength1;

			o_slopeU += dirU * s;
			o_slopeV += dirV * s;
		}

		waveLength1 *= lengthRatio;
	}

	turbulence /= SQRT_NUM_WAVES;
	o_slopeU /= SQRT_NUM_WAVES;
	o_slopeV /= SQRT_NUM_WAVES;

	return turbulence;
}

void
getFoam(
	float i_foamScale;
	float i_foamValue;
	float i_scale;
	float i_amplitude;
	float i_waveLength;
	float i_turbulence;
	float i_foamEmission;
	float i_foamThreshold;
	float i_ss, i_tt;
	float i_ssOffset, i_ttOffset;
	float i_wave_speed;
	float i_waveDirSpread;
	output float io_foam;)
{
	float foamValue = 2 * i_foamScale *
		(i_scale * i_amplitude * i_foamValue / i_waveLength + 0.25);

	float peakFoamValue = 2 * i_foamScale * 
		(i_scale * i_amplitude * i_turbulence / i_waveLength + 0.25);

	float foamRange = i_scale * 0.2 / i_foamEmission;
	float foamThreshold = 1 - i_foamThreshold;

	if(foamValue > foamThreshold)
	{
		if(foamValue <= foamThreshold + foamRange)
		{
			io_foam += 8 / i_scale  * (foamValue - foamThreshold) / foamRange;
		}
		else
		{
			io_foam += 8 / i_scale;
		}
	}

	foamThreshold += 0.05;

	if(peakFoamValue > foamThreshold) 
	{
		foamRange = i_scale * 0.1 / i_foamEmission;

		if(peakFoamValue <= foamThreshold + foamRange)
		{
			io_foam += 2 / i_scale * (peakFoamValue - foamThreshold) / foamRange;
		}
		else
		{
			io_foam += 2 / i_scale;
		}
	}

	if(io_foam > 0)
	{
		// Add some noise to the foam
		float sPos = i_ss + i_ssOffset * i_waveDirSpread;
		float tPos = i_tt + i_ttOffset * i_waveDirSpread;
		float freq = 1.5 / (i_waveLength);

		point noisePoint = point(freq * sPos, freq * tPos, freq * i_wave_speed);
		io_foam -= 0.8 * abs(2 * noise(noisePoint) - 1);

		io_foam = max(0, io_foam);
	}
}

void
getWavePeaking(
	float i_octave;
	float i_wavePeakingFactor;
	output float io_ss, io_tt;
	float i_sPos, i_tPos;
	float i_slopeS, i_slopeT;
	float i_time;
	float i_waveLength;
	float i_waveLengthMax;
	float i_foamEmission;
	float i_foamTimeOffset;
	output float o_foamValue;
	output float io_turbulence;)
{
	// Higher wavePeakingFactor produces pinched wave tops, while lower values 
	// retains the "original", wider wave tops.
	float slopeS = i_slopeS * 0.1 * i_waveLength;
	float slopeT = i_slopeT * 0.1 * i_waveLength;

	float pinchLength = LENGTH(slopeS, slopeT);
	float pinchFactor = (io_turbulence / i_waveLength + 2.0) / 4.0;
	float dummy1, dummy2;

	if(pinchLength > 0 && pinchFactor > 0)
	{
		pinchFactor = 0.15 * pinchFactor * i_wavePeakingFactor * i_waveLength /
			sqrt(pinchLength);

		float newS = i_sPos - slopeS * pinchFactor;
		float newT = i_tPos - slopeT * pinchFactor;
		
		io_turbulence = getTurbulence(
			i_octave, newS, newT, i_time, i_waveLength,
			i_waveLengthMax, dummy1, dummy2);
			
		if(i_foamEmission > EPSILON)
		{
			o_foamValue = getTurbulence(
				i_octave, newS, newT, i_time - i_foamTimeOffset, 
				i_waveLength, i_waveLengthMax, dummy1, dummy2);
		}
		
		io_ss -= slopeS * pinchFactor * 0.8;
		io_tt -= slopeT * pinchFactor * 0.8;
	}
	else if(i_foamEmission > EPSILON)
	{
		o_foamValue = getTurbulence(
			i_octave, i_sPos, i_tPos, i_time - i_foamTimeOffset,
			i_waveLength, i_waveLengthMax, dummy1, dummy2);
	}
}

void
getOcean(
	float i_ss, i_tt;
	float i_time;
	float i_scale;
	float i_windUV[2];
	float i_observerSpeed;
	float i_waveDirSpread;
	float i_numFrequencies;
	float i_waveLengthMin;
	float i_waveLengthMax;
	float i_waveHeightPositions[];
	float i_waveHeightFloatValues[];
	uniform float i_waveHeightInterps[];
	float i_waveTurbulencePositions[];
	float i_waveTurbulenceFloatValues[];
	uniform float i_waveTurbulenceInterps[];
	float i_wavePeakingPositions[];
	float i_wavePeakingFloatValues[];
	uniform float i_wavePeakingInterps[];
	float i_foamEmission;
	float i_foamThreshold;
	output float o_ocean;
	output float o_foam;)
{
	o_ocean = 0;
	o_foam = 0;

	float waveLengthMin = max( i_waveLengthMin, EPSILON );
	float numFrequencies = i_numFrequencies;
	numFrequencies -= EPSILON;

	float lengthRatio =
		exp(log(waveLengthMin / i_waveLengthMax) / numFrequencies);

	float ss = i_ss * i_scale;
	float tt = i_tt * i_scale;

	float waveDirSpread = 0;
	if (i_waveDirSpread <= 1.0)
	{
		waveDirSpread = 0.5 * (1 - i_waveDirSpread);
	}
 
	float waveLengthDiff = i_waveLengthMax - waveLengthMin;
	float curWaveLength = i_waveLengthMax;
	float lastIter = floor(numFrequencies + 1) - 1;
	float foamScale = 1.0;

	float i;
	for(i = 0; i <= lastIter; i+=1)
	{
		// Figure the index of the ramps
		float rampIndex = 0;

		if(waveLengthDiff >= EPSILON)
		{
			rampIndex = (curWaveLength - waveLengthMin) / waveLengthDiff;
		}
		else if(lastIter > 0)
		{
			rampIndex = i / lastIter;
		}

		// Compute the amplitude
		float amplitude = floatRamp(
			rampIndex,
			i_waveHeightPositions, 
			i_waveHeightInterps,
			i_waveHeightFloatValues);

		float amplitude_no_adj = amplitude;

		amplitude *= i_scale / (8 + 4 * i);

		if(i == lastIter)
		{
			amplitude *= i_numFrequencies - lastIter;
		}

		// Compute the main waves, shorter wavelengths traveling slower than
		// longer ones
		float wave_accel = WAVE_ACCEL(curWaveLength);    
		float wave_speed = wave_accel * i_time / pow(4, 2 * (i + 1));

		float initialS = ss;
		float initialT = tt;

		float ssOffset = 0.0;
		float ttOffset = 0.0;

		float ssDir = i_windUV[0];
		float ttDir = i_windUV[1];

		if(i == 0.0)
		{
			// Only the main wave is affected by the observer speed
			float dirDist = LENGTH(ssDir, ttDir);

			if(dirDist > EPSILON)
			{
				ssDir /= dirDist;
				ttDir /= dirDist;

				ssOffset = ssDir * wave_speed;
				ttOffset = ttDir * wave_speed;

				ss -= ssOffset * i_observerSpeed;
				tt -= ttOffset * i_observerSpeed;
			}
		}
		else
		{
			// This is somewhat close to what Maya does as long as i_waveDirSpread is
			// between 0 and 1; it needs some more work when windUV < 0 and
			// waveDirSpread << 1.
			// The following values approximate what Maya does. Passed the 15th
			// frequency we just pick random orientations.
			float spreadS;
			float spreadT;

			if (i < 2)
			{
				spreadS = 0.56;
				spreadT = 0.74;
			}
			else if(i < 4)
			{
				spreadS = 0.56;
				spreadT = 0.89;
			}
			else if(i < 5)
			{
				spreadS = 0.85;
				spreadT = 0.1;
			}
			else if(i < 7)
			{
				spreadS = 0.0;
				spreadT = 0.4;
			}
			else if(i < 9)
			{
				spreadS = 1.0;
				spreadT = 0.4;
			}
			else if(i < 16)
			{
				spreadS = 0;
				spreadT = 0.6;
			}
			else
			{
				spreadS = noise(i);
				spreadT = noise(-i);
			}

			ssDir = i_waveDirSpread * spreadS + (1 - i_waveDirSpread) * i_windUV[0];
			ttDir = i_waveDirSpread * spreadT + (1 - i_waveDirSpread) * i_windUV[1];

			float dirDist = sqrt(ssDir * ssDir + ttDir * ttDir);

			if(dirDist > EPSILON)
			{
				ssDir /= dirDist;
				ttDir /= dirDist;

				ssOffset = ssDir * wave_speed;
				ttOffset = ttDir * wave_speed;
			}
		}

		// the foam travels slower then the waves
		float foamTimeOffset = 0.1 * wave_accel;  
		float foamValue = 0.0;

		// Compute turbulence
		float waveTurbulenceFactor = floatRamp(
			rampIndex,
			i_waveTurbulencePositions,
			i_waveTurbulenceInterps,
			i_waveTurbulenceFloatValues);

		float turbulence = 0.0;
		if(waveTurbulenceFactor > 0)
		{
			float sPos = initialS + ssOffset * waveDirSpread;
			float tPos = initialT + ttOffset * waveDirSpread;
			float waveLength2 = 0.8 * curWaveLength;
			float slopeS = 0;
			float slopeT = 0;

			turbulence = getTurbulence(
				i, sPos, tPos, i_time, curWaveLength,
				waveLength2, slopeS, slopeT);

			float dummy1, dummy2;

			// Compute wave peaking, which can modify turbulence and foam
			float wavePeakingFactor = floatRamp(
				rampIndex,
				i_wavePeakingPositions, 
				i_wavePeakingInterps,
				i_wavePeakingFloatValues);

			if(wavePeakingFactor > 0)
			{
				getWavePeaking(
					i, wavePeakingFactor, ss, tt, sPos, tPos, slopeS, slopeT,
					i_time, curWaveLength, waveLength2, i_foamEmission, foamTimeOffset,
					foamValue, turbulence);
			}
			else if(i_foamEmission > EPSILON)
			{
				foamValue = getTurbulence(
					i, sPos, tPos, i_time - foamTimeOffset,
					curWaveLength, waveLength2, dummy1, dummy2);
			}

			turbulence *= waveTurbulenceFactor;
			foamValue *= waveTurbulenceFactor;
		}

		if(waveTurbulenceFactor < 1.0)
		{
			float sPos = initialS + ssOffset;
			float tPos = initialT + ttOffset;

			float value = cos(2.0 * PI * (sPos * ssDir + tPos * ttDir) / curWaveLength);

			turbulence += value * curWaveLength * (1 - waveTurbulenceFactor);

			if(i_foamEmission > EPSILON)
			{
				sPos -= ssDir * foamTimeOffset;
				tPos -= ttDir * foamTimeOffset;

				foamValue += amplitude * curWaveLength * (1 - waveTurbulenceFactor) * 
					cos(2 * PI * (sPos * ssDir + tPos * ttDir) / curWaveLength);          
			}
		}

		o_ocean += amplitude * turbulence;

		if(i_foamEmission > EPSILON)
		{
			getFoam(
				foamScale, foamValue, i_scale, amplitude, curWaveLength, 
				turbulence,	i_foamEmission, i_foamThreshold, ss, tt, ssOffset, ttOffset,
				wave_speed,	waveDirSpread, o_foam);

			foamScale *= 0.9;
		}

		curWaveLength *= lengthRatio;
	}
}

#endif /* __ocean_utils_h */

