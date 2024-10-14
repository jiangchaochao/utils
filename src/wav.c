//
// Created by chao.jiang on 2024/10/14.
//
#include <android/log.h>
#include "wav.h"
#define TAG "WAV"


void read_wav_info(FILE *fp, WAV *result) {
  
    ret = fread(result, 1, sizeof(WAV), fp);
    if (ret < 0){
        LOGI( "read wav info failed   ret = %d\n", ret);
        return ;
    }
    printf("read wav info sucess\n");
}

void wav_info_print(WAV wav) {
    RIFF_t riff;
    FMT_t fmt;
    Data_t data;
    riff = wav.riff;
    fmt = wav.fmt;
    data = wav.data;

    printf( "RIFF-id %c%c%c%c", riff.RIFF_id[0], riff.RIFF_id[1], riff.RIFF_id[2], riff.RIFF_id[3]);
    printf("RIFF-size %d", riff.RIFF_size);
    printf( "RIFF-type %c %c %c %c", riff.RIFF_type[0], riff.RIFF_type[1], riff.RIFF_type[2], riff.RIFF_type[3]);

    printf("FMT-id %c%c%c%c", fmt.FMT_id[0], fmt.FMT_id[1], fmt.FMT_id[2], fmt.FMT_id[3]);
    printf("FMT-size %d", fmt.FMT_size);
    printf("FMT-audio RIFF_type %d", fmt.FMT_auioFormat);
    printf("FMT-num of channels %d", fmt.FMT_numChannels);
    printf("FMT-sample rate %d", fmt.FMT_sampleRate);
    printf("FMT-byte rate %d", fmt.FMT_byteRate);
    printf("FMT-block align %d", fmt.FMT_blockAlign);
    printf("FMT-bits per sample %d", fmt.FMT_bitsPerSample);

    printf("DATA-id %c%c%c%c", data.DATA_id[0], data.DATA_id[1], data.DATA_id[2], data.DATA_id[3]);
    printf("DATA-size %d", data.DATA_size);
}

