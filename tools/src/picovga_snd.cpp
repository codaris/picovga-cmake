// Sound must be in format: PCM, mono, 8-bit unsigned with middle at 128, sound rate 22050 Hz

#include <stdio.h>
#include <cstdlib>
#include <stdint.h>
#include <cstring>

#pragma warning(disable : 4996) // unsafe fopen

typedef int8_t   s8;
typedef uint8_t  u8;
typedef int16_t  s16;
typedef uint16_t u16;
typedef int32_t  s32;
typedef uint32_t u32;

// WAV format
#pragma pack(push,1)

// WAV data descriptor (8 Bytes)
typedef struct WAVDATA_ {
    char            tDataIdent[4];     // "data"
    u32             nDataSize;         // size of following sound data
} WAVDATA;

// WAV format descriptor (28 Bytes)
typedef struct WAVFORMAT_ {
    char            tFormatIdent[8];   // "WAVEfmt "
    u32             nFormatSize;       // size of following format data

    u16             wFormatTag;        // 1 = PCM
    u16             nChannels;         // 1 = mono, 2 = stereo
    u32             nSamplesPerSec;    // sample rate
    u32             nAvgBytesPerSec;   // byte rate
    u16             nBlockAlign;       // block align (bits*channels/8)
    u16             wBitsPerSample;    // bits per sample
} WAVFORMAT;

// WAV file header (44 B)
typedef struct WAVHEAD_ {
    char        tWavIdent[4];          // "RIFF"
    u32         nFileSize;             // size of following file data

    WAVFORMAT   WavFormat;             // format descriptor
    WAVDATA     WavData;               // data block
} WAVHEAD;

#pragma pack( pop )

// --- Struct size checks (must match canonical RIFF/WAV layout)
static_assert(sizeof(WAVDATA)   == 8,  "WAVDATA must be 8 bytes");
static_assert(sizeof(WAVFORMAT) == 28, "WAVFORMAT must be 28 bytes");
static_assert(sizeof(WAVHEAD)   == 44, "WAVHEAD must be 44 bytes");

u8* Snd = NULL; // input file buffer

int main(int argc, char* argv[])
{
	// check syntax
	if (argc != 4)
	{
		printf("Syntax: input.wav output.cpp name\n");
		return 1;
	}

// === read input file

	// open main input file
	FILE* f = fopen(argv[1], "rb");
	if (f == NULL)
	{
		printf("Error opening %s\n", argv[1]);
		return 1;
	}

	// size of input file
	fseek(f, 0, SEEK_END);
	int size = ftell(f);
	fseek(f, 0, SEEK_SET);
	if (size < 44)
	{
		printf("Incorrect size of %s\n", argv[1]);
		return 1;
	}

	// create buffer
	Snd = (unsigned char*)malloc(size);
	if (Snd == NULL)
	{
		printf("Memory error\n");
		return 1;
	}

	// read file
	int size2 = (int)fread(Snd, 1, size, f);
	fclose(f);
	if (size2 != size)
	{
		printf("Error reading %s\n", argv[1]);
		return 1;
	}

	// check WAV header
	WAVHEAD* wav = (WAVHEAD*)Snd;
	WAVFORMAT* fmt = &wav->WavFormat;
	WAVDATA* data = &wav->WavData;

	if ((memcmp(wav->tWavIdent, "RIFF", 4) != 0) || // check "RIFF" header
		(memcmp(fmt->tFormatIdent, "WAVEfmt ", 8) != 0) || // check "WAVEfmt " header
		(memcmp(data->tDataIdent, "data", 4) != 0) || // check "data" header
		(fmt->wFormatTag != 1) || // check PCM format
		(fmt->nChannels != 1) || // check mono
		(fmt->nSamplesPerSec != 22050) || // check rate
		(fmt->wBitsPerSample != 8)) // check bits per sample
	{
		printf("Incorrect format of input file %s,\n", argv[1]);
		printf("  must be PCM mono 8-bit 22050Hz.\n");
		return 1;
	}
	u8* s = (u8*)&data[1]; // start of sound data
	int n = data->nDataSize; // number of samples

// === save output file

	// open output file
	f = fopen(argv[2], "wb");
	if (f == NULL)
	{
		printf("Error creating %s\n", argv[2]);
		return 1;
	}

	// save header
	fprintf(f, "// sound format: PCM mono 8-bit 22050Hz\n");
	fprintf(f, "const u8 %s[%d] __attribute__ ((aligned(4))) = {", argv[3], n);

	// load sound
	int i;
	for (i = 0; i < n; i++)
	{
		if ((i & 0x0f) == 0) fprintf(f, "\n\t");
		fprintf(f, "0x%02X, ", s[i]);
	}
	fprintf(f, "\n};\n");

	fclose(f);
	free(Snd);

	return 0;
}