//
// Created by chao.jiang on 2024/10/14.
//

#ifndef WAVEMAKER_WAV_H
#define WAVEMAKER_WAV_H
#include <stdio.h>
#ifdef __cplusplus
extern "C"{
#endif

typedef struct WAV_RIFF {
    char RIFF_id[4];
    uint32_t RIFF_size;
    char RIFF_type[4];
} RIFF_t;

typedef struct WAV_FMT {
    char FMT_id[4];
    uint32_t FMT_size;
    uint16_t FMT_auioFormat;
    uint16_t FMT_numChannels;
    uint32_t FMT_sampleRate;
    uint32_t FMT_byteRate;
    uint16_t FMT_blockAlign;
    uint16_t FMT_bitsPerSample;
} FMT_t;

typedef struct WAV_data {
    char DATA_id[4];
    uint32_t DATA_size;
} Data_t;


typedef struct WAV_fotmat {
    RIFF_t riff;
    FMT_t fmt;
    Data_t data;
} WAV;

/**
 * 读取wav头信息
 * @param fp   资源管理
 * @param result  读取到的结果
 */
void read_wav_info(FILE * fp, WAV *result);

/**
 * 打印函数
 * @param wav  wav结构
 */
void wav_info_print(WAV wav);

#ifdef __cplusplus
}
#endif

#endif //WAVEMAKER_WAV_H
