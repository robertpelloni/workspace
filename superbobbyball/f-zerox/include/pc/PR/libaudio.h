#ifndef _LIBAUDIO_H_
#define _LIBAUDIO_H_

#include <PR/ultratypes.h>

// Basic types for libaudio stubs
typedef struct {
    int unk;
} ALSynth;

typedef struct {
    int unk;
} ALPlayer;

typedef struct {
    int unk;
} ALVoice;

typedef struct {
    int unk;
} ALInstrument;

typedef struct {
    int unk;
} ALBank;

typedef struct {
    int unk;
} ALSeqpConfig;

typedef struct {
    int unk;
} ALSeqPlayer;

typedef struct {
    int unk;
} ALSeq;

// Function Prototypes used in game code
void n_alSynRemovePlayer(ALSynth *s, ALPlayer *p);
void n_alSynFreeFX(ALSynth *s, void *fx); // fx type unknown
void n_alSeqpDelete(ALSeqPlayer *seqp);

#endif
