/** 
 * @file 
 * @brief PWM sound output
 * @author Miroslav Nemecek <Panda38@seznam.cz>
 * @see PWMGroup
*/

#ifndef _PWMSND_H
#define _PWMSND_H

#define PWMSND_GPIO	19	// PWM output GPIO pin (0..29)
#define PWMSND_SLICE	((PWMSND_GPIO>>1)&7) // PWM slice index (=1)
#define PWMSND_CHAN	(PWMSND_GPIO&1) // PWM channel index (=1)

#define SOUNDRATE	22050	// sound rate [Hz]
#define PWMSND_TOP	255	// PRM top (period = PWMSND_TOP + 1 = 256)
#define PWMSND_CLOCK	(SOUNDRATE*(PWMSND_TOP+1)) // PWM clock (= 22050*256 = 5644800)

#define SNDFRAC	10	// number of fraction bits
#define SNDINT (1<<SNDFRAC) // integer part of sound fraction

// current sound
extern const u8* CurSound;	// current playing sound
extern volatile int SoundCnt;	// counter of current playing sound (<=0 no sound)
extern int SoundInc;		// pointer increment
extern volatile int SoundAcc;	// pointer accumulator
extern const u8* NextSound;	// next sound to play repeated sound
extern int NextSoundCnt;	// counter of next sound (0=no repeated sound)

/**
 * @addtogroup PWMGroup
 * @details The PicoVGA library includes support for audio output using PWM modulation. By default, the audio output is done 
 * on the GPIO19 port - defined in the pwmsnd.h file. The port can be connected to directly (e.g. headphones) or better via 
 * a simple RC filter with low pass. Audio output using PWM modulation has the advantage that 1 output pin is sufficient and 
 * the output circuitry is very simple. The disadvantages are the noise of the sound modulation frequency and the low bit 
 * depth of the sound (8 bit depth is used). Higher depth is not possible because of the limited processor frequency. This 
 * output is sufficient for most common, undemanding applications (such as retro games). For higher sound quality, another 
 * method must be used.
 * * Sounds are at format 8-bit unsigned (middle at 128), 22050 samples per second, mono
 * * PWM cycle is 256: TOP = 255
 * * Required PWM clock: 22050*256 = 5644800 Hz
 * * GP19 ... MOSI + sound output (PWM1 B)
 * @{
*/

/**
 * @brief Initialize PWM sound output
 * @note If the system clock changes, you must reinitialize the audio output settings by calling this function again.
*/
void PWMSndInit();

/**
 * @brief Output PWM sound 
 * @details The audio must be in uncompressed PCM format, mono, 8 bits, frequency 22050 Hz. The parameters can be used to 
 * specify whether the sound will be repeated and the relative speed at which it will be played (the 'speed' parameter can 
 * be used to speed up or slow down the sound).
 * @param snd Pointer to sound
 * @param len Length of sound in number of samples
 * @param rep True to repeat sample
 * @param speed Relative speed (1=normal)
*/
void PlaySound(const u8* snd, int len, Bool rep = False, float speed = 1.0f);

/**
 * @brief stop playing sound
 * @details  The output to the output pin will continue to be output (it will appear as a low noise), but the value of 
 * zero 128 will be used.
*/
void StopSound();

// update sound speed (1=normal speed)
/**
 * @brief Update sound speed
 * @details Used when repeatedly playing a sound to change the pitch (e.g. the sound of a car engine). 
 * @param speed Relative speed (1.0 represents the standard playback speed)
*/
void SpeedSound(float speed);
 
/**
 * @brief Check if playing sound
*/
Bool PlayingSound();

/**
 * @brief Set the next sound to play. 
 * @details Used for repeated sounds to finish playing the current sound and continue with the next sound.
 * @param snd Pointer to sound
 * @param len Length of sound in number of samples
*/
void SetNextSound(const u8* snd, int len);

/// @}

#endif // _PWMSND_H
