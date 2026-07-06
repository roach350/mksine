#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define PI 3.141592653
#define DEFUALT_SAMPLE_RATE 44100

int main(int argc, char **argv){
	if (argc != 6){


		printf("mksine\n");
		printf("\tUSAGE\tmksine <file name>.wav <freq> <duration> <sample rate> <amplitude>\n");
		printf("\tfreq is in Hz, duration is in ms, sample rate is samples\n");
		return 0;
	}




	FILE *fptr;

	char filename[64];
	char freq_str[16];	
	char duration_str[16];	
	char s_rate_str[16];
	char amp_str[16];
	memset(freq_str, 0, 16);	
	memset(duration_str, 0, 16);	
	memset(s_rate_str, 0, 16);	
	memset(filename, 0, 64);
	memset(amp_str, 0, 16);	

	strncpy(filename, argv[1], 32);
	strncpy(freq_str, argv[2], 16);
	strncpy(duration_str, argv[3], 16);
	strncpy(s_rate_str, argv[4], 16);
	strncpy(amp_str, argv[5], 16);

	float amplitude; 
	uint16_t s_rate, freq, duration;

	amplitude = atof(amp_str);
	s_rate = atoi(s_rate_str);
	freq = atoi(freq_str);
	duration = atoi(duration_str);


	size_t samples = s_rate * duration; 
	printf("Allocating memory for %ds sine wave at %dhz with amplitude %f at sample rate %d for file: \"%s\"\n", duration, freq, amplitude, s_rate, filename);
	int16_t *buffer = (int16_t*)malloc(samples *sizeof(int16_t));

	//fill the buffer with samples

	for (size_t i = 0; i < samples; i++){
		int16_t sample = 32768 * amplitude * (sin(((i + 0.0)/s_rate) * (freq * 2 * PI)));
		buffer[i] = sample;

	}
	//open file and write buffer

	fptr = fopen(filename, "w");
	fwrite(buffer, sizeof(int16_t), samples, fptr);

	printf("Wrote %d samples\n", samples);
	fclose(fptr);
	free(buffer);


	return 0;
}
