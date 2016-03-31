#ifndef ENVELOPE_H
#define ENVELOPE_H


class Envelope
{
public:
    enum envelopeParamIndex { attackLevel=0, decayLevel, attackRate, decayRate, releaseRate, NB_OF_ENV_PARAM_ID };
    enum envelopeState {idle=0, attack, decay, sustain, release, NB_OF_ENV_STATE};

    Envelope();
    ~Envelope();

    void reset();
    double envelopeValue();

    void startAttack();
    void releaseNote();
    int getState();

    void setAttackLevel(double level);
    void setDecayLevel(double level);

    void setAttackRate(double rate);
    void setDecayRate(double rate);
    void setReleaseRate(double rate);

    inline bool isCycleFinished() { return _finishedRelease; }

    static void setSampleRate(double sampleRate);

private:
    double multiplier(double startLevel, double endLevel, unsigned long long lengthInSamples);

private:
    envelopeState _state;

    const double _minLevel;

    double _envValue;

    double _attackLevel;
    double _decayLevel;
    double _attackMultiplier;
    double _decayMultiplier;
    double _releaseMultiplier;
    unsigned long long _attackLength;
    unsigned long long _decayLength;
    unsigned long long _releaseLength;

    static double _sampleRate;

    bool _finishedRelease;
};


#endif  // ENVELOPE_H
